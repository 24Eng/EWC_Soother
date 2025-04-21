/*
The fours functions come from the NimBLE examples
*/
// ====================================================================================
// Event handlers for incoming MIDI messages
// ====================================================================================
// -----------------------------------------------------------------------------
// Device connected
// -----------------------------------------------------------------------------
void OnConnected() {
  isConnected = true;
  Serial.print(F("Bluetooth connected\n"));
}
// -----------------------------------------------------------------------------
// Device disconnected
// -----------------------------------------------------------------------------
void OnDisconnected() {
  isConnected = false;
  Serial.print(F("Bluetooth disconnected\n"));
}
// -----------------------------------------------------------------------------
// Received note on
// -----------------------------------------------------------------------------
void OnNoteOn(byte channel, byte note, byte velocity) {
}
// -----------------------------------------------------------------------------
// Received note off
// -----------------------------------------------------------------------------
void OnNoteOff(byte channel, byte note, byte velocity) {
}


void sendBluetoothCommand(int funOne, int funTwo, int funThree){
  if(menuBluetooth.getCurrentValue() == 1){
    if(funOne >= 0x90 && funOne < 0xA0){
      MIDI.sendNoteOn(funTwo, funThree, 1);
    }
    if(funOne >= 0x80 && funOne < 0x90){
      MIDI.sendNoteOff(funTwo, funThree, 1);
    }
  }
}
