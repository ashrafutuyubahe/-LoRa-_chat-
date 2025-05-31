#include <SPI.h>
#include <RH_RF95.h>

// Pin definitions
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

// LoRa frequency (make sure both sides match)
#define RF95_FREQ 952.2

// Radio driver instance
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  pinMode(12, OUTPUT); // Output pin for ON/OFF control
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  delay(100);
  Serial.println("LoRa Chat!");

  // Manual reset of LoRa module
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Set frequency
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: ");
  Serial.println(RF95_FREQ);

  // Set TX power (max is 23 for RH_RF95)
  rf95.setTxPower(23, false);
}

void loop() {
  // Receive logic
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      buf[len] = '\0'; // Ensure it's null-terminated
      String mString = String((char*)buf);

      if (mString.indexOf("ON") >= 0) {
        digitalWrite(12, LOW); //Turn ON
        delay(100);
      }

      if (mString.indexOf("OFF") >= 0) {
        digitalWrite(12, HIGH); //Turn 
        delay(100);
      }

      Serial.print("Received: ");
      Serial.println(mString);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      Serial.println("***");
    } else {
      Serial.println("Receive failed");
    }
  }

  // Transmit logic (from serial input)
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any whitespace or newline

    if (input.length() > 0) {
      Serial.print("Sent: ");
      Serial.println(input);

      rf95.send((uint8_t *)input.c_str(), input.length());
      rf95.waitPacketSent();

      Serial.println("***");
    }
  }
}