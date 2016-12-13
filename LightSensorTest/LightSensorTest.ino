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
//int minLight;          //Used to calibrate the readings
// int maxLight;          //Used to calibrate the readings
int lightLevelLivingRoom;
int lightLevelKitchen;
// int adjustedLightLevel;
int  minLightLivingRoom=lightLevel = 0;
int  maxLightLivingRoom=lightLevel = 0;
int  minLightLivingRoom=lightLevel = 0;
int  maxLightLivingRoom=lightLevel = 0;
void setup() {
 Serial.begin(9600);
 
 //Setup the starting light level limits
 lightLevelLivingRoom=calibrateLight(photoRPinLivingRoom);
 lightLevelKitchen=calibrateLight(photoRPinKitchen);

 pinMode(3,OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(9, OUTPUT);
 
 }
void loop(){
 //auto-adjust the minimum and maximum limits in real time
// lightLevel=analogRead(photoRPin);
// if(minLight>lightLevel){
// minLight=lightLevel;
// }
// if(maxLight<lightLevel){
// maxLight=lightLevel;
// }

 
 //Adjust the light level to produce a result between 0 and 100.
 lightLevelLivingRoom=readLight(photoRPinLivingRoom);
 lightLevelKitchen=readLight(photoRPinKitchen);
 if(lightLevelLivingRoom < 20){
    digitalWrite(3, HIGH);
   }
 else
 {  
     digitalWrite(3, LOW);
     
 }
 if(lightLevelKitchen < 20){
   digitalWrite(4, HIGH);
 }
 else{
   digitalWrite(4,LOW);
 }
 //Send the adjusted Light level result to Serial port for debugging
Serial.print("Livingroom: ");
Serial.print(lightLevelLivingRoom);
Serial.print("\n");
Serial.print("Kitchen: ");
Serial.print(lightLevelKitchen);
Serial.print("\n");
//slow do\nwn the transmission for effective Serial communication.
 delay(300);
}


// Function for calibrate photocell to ambient light.
int calibrateLight(int photoRP){
  Serial.print("initial calibration: ");
  Serial.print(photoRP);
  int lightLevel=analogRead(photoRP);
  switch (photoRP){
  case 0:
  minLightLivingRoom=lightLevel-20;
  maxLightLivingRoom=lightLevel;
  break;
  case 1:
  minLightLivingRoom=lightLevel-20;
  maxLightLivingRoom=lightLevel;
  break;}
  Serial.print(photoRP);
Serial.print("\n");
 
}

int readLight(int photoRP)
{
  int minLight = 0;
  int maxLight = 0;
  int lightLevel = analogRead(photoRP);
  switch (photoRP){
  case 0:
  minLight = minLightLivingRoom;
  maxLight = maxLightLivingROom;
  break;
  case 1:
  minLight = minLightKitchen;
  maxLight = maxLightKitchen;
  break;
  }
  if(minLight>lightLevel){
   minLight=lightLevel;
 }
 if(maxLight<lightLevel){
   maxLight=lightLevel;
 }
 int adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100);
 Serial.print("adjusted light level ");
 Serial.print(adjustedLightLevel);
 return adjustedLightLevel;
}
