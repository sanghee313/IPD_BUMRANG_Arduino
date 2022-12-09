/**
1.수위 낮음 => 12v 펌프 작동 => 수위 높음 => 12v 펌프 정지 
2.처음으로 물 수위가 높아졌을때 모터 작동
3.버튼을 만들어서 사람들이 모터가 회전하는 설정값을 만듬.
*/

/**
1.여기서 해야될거 => 모터가 회전 중일때 솔레노이드 벨브가 작동이 되지않게 값을 보내는 데이터를 보냄

2.WaterTank1와 시리얼 통신을 하여 모터 작동시 솔베노이드가 작동이 안되게 제어
  모터 작동    시 OFF 전송 
  모터 작동 안할시 ON  전송 
*/

#define WLS_PIN_L 5   // 수위센서 핀 번호  LOW 4번 
#define WLS_PIN_H 4   // 수위센서 핀 번호  HIGH 5번
#define PUMP_PIN 6    // 펌프 핀 번호 6번
#define SPIN_PIN 7    // 회전 모터 핀 번호 7번 
#define SPIN_BUTTON 8 // 회전 모터 버튼
#define SPIN_STATE 9  // 회전 모터 상태 전송 


int MotorState = 0;
unsigned long int preTime = 0;
 
void setup() {
  Serial.begin(9600);       // 시리얼 모니터 출력을 위한 시리얼
  pinMode(WLS_PIN_L, INPUT);  // 수위센서 LOW핀을 입력 핀으로 설정
  pinMode(WLS_PIN_H, INPUT);  // 수위센서 HIGH핀을 입력 핀으로 설정
  pinMode(SPIN_PIN, OUTPUT);  //릴레이 신호용 아두이노 디지털 핀을 출력으로 설정 
  pinMode(SPIN_BUTTON,INPUT_PULLUP); // 펌프핀 번튼 입력 설정 
  pinMode(PUMP_PIN,OUTPUT);   //펌프 핀 번호 8번 
  pinMode(SPIN_STATE,OUTPUT); //스핀상태 워터 탱크1에 5v 0v 전송
}

void loop() {
  int val_low = digitalRead(WLS_PIN_L); // 수위센서 핀으로부터 값 받아오기
  int val_high = digitalRead(WLS_PIN_H);
  unsigned long int currentTime = millis();

  if( currentTime - preTime > 10000){ // 수위 센서는 10초마다 확인한다.
    preTime = currentTime;
      /**수중 센서 에 의한 24v 모터 제어*/
    if (val_low == HIGH && val_high == HIGH) //물이 부족한 상태 
    { 
      digitalWrite(PUMP_PIN, HIGH); //릴레이 접점 ON -> 물채우기
      delay(5000); //5초 대기
      digitalWrite(PUMP_PIN, LOW); //릴레이 접점 OFF
      MotorState = 0;
    }
    else if(val_low == LOW && val_high == LOW)  //물이 가득찬 상태
    {  
      if(MotorState == 0)  //MotorState 가 0 값이면 회전 한다.
      {  
        Serial.println("First Water Filled");
        digitalWrite(SPIN_STATE, HIGH); //회전 상태 전송 ON
        digitalWrite(SPIN_PIN, HIGH); //릴레이 접점 ON -> 물채우기
        delay(30000); //30초 대기
        digitalWrite(SPIN_PIN, LOW); //릴레이 접점 OFF
        digitalWrite(SPIN_STATE, HIGH); //회전 상태 전송 OFF
        MotorState++;
      }
      else
      { 
        Serial.println("Already Rotate");
        MotorState++;  
      }
    }      
  }       

  /**버튼 클릭에 의한 회전 모터 적용*/
  if(digitalRead(SPIN_BUTTON) == HIGH)
  {
    digitalWrite(SPIN_STATE, HIGH); //회전 상태 전송 ON
    digitalWrite(SPIN_PIN,HIGH);
    Serial.println("SPIN_MOTOR_ON");
    delay(1000);
  }
  else
  {
    digitalWrite(SPIN_PIN, LOW);
    digitalWrite(SPIN_STATE, LOW); 
    Serial.println("SPIN_MOTOR_OFF");  
  }

  

}
