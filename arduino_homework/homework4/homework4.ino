#include <LiquidCrystal_I2C.h>
#include "cactus_io_DHT22.h"
#define DHT22_PIN 2
DHT22 dht(DHT22_PIN);
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 0x20,0x2);	// lcd set

int echoPin = 9;						    // the pin of Ultrasonic echo
int trigPin = 10;						    // the pin of Ultrasonic tri
int soundPin = 11;						  // the pin of buzzer
int pred = 0, light_f = 0, sound_f = 0;

void setup(){
	lcd.init();						        // LCD init
	lcd.backlight();					    // open backlight
	for( int i = 5; i <= 7; i++ ){
		pinMode(i, OUTPUT);				  // LED output
	}
	pinMode(trigPin, OUTPUT);			// Ultrasonic output
	pinMode(echoPin, INPUT);			// Ultrasonic input
	pinMode(soundPin, OUTPUT);		// buzzer output
	Serial.begin(9600);					  // the link of computer
  dht.begin();
}

bool change_mode(float rear, float pre){    // check out if the mode is the same as the one before
  bool same=false;
  if(rear>=0 && rear<=28 && pre>=0 && pre<=28){
    return true;
  }
  if(rear>28 && rear<=30 && pre>28 && pre<=30){
    return true;
  }
  if(rear>30 && rear<=32 && pre>30 && pre<=32){
    return true;
  }
  if(rear>32 && pre>32){
    return true;
  }
  return false;
}

int checkPlace( float tmp ){
  if(0 <= tmp && tmp <= 28.0){
    return 1;
  }
  else if( tmp <= 30.0 ){
    return 2;
  }
  else if( tmp <= 32.0 ){
    return 3;
  }
  else{
    return 4;
  }
}

void T_HSensorWork(){
  dht.readHumidity();
  dht.readTemperature();
}

void soundOut( float tmp,bool same ){
	if(!same){							      // if the set of length is change, change the soundset
		sound_f = 0;
	}
  if( checkPlace( tmp ) == 1 ){
    delay(1000);
    return;
  }
  else if( checkPlace( tmp ) == 2 ){
    if( sound_f == 0 ){
      for( int i = 0; i < 5; i++ ){
        tone(soundPin, 1066 + 100 * 1, i++ );
        delay(100);
      }
    }
    else{
      delay(1000);
    }
    sound_f = (sound_f + 1) % 6;
  }
  else if( checkPlace( tmp ) == 3 ){
    if( sound_f == 0 ){
      for( int i = 0; i < 5; i++ ){
        tone(soundPin, 1066 + 100 * 1, i++ );
        delay(100);
      }
    }
    else{
      delay(1000);
    }
    sound_f = (sound_f + 1) % 3;
  }
  else{
    tone(soundPin, 1466, 1000);
    delay(1000);
    return;
  }
}

void LCDOut(){
	// to avoid the delay of lcd.clear();
	// clear the first line of LCD
  lcd.clear();
  // lcd print temperature
  lcd.print(dht.temperature_C);
	// clear second line of LCD
  // lcd print humiditiy
  lcd.setCursor(0, 1);
	lcd.print(lcd.print(dht.humidity));
}

void LEDOut( float tmp, bool same ){
  if( !same ){
    light_f = 0;
  }
	if( checkPlace( tmp ) == 1 ){
		digitalWrite(5,HIGH);
		digitalWrite(6,LOW);
		digitalWrite(7,LOW);
	}
	else if( checkPlace( tmp ) == 2 ){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
	}
  else if( checkPlace( tmp ) == 3 ){
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    if( light_f == 0 ){
      digitalWrite( 7, HIGH );
    }
    else{
      digitalWrite( 7, LOW );
    }
    light_f = (light_f + 1) % 2;
  }
  else{
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
}

void loop(){
  //digitalWrite(5,HIGH);
  T_HSensorWork();
	LCDOut();
	LEDOut(dht.temperature_C, change_mode(dht.temperature_C, pred));
	soundOut(dht.temperature_C, change_mode(dht.temperature_C, pred));
  pred = dht.temperature_C;
}
