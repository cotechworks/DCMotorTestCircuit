#include "main.h"

int   pwm          = 0;     // モーターのPWM値 (0-1024)
bool  direction    = true;  // モーターの回転方向 (true: 正転, false: 逆転)
float angle        = 0.0;   // エンコーダの角度
float angle_target = 0.0;
int   control_mode = SPEED;

struct repeating_timer st_timer;
bool                   timerFlag = false;

Encoder     encoder(PIN_ENC_A, PIN_ENC_B, ANGLE_PER_PULSE, false);
PID_Control pid(PID_KP, PID_KI, PID_KD, CONTROL_PERIOD_US);  // PID制御オブジェクトの生成 (Kp, Ki, Kd)

void Interrupt() {
  encoder.update();
}

bool Timer(struct repeating_timer* t) {
  timerFlag = true;
  return true;
}

void Timer_Init() {
  add_repeating_timer_us(CONTROL_PERIOD_US, Timer, NULL, &st_timer);
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
}

void setPwmforPid(int value) {
  if (value >= 0) {
    direction = true;
    setPwm(value, direction);
  } else {
    direction = false;
    setPwm(-1 * value, direction);
  }
}