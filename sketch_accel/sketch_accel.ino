
#define PIN 3
#define BEATTIME_ORIG 120
#define SEND_PIN 10 // D10

#include <math.h>
#include <Wire.h>                 // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h"    // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q
#include <VirtualWire.h>

MMA8452Q accel;                   // create instance of the MMA8452 class

int BEATTIME = 60;
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
int num = 0;

int get_beattime(){
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
    
    //Serial.print(ACCEL, 3);
    //Serial.print("\t");
    //Serial.println(Speed, 3);

    int tempo = (BEATTIME_ORIG*1.5*Speed-50)/2;
    //int tempo = BEATTIME_ORIG*0.6*ACCEL;
    //Serial.println(tempo);
    return tempo;
  }
  else return BEATTIME_ORIG;
}


void setup() {
  vw_set_tx_pin(SEND_PIN);
  vw_setup(7000);
  
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();
  if (accel.begin() == false) {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1);
  }
  for(int i = 0; i < 10; i++){
    delay(1000);
    get_beattime();
  }
}

void loop() {
  char char_tempo[1];
  digitalWrite(13, HIGH);
  for(int i = 0; i < 10; i++){ 
    BEATTIME = get_beattime();
    if(i == 9){
      Serial.println(BEATTIME);
      char_tempo[0] = (char)BEATTIME;
      vw_send((uint8_t *)char_tempo, 1);
      vw_wait_tx();
    }
//    delay(60/float(BEATTIME)*1000/10);
 delay(60/float(BEATTIME_ORIG)*1000/10);

  }
  digitalWrite(13, LOW);
}
