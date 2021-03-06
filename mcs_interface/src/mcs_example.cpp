/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

 /**
  *  implement the mcs_interface node
  */

#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "termios.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"

#include "ros/ros.h"
#include "CANOpen/CANOpenDataTypeDef.h"
#include "CANOpen/PdoTypeDef.h"

#include "std_msgs/String.h"
#include "mcs_interface/CiA_SdoMessage.h"
#include "mcs_interface/CiA_PdoMessage.h"
#include "mcs_interface/CiA_NmtMessage.h"

volatile bool terminate;
std::ofstream OutputFile;

void SdoReplyCallback(const mcs_interface::CiA_SdoMessage::ConstPtr& msg){
  printf("got reply! \n");
  terminate = true;

  ObdAccessHandle handle;
  handle.Data.DataInt16[0] = msg->Data[0];
  handle.Data.DataInt16[1] = msg->Data[1];
  handle.AccessResult = msg->AccessResult;

  if(handle.AccessResult==0){
    printf("sdo access successful, value: %d\n", handle.Data.DataUint16[0] );
  }else{
    printf("sdo access failed: %d\n", handle.AccessResult);
  }
}

void PdoCallback(const mcs_interface::CiA_PdoMessage::ConstPtr& msg){
  PdoData data;

  if(msg->PDO_ID==PDO_ID_CLSW){
    data.data[0] = msg->Data[0];
    data.data[1] = msg->Data[1];
    data.data[2] = msg->Data[2];
    data.data[3] = msg->Data[3];
    data.data[4] = msg->Data[4];

    OutputFile << data.clsw.CurrentActual[0] << std::endl;
    OutputFile << data.clsw.CurrentActual[1] << std::endl;
    OutputFile << data.clsw.CurrentActual[2] << std::endl;
    OutputFile << data.clsw.CurrentActual[3] << std::endl;
  }
}

int main(int argc, char **argv){

  ros::init(argc, argv, "mcs_example");
  ros::NodeHandle node;

  terminate = false;

  // initialize publisher
  ros::Publisher sdo_pub = node.advertise<mcs_interface::CiA_SdoMessage>("SdoRequest", 20);
  ros::Publisher nmt_pub = node.advertise<mcs_interface::CiA_NmtMessage>("Nmt", 20);
  ros::Subscriber sdo_sub = node.subscribe("SdoReply", 5, SdoReplyCallback);
  ros::Subscriber pdo_sub = node.subscribe("Pdo", 100, PdoCallback);

  ObdAccessHandle handle;
  handle.Data.DataFloat32 = 31.2;

  mcs_interface::CiA_SdoMessage msg;
  msg.Idx = 0x2106;
  msg.SubIdx = 0x05;
  msg.AccessType = SDO_CSS_READ;
  msg.AccessResult = 0;
  msg.Data[0] = 34;
  msg.Data[1] = 43;
  msg.Length = 10;

  usleep (1000000);
  //sdo_pub.publish(msg);

  mcs_interface::CiA_NmtMessage msg1;
  msg1.NodeID = 0x03;
  msg1.State = NMT_TEST_CALIBRATION;
  nmt_pub.publish(msg1);

  while(ros::ok() && (!terminate)){

    ros::spinOnce();
    usleep(100);
  }
}
