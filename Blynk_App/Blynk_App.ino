#include <SPI.h>
#include <WiFiLink.h>
#include <BlynkSimpleWiFiLink.h>

unsigned long a, b, f, a2, b2, f2;
char auth[] = "2879ce1054274c4095fd6737041a9746";

// WiFi credentials.
char ssid[] = "EEERover";
char pass[] = "exhibition";

BLYNK_WRITE(V1) {
//Joystick code
  int x = param[0].asInt();
  int y = param[1].asInt();
  int speedL = 0, speedR = 0, directionL = 0, directionR = 0, tempL = 0, tempR = 0;
  int dirL = 5;
  int dirR = 4;
  int pwmL = 9;
  int pwmR = 10;

if (y >= 0) { 
 tempR = y - x;
 tempL = y + x;
}

if (y < 0) {
  
 if (x <= 0) {
 tempR = -abs(y + x);
 tempL = y - x;
 }
 
 if (x > 0) {
 tempR = y + x;
 tempL = -abs(y - x);
 }
}
 
 if (tempL >= 0) {
 directionL = HIGH;
 speedL = tempL;
 }
 if (tempL < 0) {
 directionL = LOW;
 speedL = -tempL;
 }
 
 if (tempR >= 0) {
 directionR = HIGH;
 speedR = tempR;
 }
 if (tempR < 0) {
 directionR = LOW;
 speedR = -tempR;
 }

  analogWrite(pwmL, speedL);
  analogWrite(pwmR, speedR);
  digitalWrite(dirL, directionL);
  digitalWrite(dirR, directionR);

}

void setup()
{
  Serial.begin(9600);

  delay(10);
  pinMode(13, INPUT);

  Blynk.begin(auth, ssid, pass, IPAddress(192,168,0,51));
}

void loop(){

  Blynk.run();
  //IR freq measure
  a = pulseIn(13, HIGH);
  b = pulseIn(13, LOW);
  f = 1000000/(a + b);

  if (f<1000){
  Blynk.virtualWrite(V3, f);
}
  //RF freq measure
  a2 = pulseIn(12, HIGH);
  b2 = pulseIn(12, LOW);
  f2 = 1000000/(a2 + b2);

  if (f2<1000){
  Blynk.virtualWrite(V4, f2);
  }
  
}  
