#include <Arduino.h>

#define ENCODER_RESOLUTION 40.0                                         // エンコーダの分解能 (1回転あたりのパルス数)
#define GEAR_RATIO         300.0                                        // ギア比
#define ANGLE_PER_PULSE    (360.0 / (ENCODER_RESOLUTION * GEAR_RATIO))  // 1パルスあたりの角度変化量
// #define ANGLE_PER_PULSE 1

#define PIN_IN1   15
#define PIN_IN2   14
#define PIN_ENC_A 4
#define PIN_ENC_B 6

extern void GPIO_Init();
extern void EncoderUpdate();
extern void setPwm(int value, bool direction);
extern bool RecieveSerialCommand();

extern int   pwm;
extern bool  direction;
extern float angle;
extern bool  encoder_update_flag;