#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#define DHTPIN A1     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Create global varibales to store temperature, humidity, heat index and soil moisture
int t; // temperature in celcius
float f; // temperature in fahrenheit
int h; // humidity
float hif; // heat index in fahrenheit
int hic; // heat index in celcius
int sensorPin = A0;  // digital pin connected to the soil moisture sensor
int sensorValue; // variable to store value read from soil moisture sensor
int limit = 1000;



void setup()
{
  Serial.begin(9600);
  Serial.println(F("Plant Update!"));

  dht.begin();

 //Soil Moisture
 pinMode(13, OUTPUT);

 lcd.init();// initialize the lcd 
 lcd.init();

}


void loop()
{

   // scroll positions to the right
  // to move it offscreen right:
  for (int positionCounter = 3; positionCounter < 13 ; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(300);
  }

  

  // Wait a few seconds between measurements.
  delay(2000);
  sensorValue = analogRead(sensorPin); 

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old'
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;

  

}

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  int hic = dht.computeHeatIndex(t, h, false);

 
  //Display plant update to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(1,2);
  lcd.print("HeatIndex: ");
  lcd.print(hic);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(1,3);
  lcd.print("Soil: ");
  if (sensorValue<limit) {
  lcd.print("Moist"); 
 }
 else {
 lcd.print("Dry");  
 }



  //Display plant update  on the Monitor 
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(F("°F"));
  Serial.print("   Soil Moisture : ");
   if (sensorValue<limit) {
  Serial.println("Moist"); 
 }
 else {
 Serial.println("Dry");  
 }


}
