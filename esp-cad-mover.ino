#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <BleCombo.h>
#define BUTTON_PIN 2

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Starting work!");
  Keyboard.begin();
  Mouse.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
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
  Serial.print("Gyro range set to: ");
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
  Serial.print("Filter bandwidth set to: ");
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
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


/* key strokes */


int buttonState = digitalRead(BUTTON_PIN);
if(Keyboard.isConnected()) {
    unsigned long startTime;
    if(a.acceleration.y > 1.5 && buttonState == 0 ){
      Serial.println("Move mouse pointer right");
      Keyboard.press(KEY_LEFT_SHIFT);
      Mouse.press(MOUSE_MIDDLE);
      Mouse.move(1,0);
    }
   else if(a.acceleration.y < -1.5 && buttonState == 0){
      Serial.println("Move mouse pointer left");
      Keyboard.press(KEY_LEFT_SHIFT);
      startTime = millis();
      Mouse.press(MOUSE_MIDDLE);
      Mouse.move(-1,0);
    }
   else if(a.acceleration.x < -1.5 && buttonState == 0){
      Serial.println("Move mouse pointer down");
      Keyboard.press(KEY_LEFT_SHIFT);
      startTime = millis();
      Mouse.press(MOUSE_MIDDLE);
      Mouse.move(0,1);
    }
  else if(a.acceleration.x > 1.5 && buttonState == 0){
      Serial.println("Move mouse pointer up");
      Keyboard.press(KEY_LEFT_SHIFT);
      startTime = millis();
      Mouse.press(MOUSE_MIDDLE);
      Mouse.move(0,-1);
 
    }else{
      Mouse.release(MOUSE_MIDDLE);
      Keyboard.releaseAll();  
    }
  }else{
    Serial.println("Oh something bad happend");
  
  }
  Serial.println("");
}
