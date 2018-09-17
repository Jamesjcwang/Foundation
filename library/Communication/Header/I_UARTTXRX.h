

#include <stdbool.h>
#include <stdint.h>
#include "library\Component\Header\I_Model.h"
#include "library\Physic\Header\I_UART.h"
#include "library\Physic\Header\I_IO.h"
#include "library\Component\Header\I_Delayobject.h"
#include "library\Component\Header\I_CRC.h"

#ifndef __I_UARTTXRX_h__
#define __I_UARTTXRX_h__


typedef struct
{

    uint32_t step_send,step_receive;
    uint32_t _f1,_p;
    uint8_t tempvalue,tempcount,templength,tempcmd;
    uint32_t tempindex;
    uint32_t lengthofdata;
    uint32_t flagreceived;
    uint32_t refresh;
    uint8_t  receivedata[50];



    UARTBaseAddress uartport;
    IOBaseAddress ioport;
   // uint32_t frequency;
   // Baudrate baudrate;
   // DataLength datalength;
   // StopBitType stopbit;
   // ParityType parity;

    PinAndPinset txpin;
    PinAndPinset rxpin;
    PinAndPinset cstpin;
    PinAndPinset rstpin;
    uint8_t startchar;


    uint32_t crcparainindex;
    uint32_t crcparaoutindex;
    uint32_t crcparaoutindex_transfer;
    uint32_t crcparaoutindex_transfer2;
    uint32_t delayparaindex;
    uint32_t modelinindex;
    uint32_t modeloutindex;

} UARTTXRXParameter;

typedef struct {

 void(* UARTTXRX_Routine)(bool reset,
                        uint32_t paraindex);


 uint32_t (*ParameterInitial)(uint8_t startchar,
                              UARTBaseAddress uartport,IOBaseAddress ioport,
                              PinAndPinset txpin,PinAndPinset rxpin,
                              PinAndPinset cstpin,PinAndPinset rstpin,
                              uint32_t crcparainindex,uint32_t crcparaoutindex,
                              uint32_t crcparaoutindex_transfer,
                              uint32_t crcparaoutindex_transfer2,
                              uint32_t delayparaindex,
                              uint32_t modelinindex,
                              uint32_t modeloutindex);


} UARTTXRXDevice;
ListStruct_uint8 uartlist;
ListCollection* uart_listcomp;
ModelDevice* uart_modelcomp;
CRCDevice* uart_crccomp;
DelayObject* uart_delaycomp;
UARTDevice * uart_uartcomp;
IODevice* uart_iocomp;
uint32_t uartparalist[1];
extern void CreateUARTTXRXDevice(UARTTXRXDevice* component,
                                 ModelDevice* modelcomp,CRCDevice* crccomp,
                                 DelayObject* delaycomp,UARTDevice* uartcomp,
                                 IODevice* iocomp,ListCollection* listcomp);

#endif
