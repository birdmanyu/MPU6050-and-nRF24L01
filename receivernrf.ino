
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);

unsigned long t0;
unsigned long t1;

void setup()
{
  pinMode(13,OUTPUT);
  
  while (!Serial);
  Serial.begin(115200);
  
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0A1LL);
  radio.openReadingPipe(2, 0xF0F0F0F0A2LL);
  
  radio.startListening();
  t0=0;
}

byte pipeNum=0; //variable to hold which reading pipe sent data

void loop()
{  
  t1=millis();
  /*digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(500);
  */
  if (t1-t0>100){
  if (radio.available(&pipeNum))
  {
    //char text[32] = {0};
    //int text[3];
    typedef struct Value {
              int x;
              int y;
              int z;
              int e0;
              int e1;
              int e2;    
            } Value;

            Value value;
            
    //radio.read(&text, sizeof(text));
    radio.read(&value, sizeof(value));
    //int coordinates[] ={value.x,value.y};
    Serial.print(t1);
    Serial.print("\t");
    Serial.print(pipeNum);
    Serial.print("\t");
    Serial.print(value.x);
    Serial.print("\t");
    Serial.print(value.y);
    Serial.print("\t");
    Serial.print(value.z);
    Serial.print("\t");
    Serial.print(value.e0);
    Serial.print("\t");
    Serial.print(value.e1);
    Serial.print("\t");
    Serial.print(value.e2);
    Serial.println();
    t0=t1;
    
    //Serial.println("X-acceleration");
    //int number=atol(text);
    //Serial.println(number);
    //Serial.println((int)text);
    //Serial.println(value);
    //delay(100);
   
  }
  }

  
  

}
