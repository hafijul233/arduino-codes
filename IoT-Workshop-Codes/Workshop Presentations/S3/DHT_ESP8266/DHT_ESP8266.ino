#include "DHTesp.h"

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  dht.setup(4, DHTesp::DHT22); // Connect DHT sensor to D2
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float realfeel = dht.computeHeatIndex(temperature,humidity);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Real Feel: ");
  Serial.println(realfeel);
}
