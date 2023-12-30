#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
  #define MD04MOTORSHIELD_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class MD04MotorShield
{
  public:
    // CONSTRUCTORS
    // Default pin selection.
    MD04MotorShield();
    // User-defined pin selection.
    MD04MotorShield(unsigned char INA1,
                    unsigned char PWM1,
                    unsigned char INA2,
                    unsigned char PWM2);          
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ.
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setSpeeds(int m1Speed, int m2Speed); // Set speed for both M1 and M2.
    void setM1Brake(int brake); // Brake M1.
    void setM2Brake(int brake); // Brake M2.
    void setBrakes(int m1Brake, int m2Brake); // Brake both M1 and M2.

  private:
    unsigned char _INA1;
    unsigned char _PWM1;
    static const unsigned char _PWM1_TIMER1_PIN = 13;
    unsigned char _INA2;
    unsigned char _PWM2;
    static const unsigned char _PWM2_TIMER1_PIN = 14;

};
