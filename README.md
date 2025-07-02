# spotify_player


This is a DIY Spotify Controller built using an ESP32 microcontroller, inspired by the discontinued Spotify Car Thing. The idea came from wanting a simple and elegant way to control music without needing to touch my phone. Since buying the original Car Thing is now super expensive, I decided to make my own version using the components I had and some custom PCB design.



![image](https://github.com/user-attachments/assets/87afe39f-2cc8-41ec-a4d9-e944e3d86e87)




The device uses a 2.4-inch TFT display to show real-time song information like title, artist, and playback progress. It also includes word wrapping, so even long track names are displayed neatly without getting cut off. I’ve added three mechanical switches to handle play/pause, next, and previous track actions, all of which are sent directly to the Spotify Web API over Wi-Fi. To add a fun and futuristic twist, the project includes an NFC reader. Each NFC card can trigger a specific playlist or song, so all you have to do is tap a card, and the vibe changes instantly.

![image](https://github.com/user-attachments/assets/ad098cae-463c-4d6f-9648-c7cad6be31ff)


Custom esp32:

![Screenshot 2025-06-29 230803](https://github.com/user-attachments/assets/ccd1fb47-6fcc-4782-928d-e0e3c69e5803)


![Screenshot 2025-06-29 230819](https://github.com/user-attachments/assets/fcfbe474-e7a8-456a-89ed-86d769538cc0)

![Screenshot 2025-06-29 230737](https://github.com/user-attachments/assets/053cebfa-227e-4df4-afd0-886c7b7ad784)


Custom Case:

![Screenshot 2025-06-29 233933](https://github.com/user-attachments/assets/49960f1d-7479-42e8-a211-1f99ae93dae6)


![Screenshot 2025-06-29 234041](https://github.com/user-attachments/assets/18508b7a-d42e-443b-b433-bfaa73dafc95)



## Bill of Materials (BOM)

| Component                         | Qty | Price (USD) | Price (INR) | Store          | Link |
|----------------------------------|-----|--------------|--------------|----------------|------|
| Custom ESP32 PCB Prototype (5 pcs) | 5   | 14.60        | 1219.10      | JLC            | -    |
| Custom ESP32 PCBA Assembled (2 pcs) | 2   | 83.85        | 7001.48      | JLC            | -    |
| Shipping                          | 1   | 16.97        | 1416.99      | JLC            | -    |
| PN532 NFC Module                  | 1   | 3.04         | 254.00       | Robocraze      | [Link](https://robocraze.com/products/nfc-near-field-communication-rf-id-v3-module?variant=40193169096857&country=IN&currency=INR&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&campaignid=21590308288&adgroupid=&keyword=&device=c&gad_source=1&gad_campaignid=21586648451&gbraid=0AAAAADgHQvYmNBcrELJJmoBrlbc9qJGsq&gclid=Cj0KCQjwyIPDBhDBARIsAHJyyVija9jdBLYwi1AIBR4NGTak_4R1Fw639eS4X_mnjcoLhtqIzoUGwDgaAqa1EALw_wcB) |
| 2.4" SPI TFT Display              | 1   | 5.54         | 463.00       | Robocraze      | [Link](https://robocraze.com/products/2-4in-tft-display-for-uno-board-compatible-with-arduino?srsltid=AfmBOooHw__J4xEGz5m5F3e8zxRdUqBesVLdjJFDkCUiQz60vcqm9rYM) |
| Mechanical Switches (Silver)     | 10  | 2.99         | 250.00       | Cosmic Byte    | [Link](https://www.thecosmicbyte.com/product/kailh-mechanical-switches-for-swappable-keyboards-pack-of-10/?attribute_pa_switch-type=silver-switch&utm_source=Google%20Shopping&utm_campaign=googlefeeds&utm_medium=cpc&utm_term=249118&gad_source=1&gad_campaignid=16128104146&gbraid=0AAAAADJ1AVRNM2fcuNF0ILO_4QkzhfIX0&gclid=Cj0KCQjwjo7DBhCrARIsACWauSnFd3gOFCKCvGJkIBoWk8x_Mejey2keijRJbHJybV1Gn0Dd1cn_5O0aAi70EALw_wcB) |
| DSA Keycaps                      | 10  | 1.80         | 150.00       | Amazon         | [Link](https://www.amazon.in/MAXBELL-Keycaps-Switches-Mechanical-Keyboard/dp/B09GPQCRC5) |
| NFC Cards                        | 5   | 3.00         | 260.00       | Amazon         | [Link](https://www.amazon.in/Cards-Works-Android-Blank-Printable/dp/B0DH4Q9GY9) |
| 3D Prints                        | -   | -            | Have mine    | -              | -    |
| **Total**                        |     | **131.80**   | **₹11014.57** |                |      |



FInal assembled and render model:

![image](https://github.com/user-attachments/assets/8bec8837-89e2-4b0f-845e-995b953c41bf)

![image](https://github.com/user-attachments/assets/332973ba-0b29-4e43-abbb-fc9908f303de)




Spotify integration is done through the Spotify Web API using a library that handles OAuth and token refresh. The ESP32 acts as a remote control and communicates with an existing Spotify session running on a phone, PC, or other authorized device. Once authenticated, the ESP32 can send commands and receive playback data, allowing for full control and status updates on the display.

If you’ve ever wanted your own Spotify control panel, or just enjoy working with NFC, displays, and custom PCBs, this is a great project to try. The code is clean and modular, with all Spotify functions wrapped in a single method that runs in the loop. You can easily modify icons, change the screen layout, or add new NFC cards for more playlists. I’ve added a bill of materials, the .ino sketch, and a build journal to help anyone who wants to replicate or improve on this idea.


