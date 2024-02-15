# DistributedWeatherStation
![Station Image](/images/StationImage.jpg)
## Section links
- [Project Description](#Project-Description)
- [Features](#Features)
- [Requirements](#Requirements)
    - [Required Hardware](#Required-Hardware)
    - [Required Software](#Required-Software)
- [Installation](#Installation)
    - [ESP32 Station](#ESP32-Station)
    - [Raspberry Server](#Raspberry-Server)
- [Next Feature](#Next-Feature)
- [Pinout](#Pinout)



## Project Description

This project is a distributed weather station built using three ESP32 boards equipped with various sensors to measure environmental temperature, humidity, pressure, and light intensity. The collected data is sent every hour to a Node.js web server hosted on a Raspberry Pi and displayed across web pages.

## Features
- **Distributed Sensing**: Utilizes three ESP32 boards for distributed data collection.
- **Multi-Sensor Support**: Each ESP32 board is equipped with sensors for measuring temperature, humidity, pressure, and ambient light.
- **Real-Time Data**: Data is sent every hour to a Node.js web server.
- **Web Interface**: Real-time data and daily trends can be viewed through the web interface.
- **Wireless communication**: with the web server via ESP32.
- **Low power consumption**.
## Requirements
### Required Hardware

- ESP32 Module
- DHT11 (temperature and humidity)
- BMP180 (pressure and calculated altitude)
- BH1750 (light intensity)
- Raspberry Pi

### Required Software

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
2. Install Node.js on the Raspberry:

```
sudo apt update
curl -fsSL https://deb.nodesource.com/setup_21.x | sudo -E bash - &&\
sudo apt-get install -y nodejs
```

3. Create a folder for the website, move inside it and init the project:

```
mkdir mio-progetto-nodejs
cd mio-progetto-nodejs
npm init
```

4. Install the necessary packages:

```
npm install express
npm install body-parser
npm install ws
```

5. Add the file from this repository WebServer folder inside a folder named public in your Node.js project.

6. run the web server

```
node webserver.js
```

## User Guide

finire di aggiungere come usare il sito........

## Next Feature
This project is easily scalable, in the future we can add:
- sensors: to make measurement of other type of data, such ad the wind sensor, the rain sensor,...
- stations: in order to cover a larger geographic area, we can add new weather stations.

In addition, we can implement the storage of the data using a database. In this way we can build graphic with a larger number of data instead of the last 24 hours only.

## Source code organization


## Pinout

<table>
<tr><th colspan=2> ESP32 </th></tr>
<tr><th>Pin left </th><th>Pin right</th></tr>
<tr><td>

| pin  | description
| --- | --- 
|EN | 
|VP  |
|VN  |
|34  |
|35  |
|32  | 
|33  |
|25  |
|26  |
|27 |
|14  | 
|12  | 
|13  | DHT11 data
|GND  |
|5V | DHT11


</td><td>

| pin  | description
| --- | --- 
|23 |
|SCL| I2C
|TX|
|RX |
|SDA | I2C
|19 |
|18 |
|5 |
|17| 
|16 |
|4 |
|2| 
|15 |
|GND | GROUND
|3.3V| BH1750, BMP180


</td></tr> </table>

## Team members

The project was created by all members of the group together, each member contributed on all parts of the project.
However, we can highlight the areas of greatest competence for each member:

- Brognara Alessandro (sensor testing with arduino IDE)
- Cappellaro Nicola (interconnection between ESP32 and Raspberry, ESP32 coding)
- Zannoni Riccardo (website and javascript coding)