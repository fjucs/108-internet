#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 0x20,0x2);  // lcd set

long double duration, dis;
int PIRPin = 2;
int echoPin = 9;                // the pin of Ultrasonic echo
int trigPin = 10;               // the pin of Ultrasonic tri
int soundPin = 11;              // the pin of buzzer
int ledPin = 13;
int PIRMode = 0;
int pred = 0, light_f = 0, sound_f = 0;

void setup(){
  lcd.init();                   // LCD init
  lcd.backlight();              // open backlight
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);     // Ultrasonic output
  pinMode(echoPin, INPUT);      // Ultrasonic input
  pinMode(soundPin, OUTPUT);    // buzzer output
  Serial.begin(9600);           // the link of computer
}

void soundOut( double d,bool same ){
  if(!same){                    // if the set of length is change, change the soundset
    sound_f = 0;
  }
  if(d>=30){                    // no sound, delay one second for break
    delay(1000);
    return;
  }
  if(d<10){
    tone(soundPin,1466,1000);         // keep ringing
  }
  else if(d<20){                // two second as a cycle, one second ring five time
    if(sound_f == 0){
      for(int i=0;i<5;i++){
        tone(soundPin,1066+100*i,100);
        delay(100);
      }
    }
    else{
      delay(1000);
    }
    sound_f=(sound_f+1)%3;
  }
  else if(d<30){                // five second a cycle, one second ring five time
    if(sound_f==0){
      for(int i=0;i<5;i++){
        tone(5,1066+100*i,100);
        delay(100);
      }
    }
    else{
      delay(1000);
    }
    sound_f=(sound_f+1)%6;
  }
}

void LCDOut( double d ){
  // to avoid the delay of lcd.clear();
  // clear the first line of LCD
  lcd.setCursor(0, 0);
  lcd.print("         ");
  // output the different type for different length
  lcd.setCursor(0, 0);
  if( d <= 10 ){
    lcd.print("Urgency");
  }
  else if( d <= 30 ){
    lcd.print("Attention");
  }
  else{
    lcd.print("Safely");
  }
  // clear second line of LCD
  lcd.setCursor(0, 1);
  lcd.print("       ");
  // output the length ultrasonic get in second line;
  lcd.setCursor(0, 1);        // set the output at second line
  lcd.print(d);           // output length
}

void LEDOut( double d, bool same ){
  if(!same){
    light_f=0;
  }
  if(0<=d && d<10){
    if(light_f==0){
      digitalWrite(ledPin,HIGH);
    }
    else{
      digitalWrite(ledPin,LOW);
    }
    light_f=(light_f+1)%2;
  }
  else if(d>=10 && d<20){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
}

void ultrasonicWork(){          // set the frequency of ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
}

void PIRWork(){
  PIRMode = digitalRead(PIRPin);
}

bool change_mode(double d, double pre){   // check out if the mode is the same as the one before
  bool same=false;
  if(d>0 && d<=10 && pre>0 && pre<=10){
    return true;
  }
  if(d>10 && d<20 && pre>10 && pre<20){
    return true;
  }
  if(d>20 && d<30 && pre>20 && pre<30){
    return true;
  }
  if(d>30 && pre>30){
    return true;
  }
  return false;
}

void loop(){
  ultrasonicWork();
  PIRWork();
  dis = (duration/2)/29.1;      // count out the length in CM
  if( PIRMode == 1 ){
    LCDOut(dis);
    LEDOut(dis, change_mode( dis, pred ));
    soundOut(dis, change_mode( dis, pred ));
  }
}
