#include <Arduino.h>

class Encoder {
 public:
  Encoder(int pinA, int pinB, float angle_per_pulse, bool pull_up);
  void  update();
  float getAngle();
  bool  isChanged();

 private:
  int   _pinA;             // エンコーダA相のピン番号
  int   _pinB;             // エンコーダB相のピン番号
  int   _angle;            // エンコーダの現在の角度（パルス数）
  float _angle_per_pulse;  // 1パルスあたりの角度変化量
  int   _mode;             // 現在のエンコーダの状態
  int   _pre_mode;         // 前回のエンコーダの状態
  bool  _change_flag;      // 状態変化フラグ
};