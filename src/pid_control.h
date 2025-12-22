#pragma once

#include <Arduino.h>

class PID_Control {
 public:
  PID_Control(float kp, float ki, float kd, float dt_us);
  float update(float target, float measured);
  void  reset();

 private:
  float _kp;               // 比例ゲイン
  float _ki;               // 積分ゲイン
  float _kd;               // 微分ゲイン
  float _dt_us;             // 更新時間(us)
  float _integral;         // 積分値
  float _last_error;       // 前回の誤差
};