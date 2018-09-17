#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_SPIM.h"
#include "library\Physic\Header\I_IO.h"
#include "library\Physic\Header\I_Timer.h"
#include "library\Component\Header\I_Delayobject.h"
#include "library\Component\Header\I_Model.h"
#include "library\Component\Header\I_CRC.h"

#ifndef __I_GetFlashID_h__
#define __I_GetFlashID_h__

typedef struct
{
    PinAndPinset sckpin;
    PinAndPinset mosipin;
    PinAndPinset misopin;
    PinAndPinset sspin;

    SPIBaseAddress spiport;
    IOBaseAddress ioport;
    uint32_t step;
    enum_CmdID tempcmd;
    uint8_t templength,tempvalue,tempcount;
    volatile  uint8_t receivedata[50];

    //DelayObjectParameter* delaycomponentparameter;

    enum_CmdID cmdft;


} ExternalFlashParameter;


typedef struct {

 void(* ExFlash_Routine)(bool reset,uint32_t flashparaindex,
                         uint32_t crcparaindex, uint32_t delayparaindex,
                         uint32_t modelinindex,uint32_t modeloutindex);
 uint32_t (*ParameterInitial)(enum_CmdID cmdft,
                              SPIBaseAddress spiport,IOBaseAddress ioport,
                              PinAndPinset sckpin,PinAndPinset mosipin,
                              PinAndPinset misopin,PinAndPinset sspin);

} ExternalFlashDevice;
ListStruct_uint8 flashlist;
SPIMDevice* flash_spicomponent;
DelayObject* flash_delaycomponent;
IODevice*  flash_iocomponent;
CRCDevice* flash_crccomp;
ListCollection* flash_listcomp;
ModelDevice* flash_modelcomp;


extern void CreateExFlashHandshakeModule(ExternalFlashDevice* exflashmodule,
                                         SPIMDevice* spicomponent,
                                         DelayObject* delaycomponent,
                                         IODevice*  iocomponent,
                                         CRCDevice* crccomp,
                                         ListCollection* Delay_listcomp,
                                         ModelDevice* modelcomp);


#endif

