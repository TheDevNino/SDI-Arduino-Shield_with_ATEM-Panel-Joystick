#include <BMDSDIControl.h> // Library um mit dem SDI Shield zu kommunizieren
#define SDI_CONTROL_PIN 10 // Pin des SDI Shields
const int shieldAddress = 0x6E; // Adresse des SDI Shields

#include "LedControl.h" // Library um die LED Matrix anzusteuern
LedControl lc = LedControl(12, 11, 10, 1); // Initialisieren der LED Matrix

bool tallyPreview, tallyProgram;
unsigned long previousMillis = 0;   // Speichert den Zeitpunkt des letzten Statuswechsels
const long intervalSlow = 1000;     // Blinkintervall für 'tallyPreview' (langsam)
const long intervalFast = 100;      // Blinkintervall für 'tallyProgram' (schnell)
bool ledState = false;              // Aktueller Zustand der LED

// Create an instance of the SDI control class
BMD_SDICameraControl_I2C sdiCameraControl(shieldAddress);
BMD_SDITallyControl_I2C sdiTallyControl(shieldAddress);

// Vorwärtsdeklarationen  
void matrixRepresentation(int h, int v, int r);
int realValue(int x, int y);
void tallyRepresentation(unsigned long currentMillis); // Funktionsdeklaration

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialisierung der Matrix
  lc.shutdown(0, false);
  lc.setIntensity(0, 5); // Helligkeit auf mittleren Wert setzen
  lc.clearDisplay(0);    // Matrix leeren

  // Initialize the SDI control
  sdiCameraControl.begin();
  sdiCameraControl.setOverride(true);
}

void loop() {
  unsigned long currentMillis = millis();

  // Define a buffer to store received data
  byte data[64]; // Adjust the size according to your data requirements

  // Read data from ATEM using SDI Camera Control
  int cameraDataLength = sdiCameraControl.read(data, sizeof(data));


    // Extract horizontal joystick movement
    byte horizontalMovement[2] = {data[8], data[9]};

    // Extract vertical joystick movement
    byte verticalMovement[2] = {data[10], data[11]};

    // Extract rotation movement
    byte rotationMovement[2] = {data[20], data[21]};

    Serial.print("H ");
    int h1 = int(horizontalMovement[0]);
    int h2 = int(horizontalMovement[1]);
    int h = realValue(h1, h2);
    Serial.println(h);

    Serial.print("V ");
    int v1 = int(verticalMovement[0]);
    int v2 = int(verticalMovement[1]);
    int v = realValue(v1, v2);
    Serial.println(v);

    Serial.print("R ");
    int r1 = int(rotationMovement[0]);
    int r2 = int(rotationMovement[1]);
    int r = realValue(r1, r2);
    Serial.println(r); 
    Serial.println("---");

    if (sdiTallyControl.getCameraTally(1, tallyProgram, tallyPreview)) {
      // Tally