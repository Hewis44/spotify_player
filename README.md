# spotify_player


This is a DIY Spotify Controller built using an ESP32 microcontroller, inspired by the discontinued Spotify Car Thing. The idea came from wanting a simple and elegant way to control music without needing to touch my phone. Since buying the original Car Thing is now super expensive, I decided to make my own version using the components I had and some custom PCB design.



![image](https://github.com/user-attachments/assets/87afe39f-2cc8-41ec-a4d9-e944e3d86e87)




The device uses a 2.4-inch TFT display to show real-time song information like title, artist, and playback progress. It also includes word wrapping, so even long track names are displayed neatly without getting cut off. I’ve added three mechanical switches to handle play/pause, next, and previous track actions, all of which are sent directly to the Spotify Web API over Wi-Fi. To add a fun and futuristic twist, the project includes an NFC reader. Each NFC card can trigger a specific playlist or song, so all you have to do is tap a card, and the vibe changes instantly.

![image](https://github.com/user-attachments/assets/ad098cae-463c-4d6f-9648-c7cad6be31ff)



## Update:
---
Motion-Reactive Animation: Dasai Mochi Bot

---


With the latest revision of the PCB, I’ve added an onboard MPU6050 accelerometer and gyroscope module. This opens the door to a brand new feature I call “Dasai Mochi Bot” – a cute, reactive animation engine that responds to motion and song titles.
The MPU6050 detects physical movement too – so if you tilt or shake the device, Mochi responds accordingly (like reacting dizzy or resetting pose). These animations run smoothly on the 2.4" TFT using sprite-based rendering.

Custom esp32:

<img width="1233" height="519" alt="image" src="https://github.com/user-attachments/assets/5e9507c6-8429-433b-be1c-70defedaae08" />

<img width="1188" height="587" alt="image" src="https://github.com/user-attachments/assets/4597a585-2bfa-4579-a9d9-cd504d7ce93a" />

<img width="1026" height="419" alt="image" src="https://github.com/user-attachments/assets/5c2f9377-7649-49a9-b50c-c30883cddfd6" />




Custom Case:

![image](https://github.com/user-attachments/assets/3dc52b39-108b-4e31-a988-efc88fdacee9)

![image](https://github.com/user-attachments/assets/b95bc6ab-5c95-4caf-911c-c3a67364b09d)


## Bill of Materials (BOM)

| Component                           | Qty | Price (USD) | Price (INR) | Store         | Link                                                                                                                                              |
| ----------------------------------- | --- | ----------- | ----------- | ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| Custom ESP32 PCB Prototype (5 pcs)  | 5   | **\$17.73** | ₹1480       | JLCPCB        | —                                                                                                                                                 |
| Custom ESP32 PCBA Assembled (2 pcs) | 2   | **\$52.88** | ₹4412       | JLCPCB        | —                                                                                                                                                 |
| Shipping (Estimated)                | 1   | **\$10.24** | ₹854        | JLCPCB        | —                                                                                                                                                 |
| PN532 NFC Module                    | 1   | \$3.04      | ₹254        | robocraze.in  | [Buy](https://robocraze.com/products/nfc-near-field-communication-rf-id-v3-module?variant=40193169096857)                                         |
| 2.4" SPI TFT Display                | 1   | \$5.54      | ₹463        | robocraze.in  | [Buy](https://robocraze.com/products/2-4in-tft-display-for-uno-board-compatible-with-arduino)                                                     |
| Kailh Silver Mechanical Switches    | 10  | \$2.99      | ₹250        | cosmicbyte.in | [Buy](https://www.thecosmicbyte.com/product/kailh-mechanical-switches-for-swappable-keyboards-pack-of-10/?attribute_pa_switch-type=silver-switch) |
| DSA Keycaps                         | 10  | \$1.80      | ₹150        | amazon.in     | [Buy](https://www.amazon.in/MAXBELL-Keycaps-Switches-Mechanical-Keyboard/dp/B09GPQCRC5)                                                           |
| NFC Cards                           | 5   | \$3.00      | ₹260        | amazon.in     | [Buy](https://www.amazon.in/Cards-Works-Android-Blank-Printable/dp/B0DH4Q9GY9/)                                                                   |
| 3D Printed Case                     | —   | —           | —           | Self-Printed  | Already made                                                                                                                                      |

**🧾 Total Cost:**  
- **USD:** $97.22
- **INR:** ₹8133 (approx.)


FInal assembled and render model:

![image](https://github.com/user-attachments/assets/8bec8837-89e2-4b0f-845e-995b953c41bf)

![image](https://github.com/user-attachments/assets/332973ba-0b29-4e43-abbb-fc9908f303de)




Spotify integration is done through the Spotify Web API using a library that handles OAuth and token refresh. The ESP32 acts as a remote control and communicates with an existing Spotify session running on a phone, PC, or other authorized device. Once authenticated, the ESP32 can send commands and receive playback data, allowing for full control and status updates on the display.

If you’ve ever wanted your own Spotify control panel, or just enjoy working with NFC, displays, and custom PCBs, this is a great project to try. The code is clean and modular, with all Spotify functions wrapped in a single method that runs in the loop. You can easily modify icons, change the screen layout, or add new NFC cards for more playlists. I’ve added a bill of materials, the .ino sketch, and a build journal to help anyone who wants to replicate or improve on this idea.


