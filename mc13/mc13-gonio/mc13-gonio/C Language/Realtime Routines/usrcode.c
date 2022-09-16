//---------------------------------------------------------------------------
//  Project PowerPMAC Firmware
//  Delta Tau Data Systems, Inc.
//  Copyright  2007. All Rights Reserved.
//
//  SUBSYSTEM:			User Servo Driver
//  FILE:         		usrcode.c
//  TEMPLATE AUTHOR:		Henry Bausley
//
//  OVERVIEW
//  ~~~~~~~~
//  This file is where exportable user code can be placed.
//  To make a function callable as a user servo do three steps
//
//  1.)  Prototye the function user_func(void ,void );
//  2.)  Export the function  EXPORT_SYMBOL(user_func);
//  3.)  Make sure useralgo.ko has been loaded with projpp.ini
//
//--------------------------------------------------------------------------------
#include "usrcode.h"
//----------------------------------------------------------------------------------
// pp_proj.h is the C header for accessing PMAC Global, CSGlobal, Ptr vars
// _PPScriptMode_ for Pmac Script like access global & csglobal
// global Mypvar - access with "Mypvar"
// global Myparray(32) - access with "Myparray(i)"
// csglobal Myqvar - access with "Myqvar(i)" where "i" is Coord #
// csglobal Myqarray(16) - access with "Myqvar(i,j)" where "j" is index
// _EnumMode_ for Pmac enum data type checking on Set & Get global functions
// Example
// global Mypvar
// csglobal Myqvar
// "SetGlobalVar(Myqvar, data)" will give a compile error because its a csglobal var.
// "SetCSGlobalVar(Mypvar, data)" will give a compile error because its a global var.
//------------------------------------------------------------------------------------
// #define _PPScriptMode_	// uncomment for Pmac Script type access
// #define _EnumMode_			// uncomment for Pmac enum data type checking on Set & Get global functions		

#include "../Include/pp_proj.h"
extern struct SHM        *pshm;  // Pointer to shared memory
extern volatile unsigned *piom;  // Pointer to I/O memory
extern void              *pushm; // Pointer to user memory

void user_phase(struct MotorData *Mptr)
{
}

double user_pid_ctrl(struct MotorData *Mptr)
{
  return 0;
}

// pushm is set to 1 Mbyte (252,144 int's, 65,536 4-positions)
#define USR_MEMORY 1024*1024                  // User memory is 1Mbyte
#define MAX_CAPTURES (USR_MEMORY / 4 / 4 - 1) // Maximum Number of integer 4-position tuples

// Memory layout:
// [counter, 0, 0, 0, x, y, z, o, x, y, z, o, x, y, z, o ... ]

void CaptCompISR (void)
{
  // Get pointers to gate structures
  volatile GateArray3 *FirstGate = GetGate3MemPtr(0);
  volatile GateArray3 *SecondGate = GetGate3MemPtr(1);
  
  // Get pointer to counter
  int *counter = (int*)pushm;
  
  if(*counter < MAX_CAPTURES) 
  {
    /*int *data = (int*)pushm + 4 + 4*(*counter);
  
    // Read raw captured positions
    int x_pos = SecondGate->Chan[0].HomeCapt;
    int y_pos = FirstGate->Chan[2].HomeCapt;
    int z_pos = FirstGate->Chan[3].HomeCapt;
    int o_pos = SecondGate->Chan[3].HomeCapt;
  
    // Store raw captured positions
    *data++ = x_pos;
    *data++ = y_pos;
    *data++ = z_pos;
    *data++ = o_pos;*/
  
    ++*counter;
  }
  
  // Clear interrupt flags
  SecondGate->IntCtrl = 0xFF;
}
