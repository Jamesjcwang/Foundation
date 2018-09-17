#ifndef __I_GetShaID_h__
#define __I_GetShaID_h__
#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_I2C.h"
#include "library\Physic\Header\I_IO.h"
#include "library\Physic\Header\I_Timer.h"
#include "library\Component\Header\I_Delayobject.h"
#include "library\Component\Header\I_Model.h"
#include "library\Component\Header\I_CRC.h"


typedef struct
{

IOBaseAddress ioport;
I2CBaseAddress i2cport;
PinAndPinset sclpin,sdapin;
Pull_Push scltype,sdatype;
uint32_t slaveaddress;
uint32_t step;
enum_CmdID tempcmd;
uint8_t templength,tempvalue,tempcount;
volatile uint8_t  _receivedata[50];

enum_CmdID cmdft;


} Shaparameter;

typedef struct {

 void(* Routine)(bool reset,uint32_t shaparaindex,
                         uint32_t crcparainindex,uint32_t crcparaoutindex,
                         uint32_t delayparaindex,uint32_t modelinindex,
                         uint32_t modeloutindex);
 uint32_t (*ParameterInitial)(enum_CmdID cmdft,
                              I2CBaseAddress i2cport,IOBaseAddress ioport,
                              uint32_t slaveaddress,PinAndPinset sclpin,
                              PinAndPinset sdapin,Pull_Push scltype,Pull_Push sdatype);


} ShaDevice;
ListStruct_uint8 shalist;
I2CDevice* sha_i2component;
IODevice* sha_iocomponent;
DelayObject* sha_delaycomponent;
CRCDevice* sha_crccomp;
ListCollection* sha_listcomp;
ModelDevice* sha_modelcomp;

extern void CreateShaHandshakeModule(ShaDevice* shamodule, I2CDevice* i2ccomponent,
                                     DelayObject* delaycomponent,
                                     IODevice*  iocomponent,
                                     CRCDevice* crccomp,
                                     ListCollection* listcomp,ModelDevice* modelcomp);
#endif // __I_GetShaID_h__
