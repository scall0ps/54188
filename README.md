# 自走車專案
- 本專案結合紅外線循跡與超音波避障，讓 Arduino 控制的自走車能在黑線路徑上行駛並自動避開前方障礙物。

# 一、專案特色
- 會走走停停的循線車，且在遇到障礙時會停止三秒

# 二、硬體需求
| 元件               | 數量 |
| ---------------- | -- |
| Arduino Uno（或相容） | 1  |
| L298N 馬達驅動板      | 1  |
| 紅外線循跡感測器         | 2  |
| HC-SR04 超音波模組    | 1  |
| 直流馬達 + 車輪        | 2  |
| LED 指示燈          | 2  |
| 電源模組與連接線         | 若干 |
| 功能              | 腳位               |
| --------------- | ---------------- |


本專案使用 Arduino Uno 製作自走車，透過紅外線循跡與超音波避障，實現自動行走與停止避撞功能。

---

##  硬體連接與腳位說明

| 功能             | 腳位        |
|------------------|-------------|
| 左 IR 感測器     | D8          |
| 右 IR 感測器     | D9          |
| 超音波 TRIG/ECHO | D11 / D10   |
| 馬達驅動 ENA     | D3          |
| 左輪 IN1/IN2     | D2 / D4     |
| 馬達驅動 ENB     | D5          |
| 右輪 IN3/IN4     | D6 / D7     |
| LED 左 / 右      | D12 / D13   |

---
# 三 程式說明
##  功能說明

-  **循跡模式**：IR 感測器辨識黑線，自動左轉 / 右轉 / 前進。
-  **避障機制**：使用超音波感測距離，當前方障礙物距離 < 5cm，自動停止 4 秒。
-  **LED 指示**：不同動作時亮起左右 LED 指示燈。

---

##  程式邏輯概述

- **前進條件**：雙 IR 感測器皆偵測到黑線（LOW）
- **左轉 / 右轉**：依據左右 IR 高低自動調整馬達方向
- **停止條件**：IR 無黑線或前方障礙物過近（距離 < 5 cm）
- **速度設定**：
  - 前進：`analogWrite(...) = 200`
  - 避障：延遲 4 秒停車

---

##  原始碼（`src/self_driving_car.ino`）

```cpp
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
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  int leftIR = digitalRead(IR_L);
  int rightIR = digitalRead(IR_R);

  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long duration = pulseIn(Echo, HIGH);  
  float distance = duration / 58.0;

  if (leftIR == LOW && rightIR == LOW) {
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
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
    analogWrite(ENA, 200); analogWrite(ENB, 200);
    delay(230);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
  } else if (leftIR == HIGH && rightIR == LOW) {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3,HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, 200); analogWrite(ENB, 200);
    delay(230);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(50);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
  }

  if (distance < 5) {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    delay(4000);
  }

  delay(10);
}

