/*
 * Arduino sketch for the fiore gripper
 *
 * Is responsible for publishing sensor information
 * and subscribing to command information
 * 
 * WARNING: The XBee shield has a switch with labels UART and DLINE
 *  The switch must be in the DLINE position when uploading sketches to the arduino.
 *  Then in the UART position when running.
 *  If code is uploaded while in the UART position it will brick the XBee
 */

#include <ros.h>
#include <fiore_gripper_msgs/GripperInput.h>
#include <fiore_gripper_msgs/GripperOutput.h>

ros::NodeHandle nh;

fiore_gripper_msgs::GripperOutput outputMsg;
fiore_gripper_msgs::GripperInput inputMsg;

// callback function for when something is published on the "gripper_input" topic
void inputCb( const fiore_gripper_msgs::GripperInput& inInputMsg){
  analogWrite(7, inInputMsg.air_transducer_voltage);  
}

ros::Publisher pub("gripper_output", &outputMsg);
ros::Subscriber<fiore_gripper_msgs::GripperInput> sub("gripper_input", &inputCb );

void setup()
{
  pinMode(7, OUTPUT);
  
  nh.initNode();
  nh.advertise(pub);
  nh.subscribe(sub);
}

// we average the analog reading to eliminate some of the noise
int averageAnalog(int pin){
 int v=0;
      for(int i=0; i<4; i++) v+= analogRead(pin);
      return v/4;
}

void loop()
{

  outputMsg.force_sensors.right_top    = averageAnalog(8);
  outputMsg.force_sensors.right_middle = averageAnalog(9);
  outputMsg.force_sensors.right_bottom = averageAnalog(10);
  outputMsg.force_sensors.right_tip    = averageAnalog(11);
  outputMsg.force_sensors.left_top     = averageAnalog(12);
  outputMsg.force_sensors.left_middle  = averageAnalog(13);
  outputMsg.force_sensors.left_bottom  = averageAnalog(14);
  outputMsg.force_sensors.left_tip     = averageAnalog(15);

  pub.publish(&outputMsg);

  nh.spinOnce();
  delay(50);
}
