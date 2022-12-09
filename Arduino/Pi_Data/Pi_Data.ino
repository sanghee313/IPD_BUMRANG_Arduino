#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

void setup() {
  Serial.begin(9600); //Baud rate: 9600
  sensors.begin();
}
 
void loop() {
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //Serial.print("tubility : ");
  Serial.println(voltage); // print out the value you read:

  sensors.requestTemperatures();
  //Serial.print("Celcius : ");
  Serial.println(sensors.getTempCByIndex(0));
  //Serial.println(" C");
  //delay(1000); //1초마다 데이터 전송 
}
