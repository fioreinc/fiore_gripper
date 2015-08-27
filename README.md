# Intro
Code to interface the gripper, all actuators, and sensors with the rest of ROS. Including the arduino code that runs on the arduino.

## How to use

### arduino_sketch

**WARNING** The Arduino has a [Sparkfun XBee Shield.](https://www.sparkfun.com/products/12847) The shield has a switch with labels DLINE and UART as can be seen in [this Sparkfun Tutorial](https://learn.sparkfun.com/tutorials/xbee-shield-hookup-guide#hardware-overview) When new code is being uploaded to the arduino the switch must be in the DLINE position. When the arduino is running the switch must be in the UART position. Failure to do so will brick the XBee. This is simply a consequence of how [rosserial_xbee](http://wiki.ros.org/rosserial_xbee) works.

First thing to do is to make sure the arduino sketch contained in the folder `arduino_sketch` is loaded onto the Arduino. 
* Connect to Arduino to the PC using the USB cable. 
* Open the Arduino IDE from the start menu. 
* Open the sketch from this repository (arduino_sketch) 
* The Arduino should connect on `/dev/ttyACM0`. You may have to change this through `Tools -> Serial Port` if the Arduino does not connect autmatically. 
* Then upload the sketch. Arrow button underneath the toolbar. 

### demo_gripper_control

This package contains a simple python script that publishes to the topic `\gripper_input` values that come from user input on the command line. Essentially a quick and dirty way to control the gripper. 
The script can be run with:
    $ rosrun demo_gripper_control talker.py







