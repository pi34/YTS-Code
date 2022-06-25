// The one that works with the lidar and serial comm

// The reverse one

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

  Serial.begin(115200);
  Serial.setTimeout(1);

  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  
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
  
   analogWrite(Right_L_PWM, 0);
   analogWrite(Right_R_PWM, velocity);
   analogWrite(Left_L_PWM, 0);
   analogWrite(Left_R_PWM, velocity);
   
}

void backward (int velocity) {

  analogWrite(Right_L_PWM, velocity);
  analogWrite(Right_R_PWM, 0);
  analogWrite(Left_L_PWM, velocity);
  analogWrite(Left_R_PWM, 0);
  
}

void left () {

  analogWrite(Right_L_PWM, 0);
  analogWrite(Right_R_PWM, 500);
  analogWrite(Left_L_PWM, 0);
  analogWrite(Left_R_PWM, 200);
  
}

void right () {

  analogWrite(Right_L_PWM, 0);
  analogWrite(Right_R_PWM, 200);
  analogWrite(Left_L_PWM, 0);
  analogWrite(Left_R_PWM, 500);
  
}

void stp () {
  analogWrite(Right_R_PWM, 0);
  analogWrite(Right_L_PWM, 0);
  analogWrite(Left_R_PWM, 0);
  analogWrite(Left_L_PWM, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

    

    while (!Serial.available());
  
      int ans = Serial.readString().toInt();
      Serial.print(ans);
      if (ans == 1) {
        forward(500);
      } else if (ans == 4) {
        backward(500);
      } else if (ans == 3) {
        right(); 
      } else if (ans == 2) {
        left();
      } else if (ans == 5) {
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
    
        while (digitalRead(echo) == 0);
    
        int t1 = micros();
        while (digitalRead(echo) == 1);
        int t2 = micros();
    
        int pw = t2 - t1;
    
        int dis = pw / 58.0;

        Serial.print(dis);

        if (dis >= 100  || dis <= 0) {
          backward(500);
        } else {
          stp();
        }
      }
      //delay(1000);
   
  

}
