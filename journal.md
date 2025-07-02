---
Title: "A NFC Spotify player"
Author: "Hewis44"
Description: "Music controller"
created_at: "2025-06-28"
Total time spent: 15-18 Hours
---



## DAY 1 - 28 JUNE - 9-10 Hours  ( research + schematics + PCB)

So I saw the Spotify Car Thing online and bro, it looked so clean. Minimal, functional, and honestly, just a vibe. But when I checked the price online, it was totally crazy — like ₹15,000 or more. Apparently they discontinued it, and now everyone is just reselling it for insane prices. That’s when I had this lightbulb moment — “Why not build it myself?”  and I’d been wanting to try a custom PCB build with some real-world use. That’s how this whole thing began.
![WhatsApp Image 2025-06-17 at 01 03 31_385429e6](https://github.com/user-attachments/assets/3b0595d0-bccb-4cde-b9a0-a05888e04cb2)


i wanted to make smtg like this mann but ik hacklcub will consider this as 4 points project :( so i thought about making it from scratch

Than it flashed in my mind "" HOW ABOUT MAKE AN CUSTOM ESP32 ""
So i started researching on it and found some videos 


![image](https://github.com/user-attachments/assets/f0788d26-a0b6-4863-9e04-9ea97c549c51)



FOUND THIS GUY HE IS DA BEST
So as am new to pcb designing i started designing circuit based on his teachings



SO lets start desigining:





![image](https://github.com/user-attachments/assets/abbe24d9-62ed-4ce8-9e4f-9c217170d1b9)

![image](https://github.com/user-attachments/assets/451b82d3-df53-4169-9427-38fac9780959)


This is the brain. ESP32-WROOM module, with its pins all broken out. Capacitors near power pins for decoupling (filtering noise), and few pull-ups/pull-downs if needed for booting. This layout follows Espressif’s hardware design guide, so nothing fancy but solid and tested.




![image](https://github.com/user-attachments/assets/c1c5958d-463f-485a-81ce-fa6533ef5731)



This part is like a traffic cop for power. We’re using a Schottky diode (D1) to make sure power from USB or external supply doesn’t clash. Whichever power is higher gets passed, and the diode prevents backflow. Simple, effective, and safe for the ESP32.



![image](https://github.com/user-attachments/assets/145e3d3c-5a39-483f-8ad7-13606fab8cf3)




Bro, this is where we plug in our USB-C cable. The connector is USB-C 16-pin type, and the CC pins (Configuration Channel) are pulled down with 5.1kΩ resistors (R1, R2) to let the charger know we're a sink (not a charger). It’s routing the 5V VBUS to our 5V line and also passing D+/D- data lines to the USB-to-Serial IC for programming and debugging. Typical modern setup.




![image](https://github.com/user-attachments/assets/32113546-e680-47a5-8b21-89d0ed671428)




These buttons are the basic “jugaad” for ESP32 dev. One is RESET it just pulls EN low, and the other is BOOT which is actually GPIO0. It’s needed for getting into flash mode. This combo is what allows programming via USB without auto-reset logic, but here we also have that with transistors (next section).


![image](https://github.com/user-attachments/assets/9bbb21d5-d330-4a1c-8458-c05788e810f4)




This one is very cool  it uses two NPN BJTs (Q1 & Q2, usually S8050) to control EN and IO0. The USB-to-Serial chip sends DTR and RTS signals, and via some clever resistor network, these BJTs toggle the lines to reset the ESP32 into boot mode automatically during upload. It’s standard in many dev boards, saves you button pressing.




![image](https://github.com/user-attachments/assets/e41c75c2-f2a8-499a-a8ac-881d7ec6652e)


This part is handling all the talking between your PC and the ESP32. The CH340C IC is doing USB to UART conversion. It’s connected to TX, RX, DTR, RTS lines. Since this IC has internal crystal, we don’t need external one less headache. Very budget-friendly and works great for Arduino/ESP stuff.



![image](https://github.com/user-attachments/assets/cc141517-ac0a-4deb-8be6-6b759f0d2924)



Since ESP32 needs 3.3V, we’re using AMS1117-3.3 voltage regulator here. It converts the 5V coming from USB to 3.3V safely. Two capacitors (10uF and 100nF usually) on input and output sides to stabilize it. Common setup, works fine but does get a bit hot if current draw is high.




![image](https://github.com/user-attachments/assets/f8c537c6-ca45-444e-a938-e1447108ec52)



Two LEDs are here for quick debugging. One LED connected with 1k resistor to 3.3V shows that the board is powered (Power LED). Another one is connected to GPIO (maybe GPIO2 or 4) and you can blink it from code. Good to know if your firmware is alive or crashed.




![image](https://github.com/user-attachments/assets/f9be527c-52bf-4739-bab1-11f9b19601a7)


Extra GPIO headers are broken out here for sensors, I2C, SPI, etc. You can connect modules easily with female jumper wires. Makes this custom board usable in multiple projects very modular.




FINAL circuit:


![image](https://github.com/user-attachments/assets/2892b757-8f12-49f4-9b4d-2c31ff3febc8)



Lets start designing PCB:



![image](https://github.com/user-attachments/assets/34bc4d3d-56da-42ea-95ca-985978acfca7)



THIS WAS SO SATISFYINGGGGGG


![image](https://github.com/user-attachments/assets/a9ed80cc-ef31-4e8b-a0c8-e99b4970a400)

![image](https://github.com/user-attachments/assets/b5af1454-5b38-4488-98da-290f17779335)


I ALSO MADE SOME SILKSCREEN:


![image](https://github.com/user-attachments/assets/e621b50e-7c59-4e34-92f5-3c226b225158)


( I AM A TRUE AVIATION FAN BTW)

JLCPCB CART:


![image](https://github.com/user-attachments/assets/0c6ed91d-b08f-4e99-84e0-afa45265252a)


## DAY 2 - 29 JUNE - 6-8 Hours  ( CASE + CODE)


![image](https://github.com/user-attachments/assets/0299d681-9f98-49b1-afd7-7c5d441a0070)




 I spent almost 6 to 8 hours just sitting and fully focused on finishing the case design and writing the proper code for the Spotify player. Honestly, this day was both frustrating and satisfying. First, I started off by trying to adjust the dimensions properly for the 2.4 inch TFT display, 3 push buttons, 2 18650 batteries, and the NFC module. I made the box in Fusion 360, trying to keep everything tight but also spaced enough so wires don’t mess up later.



![Screenshot 2025-07-02 235820](https://github.com/user-attachments/assets/6f990396-fed3-4760-a1d5-9b2d6854673a)



The top part of the case was a bit tricky. I had to make those 3 rectangular slots exactly matching the buttons I have, and I didn’t want them to be loose. Below that, I made a big recessed cut for the screen to sit flush inside – I wanted that modern, clean look. In the bottom right, I added a slot to hide the batteries or maybe even fit the ESP32/NFC module depending on wiring.


![Screenshot 2025-07-02 235841](https://github.com/user-attachments/assets/a788b066-f118-4175-b6e4-9416072d8c94)



Once the case design was done and rendered decently, I shifted to coding. The idea was to complete the Spotify logic – like showing the artist, song name, progress bar, and also reacting to button inputs. But the fun part was adding NFC support. That took time to debug, bro. I had to make sure when I tap the tag, it triggers next/previous/play-pause correctly and doesn’t double trigger. So I added delay and string comparison for UID. After testing everything multiple times, it finally worked. That feeling when the song changes with just a card tap – goosebumps only.

So yeah, this day was all about making it feel real. From 3D designing the case like a product, to writing and polishing the full code with NFC magic it really came together.



Ive added evrything in the rep :)



