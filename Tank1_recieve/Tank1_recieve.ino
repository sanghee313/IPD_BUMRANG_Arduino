int data;
void setup() {
  Serial.begin(9600);
  pinMode(5,INPUT);

}
void loop() {
  data = digitalRead(5);
  if(data == 1)
  {
    Serial.println("State_High");
    delay(1000);
  }
  else if(data ==0)
  {
    Serial.println("State_Low");
    delay(1000);   
  }
}