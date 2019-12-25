#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 0x20,0x2);  // lcd set

int lightlevel;                 // the light of level
int soundPin = 11;              // the pin of buzzer

void setup() {
  // put your setup code here, to run once:
  lcd.init();                   // LCD init
  lcd.backlight();              // open backlight
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(soundPin, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pr = analogRead(A0);
  Serial.println(pr);

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    
  if(pr <= 100){                //LV1
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    LCDOut(pr);
    tone(soundPin, 1466, 1000);
  }
  
  else if(pr > 100 && pr <= 200){ //LV2
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    LCDOut(pr);
    tone(soundPin, 1100, 500);
    delay(500);
  }

  else if(pr > 200 && pr <= 300){ //LV3
    digitalWrite(5, HIGH);
    LCDOut(pr);
    tone(soundPin, 1466, 500);
    delay(500);
  }

  else{                            //LV4
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    LCDOut(pr);
  }
  delay(1000);
}

void LCDOut( int light ){
  // to avoid the delay of lcd.clear();
  // clear the first line of LCD
  lcd.setCursor(0, 0);
  lcd.print("   ");
  lcd.setCursor(0, 0);
  lcd.print(light);
}
