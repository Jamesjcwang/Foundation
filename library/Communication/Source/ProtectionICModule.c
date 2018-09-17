
#include <stdbool.h>
#include <stdint.h>
#include "library\Communication\Header\I_ProtectionICModule.h"


//static ProtectionICParameter* _protectionicparameterset0;
//static ProtectionICParameter* _protectionicparameterset1;

//static void _i2c_handler(I2CMISenum event,I2CBaseAddress i2cbaseaddress)
// {
//
//
//         if (event==EVENTS_TXDSENT)
//         {
//      // SEGGER_RTT_printf(0,"Times %d\r\n",55);
//           if (i2cbaseaddress==I2C0_BASE)
//             {
//              _protectionicparameterset0->_f1=1;
//             }
//           else
//             {
//              _protectionicparameterset1->_f1=1;
//             }
//
//
//         }
//         if (event==EVENTS_ERROR)
//         {
//          //   SEGGER_RTT_printf(0,"Times %d\r\n",54);
//             if (i2cbaseaddress==I2C0_BASE)
//             {
//              _protectionicparameterset0->_f6=1;
//             }
//             else
//             {
//              _protectionicparameterset1->_f6=1;
//             }
//
//
//         }
//            if (event==EVENTS_BB)
//         {
//
//              if (i2cbaseaddress==I2C0_BASE)
//             {
//              _protectionicparameterset0->_f5=1;
//             }
//             else
//             {
//              _protectionicparameterset1->_f5=1;
//             }
//           //  SEGGER_RTT_printf(0,"Times %d\r\n",53);
//         }
//             if (event==EVENTS_RXDREADY)
//         {
//
//            // SEGGER_RTT_printf(0,"Times %d\r\n",51);
//             if (i2cbaseaddress==I2C0_BASE)
//             {
//              _protectionicparameterset0->_f4=1;
//             }
//             else
//             {
//              _protectionicparameterset1->_f4=1;
//             }
//
//         }
//
//               if (event==EVENTS_SUSPENDED)
//         {
//
//            // SEGGER_RTT_printf(0,"Times %d\r\n",57);
//
//              if (i2cbaseaddress==I2C0_BASE)
//             {
//               _protectionicparameterset0->_f2=1;
//             }
//             else
//             {
//               _protectionicparameterset1->_f2=1;
//             }
//         }
//
//            if (event==EVENTS_STOPPED)
//         {
//
//          //   SEGGER_RTT_printf(0,"Times %d\r\n",59);
//
//             if (i2cbaseaddress==I2C0_BASE)
//             {
//               _protectionicparameterset0->_f3=1;
//             }
//             else
//             {
//               _protectionicparameterset1->_f3=1;
//             }
//         }
//
//
//
// }
//




void _protection_cleanbus(ProtectionICParameter* paramters)
{
  uint32_t i,j;
//SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1000);
 pro_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_26,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                       Sense_Disabled);

 pro_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_27,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                       Sense_Disabled);


 pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,GPIO_PIN_26);
 pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,GPIO_PIN_27);


 pro_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_26,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_OUT,GPIO_DIR_MODE_IN,
                       Sense_Disabled);
 pro_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_27,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_OUT,GPIO_DIR_MODE_IN,
                       Sense_Disabled);

//SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 900);

  for(j=0;j<10;j++)
   {
  //  SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1300);
     pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,0);
   //      SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1400);
            for( i = 0; i < 1000; i++)
            {

            }
   // SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1500);

     pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,
                                         GPIO_PIN_27);
            for( i = 0; i < 1000; i++)
            {

            }
   //             SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1600);
     pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,0);
       for( i = 0; i < 1000; i++)
       {

       }
   //        SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1700);
     pro_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,
                                         GPIO_PIN_26);
    }



}
static void _ProtectionIC_Startup(ProtectionICParameter* paramters)
{
    volatile uint32_t tempi;
   _protection_cleanbus(paramters);
  //SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 800);
    pro_iocomponent->IO_Configure(paramters->ioport,paramters->sdapin
                                            ,NRF_GPIO_PIN_S0D1,paramters->sdatype,
                                            GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                                            Sense_Disabled);
    pro_iocomponent->IO_Configure(paramters->ioport,paramters->sclpin,
                                            NRF_GPIO_PIN_S0D1,paramters->scltype,
                                            GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                                            Sense_Disabled);

    pro_i2component->I2C_Configure(paramters->i2cport,I2C_FREQUENCY_K100,
                                   GPIO_PIN_27,GPIO_PIN_26);
    pro_i2component->I2C_IntConfigure(paramters->i2cport,EVENTS_BB|EVENTS_ERROR|
                                  EVENTS_RXDREADY|EVENTS_TXDSENT|EVENTS_STOPPED,true,0,true);

    pro_iocomponent->IO_PinWrite(paramters->ioport,paramters->enablepin,
                                paramters->enablepin);
      for(tempi=0;tempi<6000000;tempi++)
      {

      }
      pro_iocomponent->IO_PinWrite(paramters->ioport,paramters->enablepin,
                                0);
}
void dataswap(uint8_t* data,uint32_t length)
{
    uint8_t tempdata,tempi;
    for (tempi=1;tempi<(length>>1);tempi++)
     {
        tempdata=*(data+tempi);
        *(data+tempi)=*(data+tempi+1);
        *(data+tempi+1)=tempdata;

     }

}



static void _ProtectionIC_Routine(bool reset,uint32_t proparaindex,
                         uint32_t crcparainindex,uint32_t crcparaoutindex,
                         uint32_t delayparaindex,uint32_t modelinindex,
                         uint32_t modeloutindex)
 {
    resultofaccess _tempmodelresult;
    enum_i2cresult tempresult;

    uint8_t templength;
    uint8_t tempresult1[2];
    uint32_t temp;
    volatile uint32_t i;

    ProtectionICParameter* parameters;
    parameters=(ProtectionICParameter*)pro_listcomp->GetAt(&prolist,proparaindex);

    if (reset)
     {
        _ProtectionIC_Startup(parameters);

        parameters->step=0;

     }

   switch ( parameters->step)
    {

    case 0:
     if (pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
        &parameters->tempvalue,0,false)!=notvalid_model&&parameters->tempcmd==parameters->cmdft)

        {

               parameters->step=5;
        }

      break;


    case 5:

            pro_delaycomponent->Delay_Routine(true,1,7,delayparaindex);
            parameters->step=10;

            break;

    case 10:

     if (pro_delaycomponent->Delay_Routine(false,1,7,delayparaindex)==true)
       {
      //  SEGGER_RTT_printf(0,"Pro%d\r\n", 10);

        pro_i2component->I2C_Send(open,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                  &(parameters->tempvalue));
        parameters->tempcountin=0;
        parameters->step=20;
       }
     break;

    case 20:

     pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,parameters->tempcountin++,false);
         parameters->tempcountout=parameters->tempvalue;


          parameters->step=25;
          break;


    case 25 :
        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,parameters->tempcountin++,false);
       if (parameters->tempcountin==parameters->templength-1)
       {

        // SEGGER_RTT_printf(0,"Pro%d\r\n", 21);

         pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);
         parameters->templength=parameters->tempcountout;

         parameters->step=100;

       }
     else
       {

       //  SEGGER_RTT_printf(0,"Pro%d\r\n", 20);
         pro_delaycomponent->Delay_Routine(true,1,2,delayparaindex);
         parameters->step=30;


       }
         break;

     case 30:
       tempresult=pro_i2component->I2C_Send(null,parameters->i2cport,
                            (uint8_t)parameters->slaveaddress,&(parameters->tempvalue));
      if(tempresult==i2c_success)
       {
        //    SEGGER_RTT_printf(0,"se%d\r\n", parameters->tempvalue);

          parameters->step=25;

       }
      else if(tempresult==i2c_fail)
        {
//SEGGER_RTT_printf(0,"Pro%d\r\n", 31);
        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
        parameters->step=1000;
        }
       else if ( pro_delaycomponent->Delay_Routine(true,1,2,delayparaindex)==true)
        {
//SEGGER_RTT_printf(0,"Pro%d\r\n", 32);

        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
        parameters->step=1000;

        }

        break;


    case 100:


        //  SEGGER_RTT_printf(0,"pro%d\r\n", 100);


          pro_i2component->I2C_Receive(open,parameters->i2cport,
                                       (uint8_t)parameters->slaveaddress,parameters->tempvalue);
          parameters->step=120;


           break;

  case 120:
            if (parameters->tempcountout==0)
            {
                parameters->step=160;
            }

            else if (parameters->tempcountout==1)

             {
           //   SEGGER_RTT_printf(0,"SHA%d\r\n", 120);

            //      SEGGER_RTT_printf(0,"SHA%d\r\n", 121);
              pro_i2component->I2C_Receive(close,parameters->i2cport,parameters->slaveaddress,
                                         &(parameters->tempvalue));
                parameters->step=160;
             }
             else
             {
                parameters->step=150;
             }
             pro_delaycomponent->Delay_Routine(true,1,1,delayparaindex);



         break;

    case 150:
        if (pro_i2component->I2C_Receive(null,parameters->i2cport,parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_success)
        {
        //   SEGGER_RTT_printf(0,"re%d\r\n", parameters->tempvalue);
          *(parameters->_receivedata+(parameters->templength-parameters->tempcountout--))
                                                                =parameters->tempvalue;


          parameters->step=120;

        }
        else if (pro_delaycomponent->Delay_Routine(false,1,2,delayparaindex)==true)
        {
        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
        parameters->step=1000;
        }
        break;

    case 160:
        if (pro_i2component->I2C_Receive(null,parameters->i2cport,parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_success)
        {
         //   SEGGER_RTT_printf(0,"re%d\r\n", parameters->tempvalue);
          *(parameters->_receivedata+(parameters->templength-parameters->tempcountout--))
                                                                 = parameters->tempvalue;

            pro_delaycomponent->Delay_Routine(true,1,2,delayparaindex);

            //dataswap(parameters->_receivedata,4);

            parameters->step=200;


        }
        else if (pro_delaycomponent->Delay_Routine(false,1,2,delayparaindex)==true)
        {
        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
        parameters->step=1000;
        }
        break;




     case 200:

        // dataswap(parameters->_receivedata,4);

         pro_crccomp->crc(crcparaoutindex,parameters->templength,parameters->_receivedata,tempresult1,
                      &templength);

         *(parameters->_receivedata+parameters->templength)=*tempresult1;
         *(parameters->_receivedata+parameters->templength+1)=*(tempresult1+1);
         parameters->step=210;

         break;
     case 210:

      _tempmodelresult=pro_modelcomp->Set(modeloutindex,parameters->tempcmd,
                                           parameters->_receivedata,parameters->templength+2);
     if (_tempmodelresult==successful_model)
     {
       //     SEGGER_RTT_printf(0,"pro%d\r\n", 210);

           parameters->step=220;

     }
     else if (_tempmodelresult==failure_model)
     {

         parameters->step=1000;

     }
        break;



    case 220:

        if (pro_i2component->I2C_Receive(null,parameters->i2cport,parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_stop)
        {
        //    SEGGER_RTT_printf(0,"SHA%d\r\n", 220);

            parameters->step=230;

        }
        else if (pro_delaycomponent->Delay_Routine(false,1,2,delayparaindex)==true)
        {
        pro_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
        parameters->step=1000;
        }
        break;
    case 230:

        parameters->step=240;

      break;

    case 240:
      pro_delaycomponent->Delay_Routine(true,1,1,delayparaindex);
      parameters->step=250;
       break;

    case 250:

        if (pro_delaycomponent->Delay_Routine(false,1,1,delayparaindex)==true)
        {
        //    SEGGER_RTT_printf(0,"SHA%d\r\n", 250);
            parameters->step=0;
        }
         break;
    case 1000:
      parameters->_receivedata[0]=0xff;
      pro_crccomp->crc(crcparaoutindex,1,parameters->_receivedata,
                        tempresult1,&templength);
     *(parameters->_receivedata+1)=*(tempresult1);
     *(parameters->_receivedata+2)=*(tempresult1+1);

    case 1100:

       parameters->_receivedata[0]=0xff;

        if (pro_modelcomp->Set(modeloutindex,
                               parameters->tempcmd,parameters->_receivedata,
                               3)==successful_model)
        {
              parameters->step=0;
              SEGGER_RTT_printf(0,"SHA%d\r\n", 1100);
        }


         break;
      }





 }

uint32_t _Pro_ParameterInitial(enum_CmdID cmdft,
                              I2CBaseAddress i2cport,IOBaseAddress ioport,
                              uint32_t slaveaddress,PinAndPinset sclpin,
                              PinAndPinset sdapin,PinAndPinset enablepin,
                              Pull_Push scltype,Pull_Push sdatype)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(ProtectionICParameter));
    ((ProtectionICParameter*)(tempdata.value))->slaveaddress=slaveaddress;
    ((ProtectionICParameter*)(tempdata.value))->cmdft=cmdft;
    ((ProtectionICParameter*)(tempdata.value))->ioport=ioport;
    ((ProtectionICParameter*)(tempdata.value))->i2cport=i2cport;
    ((ProtectionICParameter*)(tempdata.value))->sclpin=sclpin;
    ((ProtectionICParameter*)(tempdata.value))->sdapin=sdapin;
    ((ProtectionICParameter*)(tempdata.value))->enablepin=enablepin;
    ((ProtectionICParameter*)(tempdata.value))->sdatype=sdatype;
    ((ProtectionICParameter*)(tempdata.value))->scltype=scltype;

    return(pro_listcomp->Insert(&prolist,&tempdata));



}





 void CreatePreotectionHandshakeModule(ProtectionICDevice* protectionicmodule,
                                       I2CDevice* i2ccomponent,
                               DelayObject* delaycomponent,
                               IODevice*  iocomponent,
                               CRCDevice* crccomp,
                               ListCollection* listcomp,ModelDevice* modelcomp)
 {

      protectionicmodule->Routine=_ProtectionIC_Routine;
          protectionicmodule->ParameterInitial=_Pro_ParameterInitial;

      pro_crccomp=crccomp;
      pro_delaycomponent=delaycomponent;
      pro_iocomponent=iocomponent;
      pro_i2component=i2ccomponent;
      pro_listcomp=listcomp;
      pro_modelcomp=modelcomp;
 }
