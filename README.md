# DistributedWeatherStation
![Station Image](/images/StationImage.jpg)

## Project Description

This project is a distributed weather station built using three ESP32 boards equipped with various sensors to measure environmental temperature, humidity, pressure, and light intensity. The collected data is sent every hour to a Node.js web server hosted on a Raspberry Pi and displayed across web pages.

## Features
- **Distributed Sensing**: Utilizes three ESP32 boards for distributed data collection.
- **Multi-Sensor Support**: Each ESP32 board is equipped with sensors for measuring temperature, humidity, pressure, and ambient light.
- **Real-Time Data**: Data is sent every hour to a Node.js web server.
- **Web Interface**: Real-time data and daily trends can be viewed through the web interface.
- **Wireless communication**: with the web server via ESP32.
- **Low power consumption**.

## Required Hardware

- ESP32 Module
- DHT11 (temperature and humidity)
- BMP180 (pressure and calculated altitude)
- BH1750 (light intensity)

## Required Software

- ESP32 library for WiFi communication with Arduino IDE, add this link to board manager in arduino ide https://espressif.github.io/arduino-esp32/package_esp32_index.json
- DHT sensor library (for DHT11 temperature and humidity sensor) found inside arduino ide.
- BMP180 library (for pressure and altitude) link from manufacturer az-delivery.de https://cdn.shopify.com/s/files/1/1509/1638/files/BMP180_Arduino.zip?14280905350788070314
- BH1750 library found inside Arduino IDE (for light intensity)

## Installation

### ESP32 Station
1. Connect the sensors to the ESP32 according to the electrical diagram.
2. Upload the source code to the ESP32 using the Arduino IDE.
3. Configure the WiFi settings in the source code and change if needed the address of the web server.
4. Start the weather station and verify that the data is correctly sent to the web server with the serial monitor inside Arduino IDE.

### Raspberry Server
1. Let's start with a basic installation of Raspbarry with Ubuntu (which we don't cover in this guide, you can easily do it on the web)
2. Install Node.js on the Raspberry
'
sudo apt update
curl -fsSL https://deb.nodesource.com/setup_21.x | sudo -E bash - &&\
sudo apt-get install -y nodejs
'

3. Create a folder for the website, move inside and init the project
'cd mio-progetto-nodejs
npm init'

4. Install the necessary packages:
'npm install express
npm install body-parser
npm install ws'

5. Add the file from this repository WebServer folder inside a folder named public in your Node.js project.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
