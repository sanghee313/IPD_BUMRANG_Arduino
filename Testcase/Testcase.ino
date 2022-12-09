/**
WaterTank_1 물 작동 시스템 
1.물 마시는 버튼 클릭 => 5v 펌프 작동
2. 수위 낮아지면 => 솔레노이드 벨브 멸기 => 수위 높아지면 솔레노이드 벨브 닫음   
3. WaterTank2의 데이터 값 받음.
*/
#define WLS_PIN_L 4   // 수위센서 핀 번호  LOW 4번 
#define WLS_PIN_H 5   // 수위센서 핀 번호  HIGH 5번
#define solve_PIN 6    // 솔베노이드 핀 번호 6번

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);       // 시리얼 모니터 출력을 위한 시리얼
  pinMode(WLS_PIN_L, INPUT);  // 수위센서 LOW핀을 입력 핀으로 설정
  pinMode(WLS_PIN_H, INPUT);  // 수위센서 HIGH핀을 입력 핀으로 설정

}

void loop() {
  int val_low = digitalRead(WLS_PIN_L); // 수위센서 핀으로부터 값 받아오기
  int val_high = digitalRead(WLS_PIN_H);
  Serial.print("val_low : ");
  Serial.println(val_low);
  Serial.print("val_high : ");
  Serial.println(val_high);
  delay(2000);
}
