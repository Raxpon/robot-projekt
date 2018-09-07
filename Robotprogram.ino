#include "MeMegaPi.h"

byte ReciveDataBuffer[16];
byte TransmitBuffer[16];
byte cnt=0;
MeMegaPiDCMotor klo1(PORT2B);
MeMegaPiDCMotor motor1(PORT1A);
MeMegaPiDCMotor motor2(PORT1B);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
  //Serial3.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  isDataRecieved();
  delay(100);
}  

void isDataRecieved(){
  byte readData=0;
  byte nof_data=0;
  cnt=0;
  if(Serial3.available()!=(int)0)
  {
    Serial.println("Data recieved");
    while(Serial3.available()!=(int)0)
    {
      Serial.println(Serial3.available());
      readData=Serial3.read();
      ReciveDataBuffer[cnt]=readData;
      cnt++;
      nof_data++;
      delay(1);
    }
    DecodeData(nof_data);
  }
}

void DecodeData(byte nofData){
  for(int cnt =0;cnt<nofData;cnt ++){
    TransmitBuffer[cnt]=ReciveDataBuffer[cnt];
	switch (ReciveDataBuffer[cnt])
	{
	case 0:
		cnt++;
		motor();
	case 1:
		cnt++;
		klo();
	default:
		break;
	}
  }
  SendData(nofData);
}
void motor()
{
	motor1.run(ReciveDataBuffer[cnt]);
	cnt++;
	motor2.run(ReciveDataBuffer[cnt]);
	cnt++; /*den 4. byte bestemer hvor lang tid moterne skal køre*/
	delay(ReciveDataBuffer[cnt]);
	motor1.stop();
	motor2.stop();
	cnt = 0;
	delay(1);
}
void klo()
{
	switch (ReciveDataBuffer[cnt])
	{
	case 0:

	default:
		break;
	}

}
void SendData(byte nofData){
  for(int cnt=0;cnt<nofData;cnt++){
    Serial3.write(TransmitBuffer[cnt]);
    delay(1);
  }
}

