#define pin 11
int i = 0;

void setup() {
  pinMode(pin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() == 0);
    i = Serial.read();
    
    
    
}
