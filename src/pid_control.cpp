#include "pid_control.h"

PID_Control::PID_Control(float kp, float ki, float kd, float dt_us) {
  this->_kp         = kp;
  this->_ki         = ki;
  this->_kd         = kd;
  this->_dt_us      = dt_us;
  this->_integral   = 0.0;
  this->_last_error = 0.0;
}

float PID_Control::update(float target, float measured) {
  // 誤差の計算
  float error = target - measured;
  this->_integral += error * this->_dt_us;

  // PI制御の操作量の計算
  float output = (this->_kp * error) + (this->_ki * this->_integral) + (this->_kd * (error - this->_last_error) / (this->_dt_us / 1000000.0));

  // 前回の値の更新
  this->_last_error = error;
  return output;
}

void PID_Control::reset() {
  this->_integral   = 0.0;
  this->_last_error = 0.0;
}