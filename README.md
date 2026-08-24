# 3Duino
Bit bang a 3DS cartridge using a microcontroller. This is, to my knowledge, the only published attempt at programmatically extracting the ROM data of a 3DS gamecard. 

The main purpose of this project is to figure out the complete 3DS gamecard protocol. I am doing this based off of a series of die shots. As of now, I only have the very top layer, which is in (this Google Drive file)[https://drive.google.com/file/d/16eykgb24jz9NoaT3B1qGHCNiuC40coXf/view?usp=sharing] (each pixel is 300 nanometers)


<!--
Documentation about functionality can be found at [this site](https://paxkym.github.io/3Duino/). Usage instructions are found here.

### Usage
> Step 1: Attach the gamecard to the microcontroller

You can either solder wires directly to a gamecard, or solder wires to an existing card slot. The latter is what I did, and you can find on Ebay for about $10. If you do not wish to purchase such things, you can also desolder one from a broken 3DS or add temporary connectors to a cartridge as mentioned before.

> Step 2: Set up the microcontroller
A microcontroller with at least 14 pins is needed. I used an Arduino Uno. Download the 3ds.ino file, and connect the pins of the card slot in the following manner:
* Pin 1 to GND
* Pin 2 to D2
* Pin 3 to GND or NC
* Pin 4 to D3
* Pin 5 to D4
* Pin 6 to D5
* Pin 7 to GND or NC
* Pin 8 to 3.3 volts. ***DO NOT USE 5 VOLTS!!!***
* Pin 9 to D6 (Data pins can be 5 volts or 3.3)
* Pin 10 to D6
* Pin 11 to D7
* Pin 12 to D8
* Pin 13 to D9
* Pin 14 to D10
* Pin 15 to D11
* Pin 16 to D12
* Pin 17 to GND or NC

Upload the ino file to your microcontroller.

> Step 3: Set up the program

Download the Java program, and use.
-->

