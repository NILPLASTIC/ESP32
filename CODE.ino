#include <Wire.h>
#include <WiFi.h>
#include <BleMouse.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const int led=2;
#define LED_ON LOW
#define LED_OFF HIGH

BleMouse bleMouse("ESP32蓝牙","Espressif",100);


/* 设置引脚 */
#define MPU_I2C_SCL 35 
#define MPU_I2C_SDA 34

Adafruit_MPU6050 mpu;

int led_pin = 13;

void setup() {

  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
  
  while (!Serial)
    delay(10); //初始化MPU-6050传感器。
  Serial.println("Adafruit MPU6050 test!");
  // 尝试初始化
  if (!mpu.begin()) {
    Serial.println("not find MPU6050");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("加速计范围设置为: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("陀螺仪量程设置为: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("过滤器带宽设置为: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  
}

void loop() {

  if(bleMouse.isConnected()) {
    digitalWrite(led,LED_ON);
  }else{
    digitalWrite(led,LED_OFF);
    
    }


  /* 通过读数获取新的传感器事件 */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  
  
  
  
  unsigned long startTime;
  while(millis()<startTime+60) {
      bleMouse.move(a.acceleration.x,a.acceleration.y);//移动鼠标
      delay(3);
    }

 
  



  


  
  
}