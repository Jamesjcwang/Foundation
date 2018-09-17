#ifndef __I_ProtectionIC_h__
#define __I_ProtectionIC_h__


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
 PinAndPinset sclpin,sdapin,enablepin;
 Pull_Push scltype,sdatype;
 uint32_t slaveaddress;
 uint32_t step;

 enum_CmdID tempcmd;
 uint8_t templength,tempvalue,tempcountin,tempcountout;
 volatile uint8_t  _receivedata[50];

 enum_CmdID cmdft;


} ProtectionICParameter;

typedef struct {

 void(* Routine)(bool reset,uint32_t proparaindex,
                         uint32_t crcparainindex,uint32_t crcparaoutindex,
                         uint32_t delayparaindex,uint32_t modelinindex,
                         uint32_t modeloutindex);
 uint32_t (*ParameterInitial)(enum_CmdID cmdft,
                              I2CBaseAddress i2cport,IOBaseAddress ioport,
                              uint32_t slaveaddress,PinAndPinset sclpin,
                              PinAndPinset sdapin,PinAndPinset enablepin,
                              Pull_Push scltype,Pull_Push sdatype);

} ProtectionICDevice;

ListStruct_uint8 prolist;
I2CDevice* pro_i2component;
IODevice* pro_iocomponent;
DelayObject* pro_delaycomponent;
CRCDevice* pro_crccomp;
ListCollection* pro_listcomp;
ModelDevice* pro_modelcomp;

extern void CreatePreotectionHandshakeModule(ProtectionICDevice* promodule, I2CDevice* i2ccomponent,
                                             DelayObject* delaycomponent,
                                             IODevice*  iocomponent,
                                             CRCDevice* crccomp,
                                             ListCollection* listcomp,
                                             ModelDevice* modelcomp);


#endif

