#include <stdbool.h>
#include <stdint.h>
#include "library\Communication\Header\I_Flash.h"


static void _Exflash_Startup(ExternalFlashParameter* parameters)
 {

     flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->sckpin,0);

    flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->mosipin,0);

     flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,parameters->sspin);

  flash_spicomponent->SPIM_IntConfigure(parameters->spiport,
                                              SPI_Ready,true,0,true);


}

 void _Exflash_Routine(bool reset,uint32_t paraindex,
                       uint32_t crcparaoutindex, uint32_t delayparaindex,
                       uint32_t modelinindex,uint32_t modeloutindex)
 {
     uint8_t templength;
     uint8_t tempresult[2];
     ExternalFlashParameter* parameters;

     parameters=(ExternalFlashParameter*)flash_listcomp->
                           GetAt(&flashlist,paraindex);

    if (reset)
     {
        _Exflash_Startup(parameters);

        parameters->step=0;

        parameters->tempvalue=0;

      }


   switch ( parameters->step)
    {
    case 0:

    if (flash_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
        &parameters->tempvalue,0,false)!=notvalid_model&&parameters->tempcmd==parameters->cmdft)
      {

          SEGGER_RTT_printf(0,"Fla%d\r\n", 0);
            parameters->step=5;
      }

        break;

    case 5:

            flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,0);
            SEGGER_RTT_printf(0,"Fla%d\r\n", 5);


            flash_delaycomponent->Delay_Routine(true,1,7,delayparaindex);


            parameters->step=10;


         break;

    case 10:

      if (flash_delaycomponent->Delay_Routine(false,1,7,delayparaindex)==true)
       {

SEGGER_RTT_printf(0,"Fla%d\r\n", 10);
          parameters->step=20;
          parameters->tempcount=0;
       }
        break;

    case 20:
           flash_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,parameters->tempcount++,false);
        if (parameters->tempcount==parameters->templength-3)
        {


          flash_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);
          parameters->tempcount=3;
         SEGGER_RTT_printf(0,"Fla%d\r\n", 21);
         parameters->step=100;

        }
     else
        {
           SEGGER_RTT_printf(0,"Fla%d\r\n", 20);
         flash_spicomponent->SPIM_Transmit(true,parameters->spiport,
                                                 &(parameters->tempvalue));

         flash_delaycomponent->Delay_Routine(true,1,1,delayparaindex);
         parameters->step=60;


        }

     break;

    case 60:
      if (flash_spicomponent->SPIM_Transmit(false,parameters->spiport,
                                              &(parameters->tempvalue))==true)
       {

SEGGER_RTT_printf(0,"Fla%d\r\n", 60);
        // parameters->spicomponent->SPIM_Receive(parameters->spiport,
        //                                      &(parameters->_p));
        parameters->step=20;
       // parameters->_f1=0;

       }
       else if (flash_delaycomponent->Delay_Routine(false,1,1,delayparaindex)==true)
       {

          flash_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);
            parameters->step=1000;
       }
        break;

    case 100:
     if (parameters->tempcount>0)
        {

         SEGGER_RTT_printf(0,"Fla%d\r\n", 100);
         parameters->tempvalue=0;
         flash_spicomponent->SPIM_Transmit(true,parameters->spiport,
                                                   &(parameters->tempvalue));
         flash_delaycomponent->Delay_Routine(true,1,1,delayparaindex);
         parameters->step=110;

        }
     else
        {

         SEGGER_RTT_printf(0,"Fla%d\r\n", 101);
         parameters->step=190;

        }

      break;
    case 110:

        if ( flash_spicomponent->SPIM_Transmit(false,parameters->spiport,
                                              &(parameters->tempvalue))==true)
       {

SEGGER_RTT_printf(0,"Fla%d\r\n", 110);
         *(parameters->receivedata+(3-parameters->tempcount--))=
                            parameters->tempvalue;
SEGGER_RTT_printf(0,"Fla%d\r\n",  parameters->tempvalue);
        parameters->step=100;
        //parameters->_f1=0;

       }
       else if (flash_delaycomponent->Delay_Routine(true,1,1,delayparaindex)==true)
       {

SEGGER_RTT_printf(0,"Fla%d\r\n", 111);

            parameters->step=1000;

        }
        break;

    case 190:



        flash_crccomp->crc(crcparaoutindex,3,parameters->receivedata,
                           tempresult,&templength);

        *(parameters->receivedata+3)=*tempresult;
        *(parameters->receivedata+4)=*(tempresult+1);

        parameters->step=200;
         break;

    case 200:
    if (flash_modelcomp->Set(modeloutindex,
                             parameters->tempcmd,parameters->receivedata,
                             5)==successful_model)
       {

SEGGER_RTT_printf(0,"Fla%d\r\n", 200);


          flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,
                                 parameters->sspin);
          parameters->step=0;


      }

       break;

   case 1000:
     parameters->receivedata[0]=0xff;
     flash_crccomp->crc(crcparaoutindex,1,parameters->receivedata,
                        tempresult,&templength);
     *(parameters->receivedata+1)=*(tempresult);
     *(parameters->receivedata+2)=*(tempresult+1);

   case 1100:



        if (flash_modelcomp->Set(modeloutindex,
                                 parameters->tempcmd,parameters->receivedata,
                                 3)==successful_model)
     {
          flash_iocomponent->IO_PinWrite(parameters->ioport,parameters->sspin,
                                 parameters->sspin);
          SEGGER_RTT_printf(0,"Fla%d\r\n", 1000);
          parameters->step=0;
      }
      break;

 }
 }

uint32_t _Flash_ParameterInitial(enum_CmdID cmdft,
                              SPIBaseAddress spiport,IOBaseAddress ioport,
                              PinAndPinset sckpin,PinAndPinset mosipin,
                              PinAndPinset misopin,PinAndPinset sspin)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(ExternalFlashParameter));
    ((ExternalFlashParameter*)(tempdata.value))->cmdft=cmdft;
    ((ExternalFlashParameter*)(tempdata.value))->ioport=ioport;
    ((ExternalFlashParameter*)(tempdata.value))->spiport=spiport;
    ((ExternalFlashParameter*)(tempdata.value))->sckpin=sckpin;
    ((ExternalFlashParameter*)(tempdata.value))->misopin=misopin;
    ((ExternalFlashParameter*)(tempdata.value))->mosipin=mosipin;
    ((ExternalFlashParameter*)(tempdata.value))->sspin=sspin;
    return(flash_listcomp->Insert(&flashlist,&tempdata));



}


 void CreateExFlashHandshakeModule(ExternalFlashDevice* module,
                                   SPIMDevice* spicomponent,
                                   DelayObject* delaycomponent,
                                   IODevice*  iocomponent,
                                   CRCDevice* crccomp,
                                   ListCollection* listcomp,ModelDevice* modelcomp)
 {

    module->ExFlash_Routine=_Exflash_Routine;
    module->ParameterInitial=_Flash_ParameterInitial;
    flash_crccomp=crccomp;
    flash_delaycomponent=delaycomponent;
    flash_iocomponent=iocomponent;
    flash_spicomponent=spicomponent;
    flash_listcomp=listcomp;
    flash_modelcomp=modelcomp;


 }
