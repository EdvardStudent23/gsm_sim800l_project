## SIM800L C library
Author: Edward Student

### Introduction 
This project contains a library for working with the SIM800L GSM module using the UART on the STM32 platform in STM32CubeIDE
The SIM800L module is used to send and receive SMS, make calls and work with data over a mobile network.
The goal of a project was to provide a convinient library for connecting and controlling SIM800L via UART, using the AT command standard, and also
gives an opportunity to show the result on lcd5110 nokia screen

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



### File structure
The project has the following file structure:

![image](https://github.com/user-attachments/assets/e9a3d64c-c7a4-4316-bc81-a4862a37b11a)

It is the standard project, generated in STM32CubeIDE, but there is a custom folder named Libraries. In Libraries we have: sim800l_lib with the following folders: config - directory for configuration files, inc - directory for headers, src - directory for files of source code.

In config you can find a file sim800l_config.h - in this file you can set options of the library functions. For example, you can set LEDs or sizes of buffers etc.

In inc we have sim800l.h with functions declaration.

sim800l.c is a main file of the library, in which you can find the realisation of functions

### 
