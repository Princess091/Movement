int IN1_a = 10;
int IN2_a = 11;
// int IN3_b = 12;
// int IN4_b = 13;

// pulse width modulation pins
int EnA = 7;
// int EnB = 8;

// Encoder pins
int encodeA = 2;
int encodeB = 3;
// int encode_c = 18;
// int encode_d = 19;

int i;

void setup() {
  // put your setup code here, to run once:
pinMode(IN1_a, OUTPUT);
pinMode(IN2_a, OUTPUT);
// pinMode(IN3_b, OUTPUT);
// pinMode(IN4_b, OUTPUT);

// pulse width modulation pins
pinMode(EnA, OUTPUT);
// pinMode(EnB, OUTPUT);

//Encoder pins
// pinMode(encodeA, INPUT);
// pinMode(encodeB, INPUT);
// pinMode(encodeC, INPUT);
// pinMode(encodeD, INPUT);

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(IN1_a, HIGH);
digitalWrite(IN2_a, LOW);

i = EnA;

  for(i=180; i<=255; i++){
    digitalWrite(i, HIGH);
  }

delay(500);
}
