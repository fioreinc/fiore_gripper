#!/usr/bin/env python

## Simple talker demo that published std_msgs/Strings messages
## to the 'chatter' topic

import rospy
from std_msgs.msg import Int16

def talker():
    pub = rospy.Publisher('gripper_control', Int16, queue_size=10)
    rospy.init_node('voltage_commander', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    inVoltage = 0
    while not rospy.is_shutdown():
        inVoltage = int(raw_input("Desired inVoltage: "))
        rospy.loginfo(inVoltage)
        pub.publish(inVoltage)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
