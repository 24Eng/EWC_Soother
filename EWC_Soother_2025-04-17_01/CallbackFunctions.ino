void CALLBACK_FUNCTION BypassIncSerial(int id) {
  Serial.print("Bypass mode: ");
  Serial.print(menuBypass.getCurrentValue());
  Serial.print("\n");
}


void CALLBACK_FUNCTION startToPanic(int id) {
  panicModeBool = true;
}


// Scale functions // Scale functions // Scale functions // Scale functions 
void CALLBACK_FUNCTION scaleType(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Scale: ");
  char funName[32];
  menuScaleSelect.copyEnumStrToBuffer(funName, 32, menuScaleSelect.getCurrentValue());
  Serial.print(funName);
  Serial.print("\t{");
  if(menuScaleSelect.getCurrentValue() > 0){
    for(int i = 0; i<6; i++){
      currentScale[i] = pentatonicScales[menuScaleSelect.getCurrentValue()][i];
      Serial.print(currentScale[i]);
      if(i < 5){ 
        Serial.print(", ");
      }else{
        Serial.print("}\n");
      }
    }
  }
  Serial.print("}\n");
}

void CALLBACK_FUNCTION scalePrandom(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Which notes to prandomize: ");
  Serial.print(menuSLPrandoMenu.getCurrentValue());
  Serial.print("\n");
}

// Chord functions // Chord functions // Chord functions // Chord functions 
void CALLBACK_FUNCTION ChordSelect(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Chord: ");
  char funName[32];
  menuSelect.copyEnumStrToBuffer(funName, 32, menuSelect.getCurrentValue());
  Serial.print(funName);
  Serial.print("\t {");
  for(int i=0; i<4; i++){
    currentChord[i] = allChords[menuSelect.getCurrentValue()][i];
    Serial.print(currentChord[i]);
    if(i<3){
      Serial.print(", ");
    }else{
      Serial.print("}\n");
    }
  }
}
void CALLBACK_FUNCTION ChordAutoPlay(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Chord Auto-Play: ");
  Serial.print(menuAutoPlay.getCurrentValue());
  Serial.print("\n");
  
}


void CALLBACK_FUNCTION BluetoothOptions(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Bluetooth options: ");
  Serial.print(menuBluetooth.getCurrentValue());
  Serial.print("\n");
}


// Pitch limiting // Pitch limiting // Pitch limiting // Pitch limiting 
void CALLBACK_FUNCTION PitchLimOn(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Pitch Limiting On: ");
  Serial.print(menuPitchLimOnOrOff.getBoolean());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PitchLimFloor(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Pitch Limit Floor (incoming signals): ");
  Serial.print(menuPitchFloor.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PitchLimCeiling(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Pitch Limit Ceiling (incoming signals): ");
  Serial.print(menuPitchCeiling.getCurrentValue());
  Serial.print("\n");
}


// Velocity limiting // Velocity limiting // Velocity limiting // Velocity limiting 
void CALLBACK_FUNCTION VelocityLimOn(int id) {
  menuMgr.save();
  EEPROM.commit();
//  Serial.print("Velocity Limiting On (incoming signals): ");
//  Serial.print(menuVelLimOnOrOff.getBoolean());
//  Serial.print("\n");
}
void CALLBACK_FUNCTION VelocityCeiling(int id) {
  menuMgr.save();
  EEPROM.commit();
// Serial.print("\n");
}

void CALLBACK_FUNCTION VelocityFloor(int id) {
  menuMgr.save();
  EEPROM.commit();
}



// Looping // Looping // Looping // Looping // Looping // Looping // Looping // Looping 
void CALLBACK_FUNCTION LoopingOn(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Looping ");
  if(menuLoopOnOrOff.getBoolean()){
    Serial.print("on\n");
  }else{
    Serial.print("off\n");
  }
}

void CALLBACK_FUNCTION PrepareForNewLoop(int id) {
  Serial.print("Prepare For New Loop\n");
  startALoop();
}
void CALLBACK_FUNCTION LoopDelayMS(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Loop Delay, in milliseconds: ");
  Serial.print(menuDelayBetweenLoops.getCurrentValue());
  Serial.print("\n");
  // Replace this with the new value
//  loopTimeout = menuDelayBetweenLoops.getCurrentValue();
}


//McSTUFF


// Instrument changes ***...*** Instrument changes ***...*** Instrument changes ***...*** Instrument changes
// Instrument changes ***...*** Instrument changes ***...*** Instrument changes ***...*** Instrument changes
void CALLBACK_FUNCTION instrumentChangeChannel0(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel0.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 0 Instrument: "));
    char funName[32];
    menuInstChannel0.copyEnumStrToBuffer(funName, 32, menuInstChannel0.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x00, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel1(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel1.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 1 Instrument: "));
    char funName[32];
    menuInstChannel1.copyEnumStrToBuffer(funName, 32, menuInstChannel1.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x01, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel2(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel2.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 2 Instrument: "));
    char funName[32];
    menuInstChannel2.copyEnumStrToBuffer(funName, 32, menuInstChannel2.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x02, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel3(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel3.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 3 Instrument: "));
    char funName[32];
    menuInstChannel3.copyEnumStrToBuffer(funName, 32, menuInstChannel3.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x03, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel4(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel4.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 4 Instrument: "));
    char funName[32];
    menuInstChannel4.copyEnumStrToBuffer(funName, 32, menuInstChannel4.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x04, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel5(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel5.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 5 Instrument: "));
    char funName[32];
    menuInstChannel5.copyEnumStrToBuffer(funName, 32, menuInstChannel5.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x05, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel6(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel6.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 6 Instrument: "));
    char funName[32];
    menuInstChannel6.copyEnumStrToBuffer(funName, 32, menuInstChannel6.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x06, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel7(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel7.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 7 Instrument: "));
    char funName[32];
    menuInstChannel7.copyEnumStrToBuffer(funName, 32, menuInstChannel7.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x07, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel8(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel8.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 8 Instrument: "));
    char funName[32];
    menuInstChannel8.copyEnumStrToBuffer(funName, 32, menuInstChannel8.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x08, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel10(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel10.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 10 Instrument: "));
    char funName[32];
    menuInstChannel10.copyEnumStrToBuffer(funName, 32, menuInstChannel10.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0A, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel11(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel11.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 11 Instrument: "));
    char funName[32];
    menuInstChannel11.copyEnumStrToBuffer(funName, 32, menuInstChannel11.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0B, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel12(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel12.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 12 Instrument: "));
    char funName[32];
    menuInstChannel12.copyEnumStrToBuffer(funName, 32, menuInstChannel12.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0C, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel13(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel13.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 13 Instrument: "));
    char funName[32];
    menuInstChannel13.copyEnumStrToBuffer(funName, 32, menuInstChannel13.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0D, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel14(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel14.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 14 Instrument: "));
    char funName[32];
    menuInstChannel14.copyEnumStrToBuffer(funName, 32, menuInstChannel14.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0E, funCurrentInstrument);
}


void CALLBACK_FUNCTION instrumentChangeChannel15(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstChannel15.getCurrentValue();
  if (verboseFeedback) {
    Serial.print(F("Channel 15 Instrument: "));
    char funName[32];
    menuInstChannel15.copyEnumStrToBuffer(funName, 32, menuInstChannel15.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0F, funCurrentInstrument);
}

// Instrument changes ***...*** Instrument changes ***...*** Instrument changes ***...*** Instrument changes
// Instrument changes ***...*** Instrument changes ***...*** Instrument changes ***...*** Instrument changes

// Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments
// Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments

void CALLBACK_FUNCTION Octave0ReassignOctave(int id) {
    Serial.print(F("Octave 0 to octave "));
    Serial.print(menuOctave0ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave1ReassignOctave(int id) {
    Serial.print(F("Octave 1 to octave "));
    Serial.print(menuOctave1ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave2ReassignOctave(int id) {
    Serial.print(F("Octave 2 to octave "));
    Serial.print(menuOctave2ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave3ReassignOctave(int id) {
    Serial.print(F("Octave 3 to octave "));
    Serial.print(menuOctave3ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave4ReassignOctave(int id) {
    Serial.print(F("Octave 4 to octave "));
    Serial.print(menuOctave4ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave5ReassignOctave(int id) {
    Serial.print(F("Octave 5 to octave "));
    Serial.print(menuOctave5ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave6ReassignOctave(int id) {
    Serial.print(F("Octave 6 to octave "));
    Serial.print(menuOctave6ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave7ReassignOctave(int id) {
    Serial.print(F("Octave 7 to octave "));
    Serial.print(menuOctave7ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave8ReassignOctave(int id) {
    Serial.print(F("Octave 8 to octave "));
    Serial.print(menuOctave8ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave9ReassignOctave(int id) {
    Serial.print(F("Octave 9 to octave "));
    Serial.print(menuOctave9ToOctave.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave10ReassignOctave(int id) {
    Serial.print(F("Octave 10 to octave "));
    Serial.print(menuOctave10ToOctave.getCurrentValue());
    Serial.print("\n");
}
// Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments
// Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments ***...*** Octave reassignments

// Channel reassignments ***...*** Channel reassignments ***...*** Channel reassignments ***...*** Channel reassignments
// Channel reassignments ***...*** Channel reassignments ***...*** Channel reassignments ***...*** Channel reassignments
void CALLBACK_FUNCTION Octave0ReassignChannel(int id) {
    Serial.print(F("Octave 0 to channel "));
    Serial.print(menuOctave0ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave1ReassignChannel(int id) {
    Serial.print(F("Octave 1 to channel "));
    Serial.print(menuOctave1ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave2ReassignChannel(int id) {
    Serial.print(F("Octave 2 to channel "));
    Serial.print(menuOctave2ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave3ReassignChannel(int id) {
    Serial.print(F("Octave 3 to channel "));
    Serial.print(menuOctave3ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave4ReassignChannel(int id) {
    Serial.print(F("Octave 4 to channel "));
    Serial.print(menuOctave4ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave5ReassignChannel(int id) {
    Serial.print(F("Octave 5 to channel "));
    Serial.print(menuOctave5ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave6ReassignChannel(int id) {
    Serial.print(F("Octave 6 to channel "));
    Serial.print(menuOctave6ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave7ReassignChannel(int id) {
    Serial.print(F("Octave 7 to channel "));
    Serial.print(menuOctave7ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave8ReassignChannel(int id) {
    Serial.print(F("Octave 8 to channel "));
    Serial.print(menuOctave8ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave9ReassignChannel(int id) {
    Serial.print(F("Octave 9 to channel "));
    Serial.print(menuOctave9ToChannel.getCurrentValue());
    Serial.print("\n");
}


void CALLBACK_FUNCTION Octave10ReassignChannel(int id) {
    Serial.print(F("Octave 10 to channel "));
    Serial.print(menuOctave10ToChannel.getCurrentValue());
    Serial.print("\n");
}

//McSTUFF
