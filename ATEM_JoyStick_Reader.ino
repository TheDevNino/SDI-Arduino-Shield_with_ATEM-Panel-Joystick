#include <BMDSDIControl.h>

// Define the pin connection for the SDI-3G board
#define SDI_CONTROL_PIN 10

const int shieldAddress = 0x6E;

// Create an instance of the SDI control class
BMD_SDICameraControl_I2C sdiCameraControl(shieldAddress);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the SDI control
  sdiCameraControl.begin();
}

void loop() {
  // Define a buffer to store received data
  byte data[64]; // Adjust the size according to your data requirements

  // Read data from ATEM using SDI Camera Control
  int cameraDataLength = sdiCameraControl.read(data, sizeof(data));

  // Check if data is received
  if (cameraDataLength > 0) {
    // Extract horizontal joystick movement
    byte horizontalMovement[2] = {data[8], data[9]};

    // Extract vertical joystick movement
    byte verticalMovement[2] = {data[10], data[11]};

    // Extract rotation movement
    byte rotationMovement[2] = {data[20], data[21]};

    Serial.print("H ");
    int h1 = int(horizontalMovement[0]);
    //Serial.print(horizontalMovement[0]);
    //Serial.print(",");
    int h2 = int(horizontalMovement[1]);
    //Serial.println(horizontalMovement[1]);
    int h = realValue(h1, h2);
    Serial.println(h);

    Serial.print("V ");
    int v1 = int(verticalMovement[0]);
    //Serial.print(v1);
    //Serial.print(",");
    int v2 = int(verticalMovement[1]);
    //Serial.println(v2);/Users/ninocataffo/Downloads/ATEM_JoyStick_Reader/ATEM_JoyStick_Reader.ino
    int v = realValue(v1, v2);
    Serial.println(v);


    Serial.print("R ");
    int r1 = int(rotationMovement[0]);
    //Serial.print(r1);
    //Serial.print(",");
    int r2 = int(rotationMovement[1]);
    //Serial.println(r2);
    int r = realValue(r1, r2);
    Serial.println(r);
    
    Serial.println("---");
  }

  // Add a delay if necessary to avoid flooding the serial monitor
  delay(1); // Adjust the delay time as needed
}


int realValue(int x, int y){
  int z = 99;

  if (y <= 8) {
    z = x + y*255;
  } else {
    z = -(map(x, 255, 0, 0, 255) + map(y, 255, 248, 0, 7)*255); 
  }

  return z;
}