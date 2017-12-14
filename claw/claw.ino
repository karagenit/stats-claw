#include <elapsedMillis.h>

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

#define LIMIT_X_MIN 0
#define LIMIT_X_MAX 1
#define LIMIT_Y_MIN 2
#define LIMIT_Y_MAX 3
#define LIMIT_Z_MIN 4
#define LIMIT_Z_MAX 5

#define MOTOR_X 6
#define MOTOR_X_DIR 7
#define MOTOR_Y 8
#define MOTOR_Y_DIR 9
#define MOTOR_Z 10
#define MOTOR_Z_DIR 11
#define MOTOR_CLAW 12
#define MOTOR_CLAW_DIR 13

#define BUTTON_DROP 14
#define BUTTON_START 15

#define TIME_MAX 90000 //90,000 milliseconds = 90 seconds

void setup() {
  pinMode(JOYSTICK_X, INPUT); //Pullups?
  pinMode(JOYSTICK_Y, INPUT); //Pullups?

  pinMode(LIMIT_X_MIN, INPUT); //Pullups?
  pinMode(LIMIT_X_MAX, INPUT); //Pullups?
  pinMode(LIMIT_Y_MIN, INPUT); //Pullups?
  pinMode(LIMIT_Y_MAX, INPUT); //Pullups?
  pinMode(LIMIT_Z_MIN, INPUT); //Pullups?
  pinMode(LIMIT_Z_MAX, INPUT); //Pullups?

  pinMode(MOTOR_X, OUTPUT);
  pinMode(MOTOR_X_DIR, OUTPUT);
  pinMode(MOTOR_Y, OUTPUT);
  pinMode(MOTOR_Y_DIR, OUTPUT);
  pinMode(MOTOR_Z, OUTPUT);
  pinMode(MOTOR_Z_DIR, OUTPUT);
  pinMode(MOTOR_CLAW, OUTPUT);
  pinMode(MOTOR_CLAW_DIR, OUTPUT);

  pinMode(BUTTON_DROP, INPUT);
  pinMode(BUTTON_START, INPUT);
}

void loop() {
  disabled(); //awaits press of "Start" button
  play(); //allows operator control
  endgame(); //grabs stuff, returns to home, drops prize
}

void disabled() {
  //loop until the start button is pressed
  while(!digitalRead(BUTTON_START));
}

void play() {
  elapsedMillis timeElapsed = 0;

  //loop until either the "Drop" button is pressed or the time runs out
  while(!digitalRead(BUTTON_DROP) && timeElapsed < TIME_MAX) {
    readJoystick();
  }
}

void readJoystick() {
  int xval = map(analogRead(JOYSTICK_X), 0, 1023, -255, 255);
  int yval = map(analogRead(JOYSTICK_Y), 0, 1023, -255, 255);
  writeX(xval);
  writeY(yval);
}

//PWM value to write to X-axis motors, -255 to 255
void writeX(int pwm) {
  boolean direction = pwm >= 0;
  int output = abs(pwm);

  digitalWrite(MOTOR_X_DIR, direction);

  if(direction && !digitalRead(LIMIT_X_MAX)) {
    analogWrite(MOTOR_X, output);
  } else if (!direction && !digitalRead(LIMIT_X_MIN)) {
    analogWrite(MOTOR_X, output);
  } else {
    analogWrite(MOTOR_X, 0);
  }
}

//TODO writeY



