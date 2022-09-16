#include "usrcode.h"
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

