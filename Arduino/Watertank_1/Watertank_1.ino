/**
WaterTank_1 물 작동 시스템 
1.물 마시는 버튼 클릭 => 5v 펌프 작동
2. 수위 낮아지면 => 솔레노이드 벨브 멸기 => 수위 높아지면 솔레노이드 벨브 닫음   
3. WaterTank2의 데이터 값 받음.
*/
#define RECIEVE_MOTORSTATE 3 //탱크2에서 받은 모터 진행상태  
#define WLS_PIN_L 4   // 수위센서 핀 번호  LOW 4번 
#define WLS_PIN_H 5   // 수위센서 핀 번호  HIGH 5번
#define solve_PIN 6    // 솔베노이드 핀 번호 6번
#define Drink_Switch 7 // 물마시는곳 워터 펌프 작동하기 위한 버튼 
#define Drink_Relay 8 // 물마시는 펌프 릴레이 모듈

unsigned long int preTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // 시리얼 모니터 출력을 위한 시리얼
  pinMode(RECIEVE_MOTORSTATE,INPUT);
  pinMode(WLS_PIN_L, INPUT);  // 수위센서 LOW핀을 입력 핀으로 설정
  pinMode(WLS_PIN_H, INPUT);  // 수위센서 HIGH핀을 입력 핀으로 설정
  pinMode(solve_PIN,OUTPUT); // 솔베노이드 핀을 출력 핀으로 설정 
  pinMode(Drink_Switch,INPUT_PULLUP); //물마시는 버튼 입력 설정
  pinMode(Drink_Relay,OUTPUT);        //물마시는 릴레이 출력설정

}

void loop() {
  int val_low = digitalRead(WLS_PIN_L); // 수위센서 핀으로부터 값 받아오기
  int val_high = digitalRead(WLS_PIN_H);
  unsigned long int currentTime = millis();
  
  if( currentTime - preTime > 10000){ // 수위 센서는 10초마다 확인한다.
    preTime = currentTime;
      /**수중 센서에 의한 솔베노이드 작동*/
    if (val_low == HIGH && val_high == HIGH)//물이 부족한 상태
    { 
      Serial.println("WATER_LACK");
      if(RECIEVE_MOTORSTATE == HIGH)
      {
        Serial.println("Motor is Running");    
      }
      else
      {
        digitalWrite(solve_PIN, HIGH); //릴레이 접점 ON -> 물채우기
        delay(5000); //5초 대기
        digitalWrite(solve_PIN, LOW); //릴레이 접점 OFF
      }
    }
    else if(val_low == LOW && val_high == LOW)
    { //물이 가득찬 상태 
      Serial.println("WATER_FILLED");
    }
  }

  /**버튼 클릭에 의한 워터 펌프 작동 */
  if(digitalRead(Drink_Switch)==HIGH)
  {
   digitalWrite(Drink_Relay,HIGH);
   Serial.println("DRINK_ON");
  }
  else
  {
  digitalWrite(Drink_Relay,LOW);
  Serial.println("DRINK_OFF");  
  }
  delay(1000);
  
}
