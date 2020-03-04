//ROBOT V1.5
//PWM Pins 3, 5, 6, 9, 10, 11
  
//H Bridge - ALL PWM PINS

#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9

int Buzzer = 10; //PWM
int weapon = 12;
//4 RC CHANNELS
int RCH1 = 14; //Weapon
int RCH2 = 15; //MOTOR B SPEED
int RCH3 = 16; //MOTOR A SPEED
int RCH4 = 17; //LEDs

int RCCH1Read; //Store PPM Values
int RCCH2Read; //Store PPM Values
int RCCH3Read; //Store PPM Values
int RCCH4Read; //Store PPM Values

//Speed
int motorSpeedA = 0; //Max of 255
int motorSpeedB = 0; //Max of 255


boolean ledToggle = false;
boolean weaponToggle = false;
//Arm Robot
void arm(){
  Serial.print("Ready...\n");
  //BEEP
  tone(Buzzer, 3000, 300);
  delay(300);
  tone(Buzzer, 1000, 300);
  delay(300);
  tone(Buzzer, 5000, 300);
  delay(300);
  while(RCCH3Read = pulseIn(RCH3, HIGH) <= 1950);
  tone(Buzzer, 5000, 300);
  delay(300);
  while(RCCH3Read = pulseIn(RCH3, HIGH) >= 1000);
  tone(Buzzer, 5000, 300);
  delay(300);
  while((RCCH3Read = pulseIn(RCH3, HIGH) >= 1550) || (RCCH3Read = pulseIn(RCH3, HIGH) <= 1450));
  tone(Buzzer, 3000, 300);
  delay(300);
}

void toggleWeapon(){
  if(weaponToggle == false){
      digitalWrite(weapon, LOW);
      weaponToggle = true;
  }
  else{
      digitalWrite(weapon, HIGH);
      weaponToggle = false;
  }
  delay(50);
}

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(RCH1, INPUT);
  pinMode(RCH2, INPUT);
  pinMode(RCH3, INPUT);
  pinMode(RCH4, INPUT);
  pinMode(weapon, OUTPUT);
  arm();
  Serial.println("Done");
}

void loop() {
  //PWM Pins 3, 5, 6, 9, 10, 11
  //Read Rx Input
  RCCH3Read = pulseIn(RCH3, HIGH); //Left Stick
  RCCH2Read = pulseIn(RCH2, HIGH); //Right Stick
  RCCH1Read = pulseIn(RCH1, HIGH); //Weapon

  //CH3 Forward - MOTOR A
  if(RCCH3Read > 1550){
    motorSpeedA = map(RCCH3Read,1550,2000,0,255);
    analogWrite(IN1, motorSpeedA);
    analogWrite(IN2, 0);
  }
  //Reverse
  else if(RCCH3Read< 1450){
    motorSpeedA = map(RCCH3Read,1450,994,0,255);
    analogWrite(IN1, 0);
    analogWrite(IN2, motorSpeedA);
  }
  //Neutral  Sticks
  else{
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
  }

  //CH2 Forward - MOTOR B
  if(RCCH2Read > 1550){
    motorSpeedB = map(RCCH2Read,1550,2000,0,255);
    analogWrite(IN3, motorSpeedB);
    analogWrite(IN4, 0);
  }
  //Reverse
  else if(RCCH2Read< 1450){
    motorSpeedB = map(RCCH2Read,1450,994,0,255);
    analogWrite(IN3, 0);
    analogWrite(IN4, motorSpeedB);
    }
  else{
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
  }

  //CH4 - Weapon
  if(RCCH1Read < 1000){
    toggleWeapon();
  }
  //Neutral  Sticks
  else{
    //Do Nothing
  }
}
