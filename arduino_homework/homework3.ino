#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

long duration, distance;

// trig is output
// echo is input
int trigPin= 10;
int echoPin= 9;

void ultrasonicOut(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void ultrasonicBack(){
  duration = pulseIn(echoPin,HIGH);
}

void count(){
  distance = (duration / 2) / 29.1;
}

void lightOn(int i) {
  digitalWrite(i,  HIGH);
}

void lightOff() {
  digitalWrite(2,  LOW);
  digitalWrite(3,  LOW);
  digitalWrite(4,  LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  for(int i = 0;i <= 6;i++){
    pinMode(i,  OUTPUT);
  }
  //LCD reset
  lcd.init();
  lcd.backlight();
}

void loop(){
  ultrasonicOut();
  ultrasonicBack();
  count();
  delay(500);
}


  if( distance < 10 ){
    lightOff();
    lcd.setCursor(0,0);
    lcd.print("Urgency");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lightOn(2);
    tone( 11, 1976 );
  }
  
  if( distance >= 10 && distance < 20 ){
    lightOff();
    lcd.setCursor(0,0);
    lcd.print("Attention");
    lcd.setCursor(0,1);
    lcd.print(distance);
    tone( 11, 1976, 500 );
    delay(500);
    lightOn(2);
    delay(1000);
  }

  if( distance >= 20 && distance < 30 ){
    lightOff();
    lcd.setCursor(0,0);
    lcd.print("Attention");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lightOn(3);
    tone( 11, 1976, 500 );
    delay(4500);
  }
  
  if( distance >= 30 ){
    lightOff();
    lcd.setCursor(0,0);
    lcd.print("Safety");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lightOn(4);
  }
  delay(500);