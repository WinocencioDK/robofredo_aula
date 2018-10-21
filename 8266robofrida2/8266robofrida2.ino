#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
  #include "user_interface.h"
}
#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
// twelve servo objects can be created on most boards

Servo myservo2;  // 

Servo myservo3;  // 

Servo myservo4;  // 

int pos1 = 0;    // variable to store the servo position

int pos2 = 0;
int pos3 = 0;
int pos4 = 0;

uint8_t mac[] = {0xA0, 0x20, 0xA6, 0x25, 0x25, 0x2C};
void initVariant() {
  wifi_set_macaddr(STATION_IF, &mac[0]);
}

byte cnt=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("\r\nESP_Now MASTER CONTROLLER\r\n");
  
  myservo1.attach(D8);  // attaches the servo on pin 6 to the servo object
  myservo2.attach(D6);  // 9
  myservo3.attach(D5);  // 10
  myservo4.attach(D2);  // 11
  myservo1.write(90);
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);

  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
      Serial.printf("Got Something length =\t%i", len);

      if(len>0){
        for (pos1 = 90; pos1 <= 120; pos1 += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
        myservo2.write(pos1);              // tell servo to go to position in variable 'pos'
        delay(20);                       // waits 15ms for the servo to reach the position
        }
      
     
        delay(100);
        
        for (pos2 = 90; pos2 >= 60; pos2 -= 1) { // goes from 180 degrees to 0 degrees
          myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
          delay(4);                       // waits 15ms for the servo to reach the position
        }  
       
        delay(100);
        
         for (pos1 = 120; pos1 >= 90; pos1 -= 1) { // goes from 180 degrees to 0 degrees
          myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
          delay(20);                       // waits 15ms for the servo to reach the position
        }
      
        
        delay(100);
      
        for (pos2 = 60; pos2 <= 90; pos2 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo2.write(pos2);              // tell servo to go to position in variable 'pos'
          delay(4);                       // waits 15ms for the servo to reach the position
        }  
        
        delay(100);
      
        for (pos3 = 80; pos3 >= 50; pos3 -= 1) { // goes from 180 degrees to 0 degrees
          myservo3.write(pos3);              // tell servo to go to position in variable 'pos'
          delay(4);                       // waits 15ms for the servo to reach the position
        }
      
        delay(100);
      
        for (pos3 = 50; pos3 <= 80; pos3 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo3.write(pos3);              // tell servo to go to position in variable 'pos'
          delay(4);                       // waits 15ms for the servo to reach the position
        }
      
        delay(100);
      
      
        //4
      
      
        for (pos4 = 60; pos4 <= 90; pos4 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo4.write(pos4);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
          delay(100);
        for (pos4 = 90; pos4 >= 60; pos4 -= 1) { // goes from 180 degrees to 0 degrees
          myservo4.write(pos4);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
          delay(100);
      
        for (pos1 = 60; pos1 <= 90; pos1 += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
          delay(100);
        for (pos1 = 90; pos1 >= 60; pos1 -= 1) { // goes from 180 degrees to 0 degrees
          myservo1.write(pos1);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15ms for the servo to reach the position
        }
        
        
      }

      
      });
}

void loop()
{
  
}
