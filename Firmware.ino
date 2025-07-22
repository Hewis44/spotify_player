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

// NFC I2C pins (default for ESP32)
#define SDA_PIN 21
#define SCL_PIN 22
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);  // This is the NFC module

// Display + Spotify vars
boolean playing;
String lastArtist;
String lastTrackname;
int progressCheck = 0;

// CHANGE ALL THESE TO CONTAIN YOUR INFO! 
char* SSID = "";
const char* PASSWORD = "";
const char* CLIENT_ID = "";
const char* CLIENT_SECRET = "";
const char* REFRESH_TOKEN = "";

// CHANGE BUTTON PINS HERE
#define leftButton 10
#define middleButton 8
#define rightButton 6

// CHANGE SCREEN PINS HERE
#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 3
#define TFT_SCLK 2
#define TFT_MOSI 1

const unsigned char spotifyLogo[] PROGMEM = {
  0x00, 0x07, 0x80, 0x00,
  0x00, 0x3f, 0xf0, 0x00,
  0x00, 0xff, 0xfc, 0x00,
  0x03, 0xff, 0xff, 0x00,
  0x07, 0xff, 0xff, 0x80,
  0x0f, 0xff, 0xff, 0xc0,
  0x1f, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xe0,
  0x3f, 0x80, 0x7f, 0xf0,
  0x38, 0x00, 0x03, 0xf0,
  0x78, 0x00, 0x00, 0xf8,
  0x78, 0xff, 0xc0, 0x78,
  0x7f, 0xff, 0xf8, 0x38,
  0xff, 0x80, 0x7f, 0x7c,
  0xfc, 0x00, 0x0f, 0xfc,
  0xfc, 0x00, 0x03, 0xfc,
  0xff, 0xff, 0xe0, 0xfc,
  0x7f, 0xff, 0xf8, 0xf8,
  0x7e, 0x00, 0x3f, 0xf8,
  0x7e, 0x00, 0x0f, 0xf8,
  0x3f, 0xff, 0x83, 0xf0,
  0x3f, 0xff, 0xf3, 0xf0,
  0x1f, 0xff, 0xff, 0xe0,
  0x1f, 0xff, 0xff, 0xe0,
  0x0f, 0xff, 0xff, 0xc0,
  0x07, 0xff, 0xff, 0x80,
  0x03, 0xff, 0xff, 0x00,
  0x00, 0xff, 0xfc, 0x00,
  0x00, 0x3f, 0xf0, 0x00,
  0x00, 0x07, 0x80, 0x00
};

const unsigned char playIcon[] PROGMEM = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0xf0, 0x00,
  0x03, 0xfc, 0x00,
  0x07, 0xff, 0x00,
  0x0f, 0xff, 0x00,
  0x1f, 0xff, 0x80,
  0x1e, 0x67, 0x80,
  0x3e, 0x67, 0xc0,
  0x3e, 0x67, 0xc0,
  0x3e, 0x67, 0xc0,
  0x3e, 0x67, 0xc0,
  0x1e, 0x67, 0x80,
  0x1f, 0xff, 0x80,
  0x0f, 0xff, 0x00,
  0x07, 0xfe, 0x00,
  0x03, 0xfc, 0x00,
  0x00, 0xf0, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00
};

const unsigned char pauseIcon[] PROGMEM = {
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0xf0, 0x00,
  0x03, 0xfc, 0x00,
  0x07, 0xff, 0x00,
  0x0f, 0xff, 0x00,
  0x1f, 0xff, 0x80,
  0x1f, 0x3f, 0x80,
  0x3e, 0x0f, 0xc0,
  0x3e, 0x07, 0xc0,
  0x3e, 0x07, 0xc0,
  0x3e, 0x0f, 0xc0,
  0x1f, 0x3f, 0x80,
  0x1f, 0xff, 0x80,
  0x0f, 0xff, 0x00,
  0x07, 0xfe, 0x00,
  0x03, 0xfc, 0x00,
  0x00, 0xf0, 0x00,
  0x00, 0x00, 0x00,
  0x00, 0x00, 0x00
};

const unsigned char prev[] PROGMEM = {
  0x00, 0xf0, 0x00,
  0x03, 0xfc, 0x00,
  0x0c, 0x03, 0x00,
  0x18, 0x01, 0x80,
  0x30, 0x00, 0xc0,
  0x20, 0x00, 0x40,
  0x40, 0x00, 0x20,
  0x42, 0x04, 0x20,
  0xc2, 0x1c, 0x30,
  0xc2, 0x64, 0x30,
  0xc2, 0x64, 0x30,
  0xc2, 0x1c, 0x30,
  0x42, 0x04, 0x20,
  0x40, 0x00, 0x20,
  0x20, 0x00, 0x40,
  0x30, 0x00, 0xc0,
  0x18, 0x01, 0x80,
  0x0c, 0x03, 0x00,
  0x03, 0xfc, 0x00,
  0x00, 0xf0, 0x00
};

const unsigned char next[] PROGMEM = {
  0x00, 0xf0, 0x00,
  0x03, 0xfc, 0x00,
  0x0c, 0x03, 0x00,
  0x18, 0x01, 0x80,
  0x30, 0x00, 0xc0,
  0x20, 0x00, 0x40,
  0x40, 0x00, 0x20,
  0x42, 0x04, 0x20,
  0xc3, 0x84, 0x30,
  0xc2, 0x64, 0x30,
  0xc2, 0x64, 0x30,
  0xc3, 0x84, 0x30,
  0x42, 0x04, 0x20,
  0x40, 0x00, 0x20,
  0x20, 0x00, 0x40,
  0x30, 0x00, 0xc0,
  0x18, 0x01, 0x80,
  0x0c, 0x03, 0x00,
  0x03, 0xfc, 0x00,
  0x00, 0xf0, 0x00
};


boolean playing;
String lastArtist;
String lastTrackname;
int progressCheck = 0;

// Your WiFi + Spotify details, put correct ones or it'll not work :)
char* SSID = "Your_SSID";
const char* PASSWORD = "Your_PASSWORD";
const char* CLIENT_ID = "Your_CLIENT_ID";
const char* CLIENT_SECRET = "Your_CLIENT_SECRET";
const char* REFRESH_TOKEN = "Your_REFRESH_TOKEN";

// Button pins for prev, play/pause, next
#define leftButton 10
#define middleButton 8
#define rightButton 6

// TFT display SPI pins
#define TFT_CS 5
#define TFT_RST 4
#define TFT_DC 3
#define TFT_SCLK 2
#define TFT_MOSI 1

// TFT object banaliya bhai
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Spotify sp(CLIENT_ID, CLIENT_SECRET);

// Bitmaps (keep your icons like spotifyLogo, playIcon etc. here, skipped for now)
// Add all icons you already have here...

void setup() {
  Serial.begin(115200);

  // Buttons
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(middleButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);

  // TFT screen init
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);

  // WiFi connect
  connectToWiFi();

  // Show some info
  tft.setCursor(20, 30); tft.print("SSID: "); tft.print(SSID);
  tft.setCursor(20, 50); tft.print("IP: "); tft.print(WiFi.localIP());

  // Spotify auth bro
  sp.begin();
  while (!sp.is_auth()) {
    sp.handle_client();
  }

  playing = sp.is_playing();

  // Setup NFC
  nfc.begin();
  if (!nfc.getFirmwareVersion()) {
    Serial.println("NFC module not found, check wires!");
    while (1);
  }
  nfc.SAMConfig();
  Serial.println("NFC Ready for scanning");

  // Display icons
  tft.fillScreen(ST77XX_BLACK);
  updatePlayPauseIcon();
  tft.drawBitmap(25, 100, prev, 20, 20, ST77XX_WHITE);
  tft.drawBitmap(115, 100, next, 20, 20, ST77XX_WHITE);
}

void loop() {
  checkInput();
  checkNFC();
  displayTrackInfo();
  if (progressCheck++ > 2) {
    drawProgressBar();
    progressCheck = 0;
  }
}

// Function to connect to WiFi
void connectToWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// Check button press and do action
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

// Draw Play/Pause icon
void updatePlayPauseIcon() {
  tft.fillRect(70, 100, 20, 20, ST77XX_BLACK);
  if (playing)
    tft.drawBitmap(70, 100, playIcon, 20, 20, ST77XX_WHITE);
  else
    tft.drawBitmap(70, 100, pauseIcon, 20, 20, ST77XX_WHITE);
}

// Show currently playing song and artist
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
  }
}

// Progress bar for song time
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

// Check NFC card and trigger command
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

    delay(1000); // debounce karo
  }
}
