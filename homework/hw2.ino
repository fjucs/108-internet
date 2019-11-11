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

void light(int i) {
  on(i);
  off(i);
}

void onwd(int i) {
  digitalWrite(i,  HIGH);
}

void offwd(int i) {
  digitalWrite(i,  LOW);
}

void on(int i) {
  digitalWrite(i,  HIGH);
  delay(1000);
}

void off(int i) {
  digitalWrite(i,  LOW);
  delay(1000);
}

// show the number on LCD
void numshow(int j){
  lcd.print(j);
  lcd.setCursor(0, 0);
}

// The showing loop
void loop() {
  int j = 1;        // set the showing number j is one
  lcd.clear();      // clear up LCD before every new loop
  
  // put your main code here, to run repeatedly:
  // light on the light from first light to the least
  for(int i = 0;i <= 6;i++){
    numshow(j);
    light(i);
    j++;
  }

  // light on only the red light
  for(int i = 0;i <= 6;i+=2){
    numshow(j);
    light(i);
    j++;
  }

  // light on only the green light
  for(int i = 1;i <= 6;i+=2){
    numshow(j);
    light(i);
    j++;
  }

  // light all the red light togather
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

  // light all the green light togather
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

  // light all the light on
  for(int i = 0;i <= 6;i++){
    numshow(j);
    onwd(i);
  }
  delay(1000);
  j++;
  // kill all the lights
  for(int i = 0;i <= 6;i++){
    numshow(j);
    offwd(i);
  }
  delay(1000);
}
