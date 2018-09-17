/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */
#ifndef NRF_UART_H__
#define NRF_UART_H__

#include "nrf.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "library\Physic\Header\I_UART.h"

/**
 * @defgroup nrf_uart_hal UART HAL
 * @{
 * @ingroup nrf_uart
 *
 * @brief Hardware access layer for accessing the UART peripheral.
 */

 volatile static bool _tx_enalbe,_rx_enable ;
volatile static bool _tx_busy;
 volatile static bool _tx_suspend;_rx_suspend;
volatile static bool _uart_enable;
 static bool _fifoenable;
 static  void(*_uart_raiseevent)(UARTBaseAddress port);
static uint32_t _rxbufferLength;
static uint32_t _txbufferLength;
static uint32_t _rxbuffer[20];
static uint32_t _txbuffer[20];
static uint8_t _step_uart[uartindex_total];
static bool _f_send_uart[uartindex_total];
#define NRF_UART_PSEL_DISCONNECTED 0xFFFFFFFF





/**
 * @enum nrf_uart_task_t
 * @brief UART tasks.
 */
typedef enum
{
    /*lint -save -e30 -esym(628,__INTADDR__)*/
    NRF_UART_TASK_STARTRX = offsetof(NRF_UART_Type, TASKS_STARTRX), /**< Task for starting reception. */
    NRF_UART_TASK_STOPRX  = offsetof(NRF_UART_Type, TASKS_STOPRX),  /**< Task for stopping reception. */
    NRF_UART_TASK_STARTTX = offsetof(NRF_UART_Type, TASKS_STARTTX), /**< Task for starting transmission. */
    NRF_UART_TASK_STOPTX  = offsetof(NRF_UART_Type, TASKS_STOPTX),  /**< Task for stopping transmission. */
    NRF_UART_TASK_SUSPEND = offsetof(NRF_UART_Type, TASKS_SUSPEND), /**< Task for suspending UART. */
    /*lint -restore*/
} nrf_uart_task_t;

/**
 * @enum nrf_uart_event_t
 * @brief UART events.
 */
typedef enum
{
    /*lint -save -e30*/
    NRF_UART_EVENT_CTS    = offsetof(NRF_UART_Type, EVENTS_CTS),   /**< Event from CTS line activation. */
    NRF_UART_EVENT_NCTS   = offsetof(NRF_UART_Type, EVENTS_NCTS),  /**< Event from CTS line deactivation. */
    NRF_UART_EVENT_RXDRDY = offsetof(NRF_UART_Type, EVENTS_RXDRDY),/**< Event from data ready in RXD. */
    NRF_UART_EVENT_TXDRDY = offsetof(NRF_UART_Type, EVENTS_TXDRDY),/**< Event from data sent from TXD. */
    NRF_UART_EVENT_ERROR  = offsetof(NRF_UART_Type, EVENTS_ERROR), /**< Event from error detection. */
    NRF_UART_EVENT_RXTO   = offsetof(NRF_UART_Type, EVENTS_RXTO)   /**< Event from receiver timeout. */
    /*lint -restore*/
} nrf_uart_event_t;

/**
 * @enum nrf_uart_int_mask_t
 * @brief UART interrupts.
 */
typedef enum
{
    /*lint -save -e30*/
    NRF_UART_INT_MASK_CTS    = 1UL,    /**< CTS line activation interrupt. */
    NRF_UART_INT_MASK_NCTS   = 2UL,   /**< CTS line deactivation interrupt. */
    NRF_UART_INT_MASK_RXDRDY = 4UL, /**< Data ready in RXD interrupt. */
    NRF_UART_INT_MASK_TXDRDY = 0x80UL,  /**< Data sent from TXD interrupt. */
    NRF_UART_INT_MASK_ERROR  = 0x200UL,  /**< Error detection interrupt. */
    NRF_UART_INT_MASK_RXTO   = 0x20000UL    /**< Receiver timeout interrupt. */
    /*lint -restore*/
} nrf_uart_int_mask_t;

/**
 * @enum nrf_uart_baudrate_t
 * @brief Baudrates supported by UART.
 */


/**
 * @enum nrf_uart_error_mask_t
 * @brief Types of UART error masks.
 */
typedef enum
{
    NRF_UART_ERROR_OVERRUN_MASK = 1UL,   /**< Overrun error. */
    NRF_UART_ERROR_PARITY_MASK  = 2UL,    /**< Parity error. */
    NRF_UART_ERROR_FRAMING_MASK = 4UL,   /**< Framing error. */
    NRF_UART_ERROR_BREAK_MASK   = 8UL,     /**< Break error. */
} nrf_uart_error_mask_t;

/**
 * @enum nrf_uart_parity_t
 * @brief Types of UART parity modes.
 */
typedef enum
{
    NRF_UART_PARITY_EXCLUDED = 0UL, /**< Parity excluded. */
    NRF_UART_PARITY_INCLUDED = 14UL /**< Parity included. */
} nrf_uart_parity_t;

/**
 * @enum nrf_uart_hwfc_t
 * @brief Types of UART flow control modes.
 */
typedef enum
{
    NRF_UART_HWFC_DISABLED = 0UL, /**< HW flow control disabled. */
    NRF_UART_HWFC_ENABLED  = 1UL,  /**< HW flow control enabled. */
} nrf_uart_hwfc_t;

/**
 * @brief Function for clearing a specific UART event.
 *
 * @param[in] p_reg  UART instance.
 * @param[in] event  Event to clear.
 */
static inline void nrf_uart_event_clear(NRF_UART_Type * p_reg, nrf_uart_event_t event);

/**
 * @brief Function for checking the state of a specific UART event.
 *
 * @param[in] p_reg  UART instance.
 * @param[in] event  Event to check.
 *
 * @retval True if event is set, False otherwise.
 */
static inline bool nrf_uart_event_check(NRF_UART_Type * p_reg, nrf_uart_event_t event);

/**
 * @brief Function for returning the address of a specific UART event register.
 *
 * @param[in] p_reg  UART instance.
 * @param[in] event  Desired event.
 *
 * @retval Address of specified event register.
 */
static inline uint32_t nrf_uart_event_address_get(NRF_UART_Type  * p_reg,
                                                    nrf_uart_event_t  event);

/**
 * @brief Function for enabling a specific interrupt.
 *
 * @param p_reg     Instance.
 * @param int_mask Interrupts to enable.
 */
static inline void nrf_uart_int_enable(NRF_UART_Type * p_reg, uint32_t int_mask);

/**
 * @brief Function for retrieving the state of a given interrupt.
 *
 * @param p_reg     Instance.
 * @param int_mask  Mask of interrupt to check.
 *
 * @retval true  If the interrupt is enabled.
 * @retval false If the interrupt is not enabled.
 */
static inline bool nrf_uart_int_enable_check(NRF_UART_Type * p_reg, uint32_t int_mask);

/**
 * @brief Function for disabling specific interrupts.
 *
 * @param p_reg    Instance.
 * @param int_mask Interrupts to disable.
 */
static inline void nrf_uart_int_disable(NRF_UART_Type * p_reg, uint32_t int_mask);

/**
 * @brief Function for getting error source mask. Function is clearing error source flags after reading.
 *
 * @param p_reg    Instance.
 * @return         Mask with error source flags.
 */
static inline uint32_t nrf_uart_errorsrc_get_and_clear(NRF_UART_Type * p_reg);

/**
 * @brief Function for enabling UART.
 *
 * @param p_reg    Instance.
 */
static inline void nrf_uart_enable(NRF_UART_Type * p_reg);

/**
 * @brief Function for disabling UART.
 *
 * @param p_reg    Instance.
 */
static inline void nrf_uart_disable(NRF_UART_Type * p_reg);

/**
 * @brief Function for configuring TX/RX pins.
 *
 * @param p_reg    Instance.
 * @param pseltxd  TXD pin number.
 * @param pselrxd  RXD pin number.
 */
static inline void nrf_uart_txrx_pins_set(NRF_UART_Type * p_reg, uint32_t pseltxd, uint32_t pselrxd);

/**
 * @brief Function for disconnecting TX/RX pins.
 *
 * @param p_reg    Instance.
 */
static inline void nrf_uart_txrx_pins_disconnect(NRF_UART_Type * p_reg);

/**
 * @brief Function for getting TX pin.
 *
 * @param p_reg    Instance.
 */
static inline uint32_t nrf_uart_tx_pin_get(NRF_UART_Type * p_reg);

/**
 * @brief Function for getting RX pin.
 *
 * @param p_reg    Instance.
 */
static inline uint32_t nrf_uart_rx_pin_get(NRF_UART_Type * p_reg);

/**
 * @brief Function for getting RTS pin.
 *
 * @param p_reg    Instance.
 */
static inline uint32_t nrf_uart_rts_pin_get(NRF_UART_Type * p_reg);

/**
 * @brief Function for getting CTS pin.
 *
 * @param p_reg    Instance.
 */
static inline uint32_t nrf_uart_cts_pin_get(NRF_UART_Type * p_reg);


/**
 * @brief Function for configuring flow control pins.
 *
 * @param p_reg    Instance.
 * @param pselrts  RTS pin number.
 * @param pselcts  CTS pin number.
 */
static inline void nrf_uart_hwfc_pins_set(NRF_UART_Type * p_reg,
                                            uint32_t        pselrts,
                                            uint32_t        pselcts);

/**
 * @brief Function for disconnecting flow control pins.
 *
 * @param p_reg    Instance.
 */
static inline void nrf_uart_hwfc_pins_disconnect(NRF_UART_Type * p_reg);

/**
 * @brief Function for reading RX data.
 *
 * @param p_reg    Instance.
 * @return         Received byte.
 */
static inline uint8_t nrf_uart_rxd_get(NRF_UART_Type * p_reg);

/**
 * @brief Function for setting Tx data.
 *
 * @param p_reg    Instance.
 * @param txd      Byte.
 */
static inline void nrf_uart_txd_set(NRF_UART_Type * p_reg, uint8_t txd);

/**
 * @brief Function for starting an UART task.
 *
 * @param p_reg    Instance.
 * @param task     Task.
 */
static inline void nrf_uart_task_trigger(NRF_UART_Type * p_reg, nrf_uart_task_t task);

/**
 * @brief Function for returning the address of a specific task register.
 *
 * @param p_reg Instance.
 * @param task  Task.
 *
 * @return      Task address.
 */
static inline uint32_t nrf_uart_task_address_get(NRF_UART_Type * p_reg, nrf_uart_task_t task);

/**
 * @brief Function for configuring UART.
 *
 * @param p_reg  Instance.
 * @param hwfc   Hardware flow control. Enabled if true.
 * @param parity Parity. Included if true.
 */
static inline void nrf_uart_configure(NRF_UART_Type   * p_reg,
                                            nrf_uart_parity_t parity,
                                            nrf_uart_hwfc_t   hwfc);

/**
 * @brief Function for setting UART baudrate.
 *
 * @param p_reg    Instance.
 * @param baudrate Baudrate.
 */
static inline void nrf_uart_baudrate_set(NRF_UART_Type   * p_reg, uint32_t baudrate);

#ifndef SUPPRESS_INLINE_IMPLEMENTATION
static inline void nrf_uart_event_clear(NRF_UART_Type * p_reg, nrf_uart_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event)) = 0x0UL;

}

static inline bool nrf_uart_event_check(NRF_UART_Type * p_reg, nrf_uart_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)event);
}

static inline uint32_t nrf_uart_event_address_get(NRF_UART_Type  * p_reg,
                                                    nrf_uart_event_t  event)
{
    return (uint32_t)((uint8_t *)p_reg + (uint32_t)event);
}

static inline void nrf_uart_int_enable(NRF_UART_Type * p_reg, uint32_t int_mask)
{

    p_reg->INTENSET = int_mask;

}

static inline bool nrf_uart_int_enable_check(NRF_UART_Type * p_reg, uint32_t int_mask)
{
    return (bool)(p_reg->INTENSET & int_mask);
}

static inline void nrf_uart_int_disable(NRF_UART_Type * p_reg, uint32_t int_mask)
{
    p_reg->INTENCLR = int_mask;
}

static inline uint32_t nrf_uart_errorsrc_get_and_clear(NRF_UART_Type * p_reg)
{
    uint32_t errsrc_mask = p_reg->ERRORSRC;
    p_reg->ERRORSRC = errsrc_mask;
    return errsrc_mask;
}

static inline void nrf_uart_enable(NRF_UART_Type * p_reg)
{
    p_reg->ENABLE = 4UL;
}

static inline void nrf_uart_disable(NRF_UART_Type * p_reg)
{
    p_reg->ENABLE = 0UL;
}

static inline void nrf_uart_txrx_pins_set(NRF_UART_Type * p_reg, uint32_t pseltxd, uint32_t pselrxd)
{

    p_reg->PSELTXD = (pseltxd);
    p_reg->PSELRXD = ( pselrxd);
}

static inline void nrf_uart_txrx_pins_disconnect(NRF_UART_Type * p_reg)
{
    nrf_uart_txrx_pins_set(p_reg, NRF_UART_PSEL_DISCONNECTED, NRF_UART_PSEL_DISCONNECTED);
}

static inline uint32_t nrf_uart_tx_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSELTXD;
}

static inline uint32_t nrf_uart_rx_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSELRXD;
}

static inline uint32_t nrf_uart_rts_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSELRTS;
}

static inline uint32_t nrf_uart_cts_pin_get(NRF_UART_Type * p_reg)
{
    return p_reg->PSELCTS;
}

static inline void nrf_uart_hwfc_pins_set(NRF_UART_Type * p_reg, uint32_t pselrts, uint32_t pselcts)
{
    p_reg->PSELRTS = pselrts;
    p_reg->PSELCTS = pselcts;
}

static inline void nrf_uart_hwfc_pins_disconnect(NRF_UART_Type * p_reg)
{
    nrf_uart_hwfc_pins_set(p_reg, NRF_UART_PSEL_DISCONNECTED, NRF_UART_PSEL_DISCONNECTED);
}

static inline uint8_t nrf_uart_rxd_get(NRF_UART_Type * p_reg)
{
    return p_reg->RXD;
}

static inline void nrf_uart_txd_set(NRF_UART_Type * p_reg, uint8_t txd)
{
 //SEGGER_RTT_printf(0,"Times %c\r\n",txd);
    p_reg->TXD = txd;

}

static inline void nrf_uart_task_trigger(NRF_UART_Type * p_reg, nrf_uart_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)p_reg + (uint32_t)task)) = 0x1UL;

}

static inline uint32_t nrf_uart_task_address_get(NRF_UART_Type * p_reg, nrf_uart_task_t task)
{
    return (uint32_t)p_reg + (uint32_t)task;
}

static inline void nrf_uart_configure(NRF_UART_Type   * p_reg,
                                            nrf_uart_parity_t parity,
                                            nrf_uart_hwfc_t   hwfc)
{
    p_reg->CONFIG = (uint32_t)parity | (uint32_t)hwfc;
}

static inline void nrf_uart_baudrate_set(NRF_UART_Type* p_reg, uint32_t baudrate)
{
    p_reg->BAUDRATE=baudrate;
}



static void _UART_Configure(UARTBaseAddress port , uint32_t clockfrequency,
                   Baudrate baudrate,DataLength length, StopBitType stopbit,
                   ParityType parity,bool fifoenable,ReceiveIntLevel receivelevel,
                   TranmitIntLevel transmitlevel,bool loopback,
                   IOBaseAddress ioport ,PinAndPinset txpin,PinAndPinset rxpin,
                   PinAndPinset cstpin,PinAndPinset rstpin)
{
    _UART_Start(port,both,false);
    nrf_uart_configure((NRF_UART_Type*)port,parity,NRF_UART_HWFC_DISABLED );
    nrf_uart_baudrate_set((NRF_UART_Type*)port,baudrate);
    _fifoenable=fifoenable;
    _rxbufferLength=(uint32_t)receivelevel;
    _txbufferLength=(uint32_t)transmitlevel;

    nrf_uart_txrx_pins_set((NRF_UART_Type*)port,(uint8_t)txpin,(uint8_t)rxpin);
    nrf_uart_hwfc_pins_set((NRF_UART_Type*)port,(uint8_t)rstpin,(uint8_t)cstpin);
    nrf_uart_enable((NRF_UART_Type*)port);
    _uart_enable=true;
    _UART_Start(port,both,true);

}
 uint8_t* getstepuart(UARTBaseAddress port)
 {
    switch (port)
      {
      case UART0_BASE:

       return(&_step_uart[uart0]);


      }
     return(0);
 }

  uint8_t* getflaguart(UARTBaseAddress port)
 {
    switch (port)
      {
      case UART0_BASE:

       return(&_f_send_uart[uart0]);


      }
     return(0);
 }
static bool _UART_Send(bool reset,UARTBaseAddress port , bool blocking ,uint8_t *data, uint32_t lengthofdata)
 {

    volatile int i;
    if (_tx_busy|_tx_suspend|!_tx_enalbe|!_uart_enable)
    {
        return (false);
    }
     if (reset==true)
    {
        *getstepuart(port)=0;
        *getflaguart(port)=false;

    }

    switch (*getstepuart(port))

      {
       case 0:
         //  SEGGER_RTT_printf(0,"uart %d\r\n",0);
             nrf_uart_txd_set((NRF_UART_Type*)port,*data);
           *getstepuart(port)=10;
           return(false);
       case 10:


          // SEGGER_RTT_printf(0,"uart %d\r\n",10);
           if  (*getflaguart(port)==true)
           {


            *getstepuart(port)=0;
            *getflaguart(port)=false;
            return(true);

           }
           return(false);

      }

    return (false);

 }

static bool _UART_Receive(UARTBaseAddress port , bool blocking ,uint8_t *data)
 {
     volatile int i;


     *data=nrf_uart_rxd_get((NRF_UART_Type*)port);

     return(true);

 }

static void _UART_IntConfigure(UARTBaseAddress port, UARTMISenum interrupt,
                           bool enable,uint32_t priority,bool controllerenable)
 {

    UART_intcontroller->Configure(UARTE0_UART0_IRQn,controllerenable,priority);

    if(enable)
     {

       nrf_uart_int_enable((NRF_UART_Type*)port,(uint32_t)interrupt);

     }
    else
     {

       nrf_uart_int_disable((NRF_UART_Type*)port,(uint32_t)interrupt);

     }
 }

static void _UART_IntClear(UARTBaseAddress port, UARTMISenum interrupt)
 {
   switch (interrupt)
   {
       case UART_INT_RT:

        nrf_uart_event_clear((NRF_UART_Type*)port,NRF_UART_EVENT_RXTO);

       case UART_INT_RX:

        nrf_uart_event_clear((NRF_UART_Type*)port,NRF_UART_EVENT_RXDRDY);


       case UART_INT_TX:

        nrf_uart_event_clear((NRF_UART_Type*)port,NRF_UART_EVENT_TXDRDY);

       case UART_INT_EE:

        nrf_uart_event_clear((NRF_UART_Type*)port,NRF_UART_EVENT_ERROR);

   }

 }

static uint32_t _UART_IntStatus(UARTBaseAddress port, UARTMISenum interrupt)
 {
       switch (interrupt)
   {
       case UART_INT_RT:

        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_RXTO));

       case UART_INT_RX:

        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_RXDRDY));


       case UART_INT_TX:

        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_TXDRDY));

       case UART_INT_EE:

        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_ERROR));
       case UART_INT_CTS :

        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_CTS));

       case UART_INT_NCTS :
        return(nrf_uart_event_check((NRF_UART_Type*)port,NRF_UART_EVENT_NCTS));

   }
return(-1);
 }

void _UART_Start(UARTBaseAddress port ,Typeofuart type,bool enable)
  {
     // SEGGER_RTT_printf(0,"Times %d\r\n",20);
    if (enable)
    {
         //  SEGGER_RTT_printf(0,"Times %d\r\n",70);
        if (type==Tx)
         {
          if(!_tx_enalbe)
            {
              nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTTX);
              _tx_enalbe=true;
            }
         }
         else if (type==Rx)
         {
          if(!_rx_enable)
            {
         nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTRX);
             _rx_enable=true;
            }
         }

         else
         {
          if(!_tx_enalbe)
            {
            //     SEGGER_RTT_printf(0,"Times %d\r\n",71);
              nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTTX);
              _tx_enalbe=true;
            }
          if(!_rx_enable)
            {
           //        SEGGER_RTT_printf(0,"Times %d\r\n",72);
         nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTRX);
             _rx_enable=true;
            }

         }
    }
    else
    {
        // SEGGER_RTT_printf(0,"Times %d\r\n",110);
         if (type==Tx)
         {
          if(_tx_enalbe)
            {

             nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STOPTX);
             _tx_enalbe=false;
            }
         }
         else if(type==Rx)
         {
          if(_rx_enable)
            {
             nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STOPRX);
             _rx_enable=false;
            }
         }
         else
         {
            if(_tx_enalbe)
            {
             nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STOPTX);
             _tx_enalbe=false;
            }
            if(_rx_enable)
            {
             nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STOPRX);
             _rx_enable=false;
            }


         }

    }

  }

  void _UART_Suspend(UARTBaseAddress port ,Typeofuart type,bool enable)
  {
      if (enable)
    {
        if (type==Tx)
         {
          if(_tx_suspend)
            {
              nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTTX);
            _tx_suspend=false;
            }
         }
         else
         {
          if(_rx_suspend)
            {
              nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_STARTRX);
              _rx_suspend=false;
            }
         }

    }
    else
    {
             nrf_uart_task_trigger((NRF_UART_Type*)port,NRF_UART_TASK_SUSPEND);
             _tx_suspend=true ;
             _rx_suspend=true ;

    }
  }

   void _UART_ReceiveIntHandler ( void(*Handler)(UARTBaseAddress port) )
    {
      _uart_raiseevent=Handler;

    }


  void UartHandler(void)
  {
      volatile  uint32_t _temp ;

      _temp=nrf_uart_errorsrc_get_and_clear((NRF_UART_Type*)UART0_BASE);

        if (_UART_IntStatus(UART0_BASE,UART_INT_CTS))
      {


           _UART_IntClear(UART0_BASE,UART_INT_CTS);

      }

        if (_UART_IntStatus(UART0_BASE,UART_INT_NCTS))
      {


           _UART_IntClear(UART0_BASE,UART_INT_NCTS);

      }

      if (_UART_IntStatus(UART0_BASE,UART_INT_TX))
      {
         _f_send_uart[uart0]=true;
          _tx_busy=false;
           _UART_IntClear(UART0_BASE,UART_INT_TX);

      }
       if (_UART_IntStatus(UART0_BASE,UART_INT_RX))
      {
         _uart_raiseevent(UART0_BASE);
          _UART_IntClear(UART0_BASE,UART_INT_RX);

      }

         if (_UART_IntStatus(UART0_BASE,UART_INT_RT))
      {

          _UART_IntClear(UART0_BASE,UART_INT_RT);
          _uart_enable=false;

      }


       if (_UART_IntStatus(UART0_BASE,UART_INT_EE))
      {

          _UART_IntClear(UART0_BASE,UART_INT_EE);

      if  (_temp&1)
        {

        }

      if ((_temp&2)>>1)
        {

        }
      if ((_temp&4)>>2)
        {

        }
      if ((_temp&8)>>3)
        {

        }
      }
  }


void CreateUARTDevice(UARTDevice* device, InterruptController* intcontroller,
                      UARTBaseAddress port , uint32_t clockfrequency,
                      Baudrate baudrate,DataLength length, StopBitType stopbit,
                      ParityType parity,bool fifoenable,ReceiveIntLevel receivelevel,
                      TranmitIntLevel transmitlevel,bool loopback,
                      IOBaseAddress ioport ,PinAndPinset txpin,PinAndPinset rxpin,
                      PinAndPinset cstpin,PinAndPinset rstpin)

{
  UART_intcontroller=intcontroller;

    _UART_Configure(port,clockfrequency,baudrate,length,stopbit,parity,
                    fifoenable,receivelevel,transmitlevel,loopback,ioport,
                    txpin,rxpin,cstpin,rstpin);


    _UART_IntConfigure(port,UART_INT_EE|UART_INT_NCTS
                       |UART_INT_RT|UART_INT_RX|UART_INT_TX,true,0,true);

    device->UART_Receive=_UART_Receive;

    device->UART_Send=_UART_Send;

    device->UART_ReceiveIntHandler=_UART_ReceiveIntHandler;



    UART_intcontroller->IntHandler(UARTE0_UART0_IRQn,UartHandler);

}




#endif //SUPPRESS_INLINE_IMPLEMENTATION
/** @} */
#endif //NRF_UART_H__

