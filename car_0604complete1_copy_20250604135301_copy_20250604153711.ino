const int IR_L = 8;  // 左紅外線感測器接腳
const int IR_R = 9;  // 右紅外線感測器接腳

const int Trig = 11;
const int Echo = 10;

const int ENA = 3, IN1 = 2, IN2 = 4;
const int ENB = 5, IN3 = 6, IN4 = 7;


void setup() {
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  Serial.begin(9600);
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int leftIR = digitalRead(IR_L);
  int rightIR = digitalRead(IR_R);

  Serial.print("左感測器: ");
  Serial.println(leftIR);
  Serial.print("右感測器: ");
  Serial.println(rightIR);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  // 讀取脈衝寬度（微秒）
  long duration = pulseIn(Echo, HIGH);  

  // 計算距離（公分）
  float distance = duration / 58.0;

  // 顯示距離
  Serial.print("距離: ");
  Serial.print(distance);
  Serial.println(" cm");


  
  if (leftIR == LOW && rightIR == LOW) {
    Serial.println("前進");
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, 200); analogWrite(ENB, 200);
    delay(70);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(150);
    
  } else if (leftIR == LOW && rightIR == HIGH) {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
    Serial.println("右轉");
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(IN1,HIGH); 
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW); 
    //digitalWrite(IN4, LOW);
    analogWrite(ENA, 200); analogWrite(ENB, 200);
    delay(230);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
  } else if (leftIR == HIGH && rightIR == LOW) {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
    Serial.println("左轉");
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3,HIGH); 
    //digitalWrite(IN4, HIGH);
    
    analogWrite(ENA, 200); analogWrite(ENB, 200);
    delay(230);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
  } 
  
    else {
    Serial.println("停止");
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
  }
  if (distance < 5) {
    Serial.println("要撞到了");
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(4000);
    }
  delay(10); // 每5毫秒更新一次
}

