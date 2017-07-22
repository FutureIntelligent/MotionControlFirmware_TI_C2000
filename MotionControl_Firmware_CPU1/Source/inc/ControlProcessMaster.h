/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/*
* Control process master class
*
* Contains the main state machine of CPU1, handling control processes
*/

#ifndef CONTROL_PROCESS_MASTER_H
#define CONTROL_PROCESS_MASTER_H

#include "stdint.h"

#include "CPU1_CLA1_common.h"
#include "CommutationMaster.h"
#include "CommunicationInterface.h"
#include "ControlProcessData.h"
#include "CurrentLoopController.h"
#include "ControlProcessExecuter.h"
#include "ObjectDictionaryEntryBase.h"

#define MASTER_CYCLE_PRESCALE    4

class ControlProcessMaster: public ObjectDictionaryEntryBase{

  public:

/*
    enum ControlProcessMaster_STATES {
      STATE_PREOP,    // enabled
      STATE_OP,       // enabled and running
      STATE_STOPPED  // disabled
    };
*/
    enum ControlProcessMaster_STATES {
      STATE_NOT_READY,
      STATE_READY,
      STATE_SWITCHED_ON,
      STATE_OPERATION,
      STATE_QUICK_STOP,
      STATE_FAULT
    };

    ControlProcessMaster(CommutationMaster * CommutationMasterPtr,
                         CommunicationInterface * CommunicationInterfacePtr,
                         ControlProcessData * ControlProcessDataPtr,
                         ControlProcessExecuter * ControlProcessExecuterPtr);

    ~ControlProcessMaster(){}

    void SetCurrentValueBuffer(float32_t * bufA, float32_t * bufB);
    void UpdateProcessData(void);
    void Execute(void);

    void AccessMotionControlState(ObdAccessHandle * handle);

    typedef struct ControlProcessMaster_Status_typedef{
      uint16_t _State   :  2;
      uint16_t _ErrCode :  14;
    } ControlProcessMaster_Status;

  private:
    void UpdateMotionControlState(void);

    //enum ControlProcessMaster_STATES _State;
    enum ControlProcessMaster_STATES        _State;

    CommutationMaster * _CommutationMaster;
    CommunicationInterface * _CommunicationInterface;
    ControlProcessData * _ControlProcessData;
    ControlProcessExecuter * _ControlProcessExecuter;

    uint16_t _CycleCounter;
    uint16_t _NmtNewState;
    bool _NmtUpdated;
    ControlProcessMaster_Status _Status;

    CiA_Message _CiA_MsgBuffer;
    CiA_SdoMessage _CiA_SdoBuffer;
    CiA_PdoMessage _CiA_PdoBuffer;


};

#endif
