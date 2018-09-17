#include <stdbool.h>
#include <stdint.h>
#include "library\Communication\Header\I_UARTTXRX.h"


void _UARTTXRX_ReceiveRoutine(bool reset, UARTTXRXParameter* parameters )
{
    resultofaccess tempstatus;
    uint8_t tempresult[2];
    uint8_t templength;

    if (reset==true)
    {
        parameters->step_receive=0;
        parameters->flagreceived=0;
    }


     switch (parameters->step_receive)
     {
      case 0:
        if (parameters->flagreceived==1)
         {

        //   SEGGER_RTT_printf(0,"rx %d\r\n",21);
          if (uart_crccomp->crc(parameters->crcparainindex,
                             *(parameters->receivedata+2)-2,
                             (parameters->receivedata+3),tempresult,
                             &templength)==true)
          {
    parameters->step_receive=3;
          }

          else
          {

              *(parameters->receivedata+3)=0xff;
             uart_crccomp->crc(parameters->crcparainindex,
                              1,
                             (parameters->receivedata+3),tempresult,
                             &templength);

              *(parameters->receivedata+4)=*tempresult;
              *(parameters->receivedata+5)=*(tempresult+1);
              parameters->step_receive=5;
          //    SEGGER_RTT_printf(0,"rx %d\r\n",2);
          }

         // SEGGER_RTT_printf(0,"rx %d\r\n",00);
       }

       break;

      case 3:
              //    SEGGER_RTT_printf(0,"rx %d\r\n",20);
            tempstatus=uart_modelcomp->Set(parameters->modelinindex,
                                      *(parameters->receivedata+1),
                                     (parameters->receivedata+3),
                                     *(parameters->receivedata+2));
SEGGER_RTT_printf(0,"rx %d\r\n",22);
             if(tempstatus==successful_model)
             {
         //         SEGGER_RTT_printf(0,"rx %d\r\n",22);
               parameters->flagreceived=0;
               parameters->step_receive=0;

             }
          break;
     case 5:

       if(tempstatus=uart_modelcomp->Set(parameters->modeloutindex,
                                         *(parameters->receivedata+1),
                                        (parameters->receivedata+3),3
                                        )==successful_model)
        {
           parameters->flagreceived=0;
           parameters->step_receive=0;
        }

         SEGGER_RTT_printf(0,"rx %d\r\n",05);
      break;

    }
}
  void app_UART_IntHandler ( UARTBaseAddress port )
{
    UARTTXRXParameter* parameters;

      if (port==UART0_BASE)
       {


        parameters=(UARTTXRXParameter*)uart_listcomp->GetAt(&uartlist,uartparalist[0]);

        uart_uartcomp->UART_Receive(parameters->uartport,
                                    false,&(parameters->tempvalue));

       if (parameters->flagreceived==0&&
           (parameters->tempvalue==parameters->startchar||
            parameters->refresh==1))
       {

       if ( parameters->tempvalue==parameters->startchar)
          {
             SEGGER_RTT_printf(0,"TXRX%d\r\n", 1);
               SEGGER_RTT_printf(0,"length%d\r\n", parameters->tempvalue);

             //parameters->flagreceived=0;
             parameters->tempindex=0;
             parameters->refresh=1;
            *( parameters->receivedata+ parameters->tempindex++)=
                                        parameters->tempvalue;

          }

        else if ( parameters->tempindex==2)
          {
            SEGGER_RTT_printf(0,"TXRX%d\r\n", 2);
            SEGGER_RTT_printf(0,"length%d\r\n", parameters->tempvalue);
            parameters->lengthofdata= parameters->tempvalue;
            *( parameters->receivedata+ parameters->tempindex)=
                                     parameters->tempvalue;
             parameters->tempindex++;

          }
        else if ( parameters->tempindex== parameters->lengthofdata+2)
          {
           SEGGER_RTT_printf(0,"TXRX%d\r\n", 3);
           SEGGER_RTT_printf(0,"value%d\r\n", parameters->tempvalue);
           *( parameters->receivedata+ parameters->tempindex)=
                                    parameters->tempvalue;
           parameters->tempindex++;

            parameters->flagreceived=1;
            parameters->refresh==0;

          }

        else
          {

           SEGGER_RTT_printf(0,"TXRX%d\r\n", 4);
           SEGGER_RTT_printf(0,"value%d\r\n", parameters->tempvalue);
           if ( parameters->tempindex==50)
           {
               parameters->tempindex=49;
           }
              *( parameters->receivedata+ parameters->tempindex)=
                                  parameters->tempvalue;
               parameters->tempindex++;


          }

       }
     }
}


static void _uart_startup(UARTTXRXParameter* parameter)
{   uint32_t i;


    uart_iocomp->IO_PinWrite(parameter->ioport,
                                       parameter->txpin,
                                       parameter->txpin);


    uart_uartcomp->UART_ReceiveIntHandler(app_UART_IntHandler);


}


static void _UARTTXRX_SendRoutine(bool reset,uint32_t paraindex)
 {
    UARTTXRXParameter* parameters;
    parameters=(UARTTXRXParameter*)uart_listcomp->GetAt(&uartlist,paraindex);

    _UARTTXRX_ReceiveRoutine(reset,parameters);

     if (reset)
     {

         parameters->step_send=0;
         _uart_startup(parameters);


     }

     switch (parameters->step_send)

     {

     case 0:

        if (uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                                &parameters->templength,&parameters->tempvalue,
                                0,false)!=notvalid_model)
        {

            parameters->tempcount=0;
            parameters->step_send=10;
            parameters->tempvalue=0XEF;
            uart_uartcomp->UART_Send(true,parameters->uartport,false,&parameters->tempvalue,1);
      SEGGER_RTT_printf(0,"sx %d\r\n",0);
        }


        break;

     case 10:

      if (uart_uartcomp->UART_Send(false,parameters->uartport,false,&parameters->tempvalue,1)==true)
      {SEGGER_RTT_printf(0,"sx %d\r\n",10);
          parameters->step_send=20;
      }
      break;

     case 20:


      if (uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                              &parameters->templength,&parameters->tempvalue,
                              0,false)==overflow_model)
       {SEGGER_RTT_printf(0,"sx %d\r\n",20);
           uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                               &parameters->templength,
                              &parameters->tempvalue,1,true);

           parameters->step_send=100;
       }
      else
       {
           uart_uartcomp->UART_Send(true,parameters->uartport,false,&parameters->tempcmd,1);
           parameters->step_send=30;

       }

       break;
      //error process is needed here

     case 30:

     if (uart_uartcomp->UART_Send(false,parameters->uartport,false,&parameters->tempvalue,1)==true)
      {SEGGER_RTT_printf(0,"sx %d\r\n",30);
          parameters->step_send=40;
      }
      break;

     case 40:

       if (uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                              &parameters->templength,&parameters->tempvalue,
                              0,false)==overflow_model)
       {SEGGER_RTT_printf(0,"sx %d\r\n",40);
             uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                               &parameters->templength,
                              &parameters->tempvalue,1,true);

           parameters->step_send=100;
       }
      else
       {

        uart_uartcomp->UART_Send(true,parameters->uartport,false,&parameters->templength,1);
           parameters->step_send=50;

       }

       break;

     case 50:

      if (uart_uartcomp->UART_Send(false,parameters->uartport,false,&parameters->templength,1)==true)
        {
             SEGGER_RTT_printf(0,"Times %d\r\n",50);
          parameters->tempindex=0;
          parameters->step_send=60;
        }
        break;


     case 60:

      if (uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                              &parameters->templength,&parameters->tempvalue,
                              parameters->tempindex++,false)==overflow_model)
        { SEGGER_RTT_printf(0,"sx %d\r\n",60);
             uart_modelcomp->Get(parameters->modeloutindex,&parameters->tempcmd,
                              &parameters->templength,
                             &parameters->tempvalue,1,true);

          parameters->step_send=0;
        }
      else
        {

 SEGGER_RTT_printf(0,"Times %d\r\n",60);
  SEGGER_RTT_printf(0,"Times %d\r\n",parameters->tempvalue);
          uart_uartcomp->UART_Send(true,parameters->uartport,false,&parameters->tempvalue,1);
          parameters->step_send=70;



        }
        break;
     case 70:
      if (uart_uartcomp->UART_Send(false,parameters->uartport,false,&parameters->tempvalue,1)==true)
        {
 SEGGER_RTT_printf(0,"Times %d\r\n",70);
          parameters->step_send=60;
        }
        break;





     }


 }
static uint32_t _uarttxrx_ParameterInitial(uint8_t startchar,
                              UARTBaseAddress uartport,IOBaseAddress ioport,
                              PinAndPinset txpin,PinAndPinset rxpin,
                              PinAndPinset cstpin,PinAndPinset rstpin,
                              uint32_t crcparainindex,uint32_t crcparaoutindex
                              ,uint32_t crcparaoutindex_transfer,uint32_t crcparaoutindex_transfer2,
                              uint32_t delayparaindex,
                              uint32_t modelinindex,uint32_t modeloutindex)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(UARTTXRXParameter));

    ((UARTTXRXParameter*)(tempdata.value))->startchar=startchar;
    ((UARTTXRXParameter*)(tempdata.value))->uartport=uartport;
    ((UARTTXRXParameter*)(tempdata.value))->ioport=ioport;
    ((UARTTXRXParameter*)(tempdata.value))->txpin=txpin;
    ((UARTTXRXParameter*)(tempdata.value))->rxpin=rxpin;
    ((UARTTXRXParameter*)(tempdata.value))->cstpin=cstpin;
    ((UARTTXRXParameter*)(tempdata.value))->rstpin=rstpin;
    ((UARTTXRXParameter*)(tempdata.value))->crcparainindex=crcparainindex;
    ((UARTTXRXParameter*)(tempdata.value))->crcparaoutindex=crcparaoutindex;
    ((UARTTXRXParameter*)(tempdata.value))->delayparaindex=delayparaindex;
    ((UARTTXRXParameter*)(tempdata.value))->modelinindex=modelinindex;
    ((UARTTXRXParameter*)(tempdata.value))->modeloutindex=modeloutindex;
    ((UARTTXRXParameter*)(tempdata.value))->crcparaoutindex_transfer=
                                            crcparaoutindex_transfer;
    ((UARTTXRXParameter*)(tempdata.value))->crcparaoutindex_transfer2=
                                            crcparaoutindex_transfer2;
    uartparalist[0]=uart_listcomp->Insert(&uartlist,&tempdata);


    return(uartparalist[0]);


}



void CreateUARTTXRXDevice(UARTTXRXDevice* component,
                          ModelDevice* modelcomp,CRCDevice* crccomp,
                          DelayObject* delaycomp,UARTDevice* uartcomp,
                          IODevice* iocomp,ListCollection* listcomp)
{
    component->UARTTXRX_Routine=_UARTTXRX_SendRoutine;
    component->ParameterInitial=_uarttxrx_ParameterInitial;
    uart_modelcomp=modelcomp;
    uart_crccomp=crccomp;
    uart_delaycomp=delaycomp;
    uart_uartcomp=uartcomp;
    uart_iocomp=iocomp;
    uart_listcomp=listcomp;
}
