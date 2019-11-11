#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); 

void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i <= 6;i++){
    pinMode(i,  OUTPUT);
  }
  //LCD reset
  lcd.init();
  lcd.backlight();
}


void onwd(int i) {
  digitalWrite(i,  HIGH);
}

void on(int i) {
  digitalWrite(i,  HIGH);
  delay(1000);
}

void off(int i) {
  digitalWrite(i,  LOW);
  delay(1000);
}

void offwd(int i) {
  digitalWrite(i,  LOW);
}

void light(int i) {
  on(i);
  off(i);
}


void numshow(int j){
  lcd.print(j);
  lcd.setCursor(0, 0);
}

void loop() {
  int j = 1;
  lcd.clear();
  
  // put your main code here, to run repeatedly:
  for(int i = 0;i <= 6;i++){
    numshow(j);
    light(i);
    j++;
  }
  for(int i = 0;i <= 6;i+=2){
    numshow(j);
    light(i);
    j++;
  }
  for(int i = 1;i <= 6;i+=2){
    numshow(j);
    light(i);
    j++;
  }

  
  for(int i = 1;i <= 6;i+=2){
    numshow(j);
    onwd(i);
  }
  delay(1000);
  for(int i = 1;i <= 6;i+=2){
    numshow(j);
    offwd(i);
  }
  j++;

  for(int i = 0;i <= 6;i+=2){
    numshow(j);
    onwd(i);
  }
  delay(1000);
  for(int i = 0;i <= 6;i+=2){
    numshow(j);
    offwd(i);
  }
  j++;

  for(int i = 0;i <= 6;i++){
    numshow(j);
    onwd(i);
  }
  delay(1000);
  j++;
  for(int i = 0;i <= 6;i++){
    numshow(j);
    offwd(i);
  }
  delay(1000);
}
