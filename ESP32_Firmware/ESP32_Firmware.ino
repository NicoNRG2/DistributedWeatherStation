#include <Wire.h>
#include <DHT.h>
#include <SFE_BMP180.h>
#include <BH1750.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Ticker.h>

const char* ssid = "your_ssid";
const char* password =  "your_password";

#define DHTPIN 13  // defines the DHT11 sensor pin
#define DHTTYPE DHT11  // defines the type of sensor (DHT11 in our case)

DHT dht(DHTPIN, DHTTYPE); // object for temperature and humidity

SFE_BMP180 bmp180;  // object for pressure

BH1750 lightMeter;  // object for the light intensity

double baseline = 1025; // baseline pressure, value for our geographical area

Ticker timer;   // object to use timers

void setup() {
  Serial.begin(9600);

  timer.attach(10, sendData); // creating an interrupt that executes the sendData() function given a number of seconds

  // Initialize the sensor
  Wire.begin();
  lightMeter.begin();

  dht.begin();

  bmp180.begin();

  Serial.println("All sensors started");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
}

double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = bmp180.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = bmp180.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = bmp180.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = bmp180.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else {
          Serial.println("error retrieving pressure measurement");
          return -2;
        }
      }
      else {
        Serial.println("error starting pressure measurement");
        return -2;
      }
    }
    else {
      Serial.println("error retrieving temperature measurement");
      return -2;
    }
  }
  else {
    Serial.println("error starting temperature measurement");
    return -2;
  }
}

void sendData() {
  // collect BMP180 data
  double pressure = 0;
  double altitude = 0;

  pressure = getPressure();
  if(isnan(pressure)){
    pressure = -2;
  }
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  altitude = bmp180.altitude(pressure, baseline);
  if(isnan(altitude)){
    altitude = -2;
  }
  Serial.print("Altitude: ");
  Serial.print(altitude, 1);
  Serial.println(" meters");

  //collect DHT11 data
  float temperature = 0;
  float humidity = 0;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading DHT11 sensor");
    temperature = -2;
    humidity = -2;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  //collect BH1750 data
  float lux = 0;
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  // send json with data to the webserver
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin("http://mioserverino.homepc.it:3000/data"); //Specify the URL
    http.addHeader("Content-Type", "application/json");  //Specify content-type header

    // location of the weather station
    String location = "Enego";

    // Create JSON data
    String jsonData = "{";
    jsonData += "\"luogo\":\"" + location + "\",";
    jsonData += "\"temperatura\":" + String(temperature) + ",";
    jsonData += "\"umidita\":" + String(humidity) + ",";
    jsonData += "\"pressione\":" + String(pressure) + ",";
    jsonData += "\"altezza\":" + String(altitude) + ",";
    jsonData += "\"luce\":" + String(lux);
    jsonData += "}";

    int httpResponseCode = http.POST(jsonData);   //Send the actual POST request

    if (httpResponseCode>0) {
      String response = http.getString(); //Get the response to the request
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();  //Free resources
  }
}