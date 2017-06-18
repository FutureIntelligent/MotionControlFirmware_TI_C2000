/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/*
* communication interface
* collectively handle all communication traffic
*/

#ifndef COMMUNICATION_INTERFACE_H
#define COMMUNICATION_INTERFACE_H

#include "CiATypeDef.h"
#include "ObjectDictionary.h"
#include "Drivers/UartDriver/UartDriver.h"

class CommunicationInterface{

  public:
    CommunicationInterface(UartDriver * UartDriverPtr,
                           ObjectDictionary * ObjectDictionaryPtr)
    {
      _UartDriver = UartDriverPtr;
      _ObjectDictionary = ObjectDictionaryPtr;
    }

    ~CommunicationInterface(){}

    void ExecuteTransmission(void);
    void ExecuteReception(void);

  private:
    UartDriver * _UartDriver;
    ObjectDictionary * _ObjectDictionary;

    CiA_Message msg;

};

#endif
