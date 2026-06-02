/**
 * @file main.cpp
 * @brief Analog Waveform Monitor & Signal Integrity Verification
 * @developer Utsav Anand Sharma
 * * Target Architecture: AVR Architecture (Arduino Uno R3)
 * Use Case: Real-time sampling and visualization of demodulated laser receiver outputs.
 */

#include <Arduino.h>

// Hardware Pin Definitions
const int ANALOG_INPUT_PIN = A0;   // Connected to the output of the Transimpedance Amplifier
const int SIGNAL_INDICATOR  = 13;  // Status LED for active tracking

// Threshold parameters for Morse pulse validation
const int PULSE_THRESHOLD = 600;   // Voltage threshold for digital conversion (0-1023 scale)

void setup() {
    Serial.begin(115200); // High-speed serialization for waveform plotting
    pinMode(ANALOG_INPUT_PIN, INPUT);
    pinMode(SIGNAL_INDICATOR, OUTPUT);
}

void loop() {
    // Sample the continuous analog output from the custom receiver circuit
    int rawSignalValue = analogRead(ANALOG_INPUT_PIN);
    
    // Scale the raw reading to an actual voltage value (5V reference)
    float signalVoltage = (rawSignalValue * 5.0) / 1023.0;
    
    // Print the voltage directly to the serial port for IDE wave plotting
    Serial.println(signalVoltage);
    
    // Threshold comparison logic to track binary pulse states (Morse Code)
    if (rawSignalValue > PULSE_THRESHOLD) {
        digitalWrite(SIGNAL_INDICATOR, HIGH);
    } else {
        digitalWrite(SIGNAL_INDICATOR, LOW);
    }
    
    // 1kHz sampling frequency to prevent missing sharp transitions
    delayMicroseconds(1000); 
}
