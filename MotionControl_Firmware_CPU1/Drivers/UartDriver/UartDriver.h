/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/**
 * handling traffic from UART
 */

#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "stdint.h"
#include "F28x_Project.h"
#include "CiATypeDef.h"

class UartDriver{
  public:
    UartDriver();
    ~UartDriver();

    void ExecuteParsing(void);

  private:
    uint16_t RawDataBuffer[16];
    CiA_Message MessageBuffer;
};

#endif
