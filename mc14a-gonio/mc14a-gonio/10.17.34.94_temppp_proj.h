
#ifndef _PP_PROJ_H_
#define _PP_PROJ_H_
//***********************************************************************************
// C header for accessing PMAC Global, CSGlobal, Ptr vars
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
//************************************************************************************

#ifdef _PPScriptMode_
enum globalP {_globalP_=-1};
enum globalParray {_globalParray_=-1};
enum csglobalQ {_csglobalQ_=-1};
enum csglobalQarray {_csglobalQarray_=-1};

enum ptrM {_ptrM_=-1
,DAC1X9=8192
,ADC1X9=8193
,Enc8Equ=8194
,Enc8CompA=8195
,Enc8CompB=8196
,Enc8CompAdd=8197
,Enc8EquWrite=8198
,Enc8Equ1Ena=8199
,Enc8EquOutMask=8200
,Enc8EquOutPol=8201};
enum ptrMarray {_ptrMarray_=-1};
#define	VecState	pshm->P[8192]
#define	VecRunning	pshm->P[8193]
#define	VecGo	pshm->P[8194]
#define	VecProceed	pshm->P[8195]
#define	VecAbort	pshm->P[8196]
#define	VecExpose	pshm->P[8197]
#define	VecHold	pshm->P[8198]
#define	VecSetupGather	pshm->P[8199]
#define	VecNumSamples	pshm->P[8200]
#define	VecExposure	pshm->P[8201]
#define	VecDataAcqDuration	pshm->P[8202]
#define	VecShutChgPos	pshm->P[8203]
#define	VecShutTime	pshm->P[8204]
#define	VecBufferTime	pshm->P[8205]
#define	VecMaxTimeToSpeed	pshm->P[8206]
#define	VecTooFast(i)	pshm->P[(8207+i)%MAX_P]
#define	VecStartPos(i)	pshm->P[(8211+i)%MAX_P]
#define	VecEndPos(i)	pshm->P[(8215+i)%MAX_P]
#define	VecAccel(i)	pshm->P[(8219+i)%MAX_P]
#define	VecDataAcqDist(i)	pshm->P[(8223+i)%MAX_P]
#define	VecDesSpeed(i)	pshm->P[(8227+i)%MAX_P]
#define	VecTimeToSpeed(i)	pshm->P[(8231+i)%MAX_P]
#define	VecDir(i)	pshm->P[(8235+i)%MAX_P]
#define	VecSpeedUpDist(i)	pshm->P[(8239+i)%MAX_P]
#define	VecBufferDist(i)	pshm->P[(8243+i)%MAX_P]
#define	VecShutOpenDist(i)	pshm->P[(8247+i)%MAX_P]
#define	VecShutLagDist(i)	pshm->P[(8251+i)%MAX_P]
#define	VecBackUpDist(i)	pshm->P[(8255+i)%MAX_P]
#define	ShutterOpenPos	pshm->P[8259]
#define	ShutterClosedPos	pshm->P[8260]
#define	ShutterSpeed	pshm->P[8261]
#define	ShutterLag	pshm->P[8262]
#define	MotorIdleTime(i)	pshm->P[(8263+i)%MAX_P]
#define	HomeGonioState	pshm->P[8271]
#define	Enc8PhaseCapt	pshm->P[8272]
#define	ForceEqu8Off	pshm->P[8273]
#define	Enc8PosCompMode	pshm->P[8274]
#define	Enc8PulseA	pshm->P[8275]
#define	Enc8PulseB	pshm->P[8276]
#define	Enc8PulsePeriod	pshm->P[8277]
#define	Enc8CompAUser	pshm->P[8278]
#define	Enc8CompBUser	pshm->P[8279]
#define	Enc8CompAddUser	pshm->P[8280]
#ifndef _PP_PROJ_HDR_
  void SetEnumGlobalVar(enum globalP var, double data)
  {
    pshm->P[var] = data;
  }

  double GetEnumGlobalVar(enum globalP var)
  {
    return pshm->P[var];
  }

  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data)
  {
    pshm->P[(var + index)%MAX_P] = data;
  }

  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index)
  {
    return pshm->P[(var + index)%MAX_P];
  }

  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[var] = data;
  }

  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[var];
  }

  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q] = data;
  }

  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q];
  }

  void SetEnumPtrVar(enum ptrM var, double data)
  {
    im_write(pshm->Mdef + var, data, &pshm->Ldata);
  }

  double GetEnumPtrVar(enum ptrM var)
  {
    return im_read(pshm->Mdef + var, &pshm->Ldata);
  }

  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data)
  {
    im_write(pshm->Mdef + ((var + index)%MAX_M), data, &pshm->Ldata);
  }

  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index)
  {
    return im_read(pshm->Mdef + ((var + index)%MAX_M), &pshm->Ldata);
  }

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#else

  void SetEnumGlobalVar(enum globalP var, double data);
  double GetEnumGlobalVar(enum globalP var);
  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data);
  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index);
  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data);
  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs);
  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data);
  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs);
  void SetEnumPtrVar(enum ptrM var, double data);
  double GetEnumPtrVar(enum ptrM var);
  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data);
  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index);

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#endif
// end of #ifdef _PPScriptMode_
#else
#ifdef _EnumMode_
enum globalP {_globalP_=-1
,VecState=8192
,VecRunning=8193
,VecGo=8194
,VecProceed=8195
,VecAbort=8196
,VecExpose=8197
,VecHold=8198
,VecSetupGather=8199
,VecNumSamples=8200
,VecExposure=8201
,VecDataAcqDuration=8202
,VecShutChgPos=8203
,VecShutTime=8204
,VecBufferTime=8205
,VecMaxTimeToSpeed=8206
,ShutterOpenPos=8259
,ShutterClosedPos=8260
,ShutterSpeed=8261
,ShutterLag=8262
,HomeGonioState=8271
,Enc8PhaseCapt=8272
,ForceEqu8Off=8273
,Enc8PosCompMode=8274
,Enc8PulseA=8275
,Enc8PulseB=8276
,Enc8PulsePeriod=8277
,Enc8CompAUser=8278
,Enc8CompBUser=8279
,Enc8CompAddUser=8280};
enum globalParray {_globalParray_=-1
,VecTooFast=8207
,VecStartPos=8211
,VecEndPos=8215
,VecAccel=8219
,VecDataAcqDist=8223
,VecDesSpeed=8227
,VecTimeToSpeed=8231
,VecDir=8235
,VecSpeedUpDist=8239
,VecBufferDist=8243
,VecShutOpenDist=8247
,VecShutLagDist=8251
,VecBackUpDist=8255
,MotorIdleTime=8263};
enum csglobalQ {_csglobalQ_=-1};
enum csglobalQarray {_csglobalQarray_=-1};
enum ptrM {_ptrM_=-1
,DAC1X9=8192
,ADC1X9=8193
,Enc8Equ=8194
,Enc8CompA=8195
,Enc8CompB=8196
,Enc8CompAdd=8197
,Enc8EquWrite=8198
,Enc8Equ1Ena=8199
,Enc8EquOutMask=8200
,Enc8EquOutPol=8201};
enum ptrMarray {_ptrMarray_=-1};
#ifndef _PP_PROJ_HDR_
  void SetEnumGlobalVar(enum globalP var, double data)
  {
    pshm->P[var] = data;
  }

  double GetEnumGlobalVar(enum globalP var)
  {
    return pshm->P[var];
  }

  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data)
  {
    pshm->P[(var + index)%MAX_P] = data;
  }

  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index)
  {
    return pshm->P[(var + index)%MAX_P];
  }

  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[var] = data;
  }

  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[var];
  }

  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data)
  {
    pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q] = data;
  }

  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs)
  {
    return pshm->Coord[cs % MAX_COORDS].Q[(var + index)%MAX_Q];
  }

  void SetEnumPtrVar(enum ptrM var, double data)
  {
    im_write(pshm->Mdef + var, data, &pshm->Ldata);
  }

  double GetEnumPtrVar(enum ptrM var)
  {
    return im_read(pshm->Mdef + var, &pshm->Ldata);
  }

  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data)
  {
    im_write(pshm->Mdef + ((var + index)%MAX_M), data, &pshm->Ldata);
  }

  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index)
  {
    return im_read(pshm->Mdef + ((var + index)%MAX_M), &pshm->Ldata);
  }

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#else

  void SetEnumGlobalVar(enum globalP var, double data);
  double GetEnumGlobalVar(enum globalP var);
  void SetEnumGlobalArrayVar(enum globalParray var, unsigned index, double data);
  double GetEnumGlobalArrayVar(enum globalParray var, unsigned index);
  void SetEnumCSGlobalVar(enum csglobalQ var, unsigned cs, double data);
  double GetEnumCSGlobalVar(enum csglobalQ var, unsigned cs);
  void SetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs, double data);
  double GetEnumCSGlobalArrayVar(enum csglobalQarray var, unsigned index, unsigned cs);
  void SetEnumPtrVar(enum ptrM var, double data);
  double GetEnumPtrVar(enum ptrM var);
  void SetEnumPtrArrayVar(enum ptrMarray var, unsigned index, double data);
  double GetEnumPtrArrayVar(enum ptrMarray var, unsigned index);

  #define SetGlobalVar(i, x)              SetEnumGlobalVar(i, x)
  #define SetGlobalArrayVar(i, j, x)      SetEnumGlobalArrayVar(i, j, x)
  #define GetGlobalVar(i)                 GetEnumGlobalVar(i)
  #define GetGlobalArrayVar(i, j)         GetEnumGlobalArrayVar(i, j)

  #define SetCSGlobalVar(i, j, x)         SetEnumCSGlobalVar(i, j, x)
  #define SetCSGlobalArrayVar(i, j, k, x) SetEnumCSGlobalArrayVar(i, j, k, x)
  #define GetCSGlobalVar(i, j)            GetEnumCSGlobalVar(i, j)
  #define GetCSGlobalArrayVar(i, j, k)    GetEnumCSGlobalArrayVar(i, j, k)

  #define SetPtrVar(i, x)                 SetEnumPtrVar(i, x)
  #define SetPtrArrayVar(i, j, x)         SetEnumPtrArrayVar(i, j, x)
  #define GetPtrVar(i)                    GetEnumPtrVar(i)
  #define GetPtrArrayVar(i, j)            GetEnumPtrArrayVar(i, j)

#endif
// end of #ifdef _EnumMode_
#else
// ***** Standard default mode *****
#define VecState 8192
#define VecRunning 8193
#define VecGo 8194
#define VecProceed 8195
#define VecAbort 8196
#define VecExpose 8197
#define VecHold 8198
#define VecSetupGather 8199
#define VecNumSamples 8200
#define VecExposure 8201
#define VecDataAcqDuration 8202
#define VecShutChgPos 8203
#define VecShutTime 8204
#define VecBufferTime 8205
#define VecMaxTimeToSpeed 8206
#define VecTooFast 8207
#define VecStartPos 8211
#define VecEndPos 8215
#define VecAccel 8219
#define VecDataAcqDist 8223
#define VecDesSpeed 8227
#define VecTimeToSpeed 8231
#define VecDir 8235
#define VecSpeedUpDist 8239
#define VecBufferDist 8243
#define VecShutOpenDist 8247
#define VecShutLagDist 8251
#define VecBackUpDist 8255
#define ShutterOpenPos 8259
#define ShutterClosedPos 8260
#define ShutterSpeed 8261
#define ShutterLag 8262
#define MotorIdleTime 8263
#define HomeGonioState 8271
#define Enc8PhaseCapt 8272
#define ForceEqu8Off 8273
#define Enc8PosCompMode 8274
#define Enc8PulseA 8275
#define Enc8PulseB 8276
#define Enc8PulsePeriod 8277
#define Enc8CompAUser 8278
#define Enc8CompBUser 8279
#define Enc8CompAddUser 8280
#define DAC1X9 8192
#define ADC1X9 8193
#define Enc8Equ 8194
#define Enc8CompA 8195
#define Enc8CompB 8196
#define Enc8CompAdd 8197
#define Enc8EquWrite 8198
#define Enc8Equ1Ena 8199
#define Enc8EquOutMask 8200
#define Enc8EquOutPol 8201
#endif
#endif
#endif //_PP_PROJ_H_
