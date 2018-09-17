#include <stdbool.h>
#include <stdint.h>
#include "library\Application\Header\I_test.h"
volatile uint32_t _tempintflag,_tempdeviceid1,_tempdeviceid2,intflag,intflag2,intflag3;
 uint8_t _i,_p;
uint32_t _temp12 ;
void wheellock(uint32_t index,testParameter* parameter )
{
    if (index==1)
    {

     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_16,GPIO_PIN_16);
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_7,GPIO_PIN_7);
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_5,0);
    }
    else if (index==2)
    {
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_16,GPIO_PIN_16);
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_7,0);
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_5,GPIO_PIN_5);
    }
    else
    {

      test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_16,0);
      test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_7,0);
      test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_5,0);
    }

}

void MCUPowerOn(bool enable,testParameter* parameter)
{

       if (enable==true)
    {
    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_15,GPIO_PIN_15);
 SEGGER_RTT_printf(0,"Mcu %d\r\n",2);
    }
    else
    {

    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_15,0);
     SEGGER_RTT_printf(0,"Mcu %d\r\n",3);
    }

}

void nMosOn(bool enable,testParameter* parameter)
{

       if (enable==true)
    {
    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_4,GPIO_PIN_4);

    }
    else
    {

    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_4,0);
    }

}

void TrickleChargetestOn(bool enable,testParameter* parameter)
{

    if (enable==true)
    {

     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_30,GPIO_PIN_30);

    }
    else
    {

     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_30,0);
    }

}
void I2CresetOn(bool enable,testParameter* parameter)
{

    if (enable==true)
    {

     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_10,0);

    }
    else
    {

    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_10,GPIO_PIN_10);
    }

}





void GetDeviceID(testParameter* para)
{


  test_powercomp->Get_DeviceID(&(para->_tempdeviceid1),
                                &(para->_tempdeviceid2));

   para->receivedata[0]=para->_tempdeviceid1;
   para->receivedata[1]=para->_tempdeviceid1;
   para->templength=2;
}

void getskuid(testParameter* parameter)
{   uint32_t value;
    if(test_iocomp->IO_PinRead(GPIO_PORT0_BASE,GPIO_PIN_18)==1)
    {
        value=1;

    }
    if(test_iocomp->IO_PinRead(GPIO_PORT0_BASE,GPIO_PIN_19)==1)
    {
        value=value|2;

    }
      parameter->templength=3;
      parameter->receivedata[0]=value;


}

void open09 (bool enable,testParameter* parameter)
{

       if (enable==true)
    {
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_9,GPIO_PIN_9);

    }
    else
    {

    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_9,GPIO_PIN_0);
    }

}

void discharge (bool enable,testParameter* parameter)
{

       if (enable==true)
    {
     test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_20,GPIO_PIN_20);

    }
    else
    {

    test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_20,GPIO_PIN_0);
    }

}

void io_handler(void)
{

   intflag=1;

}
void io_handler2(void)
{
   intflag2=1;

}

void io_handler3(void)
{
   intflag3=1;

}

void resetio(void)
{ PinAndPinset pin;

 for (pin=0;pin<GPIO_Clear;pin++)
  {
  if (pin!=GPIO_PIN_28&&pin!=GPIO_PIN_29&&pin!=GPIO_PIN_31&&
      pin!=GPIO_PIN_0&&pin!=GPIO_PIN_1)
   {
   test_iocomp->IO_Powerdown(GPIO_PORT0_BASE,pin);
   }

  }

}

 void _test_Routine(bool reset,testParameter* parameter)
{
    uint8_t tempresult1[2];
    uint8_t templength;
    resultofaccess tempresult;
    uint32_t _tempi;
    uint32_t _temp ;
    if (reset==true)
    {
       test_iocomp->IO_IntConfigure(GPIOTE_PORT0_BASE,GPIOTE_PIN_28,
                                    iote_channel0,iote_polar_hitolo,io_handler);
       test_iocomp->IO_IntConfigure(GPIOTE_PORT0_BASE,GPIOTE_PIN_31,
                               iote_channel1,iote_polar_lotohi,io_handler2);
       test_iocomp->IO_IntConfigure(GPIOTE_PORT0_BASE,GPIOTE_PIN_29,
                               iote_channel2,iote_polar_lotohi,io_handler3);
       test_powercomp->IntConfigure(POWER,SLEEPENTER,true,1,true);

       parameter->step=0;
    SEGGER_RTT_printf(0,"testrest %d\r\n",1);
    }
    switch (parameter->step)
    {
    case 0:


        if (test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               0,
                               false)!=notvalid_model)
       {


        if (parameter->tempcmd==CmdMcuon)
         {
           SEGGER_RTT_printf(0,"Mcu %d\r\n",parameter->tempvalue);
           SEGGER_RTT_printf(0,"Mcuvalue %d\r\n",1);
           parameter->step=20;
         }
         else if (parameter->tempcmd==Cmdsteerlock)
         {
             parameter->step=30;
         }

          else if (parameter->tempcmd==Cmdprecharge)
           {
               parameter->step=40;
           }
          else if (parameter->tempcmd==Cmdtricklecharge)
           {
               parameter->step=50;
           }

          else if (parameter->tempcmd==CmdGetDeviceID)
           {
                parameter->step=60;
           }

          else if (parameter->tempcmd==CmdI2Creset)
           {
                parameter->step=70;
           }
          else if (parameter->tempcmd==CmdSkuID)
           {
                parameter->step=80;
           }
          else if (parameter->tempcmd==CmdSleep)
           {
                parameter->step=90;
           }
          else if (parameter->tempcmd==CmdVBAT)
           {
                parameter->step=100;
           }
          else if (parameter->tempcmd==Cmd09)
           {
                parameter->step=120;
           }
          else if (parameter->tempcmd==CmdVBAT2)
           {
                parameter->step=130;
           }
          else if (parameter->tempcmd==CmdDischarge)
           {
                parameter->step=150;
           }
          else if (parameter->tempcmd==CmdVBAT3)
           {
                parameter->step=170;
           }
          else if (parameter->tempcmd==CmdSoftreset)
           {
                parameter->step=190;
           }
           else if (parameter->tempcmd==CmdUartTest)
           {
                parameter->step=10;

           }
        }

        else if (intflag==1)
        {    SEGGER_RTT_printf(0,"iny %d\r\n",1);
            intflag=0;
            parameter->receivedata[0]=0x01;
            parameter->tempcmd=CmdInttest;
            parameter->templength=3;
          test_crccomp->crc(parameter->crcparainindex,1,parameter->receivedata,
                          tempresult1,&templength);
                                  *(parameter->receivedata+1)=*tempresult1;
        *(parameter->receivedata+2)=*(tempresult1+1);
            parameter->step=210;
        }

        else if (intflag2==1)
        {
             intflag2=0;
            parameter->receivedata[0]=0x01;
            parameter->tempcmd=CmdInttest2;
            parameter->templength=3;
          test_crccomp->crc(parameter->crcparainindex,1,parameter->receivedata,
                          tempresult1,&templength);
                                  *(parameter->receivedata+1)=*tempresult1;
        *(parameter->receivedata+2)=*(tempresult1+1);
            parameter->step=210;
        }
       else if (intflag3==1)
        {
             intflag3=0;
            parameter->receivedata[0]=0x01;
            parameter->tempcmd=CmdInttest3;
            parameter->templength=3;
          test_crccomp->crc(parameter->crcparainindex,1,parameter->receivedata,
                          tempresult1,&templength);
                                  *(parameter->receivedata+1)=*tempresult1;
        *(parameter->receivedata+2)=*(tempresult1+1);
            parameter->step=210;
        }

     break;


    case 10:

          parameter->receivedata[0]=0x01;
        parameter->templength=1;
        parameter->step=200;
        break;
    case 20:
        SEGGER_RTT_printf(0,"Mcu222 %d\r\n",parameter->tempvalue);
        if (parameter->tempvalue==0x01)
        {

          MCUPowerOn(true,&parameter);
        }
        else
        {
          MCUPowerOn(false,&parameter);
        }
        parameter->receivedata[0]=0x01;
        parameter->templength=1;
        parameter->step=200;
       break;
    case 30:

          wheellock(parameter->tempvalue,&parameter);


        parameter->receivedata[0]=0x01;
        parameter->templength=1;
        parameter->step=200;
       break;

    case 40:
        if (parameter->tempvalue==0x01)
        {
          nMosOn(true,&parameter);
        }
        else
        {
          nMosOn(false,&parameter);
        }
        parameter->receivedata[0]=0x01;
        parameter->templength=1;
        parameter->step=200;
       break;
    case 50:
        if (parameter->tempvalue==0x01)
        {
          TrickleChargetestOn(true,&parameter);
        }
        else
        {
          TrickleChargetestOn(false,&parameter);
        }
        parameter->receivedata[0]=0x01;
        parameter->templength=1;
        parameter->step=200;
       break;

    case 60:

        GetDeviceID(parameter);
        parameter->step=200;


        break;

    case 70:
          if (parameter->tempvalue==0x01)
        {
          I2CresetOn(true,&parameter);
        }
        else
        {
          I2CresetOn(false,&parameter);
        }
        parameter->templength=1;
        parameter->receivedata[0]=0x01;
        parameter->step=200;
        break;
    case 80:

            getskuid(parameter);
            parameter->step=200;
            break;

    case 90:
        resetio();
        SEGGER_RTT_printf(0,"testpower %d\r\n",90);
        test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               1,true);


        parameter->templength=1;
        parameter->receivedata[0]=1;
        parameter->step=95;

        test_crccomp->crc(parameter->crcparainindex,1,parameter->receivedata,
                          tempresult1,&templength);

        *(parameter->receivedata+1)=*tempresult1;
        *(parameter->receivedata+2)=*(tempresult1+1);
        break;

    case 95 :
SEGGER_RTT_printf(0,"testpower %d\r\n",95);
          if (test_modelcomp->Set(parameter->modeloutindex,

                                parameter->tempcmd,
                                parameter->receivedata,3)==successful_model)
       {
           _temp=0;
           parameter->step=96;
       }

       break;

    case 96 :

        if (_temp12++>1000)
        {SEGGER_RTT_printf(0,"testpower %d\r\n",40);
            test_powercomp->Sleep(true,POWER);
            parameter->step=97;
        }


      break;

    case 97:
        SEGGER_RTT_printf(0,"testpower %d\r\n",50);
        if (test_powercomp->Sleep(false,POWER)==true)
        {SEGGER_RTT_printf(0,"testpower %d\r\n",50);
          parameter->step=0;

        }
        break;
    case 100:
        test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_3,0);

        for(_tempi=0;_tempi<10000;_tempi++)
        {

        }
        test_iocomp->IO_PinWrite(GPIO_PORT0_BASE,GPIO_PIN_3,GPIO_PIN_3);
 for(_tempi=0;_tempi<10000;_tempi++)
        {

        }
 SEGGER_RTT_printf(0,"ADC %d\r\n",1);

                  test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               1,true);
            parameter->tempvalue=0;
            test_adccomp->ADC_Sample(true,channel_ADC_0,&parameter->tempvalue,true);

         parameter->step=110;
       break;

    case 110:


        if ( test_adccomp->ADC_Sample(false,channel_ADC_0,&parameter->tempvalue,true)==true)
        {

 parameter->templength=4;
           parameter->receivedata[1]=(parameter->tempvalue&0xff);
           parameter->receivedata[0]=(parameter->tempvalue>>8)&0xff;
           parameter->step=210;
         test_crccomp->crc(parameter->crcparainindex,2,parameter->receivedata,
                          tempresult1,&templength);

        *(parameter->receivedata+2)=*tempresult1;
        *(parameter->receivedata+3)=*(tempresult1+1);

SEGGER_RTT_printf(0,"ADCvalue %d\r\n", parameter->receivedata[0]);
SEGGER_RTT_printf(0,"ADCvalue %d\r\n", *(tempresult1+1));
         }
        break;

    case 120:
        if (parameter->tempvalue==0x01)
        {
          open09(true,&parameter);
        }
        else
        {
          open09(false,&parameter);
        }
        parameter->templength=1;
        parameter->receivedata[0]=0x01;
        parameter->step=200;
        break;
    case 130:
           test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               1,true);
            parameter->tempvalue=0;
            test_adccomp->ADC_Sample(true,channel_ADC_1,&parameter->tempvalue,true);

         parameter->step=140;
       break;
    case 140:
           SEGGER_RTT_printf(0,"ADC %d\r\n",3);

        if ( test_adccomp->ADC_Sample(false,channel_ADC_1,&parameter->tempvalue,true)==true)
        {

 parameter->templength=4;
           parameter->receivedata[1]=(parameter->tempvalue&0xff);
           parameter->receivedata[0]=(parameter->tempvalue>>8)&0xff;
           parameter->step=210;
         test_crccomp->crc(parameter->crcparainindex,2,parameter->receivedata,
                          tempresult1,&templength);

        *(parameter->receivedata+2)=*tempresult1;
        *(parameter->receivedata+3)=*(tempresult1+1);

SEGGER_RTT_printf(0,"ADCvalue %d\r\n", parameter->receivedata[0]);
SEGGER_RTT_printf(0,"ADCvalue %d\r\n", *(tempresult1+1));
         }
        break;

    case 150:

        if (parameter->tempvalue==0x01)
        {
          discharge(true,&parameter);
        }
        else
        {
          discharge(false,&parameter);
        }
        parameter->templength=1;
        parameter->receivedata[0]=0x01;
        parameter->step=200;
        break;
    case 170:
           test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               1,true);
            parameter->tempvalue=0;
            test_adccomp->ADC_Sample(true,channel_ADC_2,&parameter->tempvalue,true);

         parameter->step=180;
       break;
    case 180:
           SEGGER_RTT_printf(0,"ADC %d\r\n",3);

        if ( test_adccomp->ADC_Sample(false,channel_ADC_2,&parameter->tempvalue,true)==true)
        {

 parameter->templength=4;
           parameter->receivedata[1]=(parameter->tempvalue&0xff);
           parameter->receivedata[0]=(parameter->tempvalue>>8)&0xff;
           parameter->step=210;
         test_crccomp->crc(parameter->crcparainindex,2,parameter->receivedata,
                          tempresult1,&templength);

        *(parameter->receivedata+2)=*tempresult1;
        *(parameter->receivedata+3)=*(tempresult1+1);

SEGGER_RTT_printf(0,"ADCvalue %d\r\n", parameter->receivedata[0]);
SEGGER_RTT_printf(0,"ADCvalue %d\r\n", *(tempresult1+1));
         }
        break;

    case 190:
        NVIC_SystemReset();
        break;
      case 200:



        test_modelcomp->Get(parameter->modelinindex,
                               &parameter->tempcmd,
                               &parameter->templength,
                               &parameter->tempvalue,
                               1,true);
         test_crccomp->crc(parameter->crcparainindex,1,parameter->receivedata,
                          tempresult1,&templength);

        *(parameter->receivedata+1)=*tempresult1;
        *(parameter->receivedata+2)=*(tempresult1+1);

        SEGGER_RTT_printf(0,"ddvalue %d\r\n", parameter->receivedata[0]);
SEGGER_RTT_printf(0,"ddvalue %d\r\n", *(tempresult1+1));
          parameter->templength=3;

        parameter->step=210;
        break;

    case 210:

      if (test_modelcomp->Set(parameter->modeloutindex,
                                parameter->tempcmd,
                                parameter->receivedata,parameter->templength
                                )==successful_model)
       {
            parameter->step=0;
       }

       break;

    }

}
void CreatetesteModule(testDevice* testcomp,
                       InterruptController* intcomp,
                       PowerDevice* powercomp,CRCDevice* crccomp,
                       IODevice* iocomp,ADCDevice* adccomp,
                       ModelDevice* modelcomp)
{
    testcomp->test_Routine=_test_Routine;
    test_intcomp=intcomp;
    test_powercomp=powercomp;
    test_crccomp=crccomp;
    test_iocomp=iocomp;
    test_adccomp=adccomp;
    test_modelcomp=modelcomp;
}
