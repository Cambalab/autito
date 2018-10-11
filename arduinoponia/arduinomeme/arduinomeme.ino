int val = 0;
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;

void setup() {
  Serial.begin(9600);    
    pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  // put your setup code here, to run once:
  pinMode(0, INPUT);

}

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

   for (int i=1; i <= whichPin; i++){
      bitWrite(bitsToSend, i, whichState);
      delay(10);
   }
  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  Serial.println(val);
  int meme = map(val, 400, 900, 1, 5);
  registerWrite(meme, HIGH);
  delay(1000);
}
