#include "main.h"

int   pwm       = 512;   // モーターのPWM値 (0-1024)
bool  direction = true;  // モーターの回転方向 (true: 正転, false: 逆転)
float angle     = 0.0;   // エンコーダの角度
int   mode      = 0;     // エンコーダの状態
int   pre_mode  = 0;

Encoder encoder(PIN_ENC_A, PIN_ENC_B, ANGLE_PER_PULSE, false);

void Interrupt() {
  encoder.update();
}

void GPIO_Init() {
  // PWM
  analogWriteFreq(200);
  analogWriteResolution(10);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  analogWrite(PIN_IN1, 0);
  analogWrite(PIN_IN2, 0);
  attachInterrupt(PIN_ENC_A, Interrupt, CHANGE);
  attachInterrupt(PIN_ENC_B, Interrupt, CHANGE);
}

void setPwm(int value, bool direction) {
  if (direction) {
    // 正転
    analogWrite(PIN_IN1, value);
    analogWrite(PIN_IN2, 0);
  } else {
    // 逆転
    analogWrite(PIN_IN1, 0);
    analogWrite(PIN_IN2, value);
  }
  Serial.print("IN1 PWM: ");
  Serial.print(value);
  Serial.print(", IN2 PWM: ");
  Serial.println(direction ? 0 : value);
}