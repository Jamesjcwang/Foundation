
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

#include "library\Physic\Header\I_IOTE.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
* @defgroup nrf_gpiote_abs GPIOTE abstraction
* @{
* @ingroup nrf_gpiote
* @brief GPIOTE abstraction for configuration of channels.
*/


 /**
 * @enum nrf_gpiote_polarity_t
 * @brief Polarity for the GPIOTE channel.
 */
typedef enum
{
  NRF_GPIOTE_POLARITY_LOTOHI = GPIOTE_CONFIG_POLARITY_LoToHi,       ///<  Low to high.
  NRF_GPIOTE_POLARITY_HITOLO = GPIOTE_CONFIG_POLARITY_HiToLo,       ///<  High to low.
  NRF_GPIOTE_POLARITY_TOGGLE = GPIOTE_CONFIG_POLARITY_Toggle        ///<  Toggle.
} nrf_gpiote_polarity_t;


 /**
 * @enum nrf_gpiote_outinit_t
 * @brief Initial output value for the GPIOTE channel.
 */
typedef enum
{
  NRF_GPIOTE_INITIAL_VALUE_LOW  = GPIOTE_CONFIG_OUTINIT_Low,       ///<  Low to high.
  NRF_GPIOTE_INITIAL_VALUE_HIGH = GPIOTE_CONFIG_OUTINIT_High       ///<  High to low.
} nrf_gpiote_outinit_t;

/**
 * @brief Tasks.
 */
typedef enum /*lint -save -e30 -esym(628,__INTADDR__) */
{
    NRF_GPIOTE_TASKS_OUT_0     = offsetof(NRF_GPIOTE_Type, TASKS_OUT[0]), /**< Out task 0.*/
    NRF_GPIOTE_TASKS_OUT_1     = offsetof(NRF_GPIOTE_Type, TASKS_OUT[1]), /**< Out task 1.*/
    NRF_GPIOTE_TASKS_OUT_2     = offsetof(NRF_GPIOTE_Type, TASKS_OUT[2]), /**< Out task 2.*/
    NRF_GPIOTE_TASKS_OUT_3     = offsetof(NRF_GPIOTE_Type, TASKS_OUT[3]), /**< Out task 3.*/
    /*lint -restore*/
} nrf_gpiote_tasks_t;

/**
 * @brief Events.
 */
typedef enum /*lint -save -e30 -esym(628,__INTADDR__) */
{
    NRF_GPIOTE_EVENTS_IN_0     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[0]), /**< In event 0.*/
    NRF_GPIOTE_EVENTS_IN_1     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[1]), /**< In event 1.*/
    NRF_GPIOTE_EVENTS_IN_2     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[2]), /**< In event 2.*/
    NRF_GPIOTE_EVENTS_IN_3     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[3]), /**< In event 3.*/
    NRF_GPIOTE_EVENTS_IN_4     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[4]), /**< In event 4.*/
    NRF_GPIOTE_EVENTS_IN_5     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[5]), /**< In event 5.*/
    NRF_GPIOTE_EVENTS_IN_6     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[6]), /**< In event 6.*/
    NRF_GPIOTE_EVENTS_IN_7     = offsetof(NRF_GPIOTE_Type, EVENTS_IN[7]), /**< In event 7.*/
    NRF_GPIOTE_EVENTS_PORT     = offsetof(NRF_GPIOTE_Type, EVENTS_PORT), /**<  Port event.*/
    /*lint -restore*/
} nrf_gpiote_events_t;

/**
 * @enum nrf_gpiote_int_t
 * @brief GPIOTE interrupts.
 */
typedef enum
{
    NRF_GPIOTE_INT_IN0_MASK  = GPIOTE_INTENSET_IN0_Msk,  /**< GPIOTE interrupt from IN0. */
    NRF_GPIOTE_INT_IN1_MASK  = GPIOTE_INTENSET_IN1_Msk,  /**< GPIOTE interrupt from IN1. */
    NRF_GPIOTE_INT_IN2_MASK  = GPIOTE_INTENSET_IN2_Msk,  /**< GPIOTE interrupt from IN2. */
    NRF_GPIOTE_INT_IN3_MASK  = GPIOTE_INTENSET_IN3_Msk,  /**< GPIOTE interrupt from IN3. */
    NRF_GPIOTE_INT_PORT_MASK = (int)GPIOTE_INTENSET_PORT_Msk, /**< GPIOTE interrupt from PORT event. */
} nrf_gpiote_int_t;

#define NRF_GPIOTE_INT_IN_MASK (NRF_GPIOTE_INT_IN0_MASK | NRF_GPIOTE_INT_IN1_MASK |\
                                NRF_GPIOTE_INT_IN2_MASK | NRF_GPIOTE_INT_IN3_MASK)
/**
 * @brief Function for activating a specific GPIOTE task.
 *
 * @param[in]  task Task.
 */
__STATIC_INLINE void nrf_gpiote_task_set(nrf_gpiote_tasks_t task);

/**
 * @brief Function for getting the address of a specific GPIOTE task.
 *
 * @param[in] task Task.
 *
 * @returns Address.
 */
__STATIC_INLINE uint32_t nrf_gpiote_task_addr_get(nrf_gpiote_tasks_t task);

/**
 * @brief Function for getting the state of a specific GPIOTE event.
 *
 * @param[in] event Event.
 */
__STATIC_INLINE bool nrf_gpiote_event_is_set(nrf_gpiote_events_t event);

/**
 * @brief Function for clearing a specific GPIOTE event.
 *
 * @param[in] event Event.
 */
__STATIC_INLINE void nrf_gpiote_event_clear(nrf_gpiote_events_t event);

/**
 * @brief Function for getting the address of a specific GPIOTE event.
 *
 * @param[in] event Event.
 *
 * @return Address
 */
__STATIC_INLINE uint32_t nrf_gpiote_event_addr_get(nrf_gpiote_events_t event);

/**@brief Function for enabling interrupts.
 *
 * @param[in]  mask          Interrupt mask to be enabled.
 */
__STATIC_INLINE void nrf_gpiote_int_enable(uint32_t mask);

/**@brief Function for disabling interrupts.
 *
 * @param[in]  mask          Interrupt mask to be disabled.
 */
__STATIC_INLINE void nrf_gpiote_int_disable(uint32_t mask);

/**@brief Function for checking if interrupts are enabled.
 *
 * @param[in]  mask          Mask of interrupt flags to check.
 *
 * @return                   Mask with enabled interrupts.
 */
__STATIC_INLINE uint32_t nrf_gpiote_int_is_enabled(uint32_t mask);

/**@brief Function for enabling a GPIOTE event.
 *
 * @param[in]  idx        Task-Event index.
 */
__STATIC_INLINE void nrf_gpiote_event_enable(uint32_t idx);

/**@brief Function for disabling a GPIOTE event.
 *
 * @param[in]  idx        Task-Event index.
 */
__STATIC_INLINE void nrf_gpiote_event_disable(uint32_t idx);

/**@brief Function for configuring a GPIOTE event.
 *
 * @param[in]  idx        Task-Event index.
 * @param[in]  pin        Pin associated with event.
 * @param[in]  polarity   Transition that should generate an event.
 */
__STATIC_INLINE void nrf_gpiote_event_configure(uint32_t idx, uint32_t pin,
                                                nrf_gpiote_polarity_t polarity);

/**@brief Function for getting the pin associated with a GPIOTE event.
 *
 * @param[in]  idx        Task-Event index.
 *
 * @return Pin number.
 */
__STATIC_INLINE uint32_t nrf_gpiote_event_pin_get(uint32_t idx);

/**@brief Function for getting the polarity associated with a GPIOTE event.
 *
 * @param[in]  idx        Task-Event index.
 *
 * @return Polarity.
 */
__STATIC_INLINE nrf_gpiote_polarity_t nrf_gpiote_event_polarity_get(uint32_t idx);

/**@brief Function for enabling a GPIOTE task.
 *
 * @param[in]  idx        Task-Event index.
 */
__STATIC_INLINE void nrf_gpiote_task_enable(uint32_t idx);

/**@brief Function for disabling a GPIOTE task.
 *
 * @param[in]  idx        Task-Event index.
 */
__STATIC_INLINE void nrf_gpiote_task_disable(uint32_t idx);

/**@brief Function for configuring a GPIOTE task.
 * @note  Function is not configuring mode field so task is disabled after this function is called.
 *
 * @param[in]  idx        Task-Event index.
 * @param[in]  pin        Pin associated with event.
 * @param[in]  polarity   Transition that should generate an event.
 * @param[in]  init_val   Initial value of pin.
 */
__STATIC_INLINE void nrf_gpiote_task_configure(uint32_t idx, uint32_t pin,
                                               nrf_gpiote_polarity_t polarity,
                                               nrf_gpiote_outinit_t  init_val);

/**@brief Function for forcing a specific state on the pin connected to GPIOTE.
 *
 * @param[in]  idx        Task-Event index.
 * @param[in]  init_val   Pin state.
 */
__STATIC_INLINE void nrf_gpiote_task_force(uint32_t idx, nrf_gpiote_outinit_t init_val);

/**@brief Function for resetting a GPIOTE task event configuration to the default state.
 *
 * @param[in]  idx        Task-Event index.
 */
__STATIC_INLINE void nrf_gpiote_te_default(uint32_t idx);


__STATIC_INLINE void nrf_gpiote_task_set(nrf_gpiote_tasks_t task)
{
    *(__IO uint32_t *)((uint32_t)NRF_GPIOTE + task) = 0x1UL;
}

__STATIC_INLINE uint32_t nrf_gpiote_task_addr_get(nrf_gpiote_tasks_t task)
{
    return ((uint32_t)NRF_GPIOTE + task);
}

__STATIC_INLINE bool nrf_gpiote_event_is_set(nrf_gpiote_events_t event)
{
    return (*(uint32_t *)nrf_gpiote_event_addr_get(event) == 0x1UL) ? true : false;
}

__STATIC_INLINE void nrf_gpiote_event_clear(nrf_gpiote_events_t event)
{
    *(uint32_t *)nrf_gpiote_event_addr_get(event) = 0;

    volatile uint32_t dummy = *((volatile uint32_t *)nrf_gpiote_event_addr_get(event));
    (void)dummy;

}

__STATIC_INLINE uint32_t nrf_gpiote_event_addr_get(nrf_gpiote_events_t event)
{
    return ((uint32_t)NRF_GPIOTE + event);
}

__STATIC_INLINE void nrf_gpiote_int_enable(uint32_t mask)
{
    NRF_GPIOTE->INTENSET = mask;
}

__STATIC_INLINE void nrf_gpiote_int_disable(uint32_t mask)
{
    NRF_GPIOTE->INTENCLR = mask;
}

__STATIC_INLINE uint32_t nrf_gpiote_int_is_enabled(uint32_t mask)
{
    return (NRF_GPIOTE->INTENSET & mask);
}

__STATIC_INLINE void nrf_gpiote_event_enable(uint32_t idx)
{
   NRF_GPIOTE->CONFIG[idx] |= GPIOTE_CONFIG_MODE_Event;
}

__STATIC_INLINE void nrf_gpiote_event_disable(uint32_t idx)
{
   NRF_GPIOTE->CONFIG[idx] &= ~GPIOTE_CONFIG_MODE_Event;
}

__STATIC_INLINE void nrf_gpiote_event_configure(uint32_t idx, uint32_t pin, nrf_gpiote_polarity_t polarity)
{
  NRF_GPIOTE->CONFIG[idx] &= ~(GPIOTE_CONFIG_PSEL_Msk | GPIOTE_CONFIG_POLARITY_Msk);
  NRF_GPIOTE->CONFIG[idx] |= ((pin << GPIOTE_CONFIG_PSEL_Pos) & GPIOTE_CONFIG_PSEL_Msk) |
                              ((polarity << GPIOTE_CONFIG_POLARITY_Pos) & GPIOTE_CONFIG_POLARITY_Msk);
}

__STATIC_INLINE uint32_t nrf_gpiote_event_pin_get(uint32_t idx)
{
    return ((NRF_GPIOTE->CONFIG[idx] & GPIOTE_CONFIG_PSEL_Msk) >> GPIOTE_CONFIG_PSEL_Pos);
}

__STATIC_INLINE nrf_gpiote_polarity_t nrf_gpiote_event_polarity_get(uint32_t idx)
{
    return (nrf_gpiote_polarity_t)((NRF_GPIOTE->CONFIG[idx] & GPIOTE_CONFIG_POLARITY_Msk) >> GPIOTE_CONFIG_POLARITY_Pos);
}

__STATIC_INLINE void nrf_gpiote_task_enable(uint32_t idx)
{
    uint32_t final_config = NRF_GPIOTE->CONFIG[idx] | GPIOTE_CONFIG_MODE_Task;
    /* Workaround for the OUTINIT PAN. When nrf_gpiote_task_config() is called a glitch happens
    on the GPIO if the GPIO in question is already assigned to GPIOTE and the pin is in the
    correct state in GPIOTE but not in the OUT register. */
    /* Configure channel to Pin31, not connected to the pin, and configure as a tasks that will set it to proper level */
    NRF_GPIOTE->CONFIG[idx] = final_config | ((31 << GPIOTE_CONFIG_PSEL_Pos) & GPIOTE_CONFIG_PSEL_Msk);
    __NOP();
    __NOP();
    __NOP();
    NRF_GPIOTE->CONFIG[idx] = final_config;
}

__STATIC_INLINE void nrf_gpiote_task_disable(uint32_t idx)
{
    NRF_GPIOTE->CONFIG[idx] &= ~GPIOTE_CONFIG_MODE_Task;
}

__STATIC_INLINE void nrf_gpiote_task_configure(uint32_t idx, uint32_t pin,
                                                nrf_gpiote_polarity_t polarity,
                                                nrf_gpiote_outinit_t  init_val)
{
  NRF_GPIOTE->CONFIG[idx] &= ~(GPIOTE_CONFIG_PSEL_Msk |
                               GPIOTE_CONFIG_POLARITY_Msk |
                               GPIOTE_CONFIG_OUTINIT_Msk);

  NRF_GPIOTE->CONFIG[idx] |= ((pin << GPIOTE_CONFIG_PSEL_Pos) & GPIOTE_CONFIG_PSEL_Msk) |
                             ((polarity << GPIOTE_CONFIG_POLARITY_Pos) & GPIOTE_CONFIG_POLARITY_Msk) |
                             ((init_val << GPIOTE_CONFIG_OUTINIT_Pos) & GPIOTE_CONFIG_OUTINIT_Msk);
}

__STATIC_INLINE void nrf_gpiote_task_force(uint32_t idx, nrf_gpiote_outinit_t init_val)
{
    NRF_GPIOTE->CONFIG[idx] = (NRF_GPIOTE->CONFIG[idx] & ~GPIOTE_CONFIG_OUTINIT_Msk)
                              | ((init_val << GPIOTE_CONFIG_OUTINIT_Pos) & GPIOTE_CONFIG_OUTINIT_Msk);
}

__STATIC_INLINE void nrf_gpiote_te_default(uint32_t idx)
{
    NRF_GPIOTE->CONFIG[idx] = 0;
}

void (*IO_Inthandler[8])(void);


void _IO_IntConfigure(IOTEBaseAddress port ,enum_pin_iote pin, enum_channel_iote channel
                      ,enum_polarity_iote polarity,void (*handler)(void))
{

  nrf_gpiote_int_enable(1<<channel);
  nrf_gpiote_event_configure(channel,pin,polarity);
  nrf_gpiote_event_enable(channel);
  IO_Inthandler[channel]=handler;



}

void GPIOTE_Handler(void)
{


    if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_0)==true)
    {
SEGGER_RTT_printf(0,"Int %d\r\n",0);
        IO_Inthandler[0]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_0);
    }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_1)==true)
    {
        IO_Inthandler[1]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_1);
    }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_2)==true)
    {
        IO_Inthandler[2]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_2);
    }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_3)==true)
     {
        IO_Inthandler[3]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_3);
     }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_4)==true)
     {
        IO_Inthandler[4]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_4);
     }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_5)==true)
     {
        IO_Inthandler[5]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_5);
     }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_6)==true)
     {
        IO_Inthandler[6]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_6);
     }
    else if (nrf_gpiote_event_is_set(NRF_GPIOTE_EVENTS_IN_7)==true)
     {
        IO_Inthandler[7]();
        nrf_gpiote_event_clear(NRF_GPIOTE_EVENTS_IN_7);
     }



}


