// Made by an Indian kid who loves tech and Spotify :P

#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Arduino.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <Wire.h>
#include <Adafruit_PN532.h>
#include <MPU6050.h>

#define SDA_PIN 21
#define SCL_PIN 22
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
MPU6050 mpu;

boolean playing;
String lastArtist;
String lastTrackname;
int progressCheck = 0;
String lastMochiState = "";

char* SSID = "Your_SSID";
const char* PASSWORD = "Your_PASSWORD";
const char* CLIENT_ID = "Your_CLIENT_ID";
const char* CLIENT_SECRET = "Your_CLIENT_SECRET";
const char* REFRESH_TOKEN = "Your_REFRESH_TOKEN";

#define leftButton 10
#define middleButton 8
#define rightButton 6

#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 3
#define TFT_SCLK 2
#define TFT_MOSI 1

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Spotify sp(CLIENT_ID, CLIENT_SECRET);

void mochiDance() {
  tft.fillRect(0, 40, 160, 20, ST77XX_BLACK);
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.print("🎉 Dancing Mochi!");
}

void mochiChill() {
  tft.fillRect(0, 40, 160, 20, ST77XX_BLACK);
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(1);
  tft.print("😴 Chill Mochi");
}

void mochiHeadbang() {
  tft.fillRect(0, 40, 160, 20, ST77XX_BLACK);
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.print("🤘 Headbang Mode");
}

void mochiDefault() {
  tft.fillRect(0, 40, 160, 20, ST77XX_BLACK);
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("🐾 Hello Mochi");
}

void updateMochiAnimation(String title) {
  title.toLowerCase();
  String newState;

  if (title.indexOf("lofi") != -1 || title.indexOf("chill") != -1 || title.indexOf("ambient") != -1) {
    newState = "chill";
  } else if (title.indexOf("rock") != -1 || title.indexOf("metal") != -1 || title.indexOf("rage") != -1) {
    newState = "headbang";
  } else if (title.indexOf("party") != -1 || title.indexOf("dance") != -1 || title.indexOf("pop") != -1) {
    newState = "dance";
  } else {
    newState = "default";
  }

  if (newState != lastMochiState) {
    lastMochiState = newState;
    if (newState == "chill") mochiChill();
    else if (newState == "headbang") mochiHeadbang();
    else if (newState == "dance") mochiDance();
    else mochiDefault();
  }
}

void detectShake() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  float magnitude = sqrt(ax * ax + ay * ay + az * az) / 16384.0;
  if (magnitude > 2.5) {
    Serial.println("Shake detected! Resetting Mochi.");
    mochiDefault();
    delay(1000);
  }
}

void connectToWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void checkInput() {
  if (digitalRead(middleButton) == LOW) {
    playing = !playing;
    updatePlayPauseIcon();
    if (playing) sp.start_resume_playback();
    else sp.pause_playback();
  }

  if (digitalRead(leftButton) == LOW) {
    sp.previous();
  }
  if (digitalRead(rightButton) == LOW) {
    sp.skip();
  }
}

void updatePlayPauseIcon() {
  tft.fillRect(70, 100, 20, 20, ST77XX_BLACK);
  if (playing)
    tft.drawBitmap(70, 100, playIcon, 20, 20, ST77XX_WHITE);
  else
    tft.drawBitmap(70, 100, pauseIcon, 20, 20, ST77XX_WHITE);
}

void displayTrackInfo() {
  String artist = sp.current_artist_names();
  String track = sp.current_track_name();

  if (artist != lastArtist || track != lastTrackname) {
    lastArtist = artist;
    lastTrackname = track;

    tft.fillRect(0, 0, 160, 40, ST77XX_BLACK);
    tft.setCursor(5, 5);
    tft.setTextSize(2);
    tft.print(track);

    tft.setCursor(5, 25);
    tft.setTextSize(1);
    tft.print(artist);

    updateMochiAnimation(track);
  }
}

void drawProgressBar() {
  StaticJsonDocument<200> filter;
  filter["item"]["duration_ms"] = true;
  filter["progress_ms"] = true;
  response r = sp.current_playback_state(filter);

  int progress = r.reply["progress_ms"];
  int duration = r.reply["item"]["duration_ms"];

  float percent = (float)progress / duration;
  tft.fillRect(0, 124, 160, 4, ST77XX_BLACK);
  tft.fillRect(0, 124, 160 * percent, 4, ST77XX_GREEN);
}

void checkNFC() {
  uint8_t uid[] = { 0 }; uint8_t uidLength;
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    String uidStr = "";
    for (uint8_t i = 0; i < uidLength; i++) {
      uidStr += String(uid[i], HEX);
    }

    Serial.print("NFC UID: "); Serial.println(uidStr);

    if (uidStr == "aabbccdd") {
      sp.skip();
    } else if (uidStr == "11223344") {
      sp.previous();
    } else if (uidStr == "deadbeef") {
      playing = !playing;
      updatePlayPauseIcon();
      if (playing) sp.start_resume_playback();
      else sp.pause_playback();
    }

    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(middleButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);

  connectToWiFi();

  tft.setCursor(20, 30); tft.print("SSID: "); tft.print(SSID);
  tft.setCursor(20, 50); tft.print("IP: "); tft.print(WiFi.localIP());

  sp.begin();
  while (!sp.is_auth()) sp.handle_client();

  playing = sp.is_playing();

  nfc.begin();
  if (!nfc.getFirmwareVersion()) {
    Serial.println("NFC module not found, check wires!");
    while (1);
  }
  nfc.SAMConfig();
  Serial.println("NFC Ready for scanning");

  mpu.initialize();
  if (!mpu.testConnection()) Serial.println("MPU6050 failed!");

  mochiDefault();
}

void loop() {
  checkInput();
  checkNFC();
  displayTrackInfo();
  detectShake();

  if (progressCheck++ > 2) {
    drawProgressBar();
    progressCheck = 0;
  }
}
