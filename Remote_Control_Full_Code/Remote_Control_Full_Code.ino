#include <IBusBM.h>

IBusBM ibus;

const int D1_RPWM = 5;
const int D1_LPWM = 6;
const int D1_REN  = 7;
const int D1_LEN  = 8;

const int D2_RPWM = 9;
const int D2_LPWM = 10;
const int D2_REN  = 11;
const int D2_LEN  = 12;


void setup(){
  Serial.begin(115200);

  // FS-iA10B iBUS
  // Mega RX1 = Pin 19
  Serial1.begin(115200);
  ibus.begin(Serial1);


  // Driver 1
  pinMode(D1_RPWM, OUTPUT);
  pinMode(D1_LPWM, OUTPUT);
  pinMode(D1_REN, OUTPUT);
  pinMode(D1_LEN, OUTPUT);

  // Driver 2
  pinMode(D2_RPWM, OUTPUT);
  pinMode(D2_LPWM, OUTPUT);
  pinMode(D2_REN, OUTPUT);
  pinMode(D2_LEN, OUTPUT);

  // Enable both BTS7960 drivers
  digitalWrite(D1_REN, HIGH);
  digitalWrite(D1_LEN, HIGH);

  digitalWrite(D2_REN, HIGH);
  digitalWrite(D2_LEN, HIGH);


  // Start with motors stopped
  stopRobot();
    
  Serial.println("Mecanum Robot Ready");
}


void loop(){
  // CH1 = Left / Right
  // CH2 = Forward / Backward

  int ch1 = ibus.readChannel(0);
  int ch2 = ibus.readChannel(1);

  int speed = map(max(abs(ch1 - 1500), abs(ch2 - 1500)), 0, 500, 0, 255);

  speed = constrain(speed, 0, 255);

  Serial.print("CH1: ");
  Serial.print(ch1);

  Serial.print(" | CH2: ");
  Serial.print(ch2);

  Serial.print(" | Speed: ");
  Serial.println(speed);

  // Forward
  if (ch2 > 1600 && ch1 >= 1400 && ch1 <= 1600){
    forward(speed);
  }

  // Backward
  else if (ch2 < 1400 && ch1 >= 1400 && ch1 <= 1600){
    backward(speed);
  }

  // Diagonal Front Right
  else if (ch2 > 1600 && ch1 > 1600){
    diagonalFrontRight(speed);
  }

  // Diagonal Front Left
  else if (ch2 > 1600 && ch1 < 1400){
    diagonalFrontLeft(speed);
  }

  // Diagonal Back Right
  else if (ch2 < 1400 && ch1 > 1600){
    diagonalBackRight(speed);
  }

  // Diagonal Back Left
  else if (ch2 < 1400 && ch1 < 1400){
    diagonalBackLeft(speed);
  }

  // Stop
  else{
    stopRobot();
  }

  delay(20);
}

// =====================================================
// BTS7960 MOTOR CONTROL
// speed = -255 to +255
//
// Positive = Forward
// Negative = Backward
// Zero     = Stop
// =====================================================

void driveBTS(int RPWM, int LPWM, int speed){
  speed = constrain(speed, -255, 255);

  if (speed > 0){
    // Forward
    analogWrite(RPWM, speed);
    analogWrite(LPWM, 0);
  }

  else if (speed < 0){
    // Backward
    analogWrite(RPWM, 0);
    analogWrite(LPWM, abs(speed));
  }

  else{
    // Stop
    analogWrite(RPWM, 0);
    analogWrite(LPWM, 0);
  }
}


void forward(int speed){
  driveBTS(D1_RPWM, D1_LPWM, speed);
  driveBTS(D2_RPWM, D2_LPWM, -speed);
}

void backward(int speed){
  driveBTS(D1_RPWM, D1_LPWM, -speed);
  driveBTS(D2_RPWM, D2_LPWM, speed);
}

void diagonalFrontRight(int speed){
  driveBTS(D1_RPWM, D1_LPWM, speed);
  driveBTS(D2_RPWM, D2_LPWM, 0);
}

void diagonalFrontLeft(int speed){
  driveBTS(D1_RPWM, D1_LPWM, 0);
  driveBTS(D2_RPWM, D2_LPWM, -speed);
}

void diagonalBackRight(int speed){
  driveBTS(D1_RPWM, D1_LPWM, -speed);
  driveBTS(D2_RPWM, D2_LPWM, 0);
}

void diagonalBackLeft(int speed){
  driveBTS(D1_RPWM, D1_LPWM, 0);
  driveBTS(D2_RPWM, D2_LPWM, speed);
}

// // STOP

// void stopRobot(){
//   driveBTS(D1_RPWM, D1_LPWM, 0);
//   driveBTS(D2_RPWM, D2_LPWM, 0);
// }


// // FORWARD

// void forward(int speed){
//   driveBTS(D1_RPWM, D1_LPWM, speed);
//   driveBTS(D2_RPWM, D2_LPWM, speed);
// }


// // BACKWARD

// void backward(int speed)
// {
//   driveBTS(D1_RPWM, D1_LPWM, -speed);
//   driveBTS(D2_RPWM, D2_LPWM, -speed);
// }


// // DIAGONAL FRONT RIGHT

// // FR + RL → Forward
// // FL + RR → Stop

// void diagonalFrontRight(int speed){
//   driveBTS(D1_RPWM, D1_LPWM, speed);
//   driveBTS(D2_RPWM, D2_LPWM, 0);
// }


// // DIAGONAL FRONT LEFT

// // FL + RR → Forward
// // FR + RL → Stop

// void diagonalFrontLeft(int speed){
//   driveBTS(D1_RPWM, D1_LPWM, 0);
//   driveBTS(D2_RPWM, D2_LPWM, speed);
// }


// // DIAGONAL BACK RIGHT

// // FR + RL → Backward
// // FL + RR → Stop

// void diagonalBackRight(int speed){
//   driveBTS(D1_RPWM, D1_LPWM, -speed);
//   driveBTS(D2_RPWM, D2_LPWM, 0);
// }


// // DIAGONAL BACK LEFT

// // FL + RR → Backward
// // FR + RL → Stop

// void diagonalBackLeft(int speed){
//   driveBTS(D1_RPWM, D1_LPWM, 0);
//   driveBTS(D2_RPWM, D2_LPWM, -speed);
// }
