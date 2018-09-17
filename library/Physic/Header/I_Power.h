#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_Int.h"
#include "library\nrf.h"
#ifndef __I_Power_h__
#define __I_Power_h__

typedef struct
{
     __I uint32_t RESERTVED0[120];
     __IO uint32_t TASKS_CONSTLAT;
     __I uint32_t RESERTVED1[3];
     __IO uint32_t TASKS_LOWPWR;
     __I uint32_t RESERTVED2[139];
     __IO uint32_t EVENTS_POFWARN;
     __I uint32_t RESERTVED3[11];
     __IO uint32_t EVENTS_SLEEPENTER;
     __I uint32_t RESERTVED4[3];
     __IO uint32_t EVENTS_SLEEPEXIT;
     __I uint32_t RESERTVED5[491];
     __IO uint32_t  INTENSET;
     __I uint32_t RESERTVED6[3];
     __IO uint32_t INTENCLR;
     __I uint32_t RESERTVED7[247];
     __IO uint32_t  RESETREAS;
     __I uint32_t RESERTVED8[39];
     __IO uint32_t RAMSTATUS;
     __I uint32_t RESERTVED9[215];
     __IO uint32_t SYSTEMOFF;
     __I uint32_t RESERTVED10[15];
     __IO uint32_t POFCON;
     __I uint32_t RESERTVED11[11];
     __IO uint32_t GPREGRET;
     __I uint32_t RESERTVED12[3];
     __IO uint32_t GPREGRET2;
     __I uint32_t RESERTVED13[3];
     __IO uint32_t RAMON;
     __I uint32_t RESERTVED14[47];
     __IO uint32_t RAMONB;
     __I uint32_t RESERTVED15[35];
     __IO uint32_t DCDCEN  ;
     __I uint32_t RESERTVED16[903];
     __IO uint32_t RAM0_POWER;

} Powerstruc;

typedef enum
{
     POWER=0x40000000

}PowerBaseAddress;

typedef enum
{
    POFWARN=4,
    SLEEPENTER=32,
    SLEEPEXIT=64


}PowerMISenum;

typedef struct {

 void (* Get_DeviceID)(uint32_t* lsbbits,uint32_t* msbbits);
void (*IntConfigure)(PowerBaseAddress port, PowerMISenum interrupt,
                        bool enable,uint32_t priority,bool controllerenable);
 bool (*Sleep)(bool reset,PowerBaseAddress port);

} PowerDevice;


InterruptController* Power_intcontroller;

extern void CreatePowerDevice(PowerDevice* device, InterruptController* intcontroller);
#endif
