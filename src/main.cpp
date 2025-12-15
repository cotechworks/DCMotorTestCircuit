#include <Arduino.h>

#define PIN_IN1 15
#define PIN_IN2 14

// モーター制御
int pwm = 127;         // モーターのPWM値 (0-1024)
bool direction = true; // モーターの回転方向 (true: 正転, false: 逆転)

void setup() {
  // シリアル通信
  Serial.begin(9600);

  // GPIO
  analogWriteFreq(200);
  analogWriteResolution(10);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
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

void loop() {
  // シリアルコマンドの処理
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
        return;
      }
      setPwm(512,dir);

      delay(200);

      setPwm(0, direction);
    }

    // 不明なコマンド
    else {
      Serial.println("Unknown command");
    }
  }
}