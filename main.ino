#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <MQ135.h>

//MQ135 pin definition
#define ANALOGPIN_MQ135 A0

//DHT11 pin definition
#define dht_apin 9
#define DHT_TYPE DHT11

Adafruit_BMP085 bmp;
DHT dht(dht_apin, DHT_TYPE);
MQ135 gasSensor = MQ135(ANALOGPIN_MQ135);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bmp.begin();

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("Pressure: ");
  Serial.println(bmp.readPressure());

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  float rzero = gasSensor.getRZero();
  float correctedRZero = gasSensor.getCorrectedRZero(temperature, humidity);
  float ppm = gasSensor.getPPM();
  float correctedPPM = gasSensor.getCorrectedPPM(temperature, humidity);

  Serial.print(correctedPPM);
  Serial.println("ppm");
  if (correctedPPM >= 0 && correctedPPM <= 50) {
    Serial.println("GOOD");
  } else if (correctedPPM > 50 && correctedPPM <= 100) {
    Serial.println("MEDIUM");
  } else if (correctedPPM > 100 && correctedPPM <= 199) {
    Serial.println("UNHEALTHY");
  } else if (correctedPPM > 199 && correctedPPM <= 299) {
    Serial.println("VERY UNHEALTHY");
  } else if (correctedPPM > 300) {
    Serial.println("MEDIUM");
  } else {
    Serial.println("ERROR");
  }
  delay(5000);
}
