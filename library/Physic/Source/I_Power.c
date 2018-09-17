

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "library\Physic\Header\I_Power.h"
static uint8_t _step_power;
static bool _f_sleep;


static void _Power_Sleep(PowerBaseAddress port)
 {

      *((uint32_t*)0x40000500)=1UL;

    //((Powerstruc*)port)->SYSTEMOFF)=1UL;

 }
static void _Power_IntConfigure(PowerBaseAddress port, PowerMISenum interrupt,
                        bool enable,uint32_t priority,bool controllerenable)
  {
      Power_intcontroller->Configure(POWER_CLOCK_IRQn,controllerenable,
                                        priority);



     if (enable)
     {
       ((Powerstruc*)port)->INTENSET|=interrupt;

     }
     else
     {

     ((Powerstruc*)(port))->INTENCLR=interrupt;

     }




  }
static void _Power_IntClear(PowerBaseAddress port, PowerMISenum interrupt)
  {
     if (interrupt==POFWARN)
     {
      ((Powerstruc*)(port))->EVENTS_POFWARN=0UL;

     }
     if (interrupt==SLEEPENTER)
     {
      ((Powerstruc*)(port))->EVENTS_SLEEPENTER=0UL;

     }
     if (interrupt==SLEEPEXIT)
     {
      ((Powerstruc*)(port))->EVENTS_SLEEPEXIT=0UL;

     }

  }

static uint32_t _Power_IntStatus(PowerBaseAddress port,PowerMISenum interrupt)
 {
     if (interrupt==POFWARN)
     {
       return( ((Powerstruc*)(port))->EVENTS_POFWARN);

     }
     if (interrupt==SLEEPENTER)
     {
   return( ((Powerstruc*)(port))->EVENTS_SLEEPENTER);

     }
     if (interrupt==SLEEPEXIT)
     {

      return(((Powerstruc*)(port))->EVENTS_SLEEPEXIT);

     }
 }




static void Power_handler(void)
  {
         if (_Power_IntStatus(POWER,POFWARN))
      {


         // SEGGER_RTT_printf(0,"Times %d\r\n",2300);
           _Power_IntClear(POWER,POFWARN);
      }
          if (_Power_IntStatus(POWER,SLEEPENTER))
      {
             _f_sleep=true;

        //  SEGGER_RTT_printf(0,"Times %d\r\n",2300);
           _Power_IntClear(POWER,SLEEPENTER);
      }
          if (_Power_IntStatus(POWER,SLEEPEXIT))
      {


        //  SEGGER_RTT_printf(0,"Times %d\r\n",2300);
           _Power_IntClear(POWER,SLEEPEXIT);
      }


  }
// immediately after Power sleeping, all resource are closed,
// there are no interrupt service routine for entering sleep although manual do
// claim that is available.
 static bool _Sleep(bool reset,PowerBaseAddress port)
  {
      if (reset==true)
      { SEGGER_RTT_printf(0,"power %d\r\n",40);
        _step_power=0;
       return (false);
      }

    switch (_step_power)
     {
       case 0:

            SEGGER_RTT_printf(0,"power %d\r\n",0);
          _Power_Sleep(port);
          _step_power=10;
          return (false);


       case 10:
SEGGER_RTT_printf(0,"power %d\r\n",11);
          if (_f_sleep==true)
          {
              SEGGER_RTT_printf(0,"power %d\r\n",10);
             _f_sleep=false;

             _step_power=20;
             return(true);

          }

          return (false);
       case 20:
           return (false);
     }

  }

  void _get_deviceid(uint32_t* lsbbits,uint32_t* msbbits)
  {
     volatile uint32_t _templsbbits,_tempmsbbits;
     _templsbbits=*((uint32_t*)0x10000060);
     _tempmsbbits=*((uint32_t*)0x10000064);

     *lsbbits=_templsbbits;
     *msbbits=_tempmsbbits;

  }

void CreatePowerDevice(PowerDevice* device, InterruptController* intcontroller)
{
  device->Sleep=_Sleep;

  device->IntConfigure=_Power_IntConfigure;

  device->Get_DeviceID=_get_deviceid;
  Power_intcontroller=intcontroller;
  Power_intcontroller->IntHandler(POWER_CLOCK_IRQn,Power_handler);

}
