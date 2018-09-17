#include <stdbool.h>
#include <stdint.h>
#include "I_Int.h"
#include "library\nrf.h"
#ifndef __I_IOTE_h__
#define __I_IOTE_h__

typedef struct {                                    /*!< GPIOTE Structure                                                      */
  __O  uint32_t  TASKS_OUT[8];                      /*!< Description collection[0]: Task for writing to pin specified
                                                         in CONFIG[0].PSEL. Action on pin is configured in CONFIG[0].POLARITY. */
  __I  uint32_t  RESERVED0[4];
  __O  uint32_t  TASKS_SET[8];                      /*!< Description collection[0]: Task for writing to pin specified
                                                         in CONFIG[0].PSEL. Action on pin is to set it high.                   */
  __I  uint32_t  RESERVED1[4];
  __O  uint32_t  TASKS_CLR[8];                      /*!< Description collection[0]: Task for writing to pin specified
                                                         in CONFIG[0].PSEL. Action on pin is to set it low.                    */
  __I  uint32_t  RESERVED2[32];
  __IO uint32_t  EVENTS_IN[8];                      /*!< Description collection[0]: Event generated from pin specified
                                                         in CONFIG[0].PSEL                                                     */
  __I  uint32_t  RESERVED3[23];
  __IO uint32_t  EVENTS_PORT;                       /*!< Event generated from multiple input GPIO pins with SENSE mechanism
                                                         enabled                                                               */
  __I  uint32_t  RESERVED4[97];
  __IO uint32_t  INTENSET;                          /*!< Enable interrupt                                                      */
  __IO uint32_t  INTENCLR;                          /*!< Disable interrupt                                                     */
  __I  uint32_t  RESERVED5[129];
  __IO uint32_t  CONFIG[8];                         /*!< Description collection[0]: Configuration for OUT[n], SET[n]
                                                         and CLR[n] tasks and IN[n] event                                      */
} NRF_GPIOTE_Type;



typedef enum{
 GPIOTE_PORT0_BASE       =  0x40006000 // GPIO Port A

} IOTEBaseAddress;



typedef enum{
iote_disabled=0,
iote_event=1,
iote_task=3
}enum_mode_iote;

typedef enum{
GPIOTE_PIN_0   ,
GPIOTE_PIN_1   ,
GPIOTE_PIN_2   ,
GPIOTE_PIN_3   ,
GPIOTE_PIN_4   ,
GPIOTE_PIN_5   ,
GPIOTE_PIN_6   ,
GPIOTE_PIN_7   ,
GPIOTE_PIN_8   ,
GPIOTE_PIN_9   ,
GPIOTE_PIN_10  ,
GPIOTE_PIN_11  ,
GPIOTE_PIN_12  ,
GPIOTE_PIN_13  ,
GPIOTE_PIN_14  ,
GPIOTE_PIN_15  ,
GPIOTE_PIN_16  ,
GPIOTE_PIN_17  ,
GPIOTE_PIN_18  ,
GPIOTE_PIN_19  ,
GPIOTE_PIN_20  ,
GPIOTE_PIN_21  ,
GPIOTE_PIN_22  ,
GPIOTE_PIN_23  ,
GPIOTE_PIN_24  ,
GPIOTE_PIN_25  ,
GPIOTE_PIN_26  ,
GPIOTE_PIN_27  ,
GPIOTE_PIN_28  ,
GPIOTE_PIN_29  ,
GPIOTE_PIN_30  ,
GPIOTE_PIN_31


}enum_pin_iote;

typedef enum{
iote_polar_none=0x0,
iote_polar_lotohi=0x1,
iote_polar_hitolo=0x2,
iote_polar_toggle=0x3

}enum_polarity_iote;

typedef enum{
iote_init_low=0x0,
iote_init_high=0x1

}enum_initout_iote;


typedef enum{
iote_channel0,
iote_channel1,
iote_channel2,
iote_channel3,
iote_channel4,
iote_channel5,
iote_channel6,
iote_channel7

}enum_channel_iote;
extern void GPIOTE_Handler(void);
extern void _IO_IntConfigure(IOTEBaseAddress port, enum_pin_iote pin, enum_channel_iote channel
                            ,enum_polarity_iote polarity,void (*handler)(void));






#endif
