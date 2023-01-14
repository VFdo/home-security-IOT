// transmitter and receiver
#include <RH_ASK.h>
#include <SPI.h>
// wifi
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
// telegram
#include <UniversalTelegramBot.h>

#define BOTtoken "5687077345:AAE5-pWkLch0eBgHWRkJ-6a59ZwefsPa3UQ"  // Bot token 
char ssid[] = "Everyday Im Buffering!";         // Wifi SSID 
char password[] = "P@ssw0rd";     // Wifi Password


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 800;
long Bot_lasttime;  

RH_ASK driver(2000, 14, 12);
int buzzerPin=15;

#define MQ2pin A0
float sensorValue; 
 
#define LED D0

 
void setup()
{
  Serial.begin(9600);
  Serial.write("test");
  driver.init();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);}

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(10);
  client.setInsecure();
 pinMode(LED, OUTPUT);
  pinMode(buzzerPin,OUTPUT);

}

void loop()
{
  checkForSignal();
  checkMessagesEveryNMillis();
}

// ************* TRANSMITTER_RECEIVER
void checkForSignal(){
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))
  {
    for (int i = 0; i < buflen; i++) {
      Serial.write(buf[i]);
    }
    Serial.write('\n');
      digitalWrite(buzzerPin,HIGH);
    delay(1000);
    digitalWrite(buzzerPin,LOW);
    bot.sendMessage("945593826", "Motion Detected");
  }
}

void checkMessagesEveryNMillis(){
    if (millis() > Bot_lasttime + Bot_mtbs)  {
      checkAirQuality();
      Bot_lasttime = millis();
  }
}

// ************* SMOKE_DETECTOR
float sensorReadArr[5];
int cnt;
bool isSmokeActivated=0;
float avg;
void checkAirQuality(){
      digitalWrite(LED, LOW);
    	sensorValue = analogRead(MQ2pin); // read analog input pin 0
      sensorReadArr[cnt]= sensorValue;
      cnt++;
      if(cnt>=4){
        cnt=0;
      }

    avg =findAverage();

    if(avg>300){
      if(isSmokeActivated){
      digitalWrite(LED, HIGH);
      bot.sendMessage("945593826", "Smoke Detected");
        isSmokeActivated=false;
      }
    }
    if(avg<300){
      isSmokeActivated=true;
       
    }
}

float findAverage(){
  float total;
  for(int i =0;i<5;i++){
      total+=sensorReadArr[i];
  }
  return total/5;
}
