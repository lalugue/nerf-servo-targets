#include <Arduino.h>
#include <Servo.h>

Servo servo;

// put function declarations here:
void sweep();

void setup()
{
  // put your setup code here, to run once:
  servo.attach(9);
}

void loop() {}

void sweep()
{
  int pos;
  for (pos = 0; pos <= 180; pos += 1)
  {
    servo.write(pos);
    delay(15);
  }

  delay(500);

  for (pos = 180; pos >= 0; pos -= 1)
  {
    servo.write(pos);
    delay(15);
  }
}