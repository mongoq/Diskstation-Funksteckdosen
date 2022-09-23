// Install https://github.com/sui77/rc-switch before compiling

// Define RCSwitch Object -----------

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

// Define String Communication ------

const byte numChars = 12;
char receivedChars[numChars];
boolean newData = false;

// General Setup --------------------

void setup() {
  // Transmitter is connected to Arduino Pin #11
  mySwitch.enableTransmit(11);
  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  Serial.begin(9600);
  Serial.println("LINKUP!");
}

// Actual Funksteckdosen Switching function

int set(const char* dipswitches){
  
  // Show Dip Switch Values
  // Serial.println(dipswitches);
  // https://slaystudy.com/convert-char-array-to-int-c-c/

  char hauscode[] = {dipswitches[0], dipswitches[1] , dipswitches[2] , dipswitches[3] , dipswitches[4] , '\0'};
  char funksteckdose[] = {dipswitches[5] , dipswitches[6] , dipswitches[7] , dipswitches[8] , dipswitches[9], '\0'};
  
  if (strlen(dipswitches)!=11) {
   Serial.println("Error - Dip Switches not 11 chars long !!!");
   return 1;
  }
  
  for(int i = 0; i <= 10; i += 1){
   if  (!((dipswitches[i] - '0' == 1)  || (dipswitches[i]  - '0' == 0))){
    Serial.println("Error - Dip Switches should only be 1 and 0 !!!");
    return 1;
   }
  }

  if (dipswitches[10] - '0' == 1){
   Serial.println("on!");
   //Serial.println(hauscode);
   //Serial.println(funksteckdose);
   mySwitch.switchOn(hauscode, funksteckdose);
  }
  else if (dipswitches[10] - '0' == 0){
   Serial.println("off!");
   //Serial.println(hauscode);
   //Serial.println(funksteckdose);
   mySwitch.switchOff(hauscode, funksteckdose);
  }
  return 0;
}

// Receive Magic  -------------------------

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) {
  rc = Serial.read();

  if (rc != endMarker) {
   receivedChars[ndx] = rc;
   ndx++;
   if (ndx >= numChars) {
   ndx = numChars - 1;
  }
 }
  else {
   receivedChars[ndx] = '\0'; // terminate the string
   ndx = 0;
   newData = true;
  }
 }
}

// Show new data ----------------------

void showNewData() {
 if (newData == true) {
 newData = false;
 if (set(receivedChars)==0) {
  Serial.println("OK");
 }
 else{
  Serial.println("ERROR!");
 }
 }
}

// Test function ----------------------

void testing(){
 set("01010001001");
 delay(1000);
 set("01010001000");
 delay(1000);
}

// Repeat this forever ----------------

void loop() {
 recvWithEndMarker();
 showNewData();
}
