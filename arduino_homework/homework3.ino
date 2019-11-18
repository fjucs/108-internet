#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 0x20,0x2);	// lcd set

long duration, dis;
int echoPin = 9;						// the pin of Ultrasonic echo
int triPin = 10;						// the pin of Ultrasonic tri
int soundPin = 5;						// the pin of buzzer
int pred = 0, light_f = 0, sound_f = 0;

void setup(){
	lcd. init();						// LCD init
	lcd. backlight();					// open backlight
	for( int i = 2; i <= 4; i++ ){
		pinMode(i, OUTPUT);				// LED output
	}
	pinMode(triPin, OUTPUT);			// Ultrasonic output
	pinMode(echoPin, INPUT);			// Ultrasonic input
	pinMode(soundPin, OUTPUT);			// buzzer output
	Serial.begin(9600);					// the link of computer
}

void soundOut( int d,bool same ){
	if(!same){							// if the set of length is change, change the soundset
		sound_f = 0;
	}
	if(d>=30){							// no sound, delay one second for break
		delay(1000);
		return;
	}
	if(d<10){
		tone(5,1466,1000);				// keep ringing
	}
	else if(d<20){						// two second as a cycle, one second ring five time
		if(sound_f==0){
			for(int i=0;i<5;i++){
				tone(5,1066+100*i,100);
				delay(100);
			}
		}
		else{
			delay(1000);
		}
		sound_f=(sound_f+1)%3;
	}
	else if(d<30){						// five second a cycle, one second ring five time
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

void LCDOut( int d ){
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
	lcd.setCursor(0, 1);				// set the output at second line
	lcd.print(d);						// output length
}

void LEDOut( int d, bool same ){
	if(!same){
		light_f=0;
	}
	if(0<=d && d<10){
		digitalWrite(2,HIGH);
		digitalWrite(3,LOW);
		digitalWrite(4,LOW);
	}
	else if(d>=10 && d<20){
		digitalWrite(3,LOW);
		digitalWrite(4,LOW);
		if(light_f==0){
			digitalWrite(2,HIGH);
		}
		else{
			digitalWrite(2,LOW);
		}
		light_f=(light_f+1)%2;
	}
	else if(d>=20 && d<30){
		digitalWrite(2,LOW);
		digitalWrite(3,HIGH);
		digitalWrite(4,LOW);
	}
	else{
		digitalWrite(2,LOW);
		digitalWrite(3,LOW);
		digitalWrite(4,HIGH);
	}
}

void ultrasonicWork(){					// set the frequency of ultrasonic
	digitalWrite(trigPin, LOW);
	delayMicroseconds(5);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin,HIGH);
}

bool change_mode(int d, int pre){		// check out if the mode is the same as the one before
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
	dis = (duration/2)/29.1;			// count out the length in CM
	LCDOut(dis);
	LEDOut(dis);
	soundOut(dis);
}