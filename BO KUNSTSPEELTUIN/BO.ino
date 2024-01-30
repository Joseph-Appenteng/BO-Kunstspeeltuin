#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 4
const int soundpin = A2;
const int threshold = 200;

TMRpcm tmrpcm;

bool isPlaying = false;  // Variable to track whether music is currently playing or not

void setup() {
  pinMode(soundpin, INPUT);
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;

  if (!SD.begin(SD_ChipSelectPin)) {
    // Handle SD card initialization failure
    while (1);
  }
}

void loop() {
  int soundsens = analogRead(soundpin);
  
  if (soundsens >= threshold) {
    // Clap detected
    delay(50);  // Debounce delay to avoid multiple detections for a single clap

    if (isPlaying) {
      // If music is already playing, stop it
      tmrpcm.stopPlayback();
      isPlaying = false;
    } else {
      // If music is not playing, start playing
      tmrpcm.setVolume(5);
      tmrpcm.play("example.wav");
      isPlaying = true;
    }
  }
}
