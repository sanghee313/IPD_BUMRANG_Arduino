void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}
void loop() {
   digitalWrite(8,1);
   delay(1000);
   digitalWrite(8,0);
   delay(1000);
}