#include <IBusBM.h>

IBusBM ibus;

void setup()
{
  Serial.begin(115200);

  // Mega Serial1 RX = Pin 19
  Serial1.begin(115200);

  ibus.begin(Serial1);
}

void loop()
{
  Serial.print("CH1: ");
  Serial.print(ibus.readChannel(0));

  Serial.print("  CH2: ");
  Serial.print(ibus.readChannel(1));

  Serial.print("  CH3: ");
  Serial.print(ibus.readChannel(2));

  Serial.print("  CH4: ");
  Serial.println(ibus.readChannel(3));

  delay(100);
}