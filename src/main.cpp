#include "main.h"

void setup() {
  // シリアル通信
  Serial.begin(115200);

  // GPIO
  GPIO_Init();

  // タイマー
  Timer_Init();
  sendAngleTask.start();

  // モーター初期化
  setPwm(512, true);
  delay(500);
  setPwm(0, true);
  encoder.reset();
}

// =================================

void loop() {
  // シリアルコマンドの処理
  RecieveSerialCommand();
}

// =================================

void loop1() {
  // タスク更新
  sendAngleTask.update();

  // エンコーダ値の出力
  if (sendAngleTask.isFired()) {
    Serial.println(encoder.getAngle());
  }

  // // PID制御の更新
  if (timerFlag) {
    if (control_mode == POSITION) {
      pwm = static_cast<int>(pid.update(angle_target, encoder.getAngle()));
      if (pwm > 1024) pwm = 1024;
      if (pwm < -1024) pwm = -1024;
      setPwmforPid(pwm);
      timerFlag = false;
    }
  }
}