
#include <stdbool.h>
#include <stdint.h>
#include "library\Communication\Header\I_PT.h"

static void CheckSum_8bit(uint8_t* data,uint32_t length,uint8_t* result)
{
 uint8_t _i,_data;
 _data=0;
 *result=0;
 for (_i=0;_i<length;_i++)
 {
   _data=_data+*(data+_i);

 }

 for(_i=0;_i<8;_i++)
 {
     if ((_data&(1<<_i))==1<<_i)
     {
         *result=*result|(1<<_i);
         _data=_data+(1<<(_i+1));

     }


 }


}


static void _PT_Startup(PTParameter* parameters)
 {

     pt_iocomponent->IO_PinWrite(parameters->ioport,parameters->sckpin,0);

     pt_iocomponent->IO_PinWrite(parameters->ioport,parameters->mosipin,0);

     pt_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,
                                 parameters->sspin);

     pt_spicomponent->SPIM_IntConfigure(parameters->spiport,
                                              SPI_Ready,true,0,true);
 }

 void _PT_Routine(bool reset,uint32_t ptparaindex,uint32_t crcparainindex,
                  uint32_t crcparaoutindex,uint32_t delayparaindex,
                  uint32_t modelinindex,uint32_t modeloutindex)
 {
     PTParameter* parameters;
     bool tempbool;
     uint8_t headerlength;
     uint8_t tempresultofchecksum;
     uint8_t templength;
     uint8_t tempresult[2];
     uint32_t tempi;
     parameters=(PTParameter*)pt_listcomp->
                           GetAt(&ptlist,ptparaindex);
    if (reset)
     {
        _PT_Startup(parameters);
        // headerlength=3;

        parameters->step=0;
        parameters->_count=0;
       // _PT_alarm_Routine(false,true,parameters,delayparaindex);

      }

   switch ( parameters->step)
    {
    case 0:

    if (pt_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
        &parameters->tempvalue,0,false)!=notvalid_model&&parameters->tempcmd==parameters->cmdft)
      {

          SEGGER_RTT_printf(0,"PT%d\r\n", 0);
          parameters->step=5;
      }

        break;

    case 5:

         pt_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_11,0);
         SEGGER_RTT_printf(0,"pt%d\r\n", 5);

         pt_delaycomponent->Delay_Routine(true,1,7,delayparaindex);


         parameters->step=10;


         break;

    case 10:

      if (pt_delaycomponent->Delay_Routine(false,1,7,delayparaindex)==true)
       {

          SEGGER_RTT_printf(0,"pt%d\r\n", 10);
          parameters->step=20;
          parameters->tempcount=0;
       }
        break;

    case 20:
       pt_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,parameters->tempcount++,false);

        if (parameters->tempcount==parameters->templength-1)
        {
         pt_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                             &parameters->tempvalue,1,true);
         parameters->tempcount=10;
         SEGGER_RTT_printf(0,"pt%d\r\n", 21);
         parameters->step=100;

        }
     else
        {
           SEGGER_RTT_printf(0,"pt%d\r\n", 20);
         pt_spicomponent->SPIM_Transmit(true,parameters->spiport,
                                                 &(parameters->tempvalue));

         pt_delaycomponent->Delay_Routine(true,1,4,delayparaindex);
         parameters->step=60;


        }

     break;

    case 60:
        SEGGER_RTT_printf(0,"pt%d\r\n", 22);
      if (pt_spicomponent->SPIM_Transmit(false,parameters->spiport,
                                              &(parameters->tempvalue))==true)
       {

SEGGER_RTT_printf(0,"pt%d\r\n", 60);
        // parameters->spicomponent->SPIM_Receive(parameters->spiport,
        //                                      &(parameters->_p));
        parameters->step=20;
       // parameters->_f1=0;

       }


       else if (pt_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
       {

         pt_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);
            parameters->step=1000;
      }
        break;

    case 100:
     if (parameters->tempcount>0)
        {

         SEGGER_RTT_printf(0,"pt%d\r\n", 100);
         parameters->tempvalue=0;
         pt_spicomponent->SPIM_Transmit(true,parameters->spiport,
                                                   &(parameters->tempvalue));
         pt_delaycomponent->Delay_Routine(true,1,7,delayparaindex);
         parameters->step=110;

        }
     else
        {

         SEGGER_RTT_printf(0,"pt%d\r\n", 101);
         parameters->step=190;

        }

      break;
    case 110:

        if ( pt_spicomponent->SPIM_Transmit(false,parameters->spiport,
                                              &(parameters->tempvalue))==true)
       {

SEGGER_RTT_printf(0,"pt%d\r\n", 110);
         *(parameters->receivedata+(10-parameters->tempcount--))=
                            parameters->tempvalue;
SEGGER_RTT_printf(0,"pt%d\r\n",  parameters->tempvalue);
        parameters->step=100;
        //parameters->_f1=0;

       }
       else if (pt_delaycomponent->Delay_Routine(true,1,7,delayparaindex)==true)
       {

SEGGER_RTT_printf(0,"pt%d\r\n", 111);

            parameters->step=1000;

        }
        break;

    case 190:
SEGGER_RTT_printf(0,"ptretry%d\r\n", parameters->retrycount);

       CheckSum_8bit(parameters->receivedata,9,&tempresultofchecksum);

       if (*(parameters->receivedata+9)==tempresultofchecksum&&
           *(parameters->receivedata)!=0)
       {   parameters->_count=0;
           parameters->step=195;
       }
       else if (parameters->_count==parameters->retrycount)
       {   parameters->_count=0;
           parameters->step=1010;

       }
       else
       {
           parameters->_count++;

           pt_delaycomponent->Delay_Routine(true,1,3,delayparaindex);
           parameters->step=193;
           parameters->tempcount=10;
       }


      break;

    case 193:
       if (pt_delaycomponent->Delay_Routine(false,1,3,delayparaindex)==true)
        {
               parameters->step=100;
        }
        break;
    case 195:

        pt_crccomp->crc(crcparaoutindex,10,parameters->receivedata,
                           tempresult,&templength);

        *(parameters->receivedata+10)=*tempresult;
        *(parameters->receivedata+11)=*(tempresult+1);

        parameters->step=200;
        break;

    case 200:
    if (pt_modelcomp->Set(modeloutindex,
                             parameters->tempcmd,parameters->receivedata,
                             12)==successful_model)
     {

          SEGGER_RTT_printf(0,"pt%d\r\n", 200);


         pt_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,
                                parameters->sspin);
          parameters->step=0;


      }

       break;

    case 1000:
     parameters->receivedata[0]=0xff;
     pt_crccomp->crc(crcparaoutindex,1,parameters->receivedata,
                        tempresult,&templength);
     *(parameters->receivedata+1)=*(tempresult);
     *(parameters->receivedata+2)=*(tempresult+1);
      parameters->step=1100;
     break;
    case 1010:
     parameters->receivedata[0]=0xfE;
     pt_crccomp->crc(crcparaoutindex,1,parameters->receivedata,
                        tempresult,&templength);
     *(parameters->receivedata+1)=*(tempresult);
     *(parameters->receivedata+2)=*(tempresult+1);
 parameters->step=1100;
       break;

   case 1100:



    if (pt_modelcomp->Set(modeloutindex,
                                 parameters->tempcmd,parameters->receivedata,
                                 3)==successful_model)
     {    pt_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,
                                 parameters->sspin);
          SEGGER_RTT_printf(0,"pt%d\r\n", 1000);
          parameters->step=0;
      }
      break;


  }

  // parameters->_tempresult=
 // _PT_alarm_Routine(&(parameters->flag_alarm),false,parameters,delayparaindex);


 }

uint32_t _PT_ParameterInitial(SPIBaseAddress spiport,
                              IOBaseAddress ioport,enum_CmdID cmdft,
                              enum_CmdID cmdreset,
                              PinAndPinset sckpin,PinAndPinset mosipin,
                              PinAndPinset misopin,PinAndPinset sspin,
                              uint8_t retrycount)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(PTParameter));
    ((PTParameter*)(tempdata.value))->cmdft=cmdft;
    ((PTParameter*)(tempdata.value))->cmdreset=cmdreset;
    ((PTParameter*)(tempdata.value))->ioport=ioport;
    ((PTParameter*)(tempdata.value))->spiport=spiport;
    ((PTParameter*)(tempdata.value))->misopin=misopin;
    ((PTParameter*)(tempdata.value))->mosipin=mosipin;
    ((PTParameter*)(tempdata.value))->sckpin=sckpin;
    ((PTParameter*)(tempdata.value))->sspin=sspin;
    ((PTParameter*)(tempdata.value))->retrycount=retrycount;
    return(pt_listcomp->Insert(&ptlist,&tempdata));



}


 void CreatePTHandshakeModule(PTDevice* module,
                              IODevice* iocomponent,
                              DelayObject* delaycomponent,
                              SPIMDevice* spicomponent,
                              CRCDevice* crccomp,
                              ListCollection* listcomp,ModelDevice* modelcomp)
 {

    module->PT_Routine=_PT_Routine;
    module->ParameterInitial=_PT_ParameterInitial;
    pt_crccomp=crccomp;
    pt_delaycomponent=delaycomponent;
    pt_iocomponent=iocomponent;
    pt_listcomp=listcomp;
    pt_spicomponent=spicomponent;
    pt_modelcomp=modelcomp;

 }
