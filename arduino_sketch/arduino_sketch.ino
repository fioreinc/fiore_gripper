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
#include <gripper_msgs/gripperInput.h>
#include <gripper_msgs/outputForceSensors.h>
//#include <rosserial_arduino/Adc.h>

ros::NodeHandle nh;

//rosserial_arduino::Adc adc_msg;
gripper_msgs::outputForceSensors outputForceSensors_msg;
gripper_msgs::gripperInput gripperInput_msg;

void inputCb( const gripper_msgs::gripperInput& in_gripperInput_msg){
  digitalWrite(7, in_gripperInput_msg.air_transducer_voltage);   // blink the led
}

ros::Publisher pub("gripper_output_force_sensors", &output_force_sensors_msg);
ros::Subscriber<gripper_msgs::gripperInput> sub("gripper_input", &inputCb );

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

    output_force_sensors_msg.right_top    = averageAnalog(8);
    output_force_sensors_msg.right_middle = averageAnalog(9);
    output_force_sensors_msg.right_bottom = averageAnalog(10);
    output_force_sensors_msg.right_tip    = averageAnalog(11);
    output_force_sensors_msg.left_top     = averageAnalog(12);
    output_force_sensors_msg.left_middle  = averageAnalog(13);
    output_force_sensors_msg.left_bottom  = averageAnalog(14);
    output_force_sensors_msg.left_tip     = averageAnalog(15);

    pub.publish(&output_force_sensors_msg);

  nh.spinOnce();
  delay(500);
}
