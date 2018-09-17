

#include <stdbool.h>
#include <stdint.h>
#include "library\Communication\Header\I_GetShaID.h"

//static void _Getsha_handler(I2CMISenum event,I2CBaseAddress port)
// {
//
//     {
//         if (event==EVENTS_TXDSENT)
//         {
//     //  SEGGER_RTT_printf(0,"Times %d\r\n",55);
//           if (port==I2C0_BASE)
//             {
//              _GetShaIDparameterset0->_f1=1;
//             }
//           else
//             {
//              _GetShaIDparameterset1->_f1=1;
//             }
//
//
//         }
//         if (event==EVENTS_ERROR)
//         {
//             if (port==I2C0_BASE)
//             {
//              _GetShaIDparameterset0->_f6=1;
//             }
//             else
//             {
//             _GetShaIDparameterset1->_f6=1;
//             }
//
//
//         }
//            if (event==EVENTS_BB)
//         {
//
//              if (port==I2C0_BASE)
//             {
//             _GetShaIDparameterset0->_f5=1;
//             }
//             else
//             {
//              _GetShaIDparameterset1->_f5=1;
//             }
//      //       SEGGER_RTT_printf(0,"Times %d\r\n",53);
//         }
//             if (event==EVENTS_RXDREADY)
//         {
//
//       //      SEGGER_RTT_printf(0,"Times %d\r\n",51);
//             if (port==I2C0_BASE)
//             {
//              _GetShaIDparameterset0->_f4=1;
//             }
//             else
//             {
//              _GetShaIDparameterset1->_f4=1;
//             }
//
//         }
//
//               if (event==EVENTS_SUSPENDED)
//         {
//
//       //      SEGGER_RTT_printf(0,"Times %d\r\n",57);
//
//              if (port==I2C0_BASE)
//             {
//               _GetShaIDparameterset0->_f2=1;
//             }
//             else
//             {
//               _GetShaIDparameterset1->_f2=1;
//             }
//         }
//
//            if (event==EVENTS_STOPPED)
//         {
//
//
//             if (port==I2C0_BASE)
//             {
//              _GetShaIDparameterset0->_f3=1;
//             }
//             else
//             {
//               _GetShaIDparameterset1->_f3=1;
//             }
//         }
//
//
//    }
// }
//




void _sha_cleanbus(Shaparameter* paramters)
{  uint32_t i,j;
//SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1000);
 sha_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_26,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                       Sense_Disabled);

 sha_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_27,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                       Sense_Disabled);


 sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,GPIO_PIN_26);
 sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,GPIO_PIN_27);


 sha_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_26,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_OUT,GPIO_DIR_MODE_IN,
                       Sense_Disabled);
 sha_iocomponent->IO_Configure(GPIO_PORT0_BASE,GPIO_PIN_27,NRF_GPIO_PIN_S0D1,
                       NRF_GPIO_PIN_PULLUP,GPIO_DIR_MODE_OUT,GPIO_DIR_MODE_IN,
                       Sense_Disabled);

//SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 900);

  for(j=0;j<10;j++)
   {
  //  SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1300);
     sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,0);
   //      SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1400);
            for( i = 0; i < 1000; i++)
            {

            }
   // SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1500);

     sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_27,
                                         GPIO_PIN_27);
            for( i = 0; i < 1000; i++)
            {

            }
   //             SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1600);
     sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,0);
       for( i = 0; i < 1000; i++)
       {

       }
   //        SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 1700);
     sha_iocomponent->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_26,
                                         GPIO_PIN_26);
    }



}




static void _ShaID_Startup(Shaparameter* paramters)
{
    volatile uint32_t tempi;
  //  SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 700);
    _sha_cleanbus(paramters);
 // SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 800);
      sha_iocomponent->IO_Configure(paramters->ioport,paramters->sdapin
                                            ,NRF_GPIO_PIN_S0D1,paramters->sdatype,
                                            GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN,
                                            Sense_Disabled);
    sha_iocomponent->IO_Configure(paramters->ioport,paramters->sclpin,
                                            NRF_GPIO_PIN_S0D1,paramters->scltype,
                                            GPIO_DIR_MODE_IN,GPIO_DIR_MODE_IN
                                            ,Sense_Disabled);

    sha_i2component->I2C_Configure(paramters->i2cport,I2C_FREQUENCY_K100,
                                   GPIO_PIN_27,GPIO_PIN_26);
    sha_i2component->I2C_IntConfigure(paramters->i2cport,EVENTS_BB|EVENTS_ERROR|
                                  EVENTS_RXDREADY|EVENTS_TXDSENT|EVENTS_STOPPED,true,0,true);


    //for (tempi=0;tempi<1000;tempi++)
   // {

    //}

   // paramters->i2component->I2C_IntHandler(paramters->i2cport,_Getsha_handler);
 //    paramters->_p=0x00;
 //   sha_i2component->I2C_Send(open,paramters->i2cport,(uint8_t)paramters->slaveaddress,
 //                             &(paramters->_p));
 //    paramters->i2component->I2C_StartTXRX(paramters->i2cport,
 //                                             (uint8_t)paramters->slaveaddress
  //                                             ,true,true);
 //   paramters->_p=0x00;
  //     paramters->i2component->I2C_Send(paramters->i2cport,&(paramters->_p));
 //  while ( sha_i2component->I2C_Send(null,paramters->i2cport,(uint8_t)paramters->slaveaddress,
 //                            &(paramters->_p))!=i2c_success)
 //   {
 //
//
//
//    }
//   paramters->i2component->I2C_StartTXRX(paramters->i2cport,
//                                              (uint8_t)paramters->slaveaddress
//                                               ,true,false);
//   while (paramters->_f3!=1)
//   {
//SEGGER_RTT_printf(0,"SHAreceive%d\r\n", 100);
//
//   }
//   paramters->_f3=0;
//   for (tempi=0;tempi<10000;tempi++)
//   {
//
//
//   }
//
//   paramters->i2component->I2C_StartTXRX(paramters->i2cport,
//                                              (uint8_t)paramters->slaveaddress
//                                               ,false,true);
//
//     while (paramters->_f4!=1)
//    {
//
//
//
//    }
//     paramters->_f4=0;
//      paramters->i2component->I2C_Receive(paramters->i2cport,&(paramters->_p));
//  SEGGER_RTT_printf(0,"SHAreceive%d\r\n", paramters->_p);
//
//     while (paramters->_f4!=1)
//    {
//
//
//    }
//      paramters->_f4=0;
//        paramters->i2component->I2C_Receive(paramters->i2cport,&(paramters->_p));
//
//
//      SEGGER_RTT_printf(0,"SHAreceive%d\r\n", paramters->_p);
//
//     while (paramters->_f4!=1)
//    {
//
//
//    }
//      paramters->_f4=0;
//        paramters->i2component->I2C_Receive(paramters->i2cport,&(paramters->_p));
//
//
//      SEGGER_RTT_printf(0,"SHAreceive%d\r\n", paramters->_p);
//
//     while (paramters->_f4!=1)
//    {
//
//
//
//    }
// paramters->_f2=0;
//
//  nrf_twi_shorts_set((NRF_TWI_Type*) paramters->i2cport,0x2UL);
//       paramters->i2component->I2C_Receive(paramters->i2cport,&(paramters->_p));
//       SEGGER_RTT_printf(0,"SHAreceive%d\r\n", paramters->_p);
//   while(paramters->_f3!=1)
//   {
//
//    //  nrf_twi_disable((NRF_TWI_Type*)  paramters->i2cport);
//   }
//      paramters->i2component->I2C_Receive(paramters->i2cport,&(paramters->_p));
//       SEGGER_RTT_printf(0,"SHAreceive%d\r\n", paramters->_p);
//      nrf_twi_shorts_clear((NRF_TWI_Type*) paramters->i2cport,0x2UL);
// paramters->_f3=0;
//
//
//
//
//
//
//
}

static void _SHAID_Routine(bool reset,uint32_t shaparaindex,
                         uint32_t crcparainindex,uint32_t crcparaoutindex,
                         uint32_t delayparaindex,
                         uint32_t modelinindex,uint32_t modeloutindex)
{

    resultofaccess _tempmodelresult;
    enum_i2cresult tempresult;
    volatile uint32_t i;
    uint32_t templength;
    uint8_t tempresult1[2];

    Shaparameter* parameters;
    i=sha_listcomp->GetAt(&shalist,shaparaindex);

   if (i)
    {
       parameters=(Shaparameter*)i;
    }
   else
    {
       return (false);
    }
   if (reset)
     {
 _ShaID_Startup(parameters);
        parameters->tempvalue=0;

        parameters->step=0;

     }

   switch ( parameters->step)
    {
    case 0:

        if (sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
            &parameters->tempvalue,0,false)!=notvalid_model&&parameters->tempcmd==parameters->cmdft)
        {
           parameters->step=10;
        }

        break;

    case 10:
           SEGGER_RTT_printf(0,"sha%d\r\n", 10);

           sha_i2component->I2C_Send(open,parameters->i2cport,0,0);

           sha_i2component->I2C_Send(close,parameters->i2cport,0,0);
           sha_delaycomponent->Delay_Routine(true,1,7,delayparaindex);
           parameters->step=11;


         break;

    case 11:
         if (sha_i2component->I2C_Send(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,0)
            ==i2c_stop)
        {
            sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);
            parameters->step=20;
        }
        else if (sha_delaycomponent->Delay_Routine(false,1,7,delayparaindex)==true)
        {
            sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);

            parameters->step=1000;
  SEGGER_RTT_printf(0,"sha%d\r\n", 111);
        }
         break;


    case 20:

       if (sha_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
        {

        parameters->tempvalue=0x00;

        sha_i2component->I2C_Send(open,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                  &(parameters->tempvalue));






        parameters->tempcount=0;
        parameters->step=30;
        }
        break;
    case 30:
           sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,parameters->tempcount++,false);
        if (parameters->tempcount==parameters->templength-1)
       {
parameters->tempcount=7;
         sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);

         parameters->step=100;


       }

       else
       {
                 SEGGER_RTT_printf(0,"data%d\r\n",parameters->tempvalue);
         sha_delaycomponent->Delay_Routine(true,1,1,delayparaindex);
         parameters->step=40;
       }

       break;
    case 40:
      tempresult=sha_i2component->I2C_Send(null,parameters->i2cport,
                            (uint8_t)parameters->slaveaddress,&(parameters->tempvalue));

      if(tempresult==i2c_success)
      {
          SEGGER_RTT_printf(0,"SHA%d\r\n", 40);


          parameters->step=30;

      }
      else if(tempresult==i2c_fail)
      {
         SEGGER_RTT_printf(0,"SHA%d\r\n", 44);
        sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);

        parameters->step=1000;
      // error
      }
     else if(sha_delaycomponent->Delay_Routine(false,1,1,delayparaindex)
                 ==true)
     {
       SEGGER_RTT_printf(0,"SHA%d\r\n", 45);
       sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                              &parameters->tempvalue,1,true);

       parameters->step=1000;


     }
        break;


    case 100:

       SEGGER_RTT_printf(0,"SHA%d\r\n", 80);

       sha_i2component->I2C_Send(close,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                               &(parameters->tempvalue));


       parameters->step=110;


        break;



    case 110:
      tempresult=sha_i2component->I2C_Send(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                     &(parameters->tempvalue));
      SEGGER_RTT_printf(0,"SHA%d\r\n", 112);
     if (tempresult==i2c_stop)
      {
        sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);

        SEGGER_RTT_printf(0,"SHA%d\r\n", 110);

        parameters->step=120;
      }
    else if (sha_delaycomponent->Delay_Routine(false,1,2,delayparaindex)==true)
      {
        sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);
       parameters->step=1000;
        SEGGER_RTT_printf(0,"SHA%d\r\n", 111);

      }

       break;

    case 120:
      // if (sha_delaycomponent->Delay_Routine(false,1,1,delayparaindex)==true)
      // {
       //  sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);
      // }
        parameters->step=130;

        break;

    case 130:

       if (sha_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
       {

           SEGGER_RTT_printf(0," SHA%d\r\n", 130);

          sha_i2component->I2C_Receive(open,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                       parameters->tempvalue);


          parameters->step=140;

       }
       break;

    case 140:
          if (parameters->tempcount==1)
             {
                 sha_i2component->I2C_Receive(close,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue));
                 parameters->step=160;
             }
          else
             {
                 parameters->step=150;
             }
            sha_delaycomponent-> Delay_Routine(true,1,2,delayparaindex);

        break;

    case 150:
        if (sha_i2component->I2C_Receive(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_success)
        {
           *(parameters->_receivedata+(7-parameters->tempcount--))=parameters->tempvalue;
            SEGGER_RTT_printf(0,"SHA%d\r\n", 150);
             SEGGER_RTT_printf(0,"receive%d\r\n", parameters->tempvalue);

            parameters->step=140;

        }
     else if (sha_delaycomponent->
           Delay_Routine(false,1,2,delayparaindex)==true)
      {
          sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);

         parameters->step=1000;
         SEGGER_RTT_printf(0,"SHA%d\r\n", 151);

      }
        break;

    case 160:
        if (sha_i2component->I2C_Receive(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_success)
        {


            *(parameters->_receivedata+(7-parameters->tempcount--))=parameters->tempvalue;

            SEGGER_RTT_printf(0,"SHA%d\r\n", 160);
            SEGGER_RTT_printf(0,"receive%d\r\n", parameters->tempvalue);
            sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);



             parameters->step=200;
        }
     else if (sha_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
     {
        SEGGER_RTT_printf(0,"SHA%d\r\n", 161);
          sha_modelcomp->Get(modelinindex,&parameters->tempcmd,&parameters->templength,
                               &parameters->tempvalue,1,true);

       parameters->step=1000;
     }
        break;


    case 200:
        sha_crccomp->crc(crcparaoutindex,7,parameters->_receivedata,
                           tempresult1,&templength);

        *(parameters->_receivedata+7)=*tempresult1;
        *(parameters->_receivedata+8)=*(tempresult1+1);

        parameters->step=210;
         break;


    case 210:


     _tempmodelresult=sha_modelcomp->Set(modeloutindex,
                                         parameters->tempcmd,parameters->_receivedata,
                                         9);
     if (_tempmodelresult==successful_model)
     {
            SEGGER_RTT_printf(0,"SHA%d\r\n", 210);

           parameters->step=220;

     }
     else if (_tempmodelresult==failure_model)
     {

         parameters->step=1000;

     }

    break;

    case 220:

        if (sha_i2component->I2C_Receive(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_stop)
        {

           sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);
            SEGGER_RTT_printf(0,"SHA%d\r\n", 220);
            parameters->step=221;

        }
    //   else iSEGGER_RTT_printf(0,"SHA%d\r\n", 220);f (sha_delaycomponent->Delay_Routine(false,1,2,shaparaindex)==true)
     //   {
         //    SEGGER_RTT_printf(0,"SHA%d\r\n", 2201);
        //   parameters->model->output_cmd=parameters->model->input_cmd;
        //   parameters->model->outputlength= parameters->model->inputlength;
       //    parameters->model->flagreceive=false;
       //    parameters->step=1000;

     //   }
        break;

    case 221:

        if (sha_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
        {
           sha_i2component->I2C_Send(open,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue));
                                parameters->tempvalue=0x02;

           parameters->step=225;
              SEGGER_RTT_printf(0,"SHA%d\r\n", 221);
        }


        break;

    case 225:
         if (sha_i2component->I2C_Send(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_success)
         {
 parameters->tempvalue=0x00;
            sha_delaycomponent->Delay_Routine(true,1,7,delayparaindex);
sha_i2component->I2C_Send(close,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue));
            parameters->step=226;
             SEGGER_RTT_printf(0,"SHA%d\r\n", 225);
         }
         break;


    case 226:
        if (sha_delaycomponent->Delay_Routine(false,1,7,delayparaindex)==true)
        {

          parameters->step=228;
        }

        break;
    case 228:
        if (sha_i2component->I2C_Send(null,parameters->i2cport,(uint8_t)parameters->slaveaddress,
                                         &(parameters->tempvalue))==i2c_stop)
        {
            SEGGER_RTT_printf(0,"SHA%d\r\n", 226);
              parameters->step=230;
        }

       break;
    case 230:

SEGGER_RTT_printf(0,"SHA%d\r\n", 230);
       parameters->step=240;

      break;

    case 240:
      sha_delaycomponent->Delay_Routine(true,1,4,delayparaindex);
      parameters->step=250;
      SEGGER_RTT_printf(0,"SHA%d\r\n", 240);
       break;

    case 250:

        if (sha_delaycomponent->Delay_Routine(false,1,4,delayparaindex)==true)
        {
            SEGGER_RTT_printf(0,"SHA%d\r\n", 250);
            parameters->step=0;
        }
         break;
    case 1000:

        parameters->_receivedata[0]=0xff;
        sha_crccomp->crc(crcparaoutindex,1,parameters->_receivedata,
                           tempresult1,&templength);

        *(parameters->_receivedata+1)=*tempresult1;
        *(parameters->_receivedata+2)=*(tempresult1+1);

        parameters->step=200;
         break;



    case 1100:


        if (sha_modelcomp->Set(modeloutindex,
                               parameters->tempcmd,parameters->_receivedata,
                               3)==successful_model)
        {
              parameters->step=0;
              SEGGER_RTT_printf(0,"SHA%d\r\n", 1100);
        }



         break;

      }



 }
uint32_t _Sha_ParameterInitial(enum_CmdID cmdft,
                              I2CBaseAddress i2cport,IOBaseAddress ioport,
                              uint32_t slaveaddress,PinAndPinset sclpin,
                              PinAndPinset sdapin,Pull_Push scltype,Pull_Push sdatype)
{
     ListStruct_uint8 tempdata;

    tempdata.value=(uint32_t)malloc(sizeof(Shaparameter));

    ((Shaparameter*)(tempdata.value))->slaveaddress=slaveaddress;
    ((Shaparameter*)(tempdata.value))->cmdft=cmdft;
    ((Shaparameter*)(tempdata.value))->ioport=ioport;
    ((Shaparameter*)(tempdata.value))->i2cport=i2cport;
    ((Shaparameter*)(tempdata.value))->sclpin=sclpin;
    ((Shaparameter*)(tempdata.value))->sdapin=sdapin;
    ((Shaparameter*)(tempdata.value))->sdatype=sdatype;
    ((Shaparameter*)(tempdata.value))->scltype=scltype;

    return(sha_listcomp->Insert(&shalist,&tempdata));

}



 void CreateShaHandshakeModule(ShaDevice* shamodule, I2CDevice* i2ccomponent,
                               DelayObject* delaycomponent,
                               IODevice*  iocomponent,
                               CRCDevice* crccomp,
                               ListCollection* listcomp,ModelDevice* modelcomp)
 {

      shamodule->Routine=_SHAID_Routine;
      shamodule->ParameterInitial=_Sha_ParameterInitial;

      sha_crccomp=crccomp;
      sha_delaycomponent=delaycomponent;
      sha_iocomponent=iocomponent;
      sha_i2component=i2ccomponent;
      sha_listcomp=listcomp;
      sha_modelcomp=modelcomp;

 }
