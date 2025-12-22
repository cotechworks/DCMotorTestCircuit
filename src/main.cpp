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
  // エンコーダ値の出力
  if (encoder.isChanged()) {
    Serial.print("Angle: ");
    Serial.println(encoder.getAngle());
  }
}