#include <Arduino.h>
#include <Servo.h>

Servo servo;

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  servo.attach(9);
}

void loop() {}
}