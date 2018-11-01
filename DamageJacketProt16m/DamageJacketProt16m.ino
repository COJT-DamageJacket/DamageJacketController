//This is 16 motor edition (means 32pin = 2chip)

#include <SPI.h>              // We use this library, so it must be called here.
#include <MCP23S17.h>         // Here is the new class to make using the MCP23S17 easy.

MCP chip0(0, 8);//CS_Pin=8
MCP chip1(0, 9);//CS_Pin=9

//unsigned int receive = 0; 

const int numMotor = 16; //16 is number of motor

const int howByte = numMotor*2/8; //how many Bytes used for control

byte receive[howByte]={}; //receive data

int ledpin=13; //13 is builtin LED port in nano and UNO

void setup() {
  Serial.begin(9600);
  
  chip0.begin();//setup chip0
  chip1.begin();//setup chip1
  chip0.pinMode(0x0000);//set all port output
  chip1.pinMode(0x0000);
}

void loop() {
  if(Serial.available()>=howByte){
    for(int i=0;i<howByte;i++)
      receive[i] = Serial.read();
    
    /*For Debug
    if(receive==0){
      digitalWrite(ledpin,HIGH);
    }else{
      digitalWrite(ledpin,LOW);
    }*/

    chip0.digitalWrite((receive[0]<<8)|receive[1]);
    chip1.digitalWrite((receive[2]<<8)|receive[3]);
    
    
    /*for(int i=0;i<howByte;i++)
      Serial.write(receive[i]); //send raw data like echo
      //Serial.println(receive[i], BIN); //send converted data*/
  }
}
