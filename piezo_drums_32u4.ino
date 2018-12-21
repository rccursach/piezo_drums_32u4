//#include <pitchToFrequency.h>
//#include <pitchToNote.h>
//#include <frequencyToNote.h>
#include <MIDIUSB.h>

int pads[] = {A1, A2, A3};
int state[] = {0, 0, 0};
int threshold[] = {150, 150, 150};
byte pitch[] = {44, 36, 38};
byte channel = 0;

void setup() {
   Serial.begin(115200);
}

void loop() {
  for(int p=0; p<3; p++) {
    int lvl = analogRead(pads[p]);
    if(lvl > threshold[p] && state[p] == 0) {
      state[p] = lvl;
      byte vel = (byte) (map(lvl, threshold[p], 1023, 40, 127));
      noteOn(channel, pitch[p], vel);
    }
    else if(lvl < state[p]) {
      if(lvl < threshold[p]) {
        state[p] = 0;
        noteOff(channel, pitch[p], 40);
      }
    }
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}
