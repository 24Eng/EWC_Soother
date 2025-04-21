#include "EWC_Soother_TcMenu_2025-03-29_01_menu.h"

void setup() {
    setupMenu();

}

void loop() {
    taskManager.runLoop();

}


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



void CALLBACK_FUNCTION instrumentChange(int id) {
  menuMgr.save();
  EEPROM.commit();
  int funCurrentInstrument = menuInstrument.getCurrentValue();
  if (verboseFeedback) {
    Serial.print("Instrument: ");
    char funName[32];
    menuInstrument.copyEnumStrToBuffer(funName, 32, menuInstrument.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }
  midiSetInstrument(0x0 + currentChannel, funCurrentInstrument);
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


/*
/|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ 
Octave reassignments
\|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/
*/
void CALLBACK_FUNCTION OctChOn(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave / channel on: ");
  Serial.print(menuOctOnOrOff.getBoolean());
  Serial.print("\n");
}

void CALLBACK_FUNCTION Octave15Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 15 reassigned to: ");
  Serial.print(menuOctave15To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave14Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 14 reassigned to: ");
  Serial.print(menuOctave14To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave13Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 13 reassigned to: ");
  Serial.print(menuOctave13To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave12Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 12 reassigned to: ");
  Serial.print(menuOctave12To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave11Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 11 reassigned to: ");
  Serial.print(menuOctave11To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave10Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 10 reassigned to: ");
  Serial.print(menuOctave10To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave9Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 9 reassigned to: ");
  Serial.print(menuOctave9To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave8Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 8 reassigned to: ");
  Serial.print(menuOctave8To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave7Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 7 reassigned to: ");
  Serial.print(menuOctave7To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave6Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 6 reassigned to: ");
  Serial.print(menuOctave6To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave5Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 5 reassigned to: ");
  Serial.print(menuOctave5To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave4Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 4 reassigned to: ");
  Serial.print(menuOctave4To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave3Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 3 reassigned to: ");
  Serial.print(menuOctave3To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave2Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 2 reassigned to: ");
  Serial.print(menuOctave2To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave1Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 1 reassigned to: ");
  Serial.print(menuOctave1To.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION Octave0Reassign(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Octave 0 Reassigned to: ");
  Serial.print(menuOctave0To.getCurrentValue());
  Serial.print("\n");
}
/*
/|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ /|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|\ 
Octave reassignments
\|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/ \|{[<Ω○O△O○↔°•°↔○O△O○Ω>]}|/
*/


// Prandom beats // Prandom beats // Prandom beats // Prandom beats // Prandom beats 
void CALLBACK_FUNCTION PrandomOn(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Prandom On: ");
  Serial.print(menuPBOnOrOff.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PrandomizeNow(int id) {
  Serial.print("Prandomize now\n");
}
void CALLBACK_FUNCTION PerussionVelCap(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Perussion Velocity Cap: ");
  Serial.print(menuVelocityCap.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PercussionTracks(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Percussion Tracks: ");
  Serial.print(menuTracks.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PercussionTempo(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Percussion tempo: ");
  Serial.print(menuTempo.getCurrentValue());
  Serial.print("\n");
}
void CALLBACK_FUNCTION PercussionPercentage(int id) {
  menuMgr.save();
  EEPROM.commit();
  Serial.print("Percussion percentage: ");
  Serial.print(menuPercentage.getCurrentValue());
  Serial.print(" %\n");
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


void showEEPROMValues(){
  Serial.print("Bypass mode: ");
  Serial.print(menuBypass.getCurrentValue());
  Serial.print("\n");
  
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
  
  Serial.print("Which notes to prandomize: ");
  Serial.print(menuSLPrandoMenu.getCurrentValue());
  Serial.print("\n");

  Serial.print("Chord: ");
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
  
  Serial.print("Chord Auto-Play: ");
  Serial.print(menuAutoPlay.getCurrentValue());
  Serial.print("\n");

  int funCurrentInstrument = menuInstrument.getCurrentValue();
  if (verboseFeedback) {
    Serial.print("Instrument: ");
    char funName[32];
    menuInstrument.copyEnumStrToBuffer(funName, 32, menuInstrument.getCurrentValue());
    Serial.print(funName);
    Serial.print("\n");
  }


  Serial.print(menuBluetooth.getCurrentValue());
  Serial.print("\n");

  Serial.print("Pitch Limiting On: ");
  Serial.print(menuPitchLimOnOrOff.getBoolean());
  Serial.print("\n");

  Serial.print("Pitch Limit Floor (incoming signals): ");
  Serial.print(menuPitchFloor.getCurrentValue());
  Serial.print("\n");

  Serial.print("Pitch Limit Ceiling (incoming signals): ");
  Serial.print(menuPitchCeiling.getCurrentValue());
  Serial.print("\n");

  Serial.print("Velocity Limiting On (incoming signals): ");
  Serial.print(menuVelLimOnOrOff.getBoolean());
  Serial.print("\n");

  Serial.print("Octave / channel on: ");
  Serial.print(menuOctOnOrOff.getBoolean());
  Serial.print("\n");

  Serial.print("Octave 15 reassigned to: ");
  Serial.print(menuOctave15To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 14 reassigned to: ");
  Serial.print(menuOctave14To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 13 reassigned to: ");
  Serial.print(menuOctave13To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 12 reassigned to: ");
  Serial.print(menuOctave12To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 11 reassigned to: ");
  Serial.print(menuOctave11To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 10 reassigned to: ");
  Serial.print(menuOctave10To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 9 reassigned to: ");
  Serial.print(menuOctave9To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 8 reassigned to: ");
  Serial.print(menuOctave8To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 7 reassigned to: ");
  Serial.print(menuOctave7To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 6 reassigned to: ");
  Serial.print(menuOctave6To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 5 reassigned to: ");
  Serial.print(menuOctave5To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 4 reassigned to: ");
  Serial.print(menuOctave4To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 3 reassigned to: ");
  Serial.print(menuOctave3To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 2 reassigned to: ");
  Serial.print(menuOctave2To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 1 reassigned to: ");
  Serial.print(menuOctave1To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Octave 0 Reassigned to: ");
  Serial.print(menuOctave0To.getCurrentValue());
  Serial.print("\n");

  Serial.print("Prandom On: ");
  Serial.print(menuPBOnOrOff.getCurrentValue());
  Serial.print("\n");

  Serial.print("Perussion Velocity Cap: ");
  Serial.print(menuVelocityCap.getCurrentValue());
  Serial.print("\n");

  Serial.print("Percussion Tracks: ");
  Serial.print(menuTracks.getCurrentValue());
  Serial.print("\n");

  Serial.print("Percussion tempo: ");
  Serial.print(menuTempo.getCurrentValue());
  Serial.print("\n");

  Serial.print("Percussion percentage: ");
  Serial.print(menuPercentage.getCurrentValue());
  Serial.print(" %\n");

  Serial.print("Looping on: ");
  Serial.print(menuLoopOnOrOff.getBoolean());
  Serial.print("\n");

  Serial.print("Loop Delay, in milliseconds: ");
  Serial.print(menuDelayBetweenLoops.getCurrentValue());
  Serial.print("\n");
}


void CALLBACK_FUNCTION instrumentChangeChannel13(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel7(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel2(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave4ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave10ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel0(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave4ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel4(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave3ReassignOctave(int id) {
    // TODO - your menu change code
}



void CALLBACK_FUNCTION Octave3ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel10(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave0ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave6ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave5ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel15(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave10ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave1ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave5ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel3(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave2ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave7ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave9ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel8(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave1ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel1(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave6ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave7ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave0ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave8ReassignChannel(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel14(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel5(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave2ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave9ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel11(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel6(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION Octave8ReassignOctave(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION instrumentChangeChannel12(int id) {
    // TODO - your menu change code
}
