//from yellow wire to yellow wire:
//that is 5 wires: Chipkit Max32 from 2 to 6
//
//from yellow wire to orange wire:
//that is 2 wires: Chipkit Max32 11, 12
//
//red wire: Chipkit Max32 +5V
//
//black wire: Chipkit Max32 ground


// stuff for the LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int poemCount = -1;

//
/*
  HC-SR04 Ping distance sensor
  VCC to Arduino 5V
  GND to Arduino GND
  Echo to Arduino pin 13  in my case 10
  Trig to Arduino pin 12  in my case 9
  More info at: http://goo.gl/kJ8Gl
  Original code improvements to the Ping sketch sourced from Trollmaker.com
  Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
  Modified by Tolson Winters (Aug 27, 2014) for simplified serial monitor reading.
*/

// The Ultrasonic range sensor 
// grey trig
// orange echo

#define trigPin 9 
#define echoPin 10 

bool rangeEnabled = true;

int value;


int sp[] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5};

// ORIGINAL SHIFT REGISTERS EXAMPLE
int latchPin = 8;  // green
int clockPin = 12;
int dataPin = 11;

int numOfRegisters = 2;
byte* registerState;

long effectId = 0;
long prevEffect = 0;
long effectRepeat = 0;
long effectSpeed = 30;

void setup() {
  //Initialize array
  registerState = new byte[numOfRegisters];
  for (size_t i = 0; i < numOfRegisters; i++) {
    registerState[i] = 0;
  }

  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);

  // for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // for the LCD
  lcd.begin(16, 2);
 // pinMode(switchPin, INPUT);
  lcd.print("");

  lcd.setCursor(0, 1);
  lcd.print("leukemia");
}


void lcdStuff()
{
  poemCount = (poemCount + 1) % 62;

  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.print("The ball says:");
  lcd.setCursor(0, 1);
  switch (poemCount) {
    case 0:
      lcd.print("emptiness");
      break;
    case 1:
      lcd.print("mine");
      break;
    case 2:
      lcd.print("how");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("will give more");
      lcd.setCursor(0, 1);
      lcd.print("then I do");
      break;
    case 4:
      lcd.print("surplus");
      break;
    case 5:
      lcd.print("dust");
      break;
    case 6:
      lcd.print("hammer");
      break;
    case 7:
      lcd.print("heart");
      break;
    case 8:
      lcd.print("leukemia");
      break;
    case 9:
      lcd.print("wife");
      break;
    case 10:
      lcd.print("black");
      break;
    case 11:
      lcd.print("endlessly black");
      break;
    case 12:
      lcd.setCursor(0, 0);
      lcd.print("during communism");
      lcd.setCursor(0, 1);
      lcd.print("era police shot");
      break;
    case 13:
      lcd.print("workers");
      break;
    case 14:
      lcd.setCursor(0, 0);
      lcd.print("with sharp");
      lcd.setCursor(0, 1);
      lcd.print("ammunition");
      break;
    case 15:
      lcd.print("sabotage");
      break;
    case 16:
      lcd.print("bodies of miners");
      break;
    case 17:
      lcd.print("Stawisinski");
      break;
    case 18:
      lcd.print("Gnida");
      break;
    case 19:
      lcd.print("Czekalski");
      break;
    case 20:
      lcd.print("Giza");
      break;
    case 21:
      lcd.print("Gzik");
      break;
    case 22:
      lcd.print("Kopczak");
      break;
    case 23:
      lcd.print("Pelka");
      break;
    case 24:
      lcd.print("Wilk");
      break;
    case 25:
      lcd.print("Zajac");
      break;
    case 26:
      lcd.setCursor(0, 0);
      lcd.print("the monument of");
      lcd.setCursor(0, 1);
      lcd.print("Lenin");
      break;
    case 27:
      lcd.setCursor(0, 0);
      lcd.print("the cinema");
      lcd.setCursor(0, 1);
      lcd.print("of Liberty");
      break;
    case 28:
      lcd.setCursor(0, 0);
      lcd.print("he received");
      lcd.setCursor(0, 1);
      lcd.print("a bike");
      break;
    case 29:
      lcd.setCursor(0, 0);
      lcd.print("and a pair");
      lcd.setCursor(0, 1);
      lcd.print("of old shoes");
      break;
    case 30:
      lcd.print("metan lungs");
      break;
    case 31:
      lcd.print("light at the end");
      break;
    case 32:
      lcd.print("of a tunnel");
      break;
    case 33:
      lcd.print("dust like raster");
      break;
    case 34:
      lcd.setCursor(0, 0);
      lcd.print("dust like");
      lcd.setCursor(0, 1);
      lcd.print("burning");
      break;
    case 35:
      lcd.print("works of Marx");
      break;
    case 36:
      lcd.print("compete");
      break;
    case 37:
      lcd.setCursor(0, 0);
      lcd.print("with");
      lcd.setCursor(0, 1);
      lcd.print("the spectacle");
      break;
    case 38:
      lcd.print("inside me");
      break;
    case 39:
      lcd.print("- - -");
      break;
    case 40:
      lcd.print("screen");
      break;
    case 41:
      lcd.print("brick");
      break;
    case 42:
      lcd.print("van");
      break;
    case 43:
      lcd.print("have no light");
      break;
    case 44:
      lcd.setCursor(0, 0);
      lcd.print("inside");
      lcd.setCursor(0, 1);
      lcd.print("the tunnel");
      break;
    case 45:
      lcd.print("acid protect");
      break;
    case 46:
      lcd.print("against speed");
      break;
    case 47:
      lcd.print("tomorrow 298%");
      break;
    case 48:
      lcd.setCursor(0, 0);
      lcd.print("of normative");
      lcd.setCursor(0, 1);
      lcd.print("efficiency");
      break;
    case 49:
      lcd.setCursor(0, 0);
      lcd.print("knowledge");
      lcd.setCursor(0, 1);
      lcd.print("accelerates");
      break;
    case 50:
      lcd.print("past comes");
      break;
    case 51:
      lcd.setCursor(0, 0);
      lcd.print("back in");
      lcd.setCursor(0, 1);
      lcd.print("a recursive loop");
      break;
    case 52:
      lcd.setCursor(0, 0);
      lcd.print("the statue");
      lcd.setCursor(0, 1);
      lcd.print("of Lenin");
      break;
    case 53:
      lcd.setCursor(0, 0);
      lcd.print("twisted");
      lcd.setCursor(0, 1);
      lcd.print("in Zbrush along");
      break;
    case 54:
      lcd.setCursor(0, 0);
      lcd.print("Fibonacci");
      lcd.setCursor(0, 1);
      lcd.print("sequence");
      break;
    case 55:
      lcd.setCursor(0, 0);
      lcd.print("Fibonacci");
      lcd.setCursor(0, 1);
      lcd.print("sequence");
      break;
    case 56:
      lcd.setCursor(0, 0);
      lcd.print("capitalism");
      lcd.setCursor(0, 1);
      lcd.print("has no heart");
      break;
    case 57:
      lcd.setCursor(0, 0);
      lcd.print("communism");
      lcd.setCursor(0, 1);
      lcd.print("has no soul");
      break;
    case 58:
      lcd.setCursor(0, 0);
      lcd.print("capitalism");
      lcd.setCursor(0, 1);
      lcd.print("has no heart");
      break;
    case 59:
      lcd.setCursor(0, 0);
      lcd.print("a roll");
      lcd.setCursor(0, 1);
      lcd.print("with rotten meat");
      break;
    case 60:
      lcd.print("of dead animal");
      break;
    case 61:
      lcd.print("forever");
      break;


  }

}



void loop()
{

  if (Serial.available())
  {
    value = Serial.read();


    if (value = 255)
    {
  


      lcdStuff();
    }

  }

  long duration, distance;
  if (rangeEnabled)
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(15);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance >= 400 || distance <= 2) {
      distance = -1;
    }
  }

  Serial.print(distance);
  Serial.print(" ");
  Serial.print(analogRead(A0));
  Serial.println();

  delay(2);
}

