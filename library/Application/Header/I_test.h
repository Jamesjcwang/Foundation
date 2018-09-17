

#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_IO.h"

#include "library\Component\Header\I_Model.h"
#include "library\Component\Header\I_CRC.h"
#include "library\Physic\Header\I_Power.h"
#include "library\Physic\Header\I_ADC.h"
#ifndef __I_test_h__
#define __I_test_h__
typedef struct
{
 uint32_t step;

 uint32_t modelinindex,modeloutindex;
 uint32_t crcparainindex,crcparaoutindex;
 uint32_t tempvalue,tempcount,templength,tempcmd,tempindex;
 uint8_t  receivedata[50];
 uint8_t _i,_p;
 uint32_t _tempdeviceid1,_tempdeviceid2;


}testParameter;

typedef struct {

 void(* test_Routine)(bool reset,testParameter* parameter);


} testDevice;

 CRCDevice* test_crccomp;
 PowerDevice* test_powercomp;
 IODevice* test_iocomp;
 ADCDevice* test_adccomp;
 InterruptController* test_intcomp;
 ModelDevice* test_modelcomp;
extern void CreatetesteModule(testDevice* testcomp,
                              InterruptController* intcomp,
                              PowerDevice* powercomp,CRCDevice* crccomp,
                              IODevice* iocomp,ADCDevice* adccomp,
                              ModelDevice* modelcomp);


#endif
