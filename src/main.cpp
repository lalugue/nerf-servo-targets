#define DECODE_NEC
#define SERVO_PIN 9
#define IR_RECEIVE_PIN 2

#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>

Servo servo;

// put function declarations here:
void sweep();

void setup()
{
  // put your setup code here, to run once:
  servo.attach(SERVO_PIN);

  Serial.begin(115200);

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
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