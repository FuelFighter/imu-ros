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

int sample_time = 50;
ros::NodeHandle nh;

sensor_msgs::Imu imu_msg;
ros::Publisher pub_ext_imu( "/ext_imu", &imu_msg);

float zeroMatrix[] = {0,0,0,0,0,0,0,0,0};

char frameid[] = "/ext_imu";

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  myIMU.begin();
  Wire.setClock(400000); //Increase I2C data rate to 400kHz

  
  myIMU.enableAccelerometer(sample_time); //Send data update every 50ms
  myIMU.enableGyro(50);
  myIMU.enableMagnetometer(50);

  imu_msg.orientation.w = 0;


  nh.initNode();
  nh.advertise(pub_ext_imu);

    
  imu_msg.header.frame_id =  frameid;
}


void loop()
{
  if (myIMU.dataAvailable() == true){
    //Magnetometer(using quaterion orientation as placeholder)
    imu_msg.orientation.x = myIMU.getMagX();
    imu_msg.orientation.y = myIMU.getMagY();
    imu_msg.orientation.z = myIMU.getMagZ();

    //Angular velocity
    imu_msg.angular_velocity.x = myIMU.getGyroX();
    imu_msg.angular_velocity.y = myIMU.getGyroY();
    imu_msg.angular_velocity.z = myIMU.getGyroZ();

    //Accelertion
    imu_msg.linear_acceleration.x = myIMU.getAccelX();
    imu_msg.linear_acceleration.y = myIMU.getAccelY();
    imu_msg.linear_acceleration.z = myIMU.getAccelZ();
    imu_msg.header.stamp = nh.now();
    pub_ext_imu.publish(&imu_msg);
  }
  nh.spinOnce();
}
