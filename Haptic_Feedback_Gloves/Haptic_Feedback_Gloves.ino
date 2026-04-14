#define MOT_PIN1 33
#define MOT_PIN1 22

int flex1 = 4;
int flex2 = 2;
int flex3 = 35;

int flexy1;
int flexy2;
int flexy3;

void setup() {
  // put your setup code here, to run once:
  pinMode(MOT_PIN1, OUTPUT);
  pinMode(MOT_PIN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
flexy1 = analogRead(4);
flexy1 = analogRead(2);
flexy1 = analogRead(35);

flexy1 = constrain(map(flexy1, 0, 1023, 715, 960));
flexy1 = constrain(map(flexy2, 0, 1023, 715, 960));
flexy1 = constrain(map(flexy3, 0, 1023, 690, 965));

    if (flexy1 >= 715 && flexy1 <= 960){
       digitalWrite(MOT_PIN1, HIGH);
       delay(3000);
       digitalWrite(MOT_PIN1, LOW);
    }

    if (flexy1 >= 690 && flexy1 <= 965){
       digitalWrite(MOT_PIN2, HIGH);
       delay(3000);
       digitalWrite(MOT_PIN2, LOW);
    }

    // if (flexy1 >= 715 && flexy1 <= 960){

    // }

    delay(500);
}
