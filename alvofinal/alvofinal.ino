#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define WIFI_CHANNEL 1

//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteMac[] = {0xA0, 0x20, 0xA6, 0x25, 0x1F, 0x35};
const byte dataLength=7;
byte cnt=0;
byte rcvData[dataLength];
byte result;

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
const uint16_t kRecvPin = 14;

IRrecv irrecv(kRecvPin);

decode_results results;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  Serial.print("\r\n\r\nDevice MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Controller.");
  esp_now_init();
  delay(10);
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0);
  
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
}
  
void loop()
{
  for(cnt=0; cnt<dataLength; cnt++)
  {
    rcvData[cnt]++;
  }

  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");
    result = esp_now_send(remoteMac, rcvData, dataLength);
    Serial.println(result);
    irrecv.resume();  // Receive the next value
  }
  delay(100);

}
