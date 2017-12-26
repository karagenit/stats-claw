#include <elapsedMillis.h>

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

#define LIMIT_X_MIN A5 //home position, over prize drop-off
#define LIMIT_X_MAX A4
#define LIMIT_Y_MIN 13 //home position, over prize drop-off
#define LIMIT_Y_MAX 12
//TODO: to save pins, instead of having Z limit switches, we can raise/lower by time (since it's always just full up or full down)
#define LIMIT_Z_MIN 8 //totally raised
#define LIMIT_Z_MAX 7
//TODO: CLAW limits? right now it just goes by 3 seconds

#define MOTOR_X 9
#define MOTOR_X_DIR 6 //HIGH direction is AWAY from MIN, towards MAX
#define MOTOR_Y 10
#define MOTOR_Y_DIR 5
#define MOTOR_Z 11
#define MOTOR_Z_DIR 4
#define MOTOR_CLAW 3
#define MOTOR_CLAW_DIR 2 //forwards is open, backwards is close

#define BUTTON_DROP A3
#define BUTTON_START A2

#define TIME_MAX 90000 //90,000 milliseconds = 90 seconds
#define TIME_CLAW 3000 //time to actuate claw... 3 seconds

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

  Serial.begin(9600);
  Serial.println("Connected!");
}

void loop() {
  Serial.println("State: Disabled");
  disabled(); //awaits press of "Start" button
  //TODO: before play() should we home/raise claw/open claw to assure the state is correct?
  Serial.println("State: Playing");
  play(); //allows operator control
  Serial.println("State: End Game");
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

void readJoystick() { //TODO: tune the analog values... pots might not give 0-1023
  int xval = map(analogRead(JOYSTICK_X), 0, 1023, -255, 255);
  int yval = map(analogRead(JOYSTICK_Y), 0, 1023, -255, 255);
  writeX(xval);
  writeY(yval);
}

//PWM value to write to X-axis motors, -255 to 255
void writeX(int pwm) {
  boolean direction = pwm >= 0;
  int output = abs(pwm);

  if(direction) {
    digitalWrite(MOTOR_X_DIR, HIGH);
  } else {
    digitalWrite(MOTOR_X_DIR, LOW);
  }

  if(direction && !digitalRead(LIMIT_X_MAX)) {
    analogWrite(MOTOR_X, output);
  } else if (!direction && !digitalRead(LIMIT_X_MIN)) {
    analogWrite(MOTOR_X, output);
  } else {
    analogWrite(MOTOR_X, 0);
  }
}

//PWM value to write to X-axis motors, -255 to 255
void writeY(int pwm) {
  boolean direction = pwm >= 0;
  int output = abs(pwm);

  digitalWrite(MOTOR_Y_DIR, direction);

  if(direction && !digitalRead(LIMIT_Y_MAX)) {
    analogWrite(MOTOR_Y, output);
  } else if (!direction && !digitalRead(LIMIT_Y_MIN)) {
    analogWrite(MOTOR_Y, output);
  } else {
    analogWrite(MOTOR_Y, 0);
  }
}

void endgame() {
  dropClaw();
  closeClaw();
  raiseClaw();
  goHome();
  openClaw();
}

void dropClaw() {
  digitalWrite(MOTOR_Z_DIR, HIGH);
  while(!digitalRead(LIMIT_Z_MAX)) {
    analogWrite(MOTOR_Z, 255);
  }
  analogWrite(MOTOR_Z, 0);
}

void raiseClaw() {
  digitalWrite(MOTOR_Z_DIR, LOW);
  while(!digitalRead(LIMIT_Z_MIN)) {
    analogWrite(MOTOR_Z, 255);
  }
  analogWrite(MOTOR_Z, 0);
}

void closeClaw() {
  elapsedMillis timeElapsed = 0;
  digitalWrite(MOTOR_CLAW_DIR, LOW);
  while(timeElapsed < TIME_CLAW) {
    analogWrite(MOTOR_CLAW, 255);
  }
  analogWrite(MOTOR_CLAW, 0);
}

void openClaw() {
  elapsedMillis timeElapsed = 0;
  digitalWrite(MOTOR_CLAW_DIR, HIGH);
  while(timeElapsed < TIME_CLAW) {
    analogWrite(MOTOR_CLAW, 255);
  }
  analogWrite(MOTOR_CLAW, 0);
}

void goHome() {
  //TODO: do both X & Y together
  digitalWrite(MOTOR_X_DIR, LOW);
  while(!digitalRead(LIMIT_X_MIN)) {
    analogWrite(MOTOR_X, 255);
  }
  analogWrite(MOTOR_X, 0);

  digitalWrite(MOTOR_Y_DIR, LOW);
  while(!digitalRead(LIMIT_Y_MIN)) {
    analogWrite(MOTOR_Y, 255);
  }
  analogWrite(MOTOR_Y, 0);
}
