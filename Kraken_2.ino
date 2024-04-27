/*

Team RoboticGen

Code for Kraken 2

Version 4

*/

int rc_pulse_channel1;
int rc_pulse_channel2;
int rc_pulse_channel3;
int rc_pulse_channel4;
int rc_pulse_channel5;
int rc_pulse_channel6;

#define rc_channel1 3 //Turning rudder Min 986 Max 1970
#define rc_channel2 4 //Forward and Backward Min 986 Max 1970
#define rc_channel3 5 //Weapon Throttle Min 986 Max 1970
#define rc_channel4 6 // Left Rudder
#define rc_channel5 7 //Switch C Up 994 Mid 1488-1494 Down 1988
#define rc_channel6 8 //Switch A UP 986 Down 1970

#define LRelay1 22
#define LRelay2 24
#define RRelay1 26
#define RRelay2 28

#define weapon 36

#define buzzer 23

int maxSpeed = 100;

int throttle;
int rudder;
int weaponThrottle;

bool transmitterFlag = 0;



void setup() {

  pinMode(rc_channel1,INPUT);
  pinMode(rc_channel2,INPUT);
  pinMode(rc_channel3,INPUT);
  pinMode(rc_channel4,INPUT);
  pinMode(rc_channel5,INPUT);
  pinMode(rc_channel6,INPUT);


  pinMode(LRelay1,OUTPUT);
  pinMode(LRelay2,OUTPUT);
  pinMode(RRelay1,OUTPUT);
  pinMode(RRelay2,OUTPUT);
  pinMode(weapon,OUTPUT);

  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,HIGH);
  digitalWrite(weapon,HIGH);

  Serial.begin(9600);


}

void loop() {

  rc_pulse_channel1 = pulseIn(rc_channel1,HIGH,30000);
  rc_pulse_channel2 = pulseIn(rc_channel2,HIGH,30000);
  rc_pulse_channel3 = pulseIn(rc_channel3,HIGH,30000);
  rc_pulse_channel4 = pulseIn(rc_channel4,HIGH,30000);
  rc_pulse_channel5 = pulseIn(rc_channel5,HIGH,30000);
  rc_pulse_channel6 = pulseIn(rc_channel6,HIGH,30000);


  Serial.print(" ch1 = ");
  Serial.print(rc_pulse_channel1);
  Serial.print("ch2 = ");
  Serial.print(rc_pulse_channel2);
  Serial.print(" ch3 = ");
  Serial.print(rc_pulse_channel3);
  Serial.print(" ch4 = ");
  Serial.print(rc_pulse_channel4);
  Serial.print(" ch5 = ");
  Serial.print(rc_pulse_channel5);
  Serial.print(" ch6 = ");
  Serial.println(rc_pulse_channel6);


  // Turning Everything off if the receiver not connected
  if(rc_pulse_channel1 == 0 && rc_pulse_channel2 == 0 && rc_pulse_channel3 == 0 && rc_pulse_channel4 == 0 && rc_pulse_channel5 == 0 && rc_pulse_channel6 == 0){
   transmitterFlag = 0; 
  }
  else{
    transmitterFlag = 1;
  }


  // Throttle and Rudder
  if(transmitterFlag == 1){

  throttle = map(rc_pulse_channel5,994,1988,-maxSpeed,maxSpeed);
  rudder = map(rc_pulse_channel6,986,1970,-maxSpeed,maxSpeed);

  //Serial.println(throttle);

  if(throttle > maxSpeed){
    throttle = maxSpeed;
  }
  else if(throttle < -maxSpeed){
    throttle = -maxSpeed;
  }

  if(rudder > maxSpeed){
    rudder = maxSpeed;
  }
  else if(rudder < -maxSpeed){
    rudder = -maxSpeed;
  }


  if(rudder <= 10 && rudder >= -10){
    //run_robot(throttle,throttle);
    if(throttle > 50){
      go_forward();
    }
    else if(throttle < -50){
      go_backward();
    }
    else{
      stop();
    }
  }
  else if(rudder>30 && throttle > 10){
    forward_right();

  }
  else if(rudder<-30 && throttle > 10){
    forward_left();
  }
  else if(rudder>30 && throttle < -10){
    backward_right();

  }
  else if(rudder<-30 && throttle < -10){
    backward_left();
  }
  else if(throttle <= 10 && throttle >= -10){
    if(rudder>10){
      turn_right();
    }
    else if(rudder<-10){
      turn_left();
    }
  }


  if(rc_pulse_channel1 > 1800){
    //digitalWrite(relay1,HIGH);
    digitalWrite(weapon,LOW);

  }
  else{
    //digitalWrite(relay1,LOW);
    digitalWrite(weapon,HIGH);
  }


  }
  delay(10);
}



void go_forward(void){
  digitalWrite(LRelay1,LOW);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,LOW);
  digitalWrite(RRelay2,HIGH);
}

void go_backward(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,LOW);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,LOW);
}

void turn_left(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,LOW);
  digitalWrite(RRelay1,LOW);
  digitalWrite(RRelay2,HIGH);
}

void turn_right(void){
  digitalWrite(LRelay1,LOW);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,LOW);
}

void forward_left(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,LOW);
  digitalWrite(RRelay2,HIGH);
}

void forward_right(void){
  digitalWrite(LRelay1,LOW);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,HIGH);
}

void backward_left(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,LOW);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,HIGH);
}

void backward_right(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,LOW);
}

void stop(void){
  digitalWrite(LRelay1,HIGH);
  digitalWrite(LRelay2,HIGH);
  digitalWrite(RRelay1,HIGH);
  digitalWrite(RRelay2,HIGH);
}
