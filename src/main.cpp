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
  servo.write(0);

  Serial.begin(115200);

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
}

void loop()
{
  if (IrReceiver.decode())
  {

    /*
     * Print a summary of received data
     */
    if (IrReceiver.decodedIRData.protocol == UNKNOWN)
    {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print extended info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
      IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
    }
    else
    {
      IrReceiver.resume(); // Early enable receiving of the next IR frame
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
    }
    Serial.println();

    /*
     * Finally, check the received data and perform actions according to the received command
     */
    if (IrReceiver.decodedIRData.command)
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
  for (pos = 0; pos <= 120; pos += 1)
  {
    servo.write(pos);
    delay(5);
  }

  delay(10);

  for (pos = 120; pos >= 0; pos -= 1)
  {
    servo.write(pos);
    delay(5);
  }
}