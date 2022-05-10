
#include <Stepper.h>
#include <math.h>
#include <Servo.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int stepsPerRevolution = 2038;
const int rpm = 12;
const int servoPin = 6;
const int buttonPin = 4;     // the number of the pushbutton pin
const int startButtonPin = 3;     // the number of the pushbutton pin
const int unlockButton = 2; // the number of the pushbutton pin

const float stn = 50.95;   // how many steps equal one number on a 40 number combo (2038/40)
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
bool startButtonDebounce = false;
bool comboFound = false;
// Create a variable to store the servo position:
int angle = 0;
// used to get back to 0 after each combination to avoid error creep
int stepsFromZero = 0;
String currentCombo;
Servo myservo;
Stepper stepper1 = Stepper(stepsPerRevolution, 8, 10, 9, 11);


void setup() {
  pinMode(unlockButton, INPUT_PULLUP);
  digitalWrite(unlockButton, HIGH);
  attachInterrupt(digitalPinToInterrupt(unlockButton), codeFound, CHANGE); // trigger when button pressed, but not when released.

  stepper1.setSpeed(rpm);
  myservo.attach(servoPin);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(startButtonPin, INPUT);
  Serial.begin(9600);
  myservo.write(0);
  Serial.println("Program started!");
}

void loop() {

  display.clearDisplay();
  display.setTextSize(1);          // text size
  display.setTextColor(SSD1306_WHITE);     // text color
  display.setCursor(10, 10);        // position to display
  display.println("Hello World!"); // text to display
  display.display();               // show on OLED

  if (digitalRead(startButtonPin) == HIGH && startButtonDebounce == false) {
    startButtonDebounce = true; // toggle button debounce
    Serial.println("Button Pressed");
    String first_combo_sequence[20] = {"0-2-0", "1-3-1", "2-4-2", "3-5-3", "0-2-4", "1-3-5", "2-4-6", "3-5-7", "0-2-8", "1-3-9", "2-4-10", "3-5-11", "0-2-12", "1-3-13", "2-4-14", "3-5-15", "0-2-16", "1-3-17", "2-4-18", "3-5-19"};
    //For w. e reason I run out of memory without errors if I have more than 20 combinations so run above line then comment it out and uncomment below line.
    //    String first_combo_sequence[20] = { "0-2-20", "1-3-21", "2-4-22", "3-5-23", "0-2-24", "1-3-25", "2-4-26", "3-5-27", "0-2-28", "1-3-29", "2-4-30", "3-5-31", "0-2-32", "1-3-33", "2-4-34", "3-5-35", "0-2-36", "1-3-37", "2-4-38", "3-5-39"};
    for (int n = 0; n < 40; n++) {
      Serial.println("first for loop");
      Serial.println( first_combo_sequence[n]);
      int firstNumber = getValue(first_combo_sequence[n], '-', 0).toInt();
      int secondNumber = getValue(first_combo_sequence[n], '-', 1).toInt();
      int ogSecondNumber = getValue(first_combo_sequence[n], '-', 1).toInt();
      int thirdNumber = getValue(first_combo_sequence[n], '-', 2).toInt();
      Serial.println(first_combo_sequence[n]);
      Serial.println(secondNumber);

      while (firstNumber < 40) {
        while (secondNumber < 40) {
          Serial.println("decombo:");
          Serial.println(firstNumber);
          Serial.println(secondNumber);
          Serial.println(thirdNumber);
          Serial.println("-----");
          decombo(String(firstNumber) + "-" + String(secondNumber) + "-" + String(thirdNumber));
          secondNumber = secondNumber + 4;
        }
        firstNumber = firstNumber + 4;
        secondNumber = ogSecondNumber;
      }
    }
  }
  // this will prevent subsequent button presses
  if (digitalRead(startButtonPin) == LOW && startButtonDebounce == true) {
    startButtonDebounce = false;
  }

  // Button used to get to 0
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn Stepper
    stepper1.step(-51);
    Serial.println("move 1 number right");
    delay(100);
  }

}

void decombo(String sequence) {
  Serial.println("sequence:");
  Serial.println(sequence);
  currentCombo = sequence;
  display.clearDisplay();
  display.setTextSize(1);          // text size
  display.setTextColor(SSD1306_WHITE);     // text color
  display.setCursor(2, 2);        // position to display
  display.println("Attempting:"); // text to display
  display.setCursor(3, 15);        // position to display
  display.setTextSize(2);
  display.println(sequence);
  display.display();               // show on OLED
  int firstNumber = getValue(sequence, '-', 0).toInt();
  int secondNumber = getValue(sequence, '-', 1).toInt();
  int thirdNumber = getValue(sequence, '-', 2).toInt();
  delay(200);
  // turn right twice to clear lock
  //    Serial.println("resetting by turning twice to 0");
  stepper1.step(-stepsPerRevolution * 2);
  delay(200);
  // turn to first number - negative is right
  //    Serial.println("turning to first number");
  //    Serial.println(firstNumber);
  turnToNumber(firstNumber - 40);
  // calculate second number - one full rev left first + positive number
  //    int a = secondNumber - firstNumber;
  // if negative turn positive
  //    int b = a > 0 ? a*1 : a*-1 ;
  //    //    Serial.println("calculation for b:");
  //    Serial.println(b);
  //turn to second number
  int a = 0;
  if (firstNumber > secondNumber ) {
    a = 40;
  }
  //    Serial.println("turning to second number");
  //    Serial.println(secondNumber);
  turnToNumber(a + (40 - (firstNumber - secondNumber )));
  //    Serial.println("turning to third number");
  //    Serial.println(thirdNumber);
  //    Serial.println("third - second");
  //    Serial.println(thirdNumber - secondNumber);
  //turn to third number
  if (secondNumber > thirdNumber) {
    turnToNumber(thirdNumber - secondNumber);
  }
  else {
    turnToNumber((thirdNumber - secondNumber) - 40);
  }

  // Try opening lock
  myservo.write(100);
  // Check if button pressed here
  //...TODO....
  delay(1000);
  myservo.write(10);
  delay(2000);

  // Check if combo is correct
  if (comboFound) {
    display.clearDisplay();
    display.setTextSize(1);          // text size
    display.setTextColor(SSD1306_WHITE);     // text color
    display.setCursor(2, 2);        // position to display
    display.println("Code is:"); // text to display
    display.setCursor(3, 15);        // position to display
    display.setTextSize(2);
    display.println(sequence);
    display.display();               // show on OLED
    exit(0);
  }

  // return to zero
  //    Serial.println("returning to zero");
  //    Serial.println(-stepsFromZero);
  stepper1.step(-stepsFromZero);
  // reset steps from zero because we are on zero
  stepsFromZero = 0;
  delay(500);

}

void turnToNumber(int number) {
  float exactSteps = stn * number;
  //  Serial.println("exact steps");
  //  Serial.println(exactSteps);
  int steps = round(exactSteps);
  //  Serial.println("steps");
  //  Serial.println(steps);
  stepsFromZero = stepsFromZero + steps;
  //  Serial.println("steps from zero");
  //  Serial.println(stepsFromZero);
  stepper1.step(steps);
  delay(200);
}

void codeFound() {
  Serial.println("Combo found!");
  Serial.println(currentCombo);

  comboFound = true;
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
