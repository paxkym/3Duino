# 3Duino
Bit bang a 3DS cartridge using a microcontroller. This is, to my knowledge, the only published attempt at programatically extracting the ROM data of a 3DS gamecard. Documentation about functionality can be found at [this site](https://paxkym.github.io/3Duino/). Usage instructions are found here.

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
* 


