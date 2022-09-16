
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
,ADC1X9=8193};
enum ptrMarray {_ptrMarray_=-1};
#define	RasterExposure	pshm->P[8192]
#define	RasterRastering	pshm->P[8193]
#define	RasterStartX	pshm->P[8194]
#define	RasterStartO	pshm->P[8195]
#define	RasterStepX	pshm->P[8196]
#define	RasterStepO	pshm->P[8197]
#define	RasterNumSamples	pshm->P[8198]
#define	RasterDirection	pshm->P[8199]
#define	VectorStartX	pshm->P[8200]
#define	VectorStartY	pshm->P[8201]
#define	VectorStartZ	pshm->P[8202]
#define	VectorStartO	pshm->P[8203]
#define	VectorEndX	pshm->P[8204]
#define	VectorEndY	pshm->P[8205]
#define	VectorEndZ	pshm->P[8206]
#define	VectorStepO	pshm->P[8207]
#define	VectorExposure	pshm->P[8208]
#define	VectorNumSamples	pshm->P[8209]
#define	VectorRunning	pshm->P[8210]
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
// end of #ifdef _PPScriptMode_
#else
#ifdef _EnumMode_
enum globalP {_globalP_=-1
,RasterExposure=8192
,RasterRastering=8193
,RasterStartX=8194
,RasterStartO=8195
,RasterStepX=8196
,RasterStepO=8197
,RasterNumSamples=8198
,RasterDirection=8199
,VectorStartX=8200
,VectorStartY=8201
,VectorStartZ=8202
,VectorStartO=8203
,VectorEndX=8204
,VectorEndY=8205
,VectorEndZ=8206
,VectorStepO=8207
,VectorExposure=8208
,VectorNumSamples=8209
,VectorRunning=8210};
enum globalParray {_globalParray_=-1};
enum csglobalQ {_csglobalQ_=-1};
enum csglobalQarray {_csglobalQarray_=-1};
enum ptrM {_ptrM_=-1
,DAC1X9=8192
,ADC1X9=8193};
enum ptrMarray {_ptrMarray_=-1};
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
// end of #ifdef _EnumMode_
#else
// ***** Standard default mode *****
#define RasterExposure 8192
#define RasterRastering 8193
#define RasterStartX 8194
#define RasterStartO 8195
#define RasterStepX 8196
#define RasterStepO 8197
#define RasterNumSamples 8198
#define RasterDirection 8199
#define VectorStartX 8200
#define VectorStartY 8201
#define VectorStartZ 8202
#define VectorStartO 8203
#define VectorEndX 8204
#define VectorEndY 8205
#define VectorEndZ 8206
#define VectorStepO 8207
#define VectorExposure 8208
#define VectorNumSamples 8209
#define VectorRunning 8210
#define DAC1X9 8192
#define ADC1X9 8193
#endif
#endif
#endif //_PP_PROJ_H_
