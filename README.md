# imu-ros

Code to send the measurements from the inertial measurement unit(IMU) and send it through ROS to the computer. It publishes to the topic `ext_imu` as a [imu message](http://docs.ros.org/melodic/api/sensor_msgs/html/msg/Imu.html), but the covariance is not used.
