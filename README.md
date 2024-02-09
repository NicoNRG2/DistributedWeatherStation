# DistributedWeatherStation

## Project Description

This project is a weather station built with an MSP432 microcontroller and an ESP32 module for communication with a web server. The weather station is capable of detecting various environmental parameters and sending them to the web server for data processing and display.

## Features

- Detection of temperature, humidity, atmospheric pressure, and ambient brightness.
- Wireless communication with the web server via ESP32.
- Low power consumption.

## Required Hardware

- MSP432 Microcontroller
- ESP32 Module
- Weather sensors (temperature, humidity, atmospheric pressure, light sensor)

## Required Software

- Code Composer Studio for MSP432 programming
- ESP32 library for WiFi communication with Arduino IDE

## Installation

1. Connect the sensors to the MSP432 according to the electrical diagram.
2. Upload the source code to the MSP432 using the Energia IDE.
3. Configure the WiFi settings in the source code.
4. Start the weather station and verify that the data is correctly sent to the web server.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
