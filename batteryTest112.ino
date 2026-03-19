// Record sound as raw data to a SD card, and play it back.
//
// Requires the audio shield:
//   http://www.pjrc.com/store/teensy3_audio.html
//
//
// This example code is in the public domain.


#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TimeLib.h>


unsigned long timeSinceStart = 0;
unsigned long timeSincePrint = 0;

int h, m, s, d, mth, yr;

char datedir[10];
char fileName[30];

//THIS IS A TEST


// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=105,63
AudioAnalyzePeak         peak1;          //xy=278,108
AudioRecordQueue         queue1;         //xy=281,63
AudioPlaySdWav           playWav1;
AudioOutputI2S           i2s1;           //xy=470,120
AudioConnection          patchCord1(i2s2, 0, queue1, 0);
AudioConnection          patchCord2(i2s2, 0, peak1, 0);
AudioConnection          patchCord3(playWav1, 0, i2s1, 0);
AudioConnection          patchCord4(playWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=265,212
// GUItool: end automatically generated code

// For a stereo recording version, see this forum thread:
// https://forum.pjrc.com/threads/46150?p=158388&viewfull=1#post158388

// A much more advanced sound recording and data logging project:
// https://github.com/WMXZ-EU/microSoundRecorder
// https://github.com/WMXZ-EU/microSoundRecorder/wiki/Hardware-setup
// https://forum.pjrc.com/threads/52175?p=185386&viewfull=1#post185386




// which input on the audio shield will be used?
//const int myInput = AUDIO_INPUT_LINEIN;
const int myInput = AUDIO_INPUT_MIC;


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN_PLAY    10
#define SDCARD_MOSI_PIN_PLAY  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN_PLAY   14  // Teensy 4 ignores this, uses pin 13

// Use these with the Teensy 3.5 & 3.6 & 4.1 SD card
#define SDCARD_CS_PIN_REC    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN_REC  11  // not actually used
#define SDCARD_SCK_PIN_REC   13  // not actually used

// Remember which mode we're doing
int mode = 0;  // 0=stopped, 1=recording, 2=playing

// The file where data is recorded
File frec;

void setup() {
  // Audio connections require memory, and the record queue
  // uses this memory to buffer incoming audio.
  AudioMemory(100);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);

  // SPI.setMOSI(SDCARD_MOSI_PIN_REC);
  // SPI.setSCK(SDCARD_SCK_PIN_REC);
  // if (!(SD.begin(SDCARD_CS_PIN_REC))) {
  //   // stop here if no SD card, but print a message
  //   while (1) {
  //     Serial.println("Unable to access the recording card");
  //     delay(500);
  //   }
  // }

setSyncProvider(getTeensy3Time);

  // Serial.begin(115200);
  // while (!Serial);  // Wait for Arduino Serial Monitor to open
  // delay(100);
  // if (timeStatus()!= timeSet) {
  //   Serial.println("Unable to sync with the RTC");
  // } else {
  //   Serial.println("RTC has set the system time");
  // }
}



void loop() {
  // if (Serial.available()) {
  //   time_t t = processSyncMessage();
  //   if (t != 0) {
  //     Teensy3Clock.set(t); // set the RTC
  //     setTime(t);
  //   }
  // }


  timeSinceStart = millis();

  if(timeSincePrint + 1000 == timeSinceStart){
    digitalClockDisplay();
    timeSincePrint = timeSinceStart;
  }

//Play and record on the hour every hour

  if(m == 38 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 0) startPlaying();
  }

  if(m == 39 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 2) stopPlaying();
  }


  //StartRecording
  if(m == 33 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 0) startRecording();
  }


  if(m == 34 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17  || h==18 || h==19 || h==20)){
    if(mode == 1) stopRecording();
  }

//Play and record on the half hour every hour

  if(m == 58  && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 0) startPlaying();
  }

  if(m == 59 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 2) stopPlaying();
  }


  //StartRecording
  if(m == 59 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17 || h==18 || h==19 || h==20)){
    if(mode == 0) startRecording();
  }


  if(m== 00 && (h==8 || h==9 || h==10 || h==11 || h==12 || h==13 || h==14 || h==15 || h==16 || h==17  || h==18 || h==19 || h==20)){
    if(mode == 1) stopRecording();
  }


  // If we're playing or recording, carry on...
  if (mode == 1) {
    continueRecording();
  }
  if (mode == 2) {
    continuePlaying();
  }

  // when using a microphone, continuously adjust gain
  if (myInput == AUDIO_INPUT_MIC) adjustMicLevel();
}

void startRecording() {
  SPI.setMOSI(SDCARD_MOSI_PIN_REC);
  SPI.setSCK(SDCARD_SCK_PIN_REC);
  if (!(SD.begin(SDCARD_CS_PIN_REC))) {
    // stop here if no SD card, but print a message
    while (1) {
      Serial.println("Unable to access the recording card");
      delay(500);
    }
  }
    // Initialize the SD card
  Serial.println("startRecording");
  // if (SD.exists("RECORD8.RAW")) {
  //   // The SD library writes new data to the end of the
  //   // file, so to start a new recording, the old file
  //   // must be deleted before new data is written.
  //   SD.remove("RECORD8.RAW");
  // }

  sprintf(datedir, "%04d/%02d", year(), month());
  SD.mkdir(datedir);
  
  sprintf(fileName, "/%04d/%02d/%02d-%02d-%02d.RAW", year(), month(), day(), hour(), minute());

  frec = SD.open(fileName, FILE_WRITE);
  if (frec) {
    queue1.begin();
    mode = 1;
  }
}



void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    // Fetch 2 blocks from the audio library and copy
    // into a 512 byte buffer.  The Arduino SD library
    // is most efficient when full 512 byte sector size
    // writes are used.
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer + 256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
    //elapsedMicros usec = 0;
    frec.write(buffer, 512);
    // Uncomment these lines to see how long SD writes
    // are taking.  A pair of audio blocks arrives every
    // 5802 microseconds, so hopefully most of the writes
    // take well under 5802 us.  Some will take more, as
    // the SD library also must write to the FAT tables
    // and the SD card controller manages media erase and
    // wear leveling.  The queue1 object can buffer
    // approximately 301700 us of audio, to allow time
    // for occasional high SD card latency, as long as
    // the average write time is under 5802 us.
    //Serial.print("SD write, us=");
    //Serial.println(usec);
  }
}

void stopRecording() {
  Serial.println("stopRecording");
  queue1.end();
  if (mode == 1) {
    while (queue1.available() > 0) {
      frec.write((byte*)queue1.readBuffer(), 256);
      queue1.freeBuffer();
    }
    frec.close();
  }
  mode = 0;
}


void startPlaying() {
  SPI.setMOSI(SDCARD_MOSI_PIN_PLAY);
  SPI.setSCK(SDCARD_SCK_PIN_PLAY);
  if (!(SD.begin(SDCARD_CS_PIN_PLAY))) {
    // stop here if no SD card, but print a message
    while (1) {
      Serial.println("Unable to access the SD card2");
      delay(500);
    }
  }
  Serial.println("startPlaying");
  // playRaw1.play("PLAY.RAW");
  playWav1.play("BACS_PublicInfo_F+beg.WAV");
  mode = 2;
}



void continuePlaying() {
  // if (!playRaw1.isPlaying()) {
  if (!playWav1.isPlaying()) {
    // playRaw1.stop();
    playWav1.stop();
    mode = 0;
  }
}

void stopPlaying() {
  Serial.println("stopPlaying");
  // if (mode == 2) playRaw1.stop();
    if(mode==2);{
     playWav1.stop();
     mode = 0;
    }
}


void adjustMicLevel() {
  // TODO: read the peak1 object and adjust sgtl5000_1.micGain()
  // if anyone gets this working, please submit a github pull request :-)
}


void digitalClockDisplay() {
  // digital clock display of the time
  h = hour();
  m = minute();
  s = second();
  d = day();
  mth = month();
  yr = year();
  // Serial.print(hour());
  Serial.print(h);
  // printDigits(minute());
  printDigits(m);
  // printDigits(second());
  printDigits(s);
  Serial.print(" ");
  // Serial.print(day());
  Serial.print(d);
  Serial.print(" ");
  // Serial.print(month());
  Serial.print(mth);
  Serial.print(" ");
  // Serial.print(year()); 
  Serial.print(yr);
  // Serial.print current audio memory usage
  Serial.print(" CurrentMemory ");
  Serial.print(AudioMemoryUsage());
  // Serial.print max audio memoray usage
  Serial.print(" MaxMemory ");
  Serial.print(AudioMemoryUsageMax());
  Serial.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}