# Arduino Ultrasonic Sensor with 7-Segment Display & Speaker

## 📖 개요 (Overview)

이 프로젝트는 아두이노를 사용하여 HC-SR04 초음파 센서로 거리를 측정하고, 측정된 거리에 따라 7세그먼트 디스플레이에 0부터 9까지의 숫자를 표시하며, 동시에 스피커(피에조 부저)를 통해 소리의 높낮이를 조절하여 청각적인 피드백을 제공하는 프로젝트입니다.

거리가 가까울수록 높은 음이 나고 7세그먼트에는 작은 숫자가 표시되며, 거리가 멀어질수록 낮은 음이 나고 큰 숫자가 표시됩니다.

## ✨ 주요 기능 (Features)

-   **실시간 거리 측정**: 초음파 센서를 이용해 물체와의 거리를 실시간으로 측정합니다.
-   **시각적 피드백**: 측정된 거리를 0~9 사이의 값으로 매핑하여 7세그먼트 디스플레이에 숫자로 표시합니다.
-   **청각적 피드백**: 측정된 거리에 따라 스피커에서 재생되는 소리의 높낮이(주파수)가 변화합니다.
-   **쉬프트 레지스터 (74HC595) 활용**: 아두이노의 적은 핀으로 7세그먼트 디스플레이를 제어합니다.

## 🛠️ 준비물 (Hardware Required)

-   Arduino Uno (또는 호환 보드)
-   HC-SR04 초음파 센서
-   7세그먼트 디스플레이 (Common Cathode 타입)
-   74HC595 쉬프트 레지스터 (Shift Register)
-   스피커 또는 피에조 부저 (Piezo Buzzer)
-   브레드보드 (Breadboard)
-   점퍼 와이어 (Jumper Wires)
-   (선택사항) 저항 (7세그먼트 보호용, 220Ω ~ 330Ω)

## 🔌 회로 구성 (Wiring Diagram)

| 부품                  | 아두이노 핀 (Arduino Pin) | 설명                                           |
| --------------------- | ------------------------- | ---------------------------------------------- |
| **74HC595 (쉬프트 레지스터)** |                           |                                                |
| DS (Serial Data)      | `Digital 10` (dataPin)    | 데이터 핀                                      |
| ST_CP (Latch)         | `Digital 11` (latchPin)   | 래치 핀                                        |
| SH_CP (Clock)         | `Digital 12` (clockPin)   | 클럭 핀                                        |
| **HC-SR04 (초음파 센서)** |                           |                                                |
| Trig                  | `Digital 2`               | 트리거 핀                                      |
| Echo                  | `Digital 3`               | 에코 핀                                        |
| **스피커/피에조 부저** |                           |                                                |
| Positive (+)          | `Digital 5`               | 스피커 제어 핀                                 |
| Negative (-)          | `GND`                     | 접지                                           |

* **74HC595의 출력 핀(Q0~Q7)**은 7세그먼트 디스플레이의 **a~g 및 DP 핀**에 순서대로 연결합니다.
* **7세그먼트의 Common 핀**은 **GND**에 연결합니다. (Common Cathode 기준)
* 모든 부품의 **VCC**는 아두이노의 **5V**에, **GND**는 아두이노의 **GND**에 연결합니다.

## 💻 아두이노 코드 (Arduino Code)

```cpp
/*
 * 프로젝트: 초음파 센서와 7세그먼트를 이용한 거리 측정기
 * 설명: 초음파 센서로 거리를 측정하여, 그 결과에 따라
 * 7세그먼트에 0-9 사이의 숫자를 표시하고 스피커로 다른 높이의 소리를 냅니다.
 */

// 74HC595 쉬프트 레지스터 핀 설정
int dataPin = 10;  // DS (Serial Data)
int latchPin = 11; // ST_CP (Latch)
int clockPin = 12; // SH_CP (Clock)

// 7세그먼트 숫자 표시용 데이터 (Common Cathode 기준, 0~9)
byte dec_digits[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111100, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01100111  // 9
};

// HC-SR04 초음파 센서 핀 설정
int trig = 2;
int echo = 3;

// 거리 측정 범위 설정 (cm)
int maxVal = 50; // 최대 인식 거리
int minVal = 0;  // 최소 인식 거리

// 스피커 핀 설정
int SPEAKER = 5;

void setup() {
  // 시리얼 통신 시작 (디버깅용)
  Serial.begin(9600);

  // 핀 모드 설정
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(SPEAKER, OUTPUT);
}

void loop() {
  // 1. 거리 측정
  // Trig 핀으로 10us의 초음파를 발생
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Echo 핀으로 초음파가 돌아오는 시간을 측정하고 거리(cm)로 변환
  // 거리 = (시간 * 음속) / 2
  int distance = ((pulseIn(echo, HIGH) * 340) / 10000) / 2;

  // 측정된 거리를 시리얼 모니터에 출력
  Serial.print(distance);
  Serial.println("cm");

  // 2. 7세그먼트 제어
  // 측정된 거리를 0~9 사이의 값으로 매핑
  int displayNum = map(distance, minVal, maxVal, 0, 9);
  // 값이 0~9 범위를 벗어나지 않도록 제한
  displayNum = constrain(displayNum, 0, 9);

  // 쉬프트 레지스터를 통해 7세그먼트에 숫자 데이터 전송
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, dec_digits[displayNum]);
  digitalWrite(latchPin, HIGH);
  delay(10);

  // 3. 스피커 제어
  // 측정된 거리를 소리 주파수(Hz)로 매핑 (가까울수록 높은 음)
  int NOTE = map(distance, 0, 9, 5000, 500);
  // 스피커로 해당 주파수의 소리를 0.5초간 재생
  tone(SPEAKER, NOTE, 500);
}

[![Watch the video](https://img.youtube.com/vi/c6TLsp0e6p4/0.jpg)](https://www.youtube.com/watch?v=c6TLsp0e6p4)
