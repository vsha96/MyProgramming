#define pisk 3
#define laser 11
#define p A0


void setup() {
  pinMode(laser,OUTPUT);
  pinMode(p,INPUT);
}

void loop() {
  int p;
  analogWrite(laser, 255);
  p = analogRead(p);
  if (p <= 500) {
      tone(pisk,2000,50);
    }
}
