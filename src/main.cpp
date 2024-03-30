#define DECODE_NEC
#define SERVO_PIN 9
#define IR_RECEIVE_PIN 2

#define STOP_ANGLE 45

#include <Arduino.h>
#include <Servo.h>
#include <IRremote.hpp>

Servo servo;

void sweep();

void setup()
{
  servo.attach(SERVO_PIN);
  servo.write(180);

  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
}

void loop()
{
  if (IrReceiver.decode())
  {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      IrReceiver.resume();
    }
    else
    {
      IrReceiver.resume();
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
    }
    Serial.println();

    if (IrReceiver.decodedIRData.command && !(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT))
    {
      Serial.println("Resetting targets");
      sweep();
      Serial.println("Targets reset");
    }
  }
}

void sweep()
{
  int pos;
  for (pos = 180; pos >= STOP_ANGLE; pos -= 1)
  {
    servo.write(pos);
    delay(5);
  }

  delay(1000);

  for (pos = STOP_ANGLE; pos <= 180; pos += 1)
  {
    servo.write(pos);
    delay(5);
  }
}