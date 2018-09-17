
#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_SPIM.h"
#include "library\Physic\Header\I_IO.h"
#include "library\Physic\Header\I_Timer.h"
#include "library\Component\Header\I_Delayobject.h"
#include "library\Component\Header\I_Model.h"
#include "library\Component\Header\I_CRC.h"


#ifndef __I_PT_h__
#define __I_PT_h__

typedef struct
{
    SPIBaseAddress spiport;
    IOBaseAddress ioport;
    uint32_t step,step_alarm;
    volatile uint32_t _count,_count2;
    volatile  uint8_t receivedata[50];
    enum_CmdID tempcmd;
    uint8_t templength,tempvalue,tempcount;

    //ComDataStru* Alarmmodel;
    enum_CmdID cmdft;
    enum_CmdID cmdreset;
    uint8_t retrycount;
    bool flag_alarm;
    Enum_result _tempresult;
    PinAndPinset sckpin;
    PinAndPinset mosipin;
    PinAndPinset misopin;
    PinAndPinset sspin;
    bool flag_sendsuccessful;


} PTParameter;

typedef struct {

 void(* PT_Routine)(bool reset,uint32_t ptparaindex,uint32_t crcparainindex,
                    uint32_t crcparaoutindex, uint32_t delayparaindex,
                    uint32_t modelinindex,uint32_t modeloutindex);

 uint32_t (*ParameterInitial)(SPIBaseAddress spiport,
                               IOBaseAddress ioport,enum_CmdID cmdft,
                               enum_CmdID cmdreset,
                               PinAndPinset sckpin,PinAndPinset mosipin,
                               PinAndPinset misopin,PinAndPinset sspin,
                               uint8_t retrycount);
} PTDevice;
ListStruct_uint8 ptlist;
ListCollection* pt_listcomp;
IODevice*  pt_iocomponent;
DelayObject* pt_delaycomponent;
SPIMDevice* pt_spicomponent;
CRCDevice* pt_crccomp;
ModelDevice* pt_modelcomp;
extern void CreatePTHandshakeModule(PTDevice* ptmodule,
                                    IODevice* iocomponent,
                                    DelayObject* delaycomponent,
                                    SPIMDevice* spicomponent,
                                    CRCDevice* crccomp,
                                    ListCollection* listcomp,
                                    ModelDevice* modelcomp);


#endif

