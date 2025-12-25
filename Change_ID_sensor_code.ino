#include <ModbusMaster.h>

// ====== CHAN NOI ======
#define MAX485_DE_RE  19
#define RX_PIN        17
#define TX_PIN        16

// ====== MODBUS ======
#define OLD_SLAVE_ID  1     // ID HIEN TAI
#define NEW_SLAVE_ID  2     // ID MUON DOI
#define ID_REGISTER   0x0101   // Thanh ghi doi ID (theo datasheet)

ModbusMaster node;

// ----- RS485 direction control -----
void preTransmission() {
  digitalWrite(MAX485_DE_RE, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_DE_RE, LOW);
}
// ----------------------------------

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("=== ESP32 DOI SLAVE ID MODBUS ===");

  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);   // RS485 idle = receive

  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  // Ket noi toi slave co ID hien tai = 8
  node.begin(OLD_SLAVE_ID, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Serial.print("Dang doi ID tu ");
  Serial.print(OLD_SLAVE_ID);
  Serial.print(" -> ");
  Serial.println(NEW_SLAVE_ID);

  uint8_t result = node.writeSingleRegister(ID_REGISTER, NEW_SLAVE_ID);

  if (result == node.ku8MBSuccess) {
    Serial.println("✔ DOI ID THANH CONG");
    Serial.println("👉 Hay NGAT NGUON slave va cap lai");
  } else {
    Serial.print("✖ DOI ID THAT BAI - Loi: 0x");
    Serial.println(result, HEX);
  }
}

void loop() {
  // Khong lam gi trong loop
}
