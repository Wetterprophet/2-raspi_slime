#define XDIR_PIN 9
#define XSTEP_PIN 8
#define YDIR_PIN 11
#define YSTEP_PIN 10
#define XMAX_PIN 3
#define XMIN_PIN 2
#define YMAX_PIN 5
#define YMIN_PIN 4

int XDIR = LOW;
int YDIR = LOW;
int XTURNS = 0;
int YTURNS = 0;
int XLENGTH = 0;
int YLENGTH = 0;


//speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger,
//my y-stepper-driver can run between 0,01 and 0,5; 0,19 is perfect and silent, x-driver needs more speed
float XSPEED = 0.7;
float YSPEED = 0.2;


void setup() {
  Serial.begin(9600);
  pinMode(XDIR_PIN, OUTPUT);
  pinMode(XSTEP_PIN, OUTPUT);
  pinMode(YDIR_PIN, OUTPUT);
  pinMode(YSTEP_PIN, OUTPUT);
  pinMode(XMAX_PIN, INPUT);
  pinMode(XMIN_PIN, INPUT);
  pinMode(YMAX_PIN, INPUT);
  pinMode(YMIN_PIN, INPUT);
  xSetup();



 
}



void loop() {
  
  
  
}



void rotate(int steps, float speed, int dir, int DIR_PIN, int STEP_PIN) {
  //rotate a specific number of microsteps (8 microsteps per step) - (negative for reverse movement)


  digitalWrite(DIR_PIN, dir);

  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {

    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}






void xSetup() {
  //find out how long the x-axis is:
  XTURNS = 0;
  while (digitalRead(XMIN_PIN) == LOW) {
    rotate(800, XSPEED, HIGH, XDIR_PIN, XSTEP_PIN);
    XTURNS++;
  }
  Serial.print("X-Motor moved ");
  Serial.print(XTURNS);
  Serial.println(" turns backwards");
  XTURNS = 0;

  while (digitalRead(XMAX_PIN) == LOW) {
    rotate(800, XSPEED, LOW, XDIR_PIN, XSTEP_PIN);
    XTURNS++;
  }
  XLENGTH = XTURNS;
  Serial.print("X-Motor moved ");
  Serial.print(XTURNS);
  Serial.println(" turns forward");





//find out, how long the y-axis is:
  YTURNS = 0;
  while (digitalRead(YMIN_PIN) == LOW) {
    rotate(800, YSPEED, HIGH, YDIR_PIN, YSTEP_PIN);
    YTURNS++;
  }
  Serial.print("Y-Motor moved ");
  Serial.print(YTURNS);
  Serial.println(" turns backwards");
  YTURNS = 0;

  while (digitalRead(YMAX_PIN) == LOW) {
    rotate(800, YSPEED, LOW, YDIR_PIN, YSTEP_PIN);
    YTURNS++;
  }
  YLENGTH = YTURNS;
  Serial.print("Y-Motor moved ");
  Serial.print(YTURNS);
  Serial.println(" turns forward");



//rotate to the middle of the canvas:
  for (int i=0; i<XTURNS; i++){
    rotate(800, XSPEED, HIGH, XDIR_PIN, XSTEP_PIN);
  }
  for (int j=0; j<YTURNS; j++){
    rotate(800, YSPEED, HIGH, YDIR_PIN, YSTEP_PIN);
  }
}




