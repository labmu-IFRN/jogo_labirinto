#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

float x_suave = 90;
float z_suave = 90;

void setup() {
  Serial.begin(115200);   
  Serial2.begin(9600);    // bluetooth

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  Serial.println("MPU pronto (X e Z)");
}

void loop() {
  mpu6050.update();

  float angX = mpu6050.getAngleX();
  float angY = mpu6050.getAngleY();
  
  Serial.print("AngX: ");
  Serial.print(angX);
  Serial.print(" | AngY: ");
  Serial.print(angY);
  
  angX = constrain(angX, -90, 90);
  angY = constrain(angY, -78, 102); // ajustato para o angulo em que o giroscopio foi colado 

  int x_raw = map(angX, -90, 90, 0, 180);
  int y_raw = map(angY, -78, 102, 0, 180);

  Serial2.print(x_raw);
  Serial2.print(",");
  Serial2.println(y_raw);
 
  Serial.print(" || Servo: ");
  Serial.print(x_raw);
  Serial.print(", ");
  Serial.println(y_raw);
  
  delay(5);
}
