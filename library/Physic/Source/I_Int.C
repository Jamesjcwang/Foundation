#include "core_cm4.h"
#include "library\Physic\Header\I_Int.h"
static void(*uart_handler)(void);
static void(*spi0_handler)(void);
static void(*spi1_handler)(void);
static void(*spi2_handler)(void);
static void(*power_handler)(void);
static void(*adc_handler)(void);
static void(*timer0_handler)(void);
static void(*timer1_handler)(void);
static void(*timer2_handler)(void);
static void(*timer3_handler)(void);
static void(*timer4_handler)(void);
static void(*ioint_handler)(void);
void Int_Configure(IntCollection interrupt , bool enable,  uint32_t priority)
{


    NVIC_EnableIRQ(interrupt)  ;

    NVIC_ClearPendingIRQ(interrupt);

    NVIC_SetPriority(interrupt,priority);

}



 void Int_Pend(IntCollection interrupt ,bool enable)
{


   if (enable)
   {
       NVIC_SetPendingIRQ(interrupt);

   }
   else
   {
       NVIC_ClearPendingIRQ(interrupt);

   }

}

 void Int_Status(IntCollection interrupt ,bool* pendstatus, bool* activestatus)
{
   *pendstatus= (bool)NVIC_GetPendingIRQ(interrupt);
   *activestatus=(bool)NVIC_GetActive(interrupt);

}
 void Int_SoftTrigger(IntCollection interrupt )
 {



 }

 void Int_IntHandler(IntCollection interrupt, void(*handler)(void) )
 {
     switch (interrupt)
     {
     case UARTE0_UART0_IRQn:
          uart_handler=handler;
          break ;

     case SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn:
          spi0_handler=handler;
          break;

     case SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn:

          spi1_handler=handler;
          break;

     case SPIM2_SPIS2_SPI2_IRQn:
          spi2_handler=handler;
          break;

     case POWER_CLOCK_IRQn :
        //  SEGGER_RTT_printf(0,"Times %d\r\n",662);
         power_handler=handler;
         break;

     case SAADC_IRQn:
         adc_handler=handler;
         break;
     case TIMER0_IRQn:
         timer0_handler=handler;
         break;
     case TIMER1_IRQn:
         timer1_handler=handler;
     break;
     case TIMER2_IRQn:
         timer2_handler=handler;
     break;
     case TIMER3_IRQn:
         timer3_handler=handler;
     break;
     case TIMER4_IRQn:
         timer4_handler=handler;
     break;

     case GPIOTE_IRQn:
         ioint_handler=handler;
     break;


     }

 }

void  GPIOTE_IRQHandler (void)
{

    ioint_handler();
}
 void UARTE0_UART0_IRQHandler(void)
 {

     uart_handler();

 }

 void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void)
{
    spi0_handler();
}

void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void)
{

    spi1_handler();
}

void SPIM2_SPIS2_SPI2_IRQHandler(void)
{

    spi2_handler();

}
void POWER_CLOCK_IRQHandler(void)
{

    power_handler();

}
void SAADC_IRQHandler(void)
{
    adc_handler();
}

void TIMER0_IRQHandler(void)
{
    timer0_handler();
}
void TIMER1_IRQHandler(void)
{
    timer1_handler();
}
void TIMER2_IRQHandler(void)
{
    timer2_handler();
}
void TIMER3_IRQHandler(void)
{
    timer3_handler();
}
void TIMER4_IRQHandler(void)
{
    timer4_handler();
}
 void CreateIntDevice(InterruptController* intcontroller)
 {
      intcontroller->Configure=Int_Configure;
      intcontroller->IntHandler=Int_IntHandler;
      intcontroller->Pend=Int_Pend;
      intcontroller->SoftTrigger=Int_SoftTrigger;
      intcontroller->Status=Int_Status;
 }
