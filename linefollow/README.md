# Line Follower - Alternative Implementations

This directory allows for modular testing of different sensor configurations and algorithms. Each file represents a different approach or hardware setup.

## File Descriptions

### 2/3 Sensor Configurations
- **3ir.ino**
  - **Sensors**: 3 (Pins 2, 3, 4)
  - **Driver**: L298N (Discrete Pins)
  - **Description**: Standard logic for a 3-sensor robot. Uses basic if-else logic for center/left/right detection. Defines specific PWM pins for speed control.
  
- **	emp3irpid.ino**
  - **Sensors**: 3 (Pins A1, A2, A3)
  - **Driver**: L298N
  - **Description**: An attempt to implement PID control on a 3-sensor setup. Includes boilerplate comments for motor initialization.

- **3irfroback.cpp**
  - **Sensors**: 5 defined (A1-A5), but likely uses subset logic or name is legacy.
  - **Description**: C++ source file defining motor and sensor pins. Contains variables for turning speeds (	urnspeed = 180).

- **line-temp1.ino**
  - **Sensors**: 2 (Pins 12, 4)
  - **Description**: A temporary test file. Very basic setup with 2 sensors and motor pins. Likely used for connection testing.

- **linefollow1.ino**
  - **Sensors**: 2 (Pins 12, 11)
  - **Description**: Basic line follower logic for 2 sensors. Defines 	urnspeed and straightspeed.

### 4 Sensor Configurations
- **4irLinefollower.ino**
  - **Sensors**: 4 (Pins 1, 2, 3, 4)
  - **Driver**: L298N
  - **Description**: Logic handling 4 sensors (S1 to S4). Differentiates between high and low turn speeds for smoother turning.

### 5 Sensor Configurations
- **5ir.cpp**
  - **Sensors**: 5 (Pins A1-A5)
  - **Description**: C++ implementation for a 5-sensor array. Defines defaultSpeed, sharpspeed, and 	urnspeed. Used as a source to copy into main.cpp.

### PID Implementations
- **pidLinefollower.ino**
  - **Sensors**: 2 (Pins 12, 4)
  - **Description**: Implementation of a PID controller (Kp, Ki, Kd constants defined). Calculates error and adjusts motor speed based on PID output to center the robot on the line.
