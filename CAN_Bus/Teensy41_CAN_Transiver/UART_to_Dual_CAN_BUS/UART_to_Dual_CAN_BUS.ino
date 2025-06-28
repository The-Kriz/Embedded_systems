#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> MCU_CAN;  // 500kbps
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> BMS_CAN;   // 250kbps

// Output pins (optocouplers)
const uint8_t outputPins[10] = {21, 19, 17, 15, 14, 41, 39, 37, 35, 33};
volatile uint16_t outputStates = 0;
volatile bool statesChanged = false;

volatile bool canMessageReady = false;
CAN_message_t outgoingCANMessage;

void setup() {
  Serial.begin(1000000); // 1Mbps UART
  while (!Serial);

  MCU_CAN.begin();
  MCU_CAN.setBaudRate(500000);
  BMS_CAN.begin();
  BMS_CAN.setBaudRate(250000);

  for (int i = 0; i < 10; i++) {
    pinMode(outputPins[i], OUTPUT);
  }

  Serial.println("System Ready");
  Serial.println("Send commands:");
  Serial.println("R:1,B:0,... - Set outputs");
  Serial.println("U:ID:EXT:LEN:DATA - Send CAN message");
  Serial.println("Z:? - Query states");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.startsWith("U:")) {
      if (parseCANMessage(input)) {
        sendCANMessage();
      }
    } 
    else {
      handleStateUpdate(input);
    }
  }
  if (statesChanged) {
    updateOutputs();
    statesChanged = false;
  }
}

// ----------------------------------------
// CAN MESSAGE FUNCTIONS
// ----------------------------------------
bool parseCANMessage(String msg) {
  msg = msg.substring(2); // Remove "U:"
  
  // Format: ID:EXT:LEN:DATA (e.g., "123:0:8:AA:BB:CC:DD:EE:FF:11:22")
  int colon1 = msg.indexOf(':');
  int colon2 = msg.indexOf(':', colon1 + 1);
  int colon3 = msg.indexOf(':', colon2 + 1);

  if (colon1 == -1 || colon2 == -1 || colon3 == -1) {
    Serial.println("ERR: Invalid CAN format");
    return false;
  }

  outgoingCANMessage.id = strtoul(msg.substring(0, colon1).c_str(), NULL, 16);
  outgoingCANMessage.flags.extended = msg.substring(colon1 + 1, colon2).toInt();
  outgoingCANMessage.len = msg.substring(colon2 + 1, colon3).toInt();

  String dataStr = msg.substring(colon3 + 1);
  int dataIndex = 0;
  int lastSplit = 0;

  for (int i = 0; i <= dataStr.length(); i++) {
    if (i == dataStr.length() || dataStr.charAt(i) == ':') {
      outgoingCANMessage.buf[dataIndex++] = strtoul(dataStr.substring(lastSplit, i).c_str(), NULL, 16);
      lastSplit = i + 1;
      if (dataIndex >= 8) break;
    }
  }

  return true;
}

void sendCANMessage() {
  if (outgoingCANMessage.flags.extended) {
    BMS_CAN.write(outgoingCANMessage);
    Serial.print("Sent EXT CAN ID 0x");
  } else {
    MCU_CAN.write(outgoingCANMessage);
    Serial.print("Sent STD CAN ID 0x");
  }
  Serial.println(outgoingCANMessage.id, HEX);
}

// ----------------------------------------
// OUTPUT CONTROL FUNCTIONS
// ----------------------------------------
void handleStateUpdate(String msg) {
  if (msg == "Z:?") {
    sendCurrentStates();
    return;
  }
  // Parse comma-separated pairs (e.g., "R:1,B:0,L:1")
  int startIdx = 0;
  int commaIdx = msg.indexOf(',');

  while (commaIdx != -1 || startIdx < msg.length()) {
    String pair = msg.substring(startIdx, commaIdx != -1 ? commaIdx : msg.length());
    pair.trim();

    if (pair.length() >= 3 && pair.charAt(1) == ':') {
      char pin = pair.charAt(0);
      bool state = pair.substring(2).toInt() > 0;
      updateOutputState(pin, state);
    }

    startIdx = commaIdx + 1;
    commaIdx = msg.indexOf(',', startIdx);
  }
}

void updateOutputState(char key, bool state) {
  uint8_t pinIndex = 0xFF;

  switch (key) {
    case 'R': pinIndex = 0; break;
    case 'B': pinIndex = 1; break;
    case 'C': pinIndex = 2; break;
    case 'L': pinIndex = 3; break;
    case 'W': pinIndex = 4; break;
    case 'S': pinIndex = 5; break;
    case 'I': pinIndex = 6; break;
    case 'H': pinIndex = 7; break;
    case 'K': pinIndex = 8; break;
    case 'M': pinIndex = 9; break; 
  }

  if (pinIndex != 0xFF) {
    if (state) outputStates |= (1 << pinIndex);
    else outputStates &= ~(1 << pinIndex);
    statesChanged = true;
  }
}

void updateOutputs() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(outputPins[i], (outputStates >> i) & 1);
  }
}

void sendCurrentStates() {
  Serial.print("States: ");
  Serial.print("R:"); Serial.print((outputStates >> 0) & 1);
  Serial.print(",B:"); Serial.print((outputStates >> 1) & 1);
  Serial.print(",C:"); Serial.print((outputStates >> 2) & 1);
  Serial.print(",L:"); Serial.print((outputStates >> 3) & 1);
  Serial.print(",W:"); Serial.print((outputStates >> 4) & 1);
  Serial.print(",S:"); Serial.print((outputStates >> 5) & 1);
  Serial.print(",I:"); Serial.print((outputStates >> 6) & 1);
  Serial.print(",H:"); Serial.print((outputStates >> 7) & 1);
  Serial.print(",K:"); Serial.print((outputStates >> 8) & 1);
  Serial.print(",M:"); Serial.print((outputStates >> 9) & 1);
  Serial.println();
}
