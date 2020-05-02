// Adapted from https://learn.sparkfun.com/tutorials/soil-moisture-sensor-hookup-guide
// and https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-15-using-an-lcd

// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);


/********************************************************
 * Change these values based on your calibration values
 *******************************************************/
int thresholdUp = 400;
int thresholdDown = 250;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:

int soilPin = A0;
int soilPower = 7;//Variable for Soil moisture Power

int val = 0;

void setup()
{
  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:

  lcd.begin(16, 2);

  // Data sent to the display will stay there until it's
  // overwritten or power is removed. This can be a problem
  // when you upload a new sketch to the Arduino but old data
  // remains on the display. Let's clear the LCD using the
  // clear() command from the LiquidCrystal library:

  lcd.clear();

  // Now we'll display a message on the LCD!

  // Just as with the Arduino IDE, there's a cursor that
  // determines where the data you type will appear. By default,
  // this cursor is invisible, though you can make it visible
  // with other library commands if you wish.

  // When the display powers up, the invisible cursor starts
  // on the top row and first column.

  lcd.print("hello, world!");

  // Adjusting the contrast (IMPORTANT!)

  // When you run the sketch for the first time, there's a
  // very good chance you won't see anything on the LCD display.
  // This is because the contrast likely won't be set correctly.
  // Don't worry, it's easy to set, and once you set it you won't
  // need to change it again.

  // Run the sketch, then turn the potentiometer until you can
  // clearly see the "hello, world!" text. If you still can't
  // see anything, check all of your connections, and ensure that
  // the sketch was successfully uploaded to the Arduino.


  pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
}

void loop(){
  // Here we are declaring a string, which are lines of words,
  // and we want DisplayWords to be the words displayed on
  // the LCD screen, which will change based on whether the soil
  // wet or dry based on our threshold values above.
  String DisplayWords;

  // We need to set up a pin to get the value that the soil
  // moisture sensor is outputting, so sensorValue will get the
  // analog value from the sensor pin A0 on the redboard that we
  // set up earlier.

  int sensorValue;
  sensorValue = readSoil();

  lcd.clear();

  // move cursor to beginning of first line on LCD:

  lcd.setCursor(0,0);

  //Write what we want to desplay on the screen:
  lcd.print("Water Level: ");
  lcd.print(sensorValue); //Using .print instead of .write for values

  // Now we are going to check if the water level is below a
  // out thresholdDown value we set earlier, and if it is have
  // words "Dry, Water it!" display one column over on the first
  // row:

  // move cursor to beginning of second line on LCD:
  lcd.setCursor(0,1);

  if (sensorValue <= thresholdDown){

    DisplayWords = "Dry, Water it!";
    lcd.print(DisplayWords);

  } else if (sensorValue >= thresholdUp){

    DisplayWords = "Wet, Leave it!";
    lcd.print(DisplayWords);

  // Otherwise if it is inbetween the two values we want it to
  // the display it had, so if our soil was really wet and drying
  // the words would only change to "Dry, Water it!" when it got to the lower threshold
  // (thresholdDown), but if it was dry and getting wetter the words
  // would only change to "Wet, Leave it!" when it got to the upper
  // threshold (thresholdUp_):

  } else {

    lcd.print(DisplayWords);
  }

  delay(1000); //wait for a second, so it is easier to read
}

//This is a function used to get the soil moisture content
int readSoil()
{
  digitalWrite(soilPower, HIGH); //turn D7 "On"
  delay(10); //wait 10 milliseconds
  val = analogRead(soilPin); //Read the SIG value form sensor
  digitalWrite(soilPower, LOW); //turn D7 "Off"
  return val; //send current moisture value
}