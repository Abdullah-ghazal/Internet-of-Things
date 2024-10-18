#define distance_to_tank_bottom   10   // distance from sensor to zero% level
#define max_distance    2              // distance from sensor to 100% level
 
#define trigPin  12
#define echoPin  13
 
#define led1     32
#define led2     33
#define led3     25
#define led4     26
#define led5     27
#define buzzer   14  // use buzzer or LED
 
int tank_depth= distance_to_tank_bottom-max_distance;
/////////////// ultrasonic sensor variables 
long duration=0;
int distance=0;
int sensor_reading=0;
int water_level=0;
 
int is_notification_sent=0;
 
 
//---------------------------- Blynk definitions
/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2zmDpyF8f"
#define BLYNK_TEMPLATE_NAME "Water Level meter"
#define BLYNK_AUTH_TOKEN "nqgGEkPi57uQ3Fo-fURI0If2DWKe9eRf"

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2zmDpyF8f"
#define BLYNK_TEMPLATE_NAME "Water Level meter"
#define BLYNK_AUTH_TOKEN "Your Auth Token"
 
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
 
// Your WiFi credentials.
// Set passwordo to "" for open networks.
char ssid[] = "Orange-orange";
char pass[] = "A13131313#1";
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
 
 Blynk.virtualWrite(V0,water_level);
//------------------------------ calculating water level
 sensor_reading=read_ultrasonic_sensor();
 if(sensor_reading>distance_to_tank_bottom)sensor_reading=distance_to_tank_bottom;
 else if(sensor_reading<max_distance)sensor_reading=max_distance;
int sen_red1,sen_red2, av_red;
sen_red

 sensor_reading=sensor_reading-max_distance;
 sensor_reading=tank_depth-sensor_reading;
 water_level=sensor_reading*100/tank_depth;

//------------------------------ end of calculating water level
 
 Serial.println(water_level); 
 if(water_level>=0 && water_level<20 )
 { 
 digitalWrite(led1,LOW);
 digitalWrite(led2,LOW);
 digitalWrite(led3,LOW);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 digitalWrite(buzzer,HIGH);delay(50);digitalWrite(buzzer,LOW);delay(30);
 
 if(is_notification_sent==0)
    {
      Blynk.logEvent("alert", "The water level is low.\n\n   مستوى الماء منخفض");
      is_notification_sent=1;
    }
 
 }
 else if(water_level>=20 && water_level<40 )
 { 
 digitalWrite(led1,HIGH);
 digitalWrite(led2,LOW);
 digitalWrite(led3,LOW);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 is_notification_sent=0;
 }
 else if(water_level>=40 && water_level<60 )
 { 
 digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 digitalWrite(led3,LOW);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 is_notification_sent=0;
 }
 else if(water_level>=60 && water_level<80 )
 { 
 digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 digitalWrite(led3,HIGH);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 is_notification_sent=0;
 }
 else if(water_level>=80 && water_level<100 )
 { 
  digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 digitalWrite(led3,HIGH);
 digitalWrite(led4,HIGH);
 digitalWrite(led5,LOW);
 is_notification_sent=0;
 }
 else
 {
 digitalWrite(led1,HIGH);
 digitalWrite(led2,HIGH);
 digitalWrite(led3,HIGH);
 digitalWrite(led4,HIGH);
 digitalWrite(led5,HIGH);
 is_notification_sent=0;
 }
}
 
//---------------------------- End of Blynk definitions
 
void setup() {
 
//---------------------------- Blynk initialization
Serial.begin(115200);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
// Setup a function to be called every second
timer.setInterval(1000L, myTimerEvent);
//---------------------------- End of Blynk initialization
 
  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 
  
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(led5,OUTPUT);
 pinMode(buzzer,OUTPUT);
 digitalWrite(led1,LOW);
 digitalWrite(led2,LOW);
 digitalWrite(led3,LOW);
 digitalWrite(led4,LOW);
 digitalWrite(led5,LOW);
 digitalWrite(buzzer,LOW);
 
}
void loop() {
//---------------------------- Blynk Loop
Blynk.run();
timer.run(); // Initiates BlynkTimer
if ( ! Blynk.connected() )
{
  while ( ! Blynk.connected() )
   {
    // try connect again
    Serial.println("-Try to connect");
    delay(100);
   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
   }
 
    Serial.println("-Connected.. ^_^ ");
    delay(500);
 }
 
 
//---------------------------- End of Blynk Loop
 
 
 
}
 
 
int read_ultrasonic_sensor()
{
  digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        distance = duration * 0.017;
        if (distance >= 4 )
        {
          
          return distance;
        }
        else return 0;
}