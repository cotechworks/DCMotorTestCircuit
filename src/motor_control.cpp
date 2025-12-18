#include "main.h"

int   pwm       = 150;   // モーターのPWM値 (0-1024)
bool  direction = true;  // モーターの回転方向 (true: 正転, false: 逆転)
float angle     = 0.0;   // エンコーダの角度
int   mode      = 0;     // エンコーダの状態
int   pre_mode  = 0;

bool encoder_update_flag = false;

void Interrupt(){
  encoder_update_flag = true;
}

void EncoderUpdate() {
  if (digitalRead(PIN_ENC_A) == HIGH && digitalRead(PIN_ENC_B) == LOW) {
    mode = 0;
  } else if (digitalRead(PIN_ENC_A) == HIGH && digitalRead(PIN_ENC_B) == HIGH) {
    mode = 1;
  } else if (digitalRead(PIN_ENC_A) == LOW && digitalRead(PIN_ENC_B) == HIGH) {
    mode = 2;
  } else if (digitalRead(PIN_ENC_A) == LOW && digitalRead(PIN_ENC_B) == LOW) {
    mode = 3;
  }

  switch (mode) {
    case 0:
      if (pre_mode == 3) {
        angle += ANGLE_PER_PULSE;
      } else if (pre_mode == 1) {
        angle -= ANGLE_PER_PULSE;
      }
      break;
    case 1:
      if (pre_mode == 0) {
        angle += ANGLE_PER_PULSE;
      } else if (pre_mode == 2) {
        angle -= ANGLE_PER_PULSE;
      }
      break;
    case 2:
      if (pre_mode == 1) {
        angle += ANGLE_PER_PULSE;
      } else if (pre_mode == 3) {
        angle -= ANGLE_PER_PULSE;
      }
      break;
    case 3:
      if (pre_mode == 2) {
        angle += ANGLE_PER_PULSE;
      } else if (pre_mode == 0) {
        angle -= ANGLE_PER_PULSE;
      }
      break;
  }

  if (angle >= 360.0) {
    angle -= 360.0;
  } else if (angle < 0.0) {
    angle += 360.0;
  }

  pre_mode      = mode;
  encoder_update_flag = true;
}

void GPIO_Init() {
  analogWriteFreq(200);
  analogWriteResolution(10);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_ENC_A, INPUT);
  pinMode(PIN_ENC_B, INPUT);
  attachInterrupt(PIN_ENC_A, Interrupt, CHANGE);
  attachInterrupt(PIN_ENC_B, Interrupt, CHANGE);
  analogWrite(PIN_IN1, 0);
  analogWrite(PIN_IN2, 0);
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