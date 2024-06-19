# SDI-Arduino-Shield_with_ATEM-Panel-Joystick
The code reads joystick movements and tally light statuses from an SDI control shield


## About ATEM_Joystick_Reader.ino

This code initializes an SDI control shield and reads joystick movements from an ATEM switcher, then decodes and prints the horizontal, vertical, and rotational movements to the serial monitor. Easy to use for individually.

## About additionaly features (in the other code example)

This code additionally performs the following functions:

LED Matrix Control: It initializes and controls an LED matrix display using the LedControl library. The joystick movements are visually represented on the LED matrix, and the matrix's brightness is adjusted based on rotational movement.

Tally Light Status: It reads and processes tally light status from the ATEM switcher via the SDI shield and reflects this status through blinking patterns on the LED matrix. The tallyPreview and tallyProgram states determine the blink interval for the LED matrix.

Error Handling: It prints an error message if there is a failure in reading the tally light information.

Improved Matrix Representation: The matrixRepresentation function now includes a feature to display a central 2x2 block if both horizontal and vertical movements are zero.

Conditional LED Intensity Change: The LED intensity only changes when necessary, optimizing performance.

https://github.com/TheDevNino/SDI-Arduino-Shield_with_ATEM-Panel-Joystick/assets/44969214/4340b083-1944-4d33-a3a5-2c072c12d3cd

