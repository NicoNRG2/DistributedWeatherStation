# Distributed Weather Station
| ![Station Image](/images/StationImage.jpg) | ![Station Image](/images/website.png) |
|:---:|:---:|

## Section links
- [Project Description](#Project-Description)
- [Link](#Link)
- [Features](#Features)
- [Project Layout](#Project-Layout)
- [Requirements](#Requirements)
    - [Required Hardware](#Required-Hardware)
    - [Required Software](#Required-Software)
    
- [Installation](#Installation)
    - [ESP32 Station](#ESP32-Station)
    - [Pinout](#Pinout)
    - [Raspberry Server](#Raspberry-Server)
- [User Guide](#user-guide)
- [Next Feature](#Next-Feature)
- [Group Member](#team-members)

## Project Description

This project is a distributed weather station built using three ESP32 boards equipped with various sensors to measure environmental temperature, humidity, pressure, and light intensity. The collected data is sent every hour to a Node.js web server hosted on a Raspberry Pi and displayed across web pages.

## Link

[**Presentation Link**](https://docs.google.com/presentation/d/16gfYpvotDNyVWPRAXfWDlK4m0twHXV2He22jJudYA-Q/edit?usp=sharing)

[**Video Link**](https://youtu.be/8mtt4AqA1Wc?si=LxrClYKufGykfD_K)

## Features
- **Distributed Sensing**: Utilizes three ESP32 boards for distributed data collection.
- **Multi-Sensor Support**: Each ESP32 board is equipped with sensors for measuring temperature, humidity, pressure, and ambient light.
- **Real-Time Data**: Data is sent every hour to a Node.js web server.
- **Web Interface**: Real-time data and daily trends can be viewed through the web interface.
- **Wireless communication**: with the web server via ESP32.
- **Low power consumption**.

## Project Layout
![Project Layout](/images/SoftwareArchitecture.png)
```
DistributedWeatherStation
|   Power Point Presentation.pptx
|   README.md
|
+---Boards and Sensors Docs
|       DHT11_Temp Humid.pdf
|       dhtxx_protocol.png
|       dht_data_format.png
|       ESP32-Pinout.webp
|       GY-302_Licht_Sensor_Modul_Datenblatt_AZ-Delivery_Vertriebs_GmbH.pdf
|       GY-68_BMP180_Barometrischer_Sensor_Luftdruck_Modul_fur_Arduino_und_Raspberry_Pi_Datenblatt.pdf
|       MSP-EXP432P401R.jpg
|       MSP432_DriverLib_Users_Guide-MSP432P4xx-4_40_00_03 (1).pdf
|
+---ESP32_Firmware
|       ESP32_Firmware.ino
|
+---images
|       circuitScheme.jpeg
|       RaspDirectoryServer.jpeg
|       SoftwareArchitecture.png
|       StationImage.jpg
|       website.png
|
+---Sensor testing
|   +---ESP32_BH1750_test
|   |       ESP32_BH1750_test.ino
|   |
|   +---ESP32_BMP180_test
|   |       ESP32_BMP180_test.ino
|   |
|   \---ESP32_DHT11_test
|           ESP32_DHT11_test.ino
|
\---WebServer
        enego_station.html
        index.html
        marostica_station.html
        webserver.js

```

**Initialization:** In the setup() function, the code initializes the serial communication, sensors, and WiFi connection.

**Interrupts and Timers:** The Ticker object timer is used to create an interrupt that triggers the sendData() function every 10 seconds.

**Data Collection:** In the sendData() function, the code collects data from each sensor. If there’s an error in reading the data (indicated by isnan()), it assigns a default value of -2.

**Data Transmission:** If the WiFi connection is active, the code creates an HTTP client, specifies the server URL, and sets the content type to JSON. It then constructs a JSON string with the sensor data and location of the weather station, and sends this data to the server using a POST request. The server’s response is printed to the serial monitor.



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
![Station Image](/images/circuitScheme.jpeg)
2. Upload the source code to the ESP32 using the Arduino IDE.
3. Configure the WiFi settings in the source code and change if needed the address of the web server.
4. Start the weather station and verify that the data is correctly sent to the web server with the serial monitor inside Arduino IDE.

### Pinout

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

The website is very basic and easy to use, designed for a quick and streamlined user experience.
The site is accessible at the following link:
```
http://mioserverino.homepc.it:3000
```
### index.html

A first page will appear containing a geographical map with the available weather stations.

### marostica_station.html

By clicking on one of these, the current weather data for this location updated in the last hour will appear. Using the menu it is also possible to move to the graph section that shows the trend of the data measured in the last 24 hours.

## Next Feature
This project is easily scalable, in the future we can add:
- sensors: to make measurement of other type of data, such as the wind sensor, the rain sensor, ...
- stations: in order to cover a larger geographic area, we can add new weather stations.

In addition, we can implement the storage of the data using a database. In this way we can build graphic with a larger number of data instead of the last 24 hours only.

## Team members

The project was created by all members of the group together, each member contributed on all parts of the project.
However, we can highlight the areas of greatest competence for each member:

- Brognara Alessandro (sensor testing with arduino IDE)
- Cappellaro Nicola (interconnection between ESP32 and Raspberry, ESP32 coding)
- Zannoni Riccardo (website and javascript coding)