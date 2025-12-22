#include "encoder.h"

Encoder::Encoder(int pinA, int pinB, float angle_per_pulse = 1.0, bool pull_up = true) {
  this->_pinA            = pinA;
  this->_pinB            = pinB;
  this->_angle           = 0;
  this->_angle_per_pulse = angle_per_pulse;
  this->_pre_mode        = 0;

  this->_mode     = judgeMode();
  this->_pre_mode = this->_mode;

  if (pull_up) {
    pinMode(_pinA, INPUT_PULLUP);
    pinMode(_pinB, INPUT_PULLUP);
  } else {
    pinMode(_pinA, INPUT);
    pinMode(_pinB, INPUT);
  }
}

int Encoder::judgeMode() {
  if (digitalRead(_pinA) == HIGH && digitalRead(_pinB) == LOW) {
    return 0;
  } else if (digitalRead(_pinA) == HIGH && digitalRead(_pinB) == HIGH) {
    return 1;
  } else if (digitalRead(_pinA) == LOW && digitalRead(_pinB) == HIGH) {
    return 2;
  } else if (digitalRead(_pinA) == LOW && digitalRead(_pinB) == LOW) {
    return 3;
  }
  return -1;  // エラー
}

void Encoder::update() {
  // 現在の状態を取得
  _mode = judgeMode();

  // 状態が変化していなければ処理を終了
  if( _mode == _pre_mode ) {
    return;
  }

  // 状態変化に応じて角度を更新
  switch (_mode) {
    case 0:
      if (_pre_mode == 3) {
        _angle++;
      } else if (_pre_mode == 1) {
        _angle--;
      }
      break;
    case 1:
      if (_pre_mode == 0) {
        _angle++;
      } else if (_pre_mode == 2) {
        _angle--;
      }
      break;
    case 2:
      if (_pre_mode == 1) {
        _angle++;
      } else if (_pre_mode == 3) {
        _angle--;
      }
      break;
    case 3:
      if (_pre_mode == 2) {
        _angle++;
      } else if (_pre_mode == 0) {
        _angle--;
      }
      break;
  }
  _pre_mode    = _mode;
  _change_flag = true;
}

float Encoder::getAngle() {
  return static_cast<float>(_angle) * _angle_per_pulse;
}

bool Encoder::isChanged() {
  if (_change_flag) {
    _change_flag = false;
    return true;
  } else {
    return false;
  }
}

void Encoder::reset() {
  _angle = 0;
}