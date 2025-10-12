int dataPin = 10;
int latchPin = 11;
int clockPin = 12;
byte dec_digits[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111100, 0b00000111, 0b01111111, 0b01100111 };

int trig = 2;
int echo = 3;

int maxVal = 50;
int minVal = 0;

int SPEAKER = 5;
void setup() {
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  int distance = ((pulseIn(echo,HIGH) * 340) / 10000) / 2;
  Serial.print(distance);
  Serial.println("cm");

  distance = map(distance,minVal,maxVal,0,9);
  distance = constrain(distance,0,9);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[distance]);
  digitalWrite(latchPin, HIGH);
  delay(10);

  int NOTE = map(distance,0,9,5000,500);
  tone(SPEAKER,NOTE,500);
}
