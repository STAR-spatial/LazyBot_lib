#include <Arduino.h>
#include<Wire.h>
#include<math.h>
#include "LazyBot.h"

#define MPU 0x68
#define NumData 7
#define pi      3.1415926535897932384626433832795 
int  GyAccTemp[NumData];
int  GATCorr[NumData]={0,0,0,0,0,0,0};
double PitchRoll[3];

double* Giroscope()
{
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);

  // Lecture des données (3 axes accéléromètre + température + 3 axes gyroscope
  for  (int i=0;i<NumData;i++)
  {
    if(i!=3)
    {
      GyAccTemp[i]=(Wire.read()<<8|Wire.read()) + GATCorr[i];
    }
    else
    {
      GyAccTemp[i]=(Wire.read()<<8|Wire.read()) + GATCorr[i];
      GyAccTemp[i] = GyAccTemp[i]/340 + 36.53;
    }
  }
  double x = GyAccTemp[0];
  double y = GyAccTemp[1];
  double z = GyAccTemp[2];

  PitchRoll[0] = atan(x/sqrt((y*y) + (z*z))); //  pitch 
  PitchRoll[1] = atan(y/sqrt((x*x) + (z*z))); // roll
  PitchRoll[2] = atan(z/sqrt((x*x) + (y*y))); // pitch
  
  //Conversion Radian en degré
  PitchRoll[0] = PitchRoll[0] * (180.0/pi);
  PitchRoll[1] = PitchRoll[1] * (180.0/pi) ;
  PitchRoll[2] = PitchRoll[2] * (180.0/pi) ;
  return PitchRoll;
}

float axe_y(){
   double* giro = Giroscope();
   return giro[0];
}

float axe_x(){
   double* giro = Giroscope();
   return giro[1];
}

float axe_z(){
   double* giro = Giroscope();
   return giro[2];
}


//fonction parchoc du robot qui retourne la valeur des contacteurs
int Parchoc(int pin){
   pinMode(pin, INPUT_PULLUP);
   return digitalRead(pin); 
}

float Capteur_ultrasonic(int pin[]){

   const byte TRIGGER_PIN = pin[0]; // Broche TRIGGER
   const byte ECHO_PIN = pin[1];    // Broche ECHO

   /* Constantes pour le timeout */
   const unsigned long MEASURE_TIMEOUT = 25000UL;
   const float SOUND_SPEED = 340.0 / 1000;

   /* Initialise les broches */
   pinMode(TRIGGER_PIN, OUTPUT);
   digitalWrite(TRIGGER_PIN, LOW); 
   pinMode(ECHO_PIN, INPUT);
   
   /*Capte la distance*/
   digitalWrite(TRIGGER_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGGER_PIN, LOW);
   long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   float distance_mm = measure / 2.0 * SOUND_SPEED;
   return (distance_mm / 10.0);
}
