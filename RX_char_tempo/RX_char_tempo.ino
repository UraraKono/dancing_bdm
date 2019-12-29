#include <VirtualWire.h>

#define RECV_PIN 12
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("receiver setup");

  vw_set_rx_pin(RECV_PIN);
  vw_setup(5000);
  vw_rx_start();
}

void loop() {
  vw_wait_rx();
  if (vw_get_message(buf, &buflen)) {
    for (int i = 0; i < buflen; i++) {
      Serial.println(buf[i], DEC);
    }
  }
  //else Serial.println("No msg");
}
