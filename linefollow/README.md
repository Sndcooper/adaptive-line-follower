# Line Follower - Experimental Implementations

This directory contains modular, testable implementations of various line follower algorithms. Each file demonstrates a different approach, hardware configuration, or control strategy.

## 2-3 Sensor Configurations

### 3ir.ino
- **Sensors**: 3 (Pins 2, 3, 4)
- **Driver**: L298N
- **Algorithm**: Basic conditional logic
- **Use**: Simple 3-sensor line following with discrete left/right/center detection

### temp3irpid.ino
- **Sensors**: 3 (Pins A1, A2, A3)
- **Driver**: L298N
- **Algorithm**: PID control (experimental)
- **Use**: PID-based control attempt for 3-sensor configuration

### 3irfroback.cpp
- **Sensors**: 5 defined (A1-A5), uses subset logic
- **Driver**: Not specified
- **Algorithm**: Motor/sensor initialization utilities
- **Use**: Reference file for pin definitions and speed constants

### line-temp1.ino
- **Sensors**: 2 (Pins 12, 4)
- **Algorithm**: Basic binary logic
- **Use**: Minimal test setup for hardware connectivity

### linefollow1.ino
- **Sensors**: 2 (Pins 12, 11)
- **Algorithm**: Binary line detection
- **Use**: Basic 2-sensor line following implementation

## 4 Sensor Configuration

### 4irLinefollower.ino
- **Sensors**: 4 (Pins 1, 2, 3, 4)
- **Driver**: L298N
- **Algorithm**: Conditional logic with speed differentiation
- **Features**:
  - Distinguishes between sharp and gentle turns
  - Smoother turning with high/low speed profiles
- **Use**: 4-sensor setups requiring better curve handling

## 5 Sensor Configuration

### 5ir.cpp
- **Sensors**: 5 (Pins A1-A5)
- **Algorithm**: Weighted position calculation
- **Constants**: defaultSpeed, sharpspeed, turnspeed
- **Use**: Foundation for advanced 5-sensor implementations

## PID-Based Implementations

### pidLinefollower.ino
- **Sensors**: 2 (Pins 12, 4)
- **Algorithm**: PID controller (Kp, Ki, Kd tuned)
- **Features**:
  - Proportional, integral, and derivative terms
  - Continuous error calculation
  - Motor speed adjustment based on line position
- **Use**: Smooth, adaptive line following with better curve handling

## How to Use

1. Review the file descriptions above
2. Select an implementation matching your sensor count
3. Copy the code into src/main.cpp
4. Upload to your Arduino via PlatformIO
5. Tune constants (speed, PID gains) based on track conditions

## Notes

- Files with .ino extension are Arduino sketches
- Files with .cpp extension are C++ source files
- PWM pins vary by configuration - check pin definitions before uploading
- PID implementations require tuning for optimal performance
