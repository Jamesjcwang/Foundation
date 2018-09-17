#ifndef __I_ADC_h__
#define __I_ADC_h__

#include <stdbool.h>
#include <stdint.h>
#include "I_Int.h"
#include <math.h>




typedef struct
{
    volatile uint32_t TASK_START;
    volatile uint32_t TASK_SAMPLE;
    volatile uint32_t TASK_STOP;
    volatile uint32_t TASK_CALIBRATION;
    volatile uint32_t reserve[60];
    volatile uint32_t EVENT_STARTED;
    volatile uint32_t EVENT_END;
    volatile uint32_t EVENT_DONE;
    volatile uint32_t EVENT_RESULTDONE;
    volatile uint32_t EVENT_CALIBRATIONDONE;
    volatile uint32_t EVENT_STOPPED;
    volatile uint32_t EVENT_CH0_LIMITH;
    volatile uint32_t EVENT_CH0_LIMITL;
    volatile uint32_t EVENT_CH1_LIMITH;
    volatile uint32_t EVENT_CH1_LIMITL;
    volatile uint32_t EVENT_CH2_LIMITH;
    volatile uint32_t EVENT_CH2_LIMITL;
    volatile uint32_t EVENT_CH3_LIMITH;
    volatile uint32_t EVENT_CH3_LIMITL;
    volatile uint32_t EVENT_CH4_LIMITH;
    volatile uint32_t EVENT_CH4_LIMITL;
    volatile uint32_t EVENT_CH5_LIMITH;
    volatile uint32_t EVENT_CH5_LIMITL;
    volatile uint32_t EVENT_CH6_LIMITH;
    volatile uint32_t EVENT_CH6_LIMITL;
    volatile uint32_t EVENT_CH7_LIMITH;
    volatile uint32_t EVENT_CH7_LIMITL;
    volatile uint32_t reserve2[106];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t reserve3[61];
    volatile uint32_t STATUS;
    volatile uint32_t reserve4[63];
    volatile uint32_t ENABLE;
    volatile uint32_t reserve5[3];
    volatile uint32_t CH0_PSELP;
    volatile uint32_t CH0_PSELN;
    volatile uint32_t CH0_CONFIG;
    volatile uint32_t CH0_LIMIT;
    volatile uint32_t CH1_PSELP;
    volatile uint32_t CH1_PSELN;
    volatile uint32_t CH1_CONFIG;
    volatile uint32_t CH1_LIMIT;
    volatile uint32_t CH2_PSELP;
    volatile uint32_t CH2_PSELN;
    volatile uint32_t CH2_CONFIG;
    volatile uint32_t CH2_LIMIT;
    volatile uint32_t CH3_PSELP;
    volatile uint32_t CH3_PSELN;
    volatile uint32_t CH3_CONFIG;
    volatile uint32_t CH3_LIMIT;
    volatile uint32_t CH4_PSELP;
    volatile uint32_t CH4_PSELN;
    volatile uint32_t CH4_CONFIG;
    volatile uint32_t CH4_LIMIT;
    volatile uint32_t CH5_PSELP;
    volatile uint32_t CH5_PSELN;
    volatile uint32_t CH5_CONFIG;
    volatile uint32_t CH5_LIMIT;
    volatile uint32_t CH6_PSELP;
    volatile uint32_t CH6_PSELN;
    volatile uint32_t CH6_CONFIG;
    volatile uint32_t CH6_LIMIT;
    volatile uint32_t CH7_PSELP;
    volatile uint32_t CH7_PSELN;
    volatile uint32_t CH7_CONFIG;
    volatile uint32_t CH7_LIMIT;
    volatile uint32_t reserve6[24];
    volatile uint32_t RESOLUTION;
    volatile uint32_t OVERSAMPLE;
    volatile uint32_t SAMPLERATE;
    volatile uint32_t reserve7[12];
    volatile uint32_t RESULT_PTR;
    volatile uint32_t RESULT_MAXCNT;
    volatile uint32_t RESULT_AMOUNT;

} ADCStruct;

typedef enum
{

    ADC_Event_STARTED=0X00000001,
    ADC_Event_END=0X00000002,
    ADC_Event_DONE=0X00000004,
    ADC_Event_RESULTDONE=0X00000008,
    ADC_Event_CALIBRATIONDONE=0X00000010,
    ADC_Event_STOPPED=0X00000020,
    ADC_Event_CH0LIMITH=0X00000040,
    ADC_Event_CH0LIMITL=0X00000080,
    ADC_Event_CH1LIMITH=0X00000100,
    ADC_Event_CH1LIMITL=0X00000200,
    ADC_Event_CH2LIMITH=0X00000400,
    ADC_Event_CH2LIMITL=0X00000800,
    ADC_Event_CH3LIMITH=0X00001000,
    ADC_Event_CH3LIMITL=0X00002000,
    ADC_Event_CH4LIMITH=0X00004000,
    ADC_Event_CH4LIMITL=0X00008000,
    ADC_Event_CH5LIMITH=0X00010000,
    ADC_Event_CH5LIMITL=0X00020000,
    ADC_Event_CH6LIMITH=0X00040000,
    ADC_Event_CH6LIMITL=0X00080000,
    ADC_Event_CH7LIMITH=0X00100000,
    ADC_Event_CH7LIMITL=0X00200000
} enum_ADC_MIS;

typedef enum
{
    ADC_NC=0,
    ADC_AnalogIn0=1,
    ADC_AnalogIn1=2,
    ADC_AnalogIn2=3,
    ADC_AnalogIn3=4,
    ADC_AnalogIn4=5,
    ADC_AnalogIn5=6,
    ADC_AnalogIn6=7,
    ADC_AnalogIn7=8,
    ADC_VDD=9,
    Analogin_total

} enum_ADC_AnalogIn;

typedef enum
{
   ADC_Resp_Bypass=0,
   ADC_Resp_Pull_down=1,
   ADC_Resp_Pull_up=2,
   ADC_Resp_VDD1_2=3

}enum_ADC_Resp;

typedef enum
{
   ADC_ResN_Bypass=0,
   ADC_ResN_Pull_down=16,
   ADC_ResN_Pull_up=32,
   ADC_ResN_VDD1_2=48

}enum_ADC_ResN;

typedef enum
{
    ADC_GAIN_1_6=0,
    ADC_GAIN_1_5=0x100,
    ADC_GAIN_1_4=0x200,
    ADC_GAIN_1_3=0x300,
    ADC_GAIN_1_2=0x400,
    ADC_GAIN_1=0x500,
    ADC_GAIN_2=0x600,
    ADC_GAIN_4=0x700

}enum_ADC_GAIN;

typedef enum
{
    ADC_internal=0,
    ADC_VDD1_4=0x1000
}enum_ADC_refsel;

typedef enum
{
    ADC_3us=0,
    ADC_5us=0x10000,
    ADC_10us=0x20000,
    ADC_15us=0x30000,
    ADC_20us=0x40000,
    ADC_40us=0x50000
} enum_ADC_acquistion;

typedef enum
{
    ADC_SingleEnd=0,
    ADC_Differetial=0x100000
}enum_ADC_Mode;



typedef enum
{
    ADC_8bit=0,
    ADC_10bit=1,
    ADC_12bit=2,
    ADC_14bit=3
}enum_ADC_resolution;
typedef enum
{
    ADC_Task=0,
    ADC_Timer=0x1000
} enum_ADC_Samplekind;


typedef enum
{
    SAADC=0x40007000
} ADCBaseAddress;

typedef enum
{
    channel_ADC_0,
    channel_ADC_1,
    channel_ADC_2,
    channel_ADC_3,
    channel_ADC_4,
    channel_ADC_5,
    channel_ADC_6,
    channel_ADC_7,
    channel_ADC_total
} enum_ADC_channel;



typedef struct {


 bool (*ADC_Sample)(bool reset,enum_ADC_channel channel,uint32_t* value,
                    bool refreshrole);


// void (*ADC_IntConfigure)(ADCBaseAddress port, enum_ADC_MIS interrupt,
  //                         bool enable,uint32_t priority,bool controllerenable);

// void (*ADC_IntClear)(ADCBaseAddress port, enum_ADC_MIS interrupt);

// uint32_t (*ADC_IntStatus)(ADCBaseAddress port,enum_ADC_MIS interrupt);


} ADCDevice;
InterruptController* ADC_intcontroller;
uint32_t* ADC_bufferptr;
// the unit of buffersize is uint16_t
extern void CreateADCDevice(ADCDevice* device, InterruptController* intcontroller,
                     ADCBaseAddress port ,enum_ADC_channel channel,
                     enum_ADC_AnalogIn positivepin,enum_ADC_AnalogIn negativepin,
                     enum_ADC_Resp resistorofP,enum_ADC_ResN resistorofN,
                     enum_ADC_GAIN gain,enum_ADC_refsel refsel,
                     enum_ADC_acquistion tacq,enum_ADC_Mode mode,
                     enum_ADC_resolution resolution,enum_ADC_Samplekind samplekind,
                     uint32_t buffersize);






#endif
