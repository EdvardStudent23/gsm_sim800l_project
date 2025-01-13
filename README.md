## SIM800L C library
Author: Edward Student

### Introduction 
This project contains a library for working with the SIM800L GSM module using the UART on the STM32 platform in STM32CubeIDE
The SIM800L module is used to send and receive SMS, make calls and work with data over a mobile network.
The goal of a project was to provide a convinient library for connecting and controlling SIM800L via UART, using the AT command standard, and also
gives an opportunity to show the result on lcd5110 nokia screen

----
### Prerequisites
You should have:

* STM32CubeIDE - environment in which you can use the library;
* STM32F3discovery - the STM microcontroller (it can be another model, but the library is aimed to work with this model
* SIM800L - cheap GSM module which provides a basic functionality to work with GSM, 2G network
* LCD 5110 - an lcd screen to see the result of function realisation
* Power supply unit or a battery - choose such supply unit, which can provide 2A and > 4V
* LM2596 (Optional) - for a circut
* Capacitor (100, 470, 1000 uF) - optional
* SIM-card - to connect with a network


----
### File structure
The project has the following file structure:

![image](https://github.com/user-attachments/assets/e9a3d64c-c7a4-4316-bc81-a4862a37b11a)

It is the standard project, generated in STM32CubeIDE, but there is a custom folder named Libraries. In Libraries we have: sim800l_lib with the following folders: config - directory for configuration files, inc - directory for headers, src - directory for files of source code.

In config you can find a file sim800l_config.h - in this file you can set options of the library functions. For example, you can set LEDs or sizes of buffers etc.

In inc we have sim800l.h with functions declaration.

sim800l.c is a main file of the library, in which you can find the realisation of functions

----
###  STM32 Pinout

The pins, which you should set: UART (i set UART2) for SIM800L, spi2 for LCD5110:

![image](https://github.com/user-attachments/assets/6242a38f-dda0-40c6-bb22-c26b1d4622f4)

The UART settings:

- ![image](https://github.com/user-attachments/assets/dc8bb4f4-ec65-4b1b-a79e-da1e31d9a029)
  
Activate PA2 (TX), PA3 (RX) pins. Set the baud rate to 9600 - its a standard baud rate for sim800l
Activate global interruptions
Mode Asynchonius

The SPI settings:
How to set the spi2 to connect the screen and see the output on the lcd screen, you can read here:
https://indrekis2.blogspot.com/2017/01/nokia-5110-pcd8544-stm32.html

----
### Connect elements
![sim800l_connection](https://github.com/user-attachments/assets/55b30a55-93cd-46f5-9d60-a4b62510d1f8)

----
### About the library. Its structure
The library provides some basic functionality:

The description of each function you can find in a header file in /inc: sim800l.h

Most needed functions used without a connection to the net is provided here such as:
power rate, initialisiation of module, send AT command function etc.

There are function to send an sms and to make a call. BUT these functions work theoretically (based on the information from different sources), because for some unknown reason, even after connecting to a good current source and adding a 1000 µF electrolytic capacitor to smooth out voltage surges when connected to the network, my module seemed to reset the connection (it did not blink for 3 seconds, i.e. it connected, but then returned to the network search mode).

### How to use
You should create such directoris (Libraries and next ones) in your project as i have in this project.
Next check your Project -> Properties. Add the pathes here:

* ![image](https://github.com/user-attachments/assets/d7f734c5-2197-48ee-986e-7aeafddd4472)

  
Also check source pathes and add the path to Libraries here:

* ![image](https://github.com/user-attachments/assets/71032a8b-92a0-46d8-992f-ac3196c0ba0d)

To use lcd, you should download some files:



After that you can go to your main.c, where you should include:
```
#include "sim800l.h"
#include "sim800l_conf.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "lcd5110.h"
#include "lcd_shared.h"
```







