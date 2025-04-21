#include "EWC_Soother_menu.h"

#include <EEPROM.h>

// ESP32 serial UART library
#include <HardwareSerial.h>


// NimBLE inclusions
#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32_NimBLE.h>
//BLEMIDI_CREATE_DEFAULT_INSTANCE()
BLEMIDI_CREATE_INSTANCE("EWC_Soother", MIDI)
unsigned long t0 = millis();
bool isConnected = false;



static const uint8_t TX_PIN = 13;
static const uint8_t RX_PIN = 15;

//Define two Serial devices mapped to the two internal UARTs
HardwareSerial MySerial0(0);
HardwareSerial MySerial1(1);


// Global variables
bool panicModeBool = false;
int PANICCount = 0;
int currentChannel = 0;
int noteOnIncoming = 0;
int noteOffIncoming = 0;
byte serialMessage[3];
int previousNote = 0;
bool verboseFeedback = false;
int unscaledNote = 0;
int prandomChoice = 0;
int widePrandomChoice = 0;
int cancelSecondNote = 0;
int currentNotesPlaying = 0;
int rootNoteForChord = 0;
int prandomKeyRemapping[128];

// Looping variables
bool loopRecording = false;
bool loopPlaying = false;
byte currentNotePlayCounter = 0;
byte currentNoteRecordCounter = 0;
byte playbackLengthCounter = 0;
bool loopBegun = false;
long playbackStartTime = 0;
int startTime = 0;
int endTime = 0;
long firstNoteTime = 0;
int loopTimeout = 2000;
long loopTimeoutTimer = 0;
const int maxNotes = 100;
// Loop notes is [track] [sequence] []
byte loopRecordNotes[maxNotes][3];
int loopRecordTime[100];

// Scales
int currentScale[6];
const int pentatonicScales[6][6] = {
  {0, 0, 0, 0, 0, 0},
  {0, 3, 4, 7, 10, 12},
  {0, 2, 4, 7, 9, 12},
  {0, 2, 5, 7, 10, 12},
  {0, 3, 5, 8, 10, 12},
  {0, 2, 5, 7, 9, 12}};
// Chords
int currentChord[] = {0, 4, 7, 0};
const int allChords[13][4] = {
  {0, 4, 7, 0},
  {0, 4, 7, 9},
  {0, 4, 7, 10},
  {0, 4, 7, 11},
  {0, 4, 8, 0},
  {0, 4, 8, 10},
  {0, 3, 7, 0},
  {0, 3, 7, 9},
  {0, 3, 7, 10},
  {0, 3, 7, 11},
  {0, 3, 6, 0},
  {0, 3, 6, 9},
  {0, 3, 6, 10}};

/*
// Scales
const int minorPentatonicScale[] = {-12, -9, -8, -5, -2, 0, 3, 4, 7, 10, 12};
const int majorPentatonicScale[] = {-12, -10, -8, -5, -3, 0, 2, 4, 7, 9, 12};
const int EgyptianPentatonicScale[] = {-12, -10, -7, -5, -2, 0, 2, 5, 7, 10, 12};
const int bluesMinorPentatonicScale[] = {-12, -9, -7, -4, -2, 0, 3, 5, 8, 10, 12};
const int bluesMajorPentatonicScale[] = {-12, -10, -7, -5, -3, 0, 2, 5, 7, 9, 12};

const int majorTriadChord[] = {0, 4, 7, 0};
const int majorSixthChord[] = {0, 4, 7, 9};
const int dominantSeventhChord[] = {0, 4, 7, 10};
const int majorSeventhChord[] = {0, 4, 7, 11};
const int augmentedTriad[] = {0, 4, 8, 0};
const int augmentedSeventhChord[] = {0, 4, 8, 10};
const int minorTriad[] = {0, 3, 7, 0};
const int minorSixthChord[] = {0, 3, 7, 9};
const int minorSeventhChord[] = {0, 3, 7, 10};
const int minorMajorSeventhChord[] = {0, 3, 7, 11};
const int diminishedTriadChord[] = {0, 3, 6, 0};
const int diminishedSeventhChord[] = {0, 3, 6, 9};
const int halfDiminishedSeventhChord[] = {0, 3, 6, 10};

*/



void setup(){
  Serial.begin(115200);
  Serial.print(F("EWC_Soother\n"));
  
  EEPROM.begin(512);
  setupMenu();
  // always call load after setupMenu, as the EEPROM you chose in initialised only after this setupMenu()
  menuMgr.load();
  
  // Configure MySerial0 (-1, -1 means use the default)
  MySerial0.begin(115200, SERIAL_8N1, -1, -1);
  MySerial0.write("EEPROM Started\n");
//  showEEPROMValues();
  Serial.print("\n\n");

  // And configure MySerial1 on pins RX, TX
  MySerial1.begin(31250, SERIAL_8N1, RX_PIN, TX_PIN);
  
  
  MIDI.begin();
  BLEMIDI.setHandleConnected(OnConnected);
  BLEMIDI.setHandleDisconnected(OnDisconnected);
}

void loop(){
  taskManager.runLoop();
  serialTasks();
  musicTasks();
}
