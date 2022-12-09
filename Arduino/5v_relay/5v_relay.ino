// 아두이노 릴레이모듈 실험
// 1초마다 ON/OFF를 반복합니다. 1초마다 릴레이 접점이 붙었다 떨어지는 "딸깍"소리를 들을 수 있습니다.

const int relayPin = 6; //릴레이 신호핀(S)에 연결되는 아두이노 핀


void setup()
{
  pinMode(relayPin, OUTPUT); //릴레이 신호용 아두이노 디지털 핀을 출력으로 설정
}

void loop()
{
  digitalWrite(relayPin, HIGH); //릴레이 접점 ON
  delay(5000); //1초 대기
  digitalWrite(relayPin, LOW); //릴레이 접점 OFF
  delay(1000); //1초 대기

}
