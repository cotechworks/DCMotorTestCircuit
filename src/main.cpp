#include "main.h"

void setup() {
  // シリアル通信
  Serial.begin(115200);

  // GPIO
  GPIO_Init();
}

// =================================

void loop() {
  // シリアルコマンドの処理
  RecieveSerialCommand();
}

// =================================

void loop1() {
  if (encoder_update_flag) {
    EncoderUpdate();
    encoder_update_flag = false;
    Serial.println(angle);
  }
}