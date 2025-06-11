# 自走車專案
- 本專案結合紅外線循跡與超音波避障，讓 Arduino 控制的自走車能在黑線路徑上行駛並自動避開前方障礙物。

# 一、專案特色
循跡 ：雙紅外線感測器偵測黑線，依偏差自動前進、左轉、右轉。
避障 ：超音波模組測量前方距離，低於設定閾值時自動停止。
停止 ：兩邊的感應器都沒優偵測到時就會停止。
LED 狀態指示：前進、轉彎與停止時的指示燈提示。
# 二、硬體需求
Arduino Uno (或相容開發板)
L298N 雙 H 橋馬達驅動板
2x 紅外線循跡感測器 (IR modules)
1x HC-SR04 超音波感測器
2x 直流馬達 + 車輪套件
2x LED 指示燈
連接線、電源模組
腳位對應
功能	腳位
ENA (左馬達 PWM)	D3
IN1, IN2 (左輪)	D2, D4
ENB (右馬達 PWM)	D5
IN3, IN4 (右輪)	D6, D7
IR_left, IR_right	D9, D8
TRIG, ECHO	D10, D11
LED_LEFT, LED_RIGHT	D12, D13
# 三、軟體結構
sketch_apr8a/
├── 000.ino          // 主程式：初始化、主 Loop
├── planning.md      // 邏輯規劃文件
└── README.md        // 使用說明
核心函式
digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);：前進並亮雙燈
digitalWrite(IN1,HIGH); 
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW); 
digitalWrite(IN4, LOW);：原地轉彎並亮對應 LED
void backward()：後退並熄滅 LED
void stopMotors()：停止四輪並熄滅 LED
long readUltrasonic()：讀取超音波距離值
# 四、參數調整
MOTOR_SPEED：前進速度 (0~255)
TURN_SPEED：轉彎與後退速度
距離閾值：if (distance < 5) 中的 5 cm
延遲時間：50ms

