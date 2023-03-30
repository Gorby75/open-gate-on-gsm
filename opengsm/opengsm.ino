#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8);
String phone1 = "+7XXXXXXXXX";
String phone2 = "+7XXXXXXXXXX";
unsigned long tt,delayPing,PingGSM=1000000;
String val = "";
boolean boolPing = true;

void rebootrele()
{
digitalWrite(3,HIGH);  
delay(1000);
digitalWrite(3,LOW);  
}

void setup() {
  
   pinMode(3, OUTPUT);
  delay(2000);  
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(2000);
  mySerial.println("AT");
  mySerial.println("AT+CLIP=1"); 
  mySerial.println("AT+CMGF=1"); 
  mySerial.println("AT+CSCS=\"GSM\"");
  mySerial.println("AT+CNMI=2,2,0,0,0"); 
digitalWrite(3,LOW);
}
void loop() 
{
 if (millis() - delayPing < 0) delayPing=millis();

  if (millis() - delayPing > PingGSM) {
    if (boolPing == true) {
      mySerial.println("AT");
      delay(100);
      boolPing = false;
    } if (val.indexOf("OK") > -1) {
      boolPing = true;
      delayPing = millis();
      val = "";
      mySerial.println("AT+COPS?");
       if (mySerial.find("+COPS: 0,0")) {     
    }    
    }
  } 
  if (millis() - delayPing > PingGSM+500) {
    delayPing = millis();
    delay(5000);
    Serial.end();
    mySerial.end();
    delay(5000);
    Serial.begin(9600);
    mySerial.begin(9600);
    delay(3000);
    mySerial.println("AT+CFUN=1,1");
    delay(3000);
    Serial.end();
    mySerial.end();
    delay(5000);
    Serial.begin(9600);
    mySerial.begin(9600);
    mySerial.println("AT");
    mySerial.println("AT+CLIP=1");  
    mySerial.println("AT+CMGF=1"); 
    mySerial.println("AT+CSCS=\"GSM\""); 
    mySerial.println("AT+CNMI=2,2,0,0,0"); 
    mySerial.println("AT+CMGD=4");
    boolPing = true;
  }
  
 if(mySerial.available()) 
  {  
    char ch = ' ';
    String val = "";
    while(mySerial.available()) 
     {  
       ch = mySerial.read();
       val += char(ch); 
       delay(3);
     }
    Serial.print("Send");
    Serial.println(val);
   
    if(val.indexOf("RING") > -1) 
     { 
     if (val.indexOf(phone1) > -1){ 
        Serial.println("Call");
mySerial.println("ATH"); 
delay(1000);
val = "";
rebootrele();
      }
      if (val.indexOf(phone2) > -1) {
mySerial.println("ATH");
delay(1000);
val = "";
rebootrele(); 
      }
     } 

     Serial.print("OK");
    Serial.println(val);
      }
       Serial.print("Send> ");
    Serial.println(val);

if (val.indexOf("+CMT") > -1) 
    {
      if ((val.indexOf(phone1) > -1) || (val.indexOf(phone2) > -1))
      {
rebootrele(); 
      }
           
    }
}   
