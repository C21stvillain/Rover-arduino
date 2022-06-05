#include "NewPing.h"
#include <Servo.h>

Servo servoM1;
Servo servoM2;
Servo servoM3;
Servo servoM4;
int pos1 ;
int pos2 ;
int pos3 ;
int pos4 ;
int L1on = A1;
int R1on = A2;
int L2on = A3;
int R2on = A4;
int arkakaldir;
int atlama;

#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 400  

#define TRIGGER_PIN2 6
#define ECHO_PIN2 5
#define MAX_DISTANCE2 400  

#define TRIGGER_PIN3 8
#define ECHO_PIN3 9
#define MAX_DISTANCE3 400  

NewPing sonarsol(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE2);
NewPing sonarsag(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE3);
float duration, distance;
float duration2, distance2;
float duration3, distance3;

void setup() 
{
servoM1.attach(10);
Serial.begin(9600);
servoM2.attach(11);
Serial.begin(9600);
servoM3.attach(12);
Serial.begin(9600);
servoM4.attach(13);
Serial.begin(9600);

pinMode(L1on, INPUT);
pinMode(R1on, INPUT);
pinMode(L2on, INPUT);
pinMode(R2on, INPUT);
}

void onkontrol()
{
  if (distance <25 & distance3 < 25)
  {
    for( int i=0;i<=30;i+=10)
    {
    pos1 = 0;
    pos2 = 0;
    pos1 = pos1 + i;
    pos2 = pos2 + i;
    servoM1.write(pos1);  
    servoM2.write(pos2);
    delay(100);
    arkakaldir = 1;
    }
    if (distance <25 & distance2 <25)
      {
          for( int i=0;i<=30;i+=10)
            {
            pos1 = 30;
            pos2 = 30;
            pos1 = pos1 + i;
            pos2 = pos2 + i;
            servoM1.write(pos1);
            servoM2.write(pos2);
            delay(100);
              }
              arkakaldir = 2;
              atlama = 1;
      }
  }
}

void onsolkontrol()
  {
  if (distance <25 )
    {
      for( int i=0;i<=30;i+=10)
      {
      pos1 = 0;
      pos1 = pos1 + i;
      servoM1.write(pos1);
      }
       arkakaldir = 1;
        if (distance <25 )
          {
            for( int i=0;i<=30;i+=10)
              {
              pos1 = 0;
              pos1 = pos1 + i;
              servoM1.write(pos1);
              }
               arkakaldir = 1;
          }
      }
    }
void onsagkontrol()
{
  if  (distance3 <25 )
    {
      for( int i=0;i<=30;i+=10)
      {
      pos2 = 0;
      pos2 = pos2 + i;
      servoM2.write(pos2);
      }
      arkakaldir = 1;
        if (distance2 <25 )
          {
            for( int i=0;i<=30;i+=10)
              {
              pos2 = 0;
              pos2 = pos2 + i;
              servoM2.write(pos2);
              }
              arkakaldir =2;
          }
      }
  }
void arkakontrol1()
{
  if (distance2 < 60 & arkakaldir ==1)  
  {
    for( int i=0;i<=30;i+=10)
      {
      pos3 = 0;
      pos4 = 0;
      pos3 = pos3 + i;
      pos4 = pos4 + i;
      servoM3.write(pos3);
      servoM4.write(pos4);
      }
      arkakaldir = 0;
    }
  }
void arkakontrol2()
{
  if (distance2 < 60 & arkakaldir ==2) 
    {
       for( int i=0;i<=60;i+=10)
          {
          pos3 = 0;
          pos4 = 0;
          pos3 = pos3 + i;
          pos4 = pos4 + i;
          servoM3.write(pos3);
          servoM4.write(pos4);
          }
          arkakaldir = 0;
    }
  }  

void getmesafe()
{
  distance = sonarsol.ping_cm();
  
  Serial.print("MesafeONSOL = ");
  
  if (distance >= 400 || distance <= 2) 
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);

  

  distance2 = sonar2.ping_cm(); // Bu arka sensör
  
  Serial.print("MesafeARKA = ");
  
  if (distance2 >= 400 || distance2 <= 2) 
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance2);
    Serial.println(" cm");
  }
  delay(500);

  
   // On sağ sensör
  distance3 = sonarsag.ping_cm();
  
  Serial.print("MesafeONSAG = ");
  
  if (distance3 >= 400 || distance3 <= 2) 
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance3);
    Serial.println(" cm");
  }
  delay(500);

  }  

void getRC()
{
  if (L1on == 1)
  {
    for( int i=0;i<=60;i+=10)
      {
      pos1 = 0;
      pos1 = pos1 + i;
      servoM1.write(pos1);
       }
  }
  if (R1on ==1)
  {
    for( int i=0;i<=60;i+=10)
      {
      pos2 = 0;
      pos2 = pos2 + i;
      servoM2.write(pos2);
        }
  }
  if (L2on == 1)  
  {
    for( int i=0;i<=60;i+=10)
      {
      pos3 = 0;
      pos3 = pos3 + i;
      servoM3.write(pos3);
         }
  }
  if (R2on ==1)  
  {
    for( int i=0;i<=60;i+=10)
      {
      pos4 = 0;
      pos4 = pos4 + i;
      servoM1.write(pos4);
    }
    }
}  
void loop() 
{
  getRC();
  getmesafe();  
  onkontrol();
  if (atlama ==1)
  {
    atlama =0;
    goto arkakontrol1;
    }
  onsagkontrol();
  onsolkontrol();
  arkakontrol1:
  arkakontrol1();
  arkakontrol2();
}
