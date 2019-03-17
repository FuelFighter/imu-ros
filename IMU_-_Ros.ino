/* 
 * rosserial IMU Example
 * 
 * This example is for the 
 */

#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Imu.h>
#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h"

BNO080 myIMU;


ros::NodeHandle nh;

sensor_msgs::Imu imu_msg;
ros::Publisher pub_ext_imu( "/ext_imu", &imu_msg);

float zeroMatrix[] = {0,0,0,0,0,0,0,0,0};

char frameid[] = "/ext_imu";

void setup()
{
  Wire.begin();
  myIMU.begin();
  Wire.setClock(400000); //Increase I2C data rate to 400kHz

  
  myIMU.enableAccelerometer(50); //Send data update every 50ms


  nh.initNode();
  nh.advertise(pub_ext_imu);

    
  imu_msg.header.frame_id =  frameid;
}


long IMU_time = 0;

void loop()
{
  
  //publish the value every 50 milliseconds
  if ( millis() >= IMU_time ){
    imu_msg.linear_acceleration.x = myIMU.getAccelX();
    imu_msg.linear_acceleration.y = myIMU.getAccelY();
    imu_msg.linear_acceleration.z = myIMU.getAccelZ();
    imu_msg.header.stamp = nh.now();
    pub_ext_imu.publish(&imu_msg);
    IMU_time =  millis() + 50;
  }
  
  nh.spinOnce();
}
