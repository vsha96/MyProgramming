#define pin 11

void setup() {
  pinMode(pin, OUTPUT);

}

void loop() {
  analogWrite(pin,2);

}
