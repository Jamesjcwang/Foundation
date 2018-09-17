#include <stdbool.h>
#include <stdint.h>
#include "I_Int.h"
#include "I_IOTE.h"
#include "library\nrf.h"
#ifndef __I_IO_h__
#define __I_IO_h__

typedef struct {                                    /*!< GPIO Structure                                                        */
  volatile const  uint32_t  RESERVED0[321];
  volatile uint32_t  OUT;                               /*!< Write GPIO port.                                                      */
 volatile uint32_t  OUTSET;                            /*!< Set individual bits in GPIO port.                                     */
 volatile uint32_t  OUTCLR;                            /*!< Clear individual bits in GPIO port.                                   */
volatile   uint32_t  IN;                                /*!< Read GPIO port.                                                       */
  volatile uint32_t  DIR;                               /*!< Direction of GPIO pins.                                               */
 volatile uint32_t  DIRSET;                            /*!< DIR set register.                                                     */
 volatile uint32_t  DIRCLR;                            /*!< DIR clear register.                                                   */
 volatile const  uint32_t  RESERVED1[120];
  volatile uint32_t  PIN_CNF[32];                       /*!< Configuration of GPIO pins.                                           */
} NRF_GPIO_Type;



typedef enum{
 GPIO_PORT0_BASE       =  0x50000000 // GPIO Port A
// GPIO_PORTB_BASE       =  0x40005000,  // GPIO Port B
// GPIO_PORTC_BASE       =  0x40006000,  // GPIO Port C
// GPIO_PORTD_BASE       =  0x40007000,  // GPIO Port D
// GPIO_PORTE_BASE       =  0x40024000,  // GPIO Port E
// GPIO_PORTF_BASE       =  0x40025000,  // GPIO Port F
// GPIO_PORTG_BASE       =  0x40026000,  // GPIO Port G
// GPIO_PORTH_BASE       =  0x40027000,  // GPIO Port H
// GPIO_PORTA_AHB_BASE   =  0x40058000,  // GPIO Port A (high speed)
// GPIO_PORTB_AHB_BASE   =  0x40059000,  // GPIO Port B (high speed)
// GPIO_PORTC_AHB_BASE   =  0x4005A000,  // GPIO Port C (high speed)
// GPIO_PORTD_AHB_BASE   =  0x4005B000,  // GPIO Port D (high speed)
// GPIO_PORTE_AHB_BASE   =  0x4005C000,  // GPIO Port E (high speed)
// GPIO_PORTF_AHB_BASE   =  0x4005D000,  // GPIO Port F (high speed)
// GPIO_PORTG_AHB_BASE   =  0x4005E000,  // GPIO Port G (high speed)
// GPIO_PORTH_AHB_BASE   =  0x4005F000,  // GPIO Port H (high speed)
// GPIO_PORTJ_AHB_BASE   =  0x40060000,  // GPIO Port J (high speed)
// GPIO_PORTK_BASE       =  0x40061000,  // GPIO Port K
// GPIO_PORTL_BASE       =  0x40062000,  // GPIO Port L
// GPIO_PORTM_BASE       =  0x40063000,  // GPIO Port M
// GPIO_PORTN_BASE       =  0x40064000,  // GPIO Port N
// GPIO_PORTP_BASE       =  0x40065000,  // GPIO Port P
// GPIO_PORTQ_BASE       =  0x40066000, // GPIO Port Q
// GPIO_PORTR_BASE       =  0x40067000, // General-Purpose Input/Outputs
//                                     // (GPIOs)
// GPIO_PORTS_BASE       =  0x40068000,  // General-Purpose Input/Outputs
//                                     // (GPIOs)
// GPIO_PORTT_BASE       =  0x40069000  // General-Purpose Input/Outputs
//                                            // (GPIOs)
} IOBaseAddress;

typedef enum {
GPIO_FALLING_EDGE  =     0x00000000 ,
GPIO_RISING_EDGE   =     0x00000004 ,
GPIO_BOTH_EDGES    =     0x00000001 ,
GPIO_LOW_LEVEL     =     0x00000002 ,
GPIO_HIGH_LEVEL    =     0x00000006 ,
GPIO_DISCRETE_INT  =     0x00010000
} TriggerLogic;
typedef enum {

GPIO_PIN_0     ,
GPIO_PIN_1     ,
GPIO_PIN_2     ,
GPIO_PIN_3     ,
GPIO_PIN_4     ,
GPIO_PIN_5     ,
GPIO_PIN_6     ,
GPIO_PIN_7     ,
GPIO_PIN_8     ,
GPIO_PIN_9     ,
GPIO_PIN_10    ,
GPIO_PIN_11    ,
GPIO_PIN_12    ,
GPIO_PIN_13    ,
GPIO_PIN_14    ,
GPIO_PIN_15    ,
GPIO_PIN_16    ,
GPIO_PIN_17    ,
GPIO_PIN_18    ,
GPIO_PIN_19    ,
GPIO_PIN_20    ,
GPIO_PIN_21    ,
GPIO_PIN_22    ,
GPIO_PIN_23    ,
GPIO_PIN_24    ,
GPIO_PIN_25    ,
GPIO_PIN_26    ,
GPIO_PIN_27    ,
GPIO_PIN_28    ,
GPIO_PIN_29    ,
GPIO_PIN_30    ,
GPIO_PIN_31    ,
GPIO_Clear            , //GPIO Pin clean
} PinAndPinset;


typedef enum {
    NRF_GPIO_PIN_S0S1 = 0UL, ///< !< Standard '0', standard '1'
    NRF_GPIO_PIN_H0S1 = 1UL, ///< !< High drive '0', standard '1'
    NRF_GPIO_PIN_S0H1 = 2UL, ///< !< Standard '0', high drive '1'
    NRF_GPIO_PIN_H0H1 = 3UL, ///< !< High drive '0', high 'drive '1''
    NRF_GPIO_PIN_D0S1 = 4UL, ///< !< Disconnect '0' standard '1'
    NRF_GPIO_PIN_D0H1 = 5UL, ///< !< Disconnect '0', high drive '1'
    NRF_GPIO_PIN_S0D1 = 6UL, ///< !< Standard '0'. disconnect '1'
    NRF_GPIO_PIN_H0D1 = 7UL ///< !< High drive '0', disconnect '1'
} DriveStrength;

typedef enum {
   NRF_GPIO_PIN_NOPULL   = 0UL,                 ///<  Pin pullup resistor disabled
    NRF_GPIO_PIN_PULLDOWN = 1UL,                 ///<  Pin pulldown resistor enabled
    NRF_GPIO_PIN_PULLUP   = 3UL                   ///<  Pin pullup resistor enabled

 }Pull_Push;

 typedef enum{

GPIO_DIR_MODE_IN     =   0x00000000UL,
GPIO_DIR_MODE_OUT    =   0x00000001UL,
GPIO_DIR_MODE_HW     =   0x00000002UL

} PinMode;

typedef enum
{
  Sense_Disabled=0,
  Sense_High=2,
  Sense_Low=3

} enum_Sense_for_wakeup;

typedef struct {

  //InterruptController* intcontroller;
void (*IO_Configure)(IOBaseAddress port ,PinAndPinset pin, DriveStrength length,Pull_Push type,
                     PinMode mode,PinMode bufferconnected,enum_Sense_for_wakeup sense);

void (*IO_PinWrite)(IOBaseAddress port , PinAndPinset  pin, PinAndPinset status);

uint32_t (*IO_PinRead)(IOBaseAddress port ,PinAndPinset pin);

void (*IO_IntConfigure)(IOTEBaseAddress port, enum_pin_iote pin, enum_channel_iote channel
                            ,enum_polarity_iote polarity,void (*handler)(void));

void (*IO_Powerdown)(IOBaseAddress port , PinAndPinset  pin);
 //void (*IO_AlternateFunction) (IOBaseAddress Port,PinAndPinset Pin, uint32_t Enocding );

 //void (*IO_IntConfigure)(IOBaseAddress Port, PinAndPinset Pin,TriggerLogic LogicType);

 //void (*IO_IntClear)(IOBaseAddress Port, PinAndPinset Pin);

 //uint32_t (*IO_IntStatus)(IOBaseAddress Port, bool bMasked);


} IODevice;

InterruptController* IO_intcontroller;

extern void CreateIODevice(IODevice* device,InterruptController* intcomp,
                           uint8_t numofbit,IOBaseAddress* port,
                           PinAndPinset* pin,DriveStrength* length,Pull_Push* type,
                           PinMode* mode,PinMode* bufferconnected,enum_Sense_for_wakeup* sense);


//extern void IO_Configure(uint32_t Port ,PinAndPinset Pin, DriveStrength Length,Pull_Push Type,
//                     PinMode Mode)
//extern void IO_PinWrite(uint32_t Port , PinAndPinset  Pin, PinAndPinset Status)

//extern PinAndPinset IO_PinRead(uint32_t Port ,PinAndPinset Pin)

//extern void IO_AlternateFunction (uint32_t Port,PinAndPinset Pin, uint32_t Enocding );

//extern void IO_IntConfigure(uint32_t Port, PinAndPinset Pin,TriggerLogic LogicType);

//extern void IO_IntClear(uint32_t Port, PinAndPinset Pin);

//extern uint32_t IO_IntStatus(uint32_t Port, bool bMasked);




#endif
