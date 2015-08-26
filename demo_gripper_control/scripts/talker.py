#!/usr/bin/env python

## Simple talker demo that published std_msgs/Strings messages
## to the 'chatter' topic

import rospy
from gripper_msgs.msg import gripperInput

def talker():
    pub = rospy.Publisher('gripper_input', gripperInput, queue_size=10)
    rospy.init_node('demo_gripper_input', anonymous=True)
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
