#include "MD04MotorShield.h"

// Constructors ////////////////////////////////////////////////////////////////

MD04MotorShield::MD04MotorShield()
{
  //Pin map
  _INA1 = 9;
  _PWM1 = 5;
  _INA2 = 10;
  _PWM2 = 6;
}

MD04MotorShield::MD04MotorShield(unsigned char INA1,
                                 unsigned char PWM1,
                                 unsigned char INA2,
                                 unsigned char PWM2)

{
  _INA1 = INA1;
  _PWM1 = PWM1;
  _INA2 = INA2;
  _PWM2 = PWM2;
}

// Public Methods //////////////////////////////////////////////////////////////
void MD04MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

  pinMode(_INA1,OUTPUT);
  pinMode(_PWM1,OUTPUT);
  pinMode(_INA2,OUTPUT);
  pinMode(_PWM2,OUTPUT);

  #ifdef MD04MOTORSHIELD_TIMER1_AVAILABLE
    if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
    {
      // Timer 1 configuration
      // prescaler: clockI/O / 1
      // outputs enabled
      // phase-correct PWM
      // top of 400
      //
      // PWM frequency calculation
      // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
      TCCR1A = 0b10100000;
      TCCR1B = 0b00010001;
      ICR1 = 400;
    }
  #endif
}
// Set speed for motor 1, speed is a number between -400 and 400
void MD04MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;

  if (-256 < speed < 0)
  {
    reverse = 1;
    speed = -speed;  // Make speed a positive quantity
  }
  if (256 > speed > 0) {
    // Max PWM dutycyce
    speed = speed;
  }


  digitalWrite(_INA1, reverse ? LOW : HIGH );   // Make the motor coast no
  

  #ifdef MD04MOTORSHIELD_TIMER1_AVAILABLE
    if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
    {
      OCR1A = speed;
    }
    else
    {
      analogWrite(_PWM1,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_PWM1,speed * 51 / 80); // map 400 to 255
  #endif
}

// Set speed for motor 2, speed is a number between -400 and 400
void MD04MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;

  if (-256 < speed < 0)
  {
    reverse = 1;
    speed = -speed;  // Make speed a positive quantity
  }
  if (256 > speed > 0) {
    // Max PWM dutycyce
    speed = speed;
  }

  digitalWrite(_INA2, reverse ? LOW : HIGH );   // Make the motor coast no


  #ifdef MD04MOTORSHIELD_TIMER1_AVAILABLE
    if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
    {
      OCR1B = speed;
    }
    else
    {
      analogWrite(_PWM2,speed * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_PWM2,speed * 51 / 80); // map 400 to 255
  #endif
}

// Set speed for motor 1 and 2
void MD04MotorShield::setSpeeds(int m1Speed, int m2Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
}

// Brake motor 1, brake is a number between 0 and 400
void MD04MotorShield::setM1Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA1, LOW);

  #ifdef MD04MOTORSHIELD_TIMER1_AVAILABLE
    if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
    {
      OCR1A = brake;
    }
    else
    {
      analogWrite(_PWM1,brake * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_PWM1,brake * 51 / 80); // map 400 to 255
  #endif
}

// Brake motor 2, brake is a number between 0 and 400
void MD04MotorShield::setM2Brake(int brake)
{
  // normalize brake
  if (brake < 0)
  {
    brake = -brake;
  }
  if (brake > 400)  // Max brake
    brake = 400;
  digitalWrite(_INA2, LOW);

  #ifdef MD04MOTORSHIELD_TIMER1_AVAILABLE
    if (_PWM1 == _PWM1_TIMER1_PIN && _PWM2 == _PWM2_TIMER1_PIN)
    {
      OCR1B = brake;
    }
    else
    {
      analogWrite(_PWM2,brake * 51 / 80); // map 400 to 255
    }
  #else
    analogWrite(_PWM2,brake * 51 / 80); // map 400 to 255
  #endif
}

// Brake motor 1 and 2, brake is a number between 0 and 400
void MD04MotorShield::setBrakes(int m1Brake, int m2Brake)
{
  setM1Brake(m1Brake);
  setM2Brake(m2Brake);
}

