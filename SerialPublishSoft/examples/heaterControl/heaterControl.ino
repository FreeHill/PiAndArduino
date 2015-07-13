/*
This program will control the heater based on the
inputs from RaspberryPi.if temperature is more
then maxTemperature heature will be turned off,
if the temperature is less than minTemperature heater will be turned on

*/
#include <SoftwareSerial.h>
#include <SerialPublish.h>
#define tempPin A0
#define heaterPin 4
#define ledPin 13

SerialPublish pi(2,3);//rx,tx
float maxTemperature = 60, minTemperature = 50, heaterState = 0, ledState = 1, temperature;

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial publish example");
  pinMode(ledPin, OUTPUT);
  pi.publish("T", &temperature);
  pi.publish("minT", &minTemperature);
  pi.publish("maxT", &maxTemperature);
  pi.publish("heaterS", &heaterState);
  pi.publish("ledS", &ledState);
}

void loop()
{
  temperature = ((5.0 * analogRead(tempPin) * 100.0) / 1024);
  if (temperature > maxTemperature)
    heaterState = 0;
  else if (temperature < minTemperature)
    heaterState = 1;

  digitalWrite(heaterPin, heaterState);
  digitalWrite(ledPin, ledState);
 
  pi.sync();
}


