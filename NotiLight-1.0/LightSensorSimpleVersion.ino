  /* ==========================================================
Project : Send Photo resistor values to computer
Author: ScottC
Created: 25th June 2011
Description: This sketch will make the arduino read Photo resistor
             values on analog pin A0. The analog readings will
             be dependent on the amount of light reaching the
             sensor. The Analog readings will be sent to the
             computer via the USB cable using Serial communication.
==============================================================
*/

int photoRPinLivingRoom = 0;
int photoRPinKitchen = 1;
int photoRPinSofa = 2;
int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int lightLevelLivingRoom;
int lightLevelKitchen;
int lightLevelSofa;
int adjustedLightLevel;
int speakerPin = 9;
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

int tempo = 500;


void setup() {
 Serial.begin(9600);
 
 //Setup the starting light level limits
 lightLevelLivingRoom=analogRead(photoRPinLivingRoom);
 lightLevelKitchen=analogRead(photoRPinKitchen);
 lightLevelSofa=analogRead(photoRPinSofa);
 //minLight=lightLevel-20;
 //maxLight=lightLevel;
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(11, OUTPUT);

 
 }
void loop(){
 //auto-adjust the minimum and maximum limits in real time
 lightLevelLivingRoom=analogRead(photoRPinLivingRoom);
 lightLevelKitchen=analogRead(photoRPinKitchen);
 lightLevelSofa = analogRead(photoRPinSofa);
 //if(minLight>lightLevel){
 //minLight=lightLevel;
 //
 //if(maxLight<lightLevel){
 //maxLight=lightLevel;
 //}
  
 
 //Adjust the light level to produce a result between 0 and 100.
 //adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100); 
 Serial.print("LightlevelLivingRoom: ");
 Serial.print(lightLevelLivingRoom);
 Serial.print("\n");
  Serial.print("LightlevelKitchen: ");
 Serial.print(lightLevelKitchen);
 Serial.print("\n");
   Serial.print("LightlevelSofa: ");
 Serial.print(lightLevelSofa);
 Serial.print("\n");
 
 
 if(lightLevelLivingRoom < 600){
    digitalWrite(3, HIGH);
    digitalWrite(11, HIGH);
   }
   else{
     digitalWrite(3, LOW);
     digitalWrite(11, LOW);
   }
  if (lightLevelKitchen < 600){
   digitalWrite(4, HIGH);
     for (int i = 0; i < length; i++) {
      lightLevelKitchen = analogRead(photoRPinKitchen);
      if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
  }else{

    digitalWrite(4, LOW);
   
  }  
  if(lightLevelSofa < 600) {
    digitalWrite(5, HIGH);
  }else {
    digitalWrite(5, LOW);
  }    
 
 //Send the adjusted Light level result to Serial port (processing)
// Serial.println(adjustedLightLevel);
 
 //slow down the transmission for effective Serial communication.
 delay(1000);
  }


void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {

char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
