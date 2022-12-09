/**
WaterTank_1 물 작동 시스템 
1.물 마시는 버튼 클릭 => 5v 펌프 작동
2. 수위 낮아지면 => 솔레노이드 벨브 멸기 => 수위 높아지면 솔레노이드 벨브 닫음   
*/
/**
Watertank_2 작동 구현 
1.수위 낮음 => 12v 펌프 작동 => 수위 높음 => 12v 펌프 정지 
2.처음으로 물 수위가 높아졌을때 모터 작동
3.버튼을 만들어서 사람들이 모터가 회전하는 설정값을 만듬.
*/
#define TANK2_WLS_PIN_L 10  //탱크2 수위 센서 핀 번호 LOW 0번 
#define TANK2_WLS_PIN_H 11  //탠크2 수위 센서 핀 번호 HIGH 1번
#define SPIN_PIN 2      //회전 모터 핀 번호 2번 
#define SPIN_BUTTON 3      //회전 모터 버튼 3번 
#define TANK1_WLS_PIN_L 4   // 탱크 1 수위센서 핀 번호  LOW 4번 
#define TANK1_WLS_PIN_H 5   // 탱크 1 수위센서 핀 번호  HIGH 5번
#define solve_PIN 6    // 솔베노이드 핀 번호 6번
#define Drink_Switch 7 // 물마시는곳 워터 펌프 작동하기 위한 버튼 
#define Drink_Relay 8 // 물마시는 펌프 릴레이 모듈
#define PUMP_PIN 9    // 12v 펌프 핀 번호 9번

int MotorCount = 0;
bool MotorState = false; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // 시리얼 모니터 출력을 위한 시리얼
  pinMode(TANK2_WLS_PIN_L, INPUT);  // TANK2 수위센서 LOW핀을 입력 핀으로 설정
  pinMode(TANK2_WLS_PIN_H, INPUT);  // TANK2 수위센서 HIGH핀을 입력 핀으로 설정
  pinMode(TANK1_WLS_PIN_L, INPUT);  // TANK1 수위센서 LOW핀을 입력 핀으로 설정
  pinMode(TANK1_WLS_PIN_H, INPUT);  // TANK1 수위센서 HIGH핀을 입력 핀으로 설정
  
  pinMode(SPIN_PIN, OUTPUT);  //릴레이 신호용 아두이노 디지털 핀을 출력으로 설정 
  pinMode(SPIN_BUTTON,INPUT_PULLUP); // 펌프핀 번튼 입력 설정 
  
  pinMode(solve_PIN,OUTPUT); // 솔베노이드 핀을 출력 핀으로 설정 
  pinMode(Drink_Switch,INPUT_PULLUP); //물마시는 버튼 입력 설정
  pinMode(Drink_Relay,OUTPUT);        //물마시는 릴레이 출력설정
  pinMode(PUMP_PIN,OUTPUT);           //12V 펌프핀 9번 받음 
}

void loop() {
  int tank1_val_low = digitalRead(TANK1_WLS_PIN_L); // 수위센서 핀으로부터 값 받아오기
  int tank1_val_high = digitalRead(TANK1_WLS_PIN_H);
  int tank2_val_low = digitalRead(TANK1_WLS_PIN_L); // 수위센서 핀으로부터 값 받아오기
  int tank2_val_high = digitalRead(TANK1_WLS_PIN_H);

  Serial.println(tank1_val_low);
  /**버튼 클릭에 의한 워터 펌프 작동 */
  if(digitalRead(Drink_Switch)==LOW)
  {
   digitalWrite(Drink_Relay,HIGH);
   Serial.println("ON");
  }
  else
  {
  digitalWrite(Drink_Relay,LOW);
  Serial.println("OFF");  
  }

  /**버튼 클릭에 의한 워터 펌프 적용*/
  if(digitalRead(SPIN_BUTTON)==LOW)
  {
    digitalWrite(SPIN_PIN,HIGH);
    Serial.println("Water_Pump_ON");
  }
  else
  {
    digitalWrite(SPIN_PIN,LOW);
    Serial.println("Water-pump_OFF");  
  }

  
  /**수중 센서에 의한 솔베노이드 작동*/
  if (tank1_val_low == HIGH && tank1_val_high == HIGH)//물이 부족한 상태
  { 
    if(MotorState == false)
    {
        Serial.println("물이 부족해요");
        digitalWrite(solve_PIN, HIGH); //릴레이 접점 ON -> 물채우기
        Serial.println("솔베노이드 열림");
        delay(5000); //5초 대기
        Serial.println("솔베노이드 닫힘");
        digitalWrite(solve_PIN, LOW); //릴레이 접점 OFF
    }
    else
    {
      Serial.println("모터가 작동이 되는 중입니다.");  
    }
  }
  else if(tank1_val_low == LOW && tank1_val_high == LOW)
  { //물이 가득찬 상태 
    Serial.println("물이 꽉찼네");
  }

  /**수중 센서에 의한 12V 모터 제어*/
  //if (tank2_val_low == HIGH && tank2_val_high == HIGH) //물이 부족한 상태 
   if (tank2_val_low == HIGH) //물이 부족한 상태 
  { 
    Serial.println("12v 펌프 작동");
    digitalWrite(PUMP_PIN, HIGH); //릴레이 접점 ON -> 물채우기
    delay(5000); //5초 대기
    digitalWrite(PUMP_PIN, LOW); //릴레이 접점 OFF
    Serial.println("12v 펌프 정지");
    MotorCount = 0;
    
  }
  //else if(tank2_val_low == LOW && tank2_val_high == LOW)  //물이 가득찬 상태
  else if(tank2_val_low == LOW)  //물이 가득찬 상태
  {  
    if(MotorState == 0)  //MotorState 가 0 값이면 회전 한다.
    {  
      Serial.println("물이 처음으로 가득 찹니다.");
      digitalWrite(SPIN_PIN, HIGH); //릴레이 접점 ON -> 물채우기
      MotorState = true;
      delay(5000); //5초 대기
      digitalWrite(SPIN_PIN, LOW); //릴레이 접점 OFF
      MotorState = false;
      MotorCount++;
      
    }
    else
    { 
      Serial.println("이미 회전 했음");
      MotorCount++;  
    } 
  }
  
}
