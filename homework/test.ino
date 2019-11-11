void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i <= 6;i++){
    pinMode(i,  OUTPUT);
  }
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

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0;i <= 6;i++)light(i);
  for(int i = 0;i <= 6;i+=2)light(i);
  for(int i = 1;i <= 6;i+=2)light(i);
  
  for(int i = 1;i <= 6;i+=2)onwd(i);
  delay(1000);
  for(int i = 1;i <= 6;i+=2)offwd(i);

  for(int i = 0;i <= 6;i+=2)onwd(i);
  delay(1000);
  for(int i = 0;i <= 6;i+=2)offwd(i);

  for(int i = 0;i <= 6;i++)onwd(i);
  delay(1000);
  for(int i = 0;i <= 6;i++)offwd(i);
  delay(1000);
}
