# 3Duino
Bit bang a 3DS cartridge using a microcontroller. This is, to my knowledge, the only published attempt at programatically extracting the ROM data of a 3DS gamecard. ***Massive*** thanks to nocash at problemkaputt.de for their work on deciphering the 3DS cartridge protocol. Almost all sources on the internet regarding this topic seem to eventually stem from this one site.

## This guide is not yet finished, please note

### Overview
Because Nintendo is exceedingly greedy and does not want you to copy data from their game cartridges, most of the 3DS cartridge data transfer protocol is proprietary and encrypted. Still, reverse engineerers have pieced together information, though much of it seems to be incomplete. This project has pieced together the complete protocol from [GBATEK](https://problemkaputt.de/gbatek.htm#3dscartridgeregisters), [Winter Software](https://blog.winter-software.com/2024/06/02/ctr-cart-protocol), [3DBrew wiki](http://www.3dbrew.org/wiki/Gamecards), and others. It also includes two programs for Arduino language-compatible microcontrollers and for Java (any platform) to work together to obtain the cart data and put it into a runnable file for emulators such as Citra. Please do not use this for piracy. Enjoy!

### Protocol overview
The 3DS cartridge protocol (3CP) involves two parts: ROM access, and save data access. ROM access uses a proprietary encrypted protocol, whereas save data is accessed using a standard SPI protocol. For this explanation to make sense, the cartridge pinout must first be established. The following is adapted from the 3DBrew wiki:

Pin	| Name | Description
--- | ------ | ---------------
1 |	GND	| Ground
2 |	CLK	| Clock, active low
3	| NC |
4	| RCS |	ROM transfer select, active low
5 |	RST	| Reset, active low
6	| ECS |	Savegame transfer select, active low. 
7	| IRQ |	Removal detection
8 |	VCC	| Power (3.3V)


| Pin | Name | ROM transfer mode | Savegame transfer mode
----- | ---- | ----- | --------
9 |	D0 |	Bidirectional data bus | NC
10 |	D1 | Bidirectional data bus | NC
11 |	D2 | Bidirectional data bus | NC
12 |	D3 | Bidirectional data bus | NC
13 |	D4	| Bidirectional data bus | NC
14 |	D5	| Bidirectional data bus | WP#/SIO2
15 |	D6	| Bidirectional data bus | SO/SIO1
16 |	D7	| Bidirectional data bus | SI/SIO0
17 |	GND	| Ground | Ground


#### Savegame transferring
##### Pinout
Savegame data is stored in a flash memory chip known as the MX25L5121E. The datasheet is linked [here](https://www.macronix.com/Lists/Datasheet/Attachments/8796/MX25L1021E,%203V,%201Mb,%20v1.3.pdf). This chip uses the SPI interface to load and save data. The following image from akkit.com reveals the PCB traces on the gamecard (for the DS, but the structure should be very similar to that of the 3DS):


![Image which shows an opened DS cartridge with PCB traces highlighted](http://akkit.org/DS/dscard_traces.jpg)


Using these two sources, the flash chip pinout can be connected with the gamecard pinout to establish the following chart:

| Flash chip pin | Name | Description | Gamecard pin |
--- | --- | --- | --- |
1 | Chip Select | When low, enables data transfer | 6 (ECS) |
2 | MISO (CIPO) | SPI cartridge output | 15 (D6) |
3 | Write Protect | Unclear | Tied to ground |
4 | Ground | | |
5 | MOSI (COPI) | SPI input to the cartridge | 16 (D7) |
6 | Clock | Clock, latches high | 2 (CLK) |
7 | NC | | |
8 | VCC | | |

##### Commands
The savegame data is stored in an EEPROM. Commands are sent from the controller to the cartridge, and then a response in usually recieved (Depending on the command). The only command nescessary for reading savedata is the READ command. It takes the form of 0x03aaaaaa, where aaaaaa is a 3-byte starting adress. To send the command, the chip select (CS) pin is pulled low, and the message is sent via the COPI pin along with the clock signal, with data being read by the cartridge on the clock's rising edge. Once the command is sent, a response is sent via the CIPO pin forever until the CS pin is pulled up again. For an exhaustive list of the commands, the datasheet can be used. Most games have 512kb of savedata.





#### ROM transferring
##### Overview
This is the more complicated part. The ROM chip must first recieve commands from the controller (3DS, or, in this case, microcontroller), and it will then send information back according to the commands. There are two phases in which the information is sent: 8-byte mode, and 16-byte mode. The 8-byte mode is backwards-compatible with the much more well-documented DS protocol, and is unencrypted. This is an intentional design choice by Nintendo so that the 3DS can interact with both DS and 3DS games. The 16-byte mode is unique to the 3DS and is encrypted. The modes signify the length of the commands sent by the controller. For 8-byte mode, the commands are all 8 bytes long. For 16-byte mode, the commands are all 16 bytes, even when encrypted. 

##### 8-byte mode
This is when encryption keys and metadata are transferred. This mode, as mentioned before, is not encrypted. 


