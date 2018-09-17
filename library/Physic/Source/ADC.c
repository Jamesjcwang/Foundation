
#include "library\physic\header\I_ADC.h"
static uint8_t _step_adc[channel_ADC_total];
static uint8_t _stopped_adc,_started_adc,_done_adc,_end_adc;

static uint8_t _adcvalue_ready[channel_ADC_total];
static uint8_t _adcchannel_active[channel_ADC_total];
static uint32_t _adcvalue[channel_ADC_total];


static void _ADC_set_pin(ADCBaseAddress port,uint32_t channel,enum_ADC_AnalogIn pin_p,enum_ADC_AnalogIn pin_n)
  {
     if (channel==channel_ADC_0)
     {
            ((ADCStruct*)(port))->CH0_PSELP =(uint32_t)pin_p;
((ADCStruct*)(port))->CH0_PSELN =(uint32_t)pin_n;
     }
     else if (channel==channel_ADC_5)
     {
 ((ADCStruct*)(port))->CH5_PSELP =(uint32_t)pin_p;
((ADCStruct*)(port))->CH5_PSELN =(uint32_t)pin_n;
     }
       else if (channel==channel_ADC_7)
     {
 ((ADCStruct*)(port))->CH7_PSELP =(uint32_t)pin_p;
((ADCStruct*)(port))->CH7_PSELN =(uint32_t)pin_n;
     }
   // *((uint32_t*)((&(((ADCStruct*)(port))->CH0_PSELN))+((uint32_t)(16<<channel)))) =(uint32_t)pin_n;
  }
static void _ADC_set_limit(ADCBaseAddress port,uint32_t channel,uint32_t limit)
  {


      ((ADCStruct*)(port))->CH0_LIMIT =limit;

  }
static void _ADC_set_samplerate(ADCBaseAddress port,enum_ADC_Samplekind samplekind)
{
    ((ADCStruct*)(port))->SAMPLERATE=(uint32_t)samplekind;

}
static void _ADC_set_resolution(ADCBaseAddress port,enum_ADC_resolution resolution)
{
    ((ADCStruct*)(port))->RESOLUTION=(uint32_t)resolution      ;

}

static void _ADC_set_config(ADCBaseAddress port,uint32_t channel,enum_ADC_Resp resistorofp,
                      enum_ADC_Resp resistorofn,enum_ADC_GAIN gain,
                      enum_ADC_refsel refsel,enum_ADC_acquistion tacq,enum_ADC_Mode mode)
{
    if (channel==channel_ADC_0)
    {
      ((ADCStruct*)(port))->CH0_CONFIG=
     ( ((uint32_t)resistorofp)|
      ((uint32_t)resistorofn)|
      ((uint32_t)gain)|
      ((uint32_t)refsel)|
      ((uint32_t)tacq)|
      ((uint32_t)mode));
    }
    else if (channel==channel_ADC_5)
    {
      ((ADCStruct*)(port))->CH5_CONFIG=
     ( ((uint32_t)resistorofp)|
      ((uint32_t)resistorofn)|
      ((uint32_t)gain)|
      ((uint32_t)refsel)|
      ((uint32_t)tacq)|
      ((uint32_t)mode));
    }
   else if (channel==channel_ADC_7)
    {
      ((ADCStruct*)(port))->CH7_CONFIG=
     ( ((uint32_t)resistorofp)|
      ((uint32_t)resistorofn)|
      ((uint32_t)gain)|
      ((uint32_t)refsel)|
      ((uint32_t)tacq)|
      ((uint32_t)mode));
    }

  }

 void _ADC_set_sample(ADCBaseAddress port)
{
    ((ADCStruct*)(port))->TASK_SAMPLE=0x01UL;

}
static void _ADC_set_stop(ADCBaseAddress port)
{
    ((ADCStruct*)(port))->TASK_STOP=0x01UL;

}
 void _ADC_set_enable(ADCBaseAddress port)
{
    ((ADCStruct*)(port))->ENABLE=0x01UL;
}
static void _ADC_set_start(ADCBaseAddress port)
{
    ((ADCStruct*)(port))->TASK_START=0x01UL;

}

 void _ADC_set_buffer(ADCBaseAddress port,uint32_t* ptrbuffer,uint32_t maxbuffer)
{//SEGGER_RTT_printf(0,"Times %d\r\n",ptrbuffer);
//SEGGER_RTT_printf(0,"Times %d\r\n",maxbuffer);
   // *((uint32_t*)(0x4000762C))=ptrbuffer;
    //*((uint32_t*)(0x40007630))=maxbuffer;
  ((ADCStruct*)(port))->RESULT_PTR=ptrbuffer;

  ((ADCStruct*)(port))->RESULT_MAXCNT=maxbuffer;
}

static void _ADC_set_int(ADCBaseAddress port,enum_ADC_MIS interrupt)
{
    ((ADCStruct*)(port))->INTENSET=(uint32_t)interrupt;

}


static void _ADC_clear_int(ADCBaseAddress port,enum_ADC_MIS interrupt)
{
    ((ADCStruct*)(port))->INTENCLR=(uint32_t)interrupt;

}

static void _ADC_clear_int_status(ADCBaseAddress port,enum_ADC_MIS interrupt)
{
    switch (interrupt)
    {
    case ADC_Event_STARTED:
       ((ADCStruct*)(port))->EVENT_STARTED=0UL;
       break;
    case ADC_Event_END:
       ((ADCStruct*)(port))->EVENT_END=0UL;
       break;
    case ADC_Event_DONE:
        ((ADCStruct*)(port))->EVENT_DONE=0UL;
       break;
    case ADC_Event_RESULTDONE:
        ((ADCStruct*)(port))->EVENT_RESULTDONE=0UL;
       break;
    case ADC_Event_CALIBRATIONDONE:
        ((ADCStruct*)(port))->EVENT_CALIBRATIONDONE=0UL;
       break;
    case ADC_Event_STOPPED:
        ((ADCStruct*)(port))->EVENT_STOPPED=0UL;
       break;
    case ADC_Event_CH0LIMITH:
        ((ADCStruct*)(port))->EVENT_CH0_LIMITH=0UL;
       break;
    case ADC_Event_CH0LIMITL:
        ((ADCStruct*)(port))->EVENT_CH0_LIMITL=0UL;
       break;

    }


}

static uint32_t _ADC_get_int_status(ADCBaseAddress port,enum_ADC_MIS interrupt)
{
    switch (interrupt)
    {
    case ADC_Event_STARTED:

       return(((ADCStruct*)(port))->EVENT_STARTED);

    case ADC_Event_END:
       return(((ADCStruct*)(port))->EVENT_END);

    case ADC_Event_DONE:
       return( ((ADCStruct*)(port))->EVENT_DONE);

    case ADC_Event_RESULTDONE:
       return( ((ADCStruct*)(port))->EVENT_RESULTDONE);

    case ADC_Event_CALIBRATIONDONE:
       return( ((ADCStruct*)(port))->EVENT_CALIBRATIONDONE);

    case ADC_Event_STOPPED:
       return( ((ADCStruct*)(port))->EVENT_STOPPED);

    case ADC_Event_CH0LIMITH:
        return( ((ADCStruct*)(port))->EVENT_CH0_LIMITH);

    case ADC_Event_CH0LIMITL:
       return(  ((ADCStruct*)(port))->EVENT_CH0_LIMITL);


    }

}

 uint8_t* getstepadc(enum_ADC_channel channel)
 {
    if (channel>=0&&channel<channel_ADC_total)

       return(&_step_adc[channel]);

 }


static void _ADC_Configure(ADCBaseAddress port ,enum_ADC_channel channel,
                    enum_ADC_AnalogIn positivepin,enum_ADC_AnalogIn negativepin,
                    enum_ADC_Resp resistorofp,enum_ADC_ResN resistorofn,
                    enum_ADC_GAIN gain,enum_ADC_refsel refsel,
                    enum_ADC_acquistion tacq,enum_ADC_Mode mode,
                    enum_ADC_resolution resolution,enum_ADC_Samplekind samplekind)
        {
           uint32_t _templimit;



              _ADC_set_config(port,channel,resistorofp,resistorofn,gain,refsel,tacq,mode);
             _ADC_set_pin(port,channel,positivepin,negativepin);
              _ADC_set_samplerate(port,samplekind);
             _ADC_set_resolution(port,resolution);
             _adcchannel_active[channel]=1;


         //  _ADC_set_limit(port,channel,_templimit|lowlimit);

        }

static bool _ADC_Sample(bool reset,enum_ADC_channel channel,uint32_t* value,bool refreshrole)
    {
       volatile uint32_t i,j;
       if (reset==true )
       { j=0;
         _stopped_adc=0;
         _started_adc=0;

         _done_adc=0;
        _step_adc[channel]=0;

         _ADC_clear_int_status(SAADC,ADC_Event_DONE);
         _ADC_clear_int_status(SAADC,ADC_Event_STOPPED);
         _ADC_clear_int_status(SAADC,ADC_Event_STARTED);
         _ADC_clear_int_status(SAADC,ADC_Event_RESULTDONE);
         _ADC_set_stop(SAADC);

       }
       else if (refreshrole==false)
       {
         _step_adc[channel]=100;
       }

     switch (_step_adc[channel])
     {
       case 0:
            if (_stopped_adc==1)
            {
SEGGER_RTT_printf(0,"adc1 %d\r\n",0);
                _stopped_adc=0;
                _step_adc[channel]=10;
            }
            return(false);
       case 10:

            _ADC_set_start(SAADC);

            _step_adc[channel]=20;
            return(false);
       case 20:
            if (_started_adc==1)
            {
SEGGER_RTT_printf(0,"adc1 %d\r\n",20);
              _started_adc=0;

              for (j=0;j<1000;j++)
              {

              }
               _ADC_set_sample(SAADC);
              _step_adc[channel]=30;
               j=0;
            }
           return(false);

       case 30:

           if (_done_adc==1)
           {
   for (j=0;j<1000;j++)
              {

              }

             _done_adc=0;
             for(i=0;i<channel_ADC_total;i++)
             {
               if (_adcchannel_active[i]==1)
               {
                  if (i==0)
                  {
                      _adcvalue[i]=*(ADC_bufferptr)&0xFFFF;
                  }
                  else if(i==1)
                  {
                      _adcvalue[i]=(*(ADC_bufferptr)>>16)&0XFFFF;

                  }
                  else if(i==2)
                  {
                       _adcvalue[i]=*(ADC_bufferptr+1)&0XFFFF;
                  }
                  else if(i==3)
                  {
                      _adcvalue[i]=(*(ADC_bufferptr+1)>>16)&0XFFFF;
                  }
                  _adcvalue_ready[i]=1;

               }



SEGGER_RTT_printf(0,"adc1 %d\r\n",*(ADC_bufferptr));
SEGGER_RTT_printf(0,"adc1 %d\r\n",*(ADC_bufferptr+1));
             }

           _step_adc[channel]=100;
           }
           return(false);
       case 100:
         if (_adcvalue_ready[channel]==1)
         {
           _adcvalue_ready[channel]=0;
           *value=_adcvalue[channel];

           _step_adc[channel]=0;
SEGGER_RTT_printf(0,"adc1 %d\r\n",100);
           return(true);

         }
         return(false);

     }

    }

static void _ADC_IntConfigure(ADCBaseAddress port, enum_ADC_MIS interrupt,
                           bool enable,uint32_t priority,bool controllerenable)
    {

         ADC_intcontroller->Configure(SAADC_IRQn,controllerenable,priority);
         _ADC_set_int(port,interrupt);

    }
static void _ADC_IntClear(ADCBaseAddress port, enum_ADC_MIS interrupt)
    {

      _ADC_clear_int_status(port,interrupt);

    }


static uint32_t _ADC_IntStatus(ADCBaseAddress port,enum_ADC_MIS interrupt)
    {

        return(_ADC_get_int_status(port,interrupt));
    }


void ADChandler(void)
{ SEGGER_RTT_printf(0,"adc %d\r\n",0);
       if (_ADC_IntStatus(SAADC,ADC_Event_END))
      {
           SEGGER_RTT_printf(0,"adc %d\r\n",1);
         _ADC_IntClear(SAADC,ADC_Event_END);
         _end_adc=1;

      }
      else if (_ADC_IntStatus(SAADC,ADC_Event_DONE))
      {
           SEGGER_RTT_printf(0,"adc %d\r\n",2);
         _ADC_IntClear(SAADC,ADC_Event_DONE);
         _done_adc=1;

      }
      else if (_ADC_IntStatus(SAADC,ADC_Event_RESULTDONE))
      {
           SEGGER_RTT_printf(0,"adc %d\r\n",3);
         _ADC_IntClear(SAADC,ADC_Event_RESULTDONE);
 _done_adc=1;

      }
      else if (_ADC_IntStatus(SAADC,ADC_Event_STARTED))
      {
           SEGGER_RTT_printf(0,"adc %d\r\n",4);
         _ADC_IntClear(SAADC,ADC_Event_STARTED);
         _started_adc=1;

      }
      else if (_ADC_IntStatus(SAADC,ADC_Event_STOPPED))
      {
          SEGGER_RTT_printf(0,"adc %d\r\n",5);
         _ADC_IntClear(SAADC,ADC_Event_STOPPED);
         _stopped_adc=1;

      }

}


void CreateADCDevice(ADCDevice* device, InterruptController* intcontroller,
                     ADCBaseAddress port ,enum_ADC_channel channel,
                     enum_ADC_AnalogIn positivepin,enum_ADC_AnalogIn negativepin,
                     enum_ADC_Resp resistorofP,enum_ADC_ResN resistorofN,
                     enum_ADC_GAIN gain,enum_ADC_refsel refsel,
                     enum_ADC_acquistion tacq,enum_ADC_Mode mode,
                     enum_ADC_resolution resolution,enum_ADC_Samplekind samplekind,
                     uint32_t buffersize)
{

 if (ADC_bufferptr==0)
 { SEGGER_RTT_printf(0,"adcstart %d\r\n",5);
     ADC_bufferptr=(uint32_t*)malloc(buffersize*sizeof(uint32_t));
     *(ADC_bufferptr)=0;
      *(ADC_bufferptr+1)=0;

    _ADC_set_enable(port);
    _ADC_set_buffer(SAADC,ADC_bufferptr,10);

 }
  _ADC_Configure(port,channel,positivepin,negativepin,resistorofP,resistorofN,
                gain,refsel,tacq,mode,resolution,samplekind);

 // device->ADC_IntClear=_ADC_clear_int_status;
 // device->ADC_IntConfigure=_ADC_IntConfigure;
 // device->ADC_IntHandler=_ADC_IntHandler;
 // device->ADC_IntStatus=_ADC_IntStatus;
 // device->ADC_Receive=_ADC_Receive;


  _adcchannel_active[channel]=1;
  device->ADC_Sample=_ADC_Sample;
 // device->ADC_Start=_ADC_Start;
  ADC_intcontroller=intcontroller;
  ADC_intcontroller->IntHandler(SAADC_IRQn,ADChandler);
  _ADC_IntConfigure(SAADC,ADC_Event_RESULTDONE|ADC_Event_DONE|ADC_Event_END|ADC_Event_STARTED|ADC_Event_STOPPED,
                    true,0,true);

}
