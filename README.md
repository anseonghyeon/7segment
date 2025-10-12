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

## 💻 시범영상

[![Watch the video](https://img.youtube.com/vi/5XKUb0XrZ3k/0.jpg)](https://www.youtube.com/watch?v=5XKUb0XrZ3k)

