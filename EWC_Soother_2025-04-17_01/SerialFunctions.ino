void serialTasks(){
  // read from port 1, send to port 0:
  if (MySerial1.available()) {
    int inByte = MySerial1.read();
    if(menuBypass.getCurrentValue() == 0){
      // Look for NOTE ON commands
      if(noteOnIncoming > 0){
        serialMessage[noteOnIncoming] = inByte;
        noteOnIncoming++;
        if(noteOnIncoming > 2){
          processNoteOn();
        }
      }
      if(((inByte / 0x10) == 0x9) && (noteOnIncoming == 0)){
        serialMessage[0] = inByte;
        noteOnIncoming = 1;
      }
      
      // Look for NOTE OFF commands
      if(noteOffIncoming > 0){
        serialMessage[noteOffIncoming] = inByte;
        noteOffIncoming++;
        if(noteOffIncoming > 2){
          processNoteOff();
        }
      }
      if(((inByte / 0x10) == 0x8) && (noteOffIncoming == 0)){
        serialMessage[0] = inByte;
        noteOffIncoming = 1;
      }
      if(noteOnIncoming == 0 && noteOffIncoming == 0){
        if(inByte != 248 && inByte != 254){
          noteOnIncoming = 0;
          noteOffIncoming = 0;
          MySerial1.write(inByte);
        }
      }
    }else{
      if(inByte != 248 && inByte != 254){
        noteOnIncoming = 0;
        noteOffIncoming = 0;
        MySerial1.write(inByte);
      }
    }
  }
}

void recognizePianoCommands(){
  if(serialMessage[1] == 0){
    verboseFeedback = !verboseFeedback;
    if(!verboseFeedback){
      Serial.print("Not ");
    }
    Serial.print("Printing Verbosely\n");
  }
  if(serialMessage[1] == 1){
    // Print the EEPROM values
//    showEEPROMValues();
  }
  if(serialMessage[1] == 2){
    Serial.print("Starting PANIC!\n");
    panicModeBool = true;
  }
  if(serialMessage[1] == 3){
    bool newState = !menuLoopOnOrOff.getBoolean();
    menuLoopOnOrOff.setBoolean(newState);
    loopRecording = newState;
    if(!loopRecording){
      Serial.print("No Longer ");
    }else{
      startALoop();
      Serial.print("Start ");
    }
    Serial.print("Loop Recording\n");
  }
}

void recognizePitchLimits(){
  // Change the pitch if Pitch Limiting is active and the pressed note is outside the range
  if(menuPitchLimOnOrOff.getBoolean()){
    // If the played note is below the Pitch Limiting Floor, send the Floor value
    // If the played note is above the Pitch Limitcing ceiling, send the Ceiling value
    // Otherwise, send the played note
    if(serialMessage[1] < menuPitchFloor.getCurrentValue()){
      serialMessage[1] = (menuPitchFloor.getCurrentValue());
      Serial.print("\tPitch raised: ");
      Serial.print(serialMessage[0], DEC);
      Serial.print(" ");
      Serial.print(menuPitchFloor.getCurrentValue(), DEC);
      Serial.print(" ");
      Serial.print(serialMessage[2], DEC);
      Serial.print("\n");
    }else if(serialMessage[1] > menuPitchCeiling.getCurrentValue()){
      serialMessage[1] = (menuPitchCeiling.getCurrentValue());
      Serial.print("\tPitch lowered: ");
      Serial.print(serialMessage[0], DEC);
      Serial.print(" ");
      Serial.print(menuPitchCeiling.getCurrentValue(), DEC);
      Serial.print(" ");
      Serial.print(serialMessage[2], DEC);
      Serial.print("\n");
    }
  }
}

void recognizeVelocityLimits(){
  // Lower the velocity if Velocity Limiting is active and lower than the command
  if(menuVelLimOnOrOff.getBoolean()){
    if((serialMessage[2] > menuVelocityCeiling.getCurrentValue())){
      serialMessage[2] = (menuVelocityCeiling.getCurrentValue());
      if(verboseFeedback){
        Serial.print("\tVelocity Limited: ");
        for(int i = 0; i<2; i++){
          Serial.print(serialMessage[i], DEC);
          Serial.print(" ");
        }
        Serial.print(menuVelocityCeiling.getCurrentValue());
      }
    }else if((serialMessage[2] < menuVelocityFloor.getCurrentValue())){
      serialMessage[2] = (menuVelocityFloor.getCurrentValue());
      if(verboseFeedback){
        Serial.print("\tVelocity Raised: ");
        for(int i = 0; i<2; i++){
          Serial.print(serialMessage[i], DEC);
          Serial.print(" ");
        }
        Serial.print(menuVelocityCeiling.getCurrentValue());
        Serial.print("\n");
      }
    }
  }
}

void shiftOctaves(){
  shiftOctaveChannel();
  shiftOctavePitch();
}

///|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\
// Scaling functions
//\|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/

void rescaleNote(int funScaleInterval){
  if((unscaledNote > currentScale[funScaleInterval + 0] || funScaleInterval == 0) && (unscaledNote < currentScale[funScaleInterval + 1])){
    if(verboseFeedback){
      Serial.print("Note ");
      Serial.print(serialMessage[1]);
    }
    if(menuSLPrandoMenu.getCurrentValue() == 0){
      serialMessage[1] = serialMessage[1] - (unscaledNote - currentScale[funScaleInterval]);
    }
    if(menuSLPrandoMenu.getCurrentValue() == 1){
      int funPrandomNote = serialMessage[1] - (unscaledNote - currentScale[prandomChoice + funScaleInterval]);
      prandomKeyRemapping[serialMessage[1]] = funPrandomNote;
      serialMessage[1] = funPrandomNote;
    }
    if(verboseFeedback){
      Serial.print(" reprogrammed to ");
      Serial.print(serialMessage[1]);
//      Serial.print("\tLower Limit:");
//      Serial.print(currentScale[funScaleInterval + 0]);
//      Serial.print("\tUpper Limit: ");
//      Serial.print(currentScale[funScaleInterval + 1]);
      Serial.print("\n");
    }
  }
}

void recognizeScaleRecalculations(){
  prandomChoice = random(0, 2);
  widePrandomChoice = random(0,5);
  if(menuScaleSelect.getCurrentValue() > 0){
    unscaledNote = serialMessage[1] - 0;
    if(unscaledNote<0){
      unscaledNote = unscaledNote + 12;
    }
    unscaledNote = serialMessage[1] % 12;
    if(menuSLPrandoMenu.getCurrentValue() == 2){
      int funOctaveNumber = serialMessage[1] / 12;
      funOctaveNumber = funOctaveNumber*12 + currentScale[widePrandomChoice];
      prandomKeyRemapping[serialMessage[1]] = funOctaveNumber; 
      serialMessage[1] = funOctaveNumber;
    }
    if((unscaledNote != currentScale[0]) && (unscaledNote != currentScale[1]) && (unscaledNote != currentScale[2]) && (unscaledNote != currentScale[3]) && (unscaledNote != currentScale[4])){
      for(int i=0;i<5;i++){
        rescaleNote(i);
      }
    }
  }
}

///|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\
// Scaling functions
//\|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/


void addChordMessages(){
  if(menuAutoPlay.getCurrentValue() == 1){
    // Play chords every time there is an active note
    for(int i=1; i<4; i++){
      if(currentChord[i] != 0){
        MIDICommand(serialMessage[0], serialMessage[1] + currentChord[i], serialMessage[2]);
      }
    }
  }
  if(menuAutoPlay.getCurrentValue() == 2){
    // Play a chord if this is the second key pressed while there is an active note
    if((currentNotesPlaying == 1) && (noteOnIncoming > 0)){
      rootNoteForChord = serialMessage[1];
      if(noteOnIncoming > 1){
        serialMessage[1] = rootNoteForChord;
      }
    }
    if((currentNotesPlaying > 1) || (noteOffIncoming > 0)){
      for(int i=1; i<4; i++){
        if(currentChord[i] != 0){
          MIDICommand(serialMessage[0], rootNoteForChord + currentChord[i], serialMessage[2]);
        }
      }
    }
  }
}


void processNoteOn(){
  recognizePianoCommands();
  recognizePitchLimits();
  recognizeScaleRecalculations();
  recognizeVelocityLimits();
  shiftOctaves();
  
  currentNotesPlaying++;
  previousNote = (serialMessage[1]);
  if((menuAutoPlay.getCurrentValue() == 2) && currentNotesPlaying > 1){
    MIDICommand(serialMessage[0], rootNoteForChord, serialMessage[2]);
  }else{
    MIDICommand(serialMessage[0], serialMessage[1], serialMessage[2]);
  }
  processLoop();
  addChordMessages();
  noteOnIncoming = 0;
}

void processNoteOff(){
  recognizePitchLimits();
  shiftOctaves();
  if(prandomKeyRemapping[serialMessage[1]] && ((menuSLPrandoMenu.getCurrentValue() == 2) || (menuSLPrandoMenu.getCurrentValue() == 1))){
    serialMessage[1] = prandomKeyRemapping[serialMessage[1]];
    prandomKeyRemapping[serialMessage[1]] = 0;
  }
  
  currentNotesPlaying--;
  MIDICommand(serialMessage[0], serialMessage[1], serialMessage[2]);
  processLoop();
  addChordMessages();
  noteOffIncoming = 0;
}
