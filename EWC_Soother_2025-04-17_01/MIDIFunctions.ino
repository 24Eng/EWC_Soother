// The following are functions from Adafruit
void midiSetInstrument(uint8_t chan, uint8_t inst) {
  if (chan > 15) return;
  //  inst --; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127) return;

  MySerial1.write(0xC0 | chan);
  delay(10);
  MySerial1.write(inst);
  delay(10);
}

void MIDICommand(uint8_t funCommand, uint8_t n, uint8_t vel) {
  if (n > 127) {
    Serial.print(F("Note out of range\n"));
    return;
  }
  if (vel > 127) {
    Serial.print(F("Velocity out of range\n"));
    return;
  }
  
  MySerial1.write(funCommand);
  MySerial1.write(n);
  MySerial1.write(vel);
  printMIDICommand(funCommand, n, vel);
  sendBluetoothCommand(funCommand, n, vel);
}

void printMIDICommand(int funOne, int funTwo, int funThree){
  if(verboseFeedback){
    Serial.print(F("MIDI Command: "));
    Serial.print(funOne, DEC);
    Serial.print(", ");
    Serial.print(funTwo, DEC);
    Serial.print(", ");
    Serial.print(funThree, DEC);
    Serial.print("\n");
  }
}

// PANIC uses a global variable called PANICCount
void panicMode() {
  for (int i = 0; i < 127; i++) {
    MIDICommand(0x80 + PANICCount, i, 0);
  }
  PANICCount++;
  if (PANICCount > 15) {
    panicModeBool = false;
    PANICCount = 0;
    Serial.print(F("Panic complete\n"));
  }
}

void musicTasks() {
  if (panicModeBool) {
    panicMode();
  }
  if(menuLoopOnOrOff.getBoolean()){
    loopTasks();
  }
}

void loopTasks(){
  if(loopPlaying){
    if(!loopBegun){
      playbackLengthCounter = currentNoteRecordCounter;
      loopBegun = true;
      currentNotePlayCounter = 0;
      playbackStartTime = millis() + menuDelayBetweenLoops.getCurrentValue();
      Serial.print("Starting a new loop.\n");
    }
    // Check the recorded loop for any times that need to be played
    // Play them, and advance the playback counter
    if(millis() >= (loopRecordTime[currentNotePlayCounter]+playbackStartTime)){
      Serial.print("Loop playback:\t");
      Serial.print(loopRecordNotes[currentNotePlayCounter][0]);
      Serial.print(", ");
      Serial.print(loopRecordNotes[currentNotePlayCounter][1]);
      Serial.print(", ");
      Serial.print(loopRecordNotes[currentNotePlayCounter][2]);
      Serial.print("\n");
      MIDICommand(loopRecordNotes[currentNotePlayCounter][0], loopRecordNotes[currentNotePlayCounter][1], loopRecordNotes[currentNotePlayCounter][2]);
      serialMessage[0] = loopRecordNotes[currentNotePlayCounter][0];
      serialMessage[1] = loopRecordNotes[currentNotePlayCounter][1];
      serialMessage[2] = loopRecordNotes[currentNotePlayCounter][2];
      addChordMessages();
      currentNotePlayCounter++;
    }
    if(currentNotePlayCounter > playbackLengthCounter){
      loopBegun = false;
    }
    
  }
  if((millis() > loopTimeoutTimer) && (loopRecording)){
    finishALoop();
  }
}

void startALoop(){
  loopRecording = false;
  loopPlaying = false;
  currentNotePlayCounter = 0;
  loopTimeoutTimer = millis() + loopTimeout;
  menuLoopOnOrOff.setBoolean(true);
}

void finishALoop(){
  loopRecording = false;
  loopPlaying = true;
  Serial.print("Loop:\t");
  for(int i=0;i<currentNoteRecordCounter;i++){
    for(int k=0;k<3;k++){
      Serial.print(loopRecordNotes[i][k], HEX);
      if(k<2){
        Serial.print(", ");
      }
    }
    Serial.print("\t");
  }
  Serial.print("\n");
}

void addNotesToLoop(){
  for(int i=0; i<3;i++){
    loopRecordNotes[currentNoteRecordCounter][i] = serialMessage[i];
  }
  loopRecordTime[currentNoteRecordCounter] = millis() - firstNoteTime;
  currentNoteRecordCounter++;
  if(currentNoteRecordCounter > maxNotes){
    currentNoteRecordCounter = 0;
    Serial.print("Maxed out the notes");
  }
  loopTimeoutTimer = millis() + loopTimeout;
}

void processLoop(){
  if(menuLoopOnOrOff.getBoolean()){
    if(loopRecording && (serialMessage[1] > 11)){
      addNotesToLoop();
    }
    if(!loopRecording && !loopPlaying && (serialMessage[1] > 11)){
      // Record the first note
      currentNoteRecordCounter = 0;
      startTime = 0;
      firstNoteTime = millis();
      loopRecording = true;
      if(serialMessage[1] > 11){
        addNotesToLoop();
      }
      Serial.print("Recording started\n");
    }
  }
}

void shiftOctavePitch(){
  int funOctaveNumber = serialMessage[1] / 12;
  unscaledNote = serialMessage[1] % 12;
  if((menuOctave0ToOctave.getCurrentValue() != 0) && (funOctaveNumber == 0)){
    // Shift the octave to a different pitch
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave0ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave1ToOctave.getCurrentValue() != 1) && (funOctaveNumber == 1)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave1ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave2ToOctave.getCurrentValue() != 2) && (funOctaveNumber == 2)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave2ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave3ToOctave.getCurrentValue() != 3) && (funOctaveNumber == 3)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave3ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave4ToOctave.getCurrentValue() != 4) && (funOctaveNumber == 4)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave4ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave5ToOctave.getCurrentValue() != 5) && (funOctaveNumber == 5)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave5ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave6ToOctave.getCurrentValue() != 6) && (funOctaveNumber == 6)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave6ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave7ToOctave.getCurrentValue() != 7) && (funOctaveNumber == 7)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave7ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave8ToOctave.getCurrentValue() != 8) && (funOctaveNumber == 8)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave8ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave9ToOctave.getCurrentValue() != 9) && (funOctaveNumber == 9)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave9ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
  if((menuOctave10ToOctave.getCurrentValue() != 10) && (funOctaveNumber == 10)){
    if(verboseFeedback){
      Serial.print(F("Octave pitch reprogram: "));
      Serial.print(serialMessage[1]);
    }
    serialMessage[1] = (menuOctave10ToOctave.getCurrentValue() * 12) + unscaledNote;
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[1]);
      Serial.print("\n");
    }
  }
}

void shiftOctaveChannel(){
  int funCommand = serialMessage[0] / 0x10;
  int funChannel = serialMessage[0] % 0x10;
  int funOctave = serialMessage[1] / 12;
  
  if((menuOctave0ToChannel.getCurrentValue() != 0) && (funOctave == 0)){
    if(verboseFeedback){
      Serial.print(F("Channel 0 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave0ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave1ToChannel.getCurrentValue() != 0) && (funOctave == 1)){
    if(verboseFeedback){
      Serial.print(F("Channel 1 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave1ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave2ToChannel.getCurrentValue() != 0) && (funOctave == 2)){
    if(verboseFeedback){
      Serial.print(F("Channel 2 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave2ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave3ToChannel.getCurrentValue() != 0) && (funOctave == 3)){
    if(verboseFeedback){
      Serial.print(F("Channel 3 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave3ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave4ToChannel.getCurrentValue() != 0) && (funOctave == 4)){
    if(verboseFeedback){
      Serial.print(F("Channel 4 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave4ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave5ToChannel.getCurrentValue() != 0) && (funOctave == 5)){
    if(verboseFeedback){
      Serial.print(F("Channel 5 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave5ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave6ToChannel.getCurrentValue() != 0) && (funOctave == 6)){
    if(verboseFeedback){
      Serial.print(F("Channel 6 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave6ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave7ToChannel.getCurrentValue() != 0) && (funOctave == 7)){
    if(verboseFeedback){
      Serial.print(F("Channel 7 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave7ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave8ToChannel.getCurrentValue() != 0) && (funOctave == 8)){
    if(verboseFeedback){
      Serial.print(F("Channel 8 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave8ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave9ToChannel.getCurrentValue() != 0) && (funOctave == 9)){
    if(verboseFeedback){
      Serial.print(F("Channel 9 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave9ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
  if((menuOctave10ToChannel.getCurrentValue() != 0) && (funOctave == 10)){
    if(verboseFeedback){
      Serial.print(F("Channel 10 reprogram: "));
      Serial.print(serialMessage[0]);
    }
    serialMessage[0] = ((funCommand * 0x10) + menuOctave10ToChannel.getCurrentValue());
    if(verboseFeedback){
      Serial.print(" to ");
      Serial.print(serialMessage[0]);
      Serial.print("\n");
    }
  }
}
