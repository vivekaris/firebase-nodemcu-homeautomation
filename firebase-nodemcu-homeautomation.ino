
#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
// give firebase details
#define FIREBASE_HOST "firebasedb name"
#define FIREBASE_AUTH "secret_token"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PSW"                                //Password of your wifi network 

#define Relay1 12 //D6
int val1;

#define Relay2 14 //D2
int val2;

#define Relay3 4  //D1
int val3;

#define Relay4 5 //D5
int val4;

void setup() 
{
  Serial.begin(115200);          // Select the same baud rate on Serial Monitor for debug
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);
  pinMode(Relay4,OUTPUT);

  digitalWrite(Relay1,HIGH);
  digitalWrite(Relay2,HIGH);
  digitalWrite(Relay3,HIGH);
  digitalWrite(Relay4,HIGH);



  
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setString("light","0");                     
  Firebase.setString("fan","0"); 
  Firebase.setString("cooler","0"); 
  Firebase.setString("ac","0"); 
  
}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  }

void loop() 
{
  if (Firebase.failed())
      {
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
      firebasereconnect();
      return;
      }
      
  val1=Firebase.getString("light").toInt();                 //value  from the firebase
  Serial.println(val1);
  if(val1==1)                                                             // If, the Status is 1, turn on the Relay1
     {
      digitalWrite(Relay1,LOW);
      Serial.println("light 1 ON");
    }
    else if(val1==0)                                                      // If, the Status is 0, turn Off the Relay1
    {                                      
      digitalWrite(Relay1,HIGH);
      Serial.println("light 1 OFF");
    }

  val2=Firebase.getString("fan").toInt();     //value  from the firebase          
  //Serial.println(val2);
  if(val2==1)                                                             // If, the Status is 1, turn on the Relay2
     {
      digitalWrite(Relay2,LOW);
      Serial.println("FAN ON");
    }
    else if(val2==0)                                                      // If, the Status is 0, turn Off the Relay2
    {                                      
      digitalWrite(Relay2,HIGH);
      Serial.println("Fan 2 OFF");
    }

   val3=Firebase.getString("cooler").toInt();  //value  from the firebase
  //Serial.println(val3);
  if(val3==1)                                    // If, the Status is 1, turn on the Relay3
     {
      digitalWrite(Relay3,LOW);
      Serial.println("cooler ON");
    }
    else if(val3==0)                            // If, the Status is 0, turn Off the Relay3
    {                                      
      digitalWrite(Relay3,HIGH);
      Serial.println("cooler OFF");
    }

   val4=Firebase.getString("ac").toInt();         //value  from the firebase
   //Serial.println(val4);
  if(val4==1)                                    // If, the Status is 1, turn on the Relay4
     {
      digitalWrite(Relay4,LOW);
      Serial.println("AC ON");
    }
    else if(val4==0)                         // If, the Status is 0, turn Off the Relay4
    {                                      
      digitalWrite(Relay4,HIGH);
      Serial.println("AC OFF");
    }  

      
}
