# Voice Controlled Robotic Vehicle

## Description

This project allows controlling a robotic vehicle through voice commands received via an Android application. The integration of a control unit with a Bluetooth device captures and reads voice commands, and the robotic vehicle operates accordingly. The Arduino Uno microcontroller is used to enable the operation of the vehicle via the Android application.

## Components Required

1. Android system
2. Arduino Uno
3. 2x L293d motor controller circuit
4. 4x motors and wheels
5. HC SR04 ultrasonic sensor
6. 9g servo
7. Batteries
8. HC 05 Bluetooth Module

## Block Diagram
![Block Diagram](https://github.com/github2411/Voice-controlled-robotic-car/assets/67455073/dcf1db1c-55e0-4e44-b0d9-315b16ea6576)

## Circuit Diagram
![Circuit Diagram](https://github.com/github2411/Voice-controlled-robotic-car/assets/67455073/040fff23-7f55-4438-95e6-d871a4b72033)

## Working

1. The Android App has 5 keys: Forward, Reverse, Left, Right, and Stop.
2. Corresponding data associated with each key:
   - Forward – 1
   - Reverse – 2
   - Left – 3
   - Right – 4
   - Stop – 5
3. When a key is pressed, the data is transmitted to the Bluetooth Module from the Phone over Bluetooth Communication.
4. The Arduino UNO receives the data from the Bluetooth Module and performs a switch case operation.
5. Each case is associated with appropriate instructions to the Motor Driver Input Pins.
6. For example, if ‘Forward’ key is pressed, Arduino makes IN1 and IN3 as HIGH and IN2 and IN4 as LOW to achieve forward motion.
7. Other keys correspond to appropriate setting of IN1 – IN4 pins.
