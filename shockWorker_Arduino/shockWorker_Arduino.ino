// in total we have 12 digital pins on arduino to use

// so it is possible to arrange that LCD takes 7 of them
// shift registers take 3 of them
// and the ultrasonic range sensor takes 2 of them

// then the termometer and photocell take up 2 of analogue pins

// I have given up however the range sensor in this version of the sketch 
// as it was causing audible latency in the serial communication triggering the solenoids
// and broken the installation down to two micro-controllers integrated via Max/MSP on a
// computer 

// As such I have left for the Arduino code below to handle the shift registers as well
// as one photo-cell and one temperature sensor

int value;


// the array below is repsonsible for patching the indices of solenopoids
// on the shift registers. For the better layout organisation and 
// aesthetics of my solenoid driver board I have soldered I have placed
// the "indices" of pins of the two darlington arrays kind of in reverse 
// to the pins of the shift registers 
int sp[] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5};

// ORIGINAL SHIFT REGISTERS EXAMPLE
int latchPin = 8;  // green
int clockPin = 12; // 
int dataPin = 11; //

int numOfRegisters = 2;
byte* registerState;

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
}

void loop()
{

  // I am reading the control data for the solenoids sent from Max/MSP patch
  // one integer at a time
  if (Serial.available())
  {
    value = Serial.read();


    int v = value & 15;  // 4 lowest bits of integer represnt solenoid index
    int s = (value & 64) >> 6;  // 6th bit represents on/off state 

    // we change state of solenoid based on received data
    pinState(v, s);
  }

  // sending the temperature and photo-cell data to Max/MSP patch on the computer 
  Serial.print(temperature());
  Serial.print(" ");
  Serial.print(analogRead(A0));
  Serial.println();


  // triying out generating tones based on light as a back-drop
  // to solenoids (althogh it runs quite quitet) 
  // based on Light Theremin example from the Arduino Project Book 
  tone(3, analogRead(A0) * 5, 20);
  delay(2);
}

// Three funcitons interfacing control of solenoids via the shift registers
// I have maily used pinState in this version of the code
void pinOn(int n)
{
  regWrite(sp[n], HIGH); // set the respective solenoid pin on
}

void pinOff(int n)
{
  regWrite(sp[n], LOW); // set the respective solenoid pin on
}

void pinState(int n, int s)
{
  // we write to shift registers considering recent change of state
  // on of the solenoids below
  // the index of solenoid is patched to relevant pin numbers we stored
  // in our array sp[] (why is this? because solenoid 0 is not necessary on the shift registers pin 0, due to my soldeing optimisation it occured on pin 8 and so on)
  regWrite(sp[n], s);
}

// The code in the function below handles
// the two linked shift registers 
//  I have adapted it from the article: 
// http://www.instructables.com/id/Arduino-16-LEDs-using-two-74HC595-shift-registers-/
// by JanisR4
void regWrite(int pin, bool state) {
  //Determines register
  int reg = pin / 8;
  //Determines pin for actual register
  int actualPin = pin - (8 * reg);

  //Begin session
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < numOfRegisters; i++) {
    //Get actual states for register
    byte* states = &registerState[i];

    //Update state
    if (i == reg) {
      bitWrite(*states, actualPin, state);
    }

    //Write
    shiftOut(dataPin, clockPin, MSBFIRST, *states);
  }

  //End session
  digitalWrite(latchPin, HIGH);
}

// function belows calcualtes realative temparature from the voltage 
// in reading of the temperature sensor of the Arduino kit. 
// code based on the Love-o-meter from the Ardunino Project Book
float temperature()
{
  int sensorVal = analogRead(A0);

  float voltage = (sensorVal / 1024.0) * 5.0;

  return (voltage - .5) * 100;
}


