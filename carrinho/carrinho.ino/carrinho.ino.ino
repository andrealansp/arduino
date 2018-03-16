#include <PS2X_lib.h>
PS2X ps2x; // create PS2 Controller Class

void forward();
void backward();
void left();
void right();
void brake();
void checkDistance();

const int motorA1 = 3;     //motor A positive (+) pin to pin 6 (PWM) (from L298 module!)
const int motorA2 = 5;        //motor A negative (-) pin to pin 9 (PWM)
const int motorB1 = 6;   //motor B positive (+) pin to pin 10 (PWM)
const int motorB2 = 9;
const int pinBotao1 = 13;
const int buzzer=2;
bool estado = true;

int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {
  Serial.begin(38400);
  pinMode(pinBotao1, INPUT_PULLUP);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);



  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  error = ps2x.config_gamepad(12, 10, 11, 8, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }

}

void loop() {
  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed

  if (ps2x.NewButtonState(PSB_PAD_UP))           //will be TRUE if button was JUST pressed OR released
  {
    if (estado == true)
    {
      forward();
      estado = false;
    }
    else
    {
      brake();
      estado = true;
    }

  }
  if (ps2x.NewButtonState(PSB_PAD_RIGHT))           //will be TRUE if button was JUST pressed OR released
  {
    if (estado == true)
    {
      right();
      estado = false;
    }
    else
    {
      brake();
      estado = true;
    }
  }
  if (ps2x.NewButtonState(PSB_PAD_LEFT))           //will be TRUE if button was JUST pressed OR released
  {
    if (estado == true)
    {
      left();
      estado = false;
    }
    else
    {
      brake();
      estado = true;
    }

  }

  if (ps2x.NewButtonState(PSB_PAD_DOWN))           //will be TRUE if button was JUST pressed OR released
  {
    if (estado == true)
    {
      backward();
      estado = false;
    }
    else
    {
      brake();
      estado = true;
    }
  }
  if(ps2x.NewButtonState(PSB_BLUE))
  {
   if (estado == true)
    {
      tone(buzzer,2000);
      estado = false;
    }
    else
    {
      noTone(buzzer);
      estado = true;
    }
  }
}

