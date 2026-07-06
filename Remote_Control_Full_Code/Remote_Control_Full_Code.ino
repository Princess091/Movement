#include <IBusBM.h>

IBusBM ibus;

// =========================
// BTS7960 Driver 1 (FR + RL)
// =========================
const int D1_RPWM = 4;
const int D1_LPWM = 5;
const int D1_REN  = 6;
const int D1_LEN  = 7;

// =========================
// BTS7960 Driver 2 (FL + RR)
// =========================
const int D2_RPWM = 8;
const int D2_LPWM = 10;
const int D2_REN  = 11;
const int D2_LEN  = 12;

// =========================
// SETUP
// =========================
void setup()
{
    Serial.begin(115200);

    Serial1.begin(115200);
    ibus.begin(Serial1);

    pinMode(D1_RPWM, OUTPUT);
    pinMode(D1_LPWM, OUTPUT);
    pinMode(D1_REN, OUTPUT);
    pinMode(D1_LEN, OUTPUT);

    pinMode(D2_RPWM, OUTPUT);
    pinMode(D2_LPWM, OUTPUT);
    pinMode(D2_REN, OUTPUT);
    pinMode(D2_LEN, OUTPUT);

    digitalWrite(D1_REN, HIGH);
    digitalWrite(D1_LEN, HIGH);

    digitalWrite(D2_REN, HIGH);
    digitalWrite(D2_LEN, HIGH);

    stopRobot();
}

// =========================
// Generic Driver Function
// =========================
void driveDriver(int rpwm, int lpwm, int speed)
{
    speed = constrain(speed, -255, 255);

    if (speed > 0)
    {
        analogWrite(rpwm, speed);
        analogWrite(lpwm, 0);
    }
    else if (speed < 0)
    {
        analogWrite(rpwm, 0);
        analogWrite(lpwm, abs(speed));
    }
    else
    {
        analogWrite(rpwm, 0);
        analogWrite(lpwm, 0);
    }
}

// =========================
// Robot Movements
// =========================

void stopRobot()
{
    driveDriver(D1_RPWM, D1_LPWM, 0);
    driveDriver(D2_RPWM, D2_LPWM, 0);
}

void forward(int speed)
{
    driveDriver(D1_RPWM, D1_LPWM, speed);
    driveDriver(D2_RPWM, D2_LPWM, speed);
}

void backward(int speed)
{
    driveDriver(D1_RPWM, D1_LPWM, -speed);
    driveDriver(D2_RPWM, D2_LPWM, -speed);
}

void diagonalFrontRight(int speed)
{
    // FR + RL move
    driveDriver(D1_RPWM, D1_LPWM, speed);

    // FL + RR stop
    driveDriver(D2_RPWM, D2_LPWM, 0);
}

void diagonalFrontLeft(int speed)
{
    // FR + RL stop
    driveDriver(D1_RPWM, D1_LPWM, 0);

    // FL + RR move
    driveDriver(D2_RPWM, D2_LPWM, speed);
}

void diagonalBackRight(int speed)
{
    // FR + RL reverse
    driveDriver(D1_RPWM, D1_LPWM, -speed);

    // FL + RR stop
    driveDriver(D2_RPWM, D2_LPWM, 0);
}

void diagonalBackLeft(int speed)
{
    // FR + RL stop
    driveDriver(D1_RPWM, D1_LPWM, 0);

    // FL + RR reverse
    driveDriver(D2_RPWM, D2_LPWM, -speed);
}

void Left(int speed)
{
    // FR + RL stop
    driveDriver(D1_RPWM, D1_LPWM, -speed);

    // FL + RR reverse
    driveDriver(D2_RPWM, D2_LPWM, speed);
}

void Right(int speed)
{
    // FR + RL stop
    driveDriver(D1_RPWM, D1_LPWM, speed);

    // FL + RR reverse
    driveDriver(D2_RPWM, D2_LPWM, -speed);
}

// =========================
// MAIN LOOP
// =========================

void loop()
{
    int ch1 = ibus.readChannel(0);   // Left / Right
    int ch2 = ibus.readChannel(1);   // Forward / Backward

    const int speed = 200;

    Serial.print("CH1: ");
    Serial.print(ch1);
    Serial.print("   CH2: ");
    Serial.println(ch2);

    // Forward
    if (ch2 > 1600 && ch1 > 1400 && ch1 < 1600)
    {
        forward(speed);
    }

    // Backward
    else if (ch2 < 1400 && ch1 > 1400 && ch2 < 1600)
    {
        backward(speed);
    }

    // Diagonal Front Right
    else if (ch2 > 1600 && ch1 > 1600)
    {
        diagonalFrontRight(speed);
    }

    // Diagonal Front Left
    else if (ch2 > 1600 && ch1 < 1400)
    {
        diagonalFrontLeft(speed);
    }

    // Diagonal Back Right
    else if (ch2 < 1400 && ch1 > 1600)
    {
        diagonalBackRight(speed);
    }

    // Diagonal Back Left
    else if (ch2 < 1400 && ch1 < 1400)
    {
        diagonalBackLeft(speed);
    }

    // Stop
    else
    {
        stopRobot();
    }

    delay(80);
}