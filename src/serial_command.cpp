#include "main.h"

bool RecieveSerialCommand(){
    if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    // スタートコマンド
    if (command.startsWith("sta")) {
      setPwm(pwm, direction);
      Serial.println("Motor started");
    }

    // ストップコマンド
    else if (command.startsWith("sto")) {
      setPwm(0, direction);
      Serial.println("Motor stopped");
    }

    // PWM値設定コマンド
    else if (command.startsWith("pwm")) {
      int value = command.substring(3).toInt();
      if (value >= 0 && value <= 1024) {
        pwm = value;
        setPwm(pwm, direction);
        Serial.print("PWM set to ");
        Serial.println(pwm);
      } else {
        Serial.println("Invalid PWM value. Must be between 0 and 1024.");
        return false;
      }
    }

    // 回転方向設定コマンド
    else if (command.startsWith("dir")) {
      int dir = command.substring(3).toInt();
      if (dir == 1) {
        direction = true;
        Serial.println("Direction set to FORWARD");
      } else {
        direction = false;
        Serial.println("Direction set to REVERSE");
      }
      setPwm(pwm, direction);
    }

    // デバッグ用コマンド
    else if (command.startsWith("dbg")) {
      int dir = command.substring(3).toInt();
      if (dir != 0 && dir != 1) {
        Serial.println("Invalid direction for dbg command. Use 0 or 1.");
        return false;
      }
      setPwm(512, dir);

      delay(200);

      setPwm(0, direction);
    }

    // 不明なコマンド
    else {
      Serial.println("Unknown command");
      return false;
    }
  }
  return true;
}