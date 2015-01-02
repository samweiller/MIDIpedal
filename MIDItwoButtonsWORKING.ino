#include <SoftwareSerial.h>

 const int switchPinA = 10;  // The switch is on Arduino pin 10
 const int switchPinB = 8;
 const int LEDpin = 13;     //  Indicator LED

  // Variables: 
  byte note = 0;              // The MIDI note value to be played
  int AnalogValue = 0;        // value from the analog input
  int lastNotePlayed = 0;     // note turned on when you press the switch
  int lastSwitchState = 0;    // state of the switch during previous time through the main loop
  int currentSwitchStateA = 0;
  int currentSwitchStateB = 0;
  int noteA = 0;
  int noteB = 0;
  int lastSwitchStateA = 0;
  int lastSwitchStateB = 0;

 //software serial
 SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX


  void setup() {
    //  set the states of the I/O pins:
    pinMode(switchPinA, INPUT);
    pinMode(switchPinB, INPUT);
    pinMode(LEDpin, OUTPUT);
    //  Set MIDI baud rate:
   Serial.begin(9600);
    blink(3);

     midiSerial.begin(31250);

  }

  void loop() {
    //  My potentiometer gave a range from 0 to 1023:
    // AnalogValue = analogRead(0);
    //  convert to a range from 0 to 127:
    noteA = 100;
    noteB = 95;
    currentSwitchStateA = digitalRead(switchPinA);
    currentSwitchStateB = digitalRead(switchPinB);
    // Check to see that the switch is pressed:
    if (currentSwitchStateA == 1 || currentSwitchStateB == 1) {
      //  check to see that the switch wasn't pressed last time
      //  through the main loop:
      if (lastSwitchStateA == 0 && lastSwitchStateB == 0) {
        // set the note value based on the analog value, plus a couple octaves:
        // note = note + 60;
        // start a note playing:
        if (currentSwitchStateA == 1) {
          note = noteA;
        }
        if (currentSwitchStateB == 1) {
          note = noteB;
        }
        noteOn(0x90, note, 0x40);
        // save the note we played, so we can turn it off:
        lastNotePlayed = note;
        digitalWrite(LEDpin, HIGH);
      }
    }
    else {   // if the switch is not pressed:
      //  but the switch was pressed last time through the main loop:
      if (lastSwitchStateA == 1 || lastSwitchStateB == 1) {
        //  stop the last note played:
        noteOn(0x90, lastNotePlayed, 0x00);
        digitalWrite(LEDpin, LOW);
      }
    }

    //  save the state of the switch for next time
    //  through the main loop:
    lastSwitchStateA = currentSwitchStateA;
    lastSwitchStateB = currentSwitchStateB;
  }

  //  plays a MIDI note.  Doesn't check to see that
  //  cmd is greater than 127, or that data values are  less than 127:
  void noteOn(byte cmd, byte data1, byte  data2) {
    midiSerial.write(cmd);
   midiSerial.write(data1);
    midiSerial.write(data2);


   //prints the values in the serial monitor so we can see what note we're playing
   // Serial.write("cmd: ");
     Serial.write(cmd);
       //Serial.write(", data1: ");
   Serial.write(data1);
     // Serial.write(", data2: ");
    Serial.write(data2);
  }

  // Blinks an LED 3 times
  void blink(int howManyTimes) {
    int i;
    for (i=0; i< howManyTimes; i++) {
      digitalWrite(LEDpin, HIGH);
      delay(100);
      digitalWrite(LEDpin, LOW);
      delay(100);
    }
  }
