int echo = 4;
int trig = 9;

int Left_L_EN = 2;
int Left_L_PWM = 5;
int Left_RL_IS = 7;
int Left_R_EN = 1;
int Left_R_PWM = 3;

int Right_L_IS = 13;
int Right_L_EN = 12;
int Right_L_PWM = 6;
int Right_R_IS = 8;
int Right_R_EN = 11;
int Right_R_PWM = 10;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  pinMode(Left_L_EN, OUTPUT);
  pinMode(Left_L_PWM, OUTPUT);
  pinMode(Left_RL_IS, OUTPUT);
  pinMode(Left_R_EN, OUTPUT);
  pinMode(Left_R_PWM, OUTPUT);

  pinMode(Right_L_IS, OUTPUT);
  pinMode(Right_L_EN, OUTPUT);
  pinMode(Right_L_PWM, OUTPUT);
  pinMode(Right_R_IS, OUTPUT);
  pinMode(Right_R_EN, OUTPUT);
  pinMode(Right_R_PWM, OUTPUT);
  

  digitalWrite(Left_RL_IS, LOW);
  digitalWrite(Left_L_EN, HIGH);
  digitalWrite(Left_R_EN, HIGH);

  digitalWrite(Right_L_IS, LOW);
  digitalWrite(Right_L_EN, HIGH);
  digitalWrite(Right_R_IS, LOW);
  digitalWrite(Right_R_EN, HIGH);
  
}

void forward (int velocity) {
  
   analogWrite(Right_R_PWM, 0);
   analogWrite(Right_L_PWM, velocity);
   analogWrite(Left_R_PWM, 0);
   analogWrite(Left_L_PWM, velocity);
   
}

void backward (int velocity) {

  analogWrite(Right_R_PWM, velocity);
  analogWrite(Right_L_PWM, 0);
  analogWrite(Left_R_PWM, velocity);
  analogWrite(Left_L_PWM, 0);
  
}

void right () {

  analogWrite(Right_R_PWM, 100);
  analogWrite(Right_L_PWM, 0);
  analogWrite(Left_R_PWM, 0);
  analogWrite(Left_L_PWM, 300);
  
}

void left () {

  analogWrite(Right_R_PWM, 0);
  analogWrite(Right_L_PWM, 300);
  analogWrite(Left_R_PWM, 100);
  analogWrite(Left_L_PWM, 0);
  
}

void stp () {
  analogWrite(Right_R_PWM, 0);
  analogWrite(Right_L_PWM, 0);
  analogWrite(Left_R_PWM, 0);
  analogWrite(Left_L_PWM, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

  
  
  if (Serial.available()) {
    char ans = Serial.read();
    Serial.print(ans=='1');
    if (ans == '1') {
      forward(300);
    } else if (ans == '2') {
      backward(300);
    } else if (ans == '3') {
      right(); 
    } else if (ans == '4') {
      left();
    } else if (ans == '5') {
      stp();
    }
    delay(1000);
  }

}
