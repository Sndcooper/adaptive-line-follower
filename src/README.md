# Source Directory

This folder contains the active source code for the PlatformIO project.

## main.cpp

This is the **primary entry point**. PlatformIO compiles this file to run on the Arduino.

- **Current State**:
  - Configured for **3 Analog Sensors** (Right: A2, Middle: A3, Left: A4).
  - **Motor Driver**: L298N using pins 5, 6, 7, 8, 9, 10.
  - **Logic**: 
    - setup(): Initializes sensor pins as inputs.
    - loop(): Reads sensors and executes commands.
    - orward(leftSpeed, rightSpeed): Helper function to control individual motor speeds and directions.

- **How to use other files**:
  To switch to a 5-sensor PID algorithm or any other file from linefollow/ or PID-Line-Follower-Robot/:
  1. Open the desired .cpp or .ino file.
  2. Copy the contents (Variable definitions, setup, loop, helper functions).
  3. Paste them into src/main.cpp, replacing the current content.
  4. Build and Upload.
