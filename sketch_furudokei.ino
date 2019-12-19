
#define PIN 3
#define BEATTIME_ORIG 600
#define L_G 196
#define L_A 220
#define L_H 247 
#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440
#define H 494
#define H_C 523

#include <math.h>
#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel;                   // create instance of the MMA8452 class

float BEATTIME;
// 時間差分
float timeSpan = 0.1;
// ひとつ前の加速度
float oldAccel = 0;
//　加速度から算出した速度
float Speed = 0;
// ローパスフィルターの係数(これは環境によって要調整。1に近づけるほど平滑化の度合いが大きくなる)
float filterCoefficient = 0.9;
float lowpassValue = 0;
float highpassValue = 0;

float get_beattime(){
  if (accel.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    float ax = accel.getCalculatedX();
    float ay = accel.getCalculatedY();
    float az = accel.getCalculatedZ();
    float ACCEL = sqrt(ax*ax + ay*ay + az*az);
    // ローパスフィルター(現在の値 = 係数 * ひとつ前の値 ＋ (1 - 係数) * センサの値)
    lowpassValue = lowpassValue * filterCoefficient + ACCEL * (1 - filterCoefficient);
    // ハイパスフィルター(センサの値 - ローパスフィルターの値)
    highpassValue = ACCEL - lowpassValue;

    // 速度計算(加速度を台形積分する)
    Speed = ((highpassValue + oldAccel) * timeSpan) / 2 + Speed;
    oldAccel = highpassValue;
    
//    Serial.print(ax, 3);
//    Serial.print("\t");
//    Serial.print(ay, 3);
//    Serial.print("\t");
//    Serial.print(az, 3);
//    Serial.print("\t");
//    Serial.print("ACCEL :");
    Serial.print(ACCEL, 3);
    Serial.print("\t");
    Serial.print(Speed, 3);
    Serial.println();
    return BEATTIME_ORIG/Speed;
  }
  else return BEATTIME_ORIG;
}


void setup() {
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }

}

void loop() {
  BEATTIME = get_beattime();
  delay(100);
//  tone(PIN,L_G,BEATTIME) ; 
//  delay(BEATTIME) ;
//  tone(PIN,C,BEATTIME) ;
//  delay(BEATTIME) ;
//  tone(PIN,L_H,0.5*BEATTIME) ; 
//  delay(0.5*BEATTIME) ;
//  tone(PIN,C,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,D,BEATTIME) ;
//  delay(BEATTIME) ;
//  tone(PIN,C,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,D,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,E,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,E,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,F,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,E,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,L_A,BEATTIME) ; 
//  delay(BEATTIME) ;
//  tone(PIN,D,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,D,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,C,BEATTIME) ;
//  delay(BEATTIME) ;
//  tone(PIN,C,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,C,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,L_H,BEATTIME) ;
//  delay(BEATTIME) ;
//  tone(PIN,L_A,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,L_H,0.5*BEATTIME) ;
//  delay(0.5*BEATTIME) ;
//  tone(PIN,C,2*BEATTIME) ;
//  delay(2*BEATTIME) ;
//  delay(BEATTIME) ;
}
