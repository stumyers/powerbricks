#include <gplib.h>
#include <stdio.h>
#include <dlfcn.h>
#include "../../Include/pp_proj.h"
 
void user_plcc()
{
    volatile GateArray3 *Gate3_0;
    volatile GateArray3 *Gate3_1;
    Gate3_0 = GetGate3MemPtr(0);
    Gate3_1 = GetGate3MemPtr(1);
       
    int C_Enc8Equ;
       
    // C CODE Executing?
    pshm->P[1000]++;

    // SCALE QUADRATURE ENCODER PHASE CAPTURE TO MATCH COMPARE UNITS
    pshm->P[Enc8PhaseCapt] = (Gate3_1->Chan[3].PhaseCapt << 4) & 0xFFFFFFFF;
   
    // ENCODER 1 EQU
    C_Enc8Equ = (Gate3_1->Chan[3].Status & 0x1FFFFFF) >> 24;
   
    // EQU ON? COUNTER
    if(C_Enc8Equ) {pshm->P[1001]++;}
   
    // FORCE EQU 1 OFF, KEEP COMP A & B AWAY FROM PHASE CAPTURE
    if(pshm->P[ForceEqu8Off] > 0)
    {
        int Temp0;
        Temp0 = -1073741824 + (int) pshm->P[Enc8PhaseCapt];
        Gate3_1->Chan[3].CompA = Temp0;
        Gate3_1->Chan[3].CompB = Temp0;
        Gate3_1->Chan[3].CompAdd = 0;
    }
}




