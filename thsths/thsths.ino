#include <Servo.h>

Servo servos[5];  // 5개의 서보 모터를 위한 배열
int sensorPins[5] = {A0, A1, A2, A3, A4}; // 압력 센서가 연결된 아날로그 핀
int angle[5] = {0, 0, 0, 0, 0}; // 서보 모터 각도
int originalAngle[5] = {0, 0, 0, 0, 0}; // 원래 각도 저장
int threshold = 100; // 센서 값의 임계치
int moveAngle = 30; // 이동할 각도

void setup() {
  Serial.begin(9600);
  
  // 각 서보 모터를 연결
  for (int i = 0; i < 5; i++) {
    servos[i].attach(9 + i); // 서보 모터 핀 (9, 10, 11, 12, 13)
    originalAngle[i] = servos[i].read(); // 초기 각도를 저장
  }

  Serial.println("Press the conductive fabric to move the servo motors.");
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int sensorValue = analogRead(sensorPins[i]); // 압력 센서 값 읽기
    
    if (sensorValue > threshold) {
      // 임계치 초과 시 서보 모터를 이동
      int targetAngle = originalAngle[i] + moveAngle;
      targetAngle = constrain(targetAngle, 0, 180); // 각도를 0~180 사이로 제한
      servos[i].write(targetAngle); // 서보 모터에 각도 전송
      Serial.print("Servo ");
      Serial.print(i);
      Serial.print(" moved to angle: ");
      Serial.println(targetAngle);
      
      delay(1000); // 1초 동안 대기
      servos[i].write(originalAngle[i]); // 원래 각도로 되돌리기
      Serial.print("Servo ");
      Serial.print(i);
      Serial.print(" returned to angle: ");
      Serial.println(originalAngle[i]);
    }
  }

  delay(100); // 주기적으로 센서 값을 읽기 위해 지연
}
