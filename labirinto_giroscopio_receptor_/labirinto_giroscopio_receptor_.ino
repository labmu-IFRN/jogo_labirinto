#include <Servo.h>

Servo servoX;
Servo servoY;

String dados = "";

int x = 90, y = 90;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  servoX.attach(9);
  servoY.attach(10);

  dados.reserve(20);
  servoX.write(90);
  servoY.write(90);

  Serial.println("Receptor pronto");
}

void loop() {
  while (Serial2.available()) {
    char c = Serial2.read();

    if (c == '\n') {
      int separador = dados.indexOf(',');

      if (separador > 0) {
        x = dados.substring(0, separador).toInt();
        y = dados.substring(separador + 1).toInt();

        x = constrain(x, 0, 180);
        y = constrain(y, 0, 180);
      }

      dados = "";
    } else {
      dados += c;
    }
  }

  servoX.write(x);
  servoY.write(y);

  Serial.print("Servo: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);

  delay(10);
}
