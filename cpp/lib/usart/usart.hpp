/**
 * @file usart.hpp
 * @author Rohit Nimkar (nehalnimkar@gmail.com)
 * @brief Declaration of functionality related to USART
 * @version 1.2
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 *
 */


#pragma once
#include <stm32f1xx.h>
#include <system.hpp>

class USART
{
public:
    typedef enum USART_Peripheral : uint32_t
    {
        Transmitter = USART_CR1_TE,
        Receiver = USART_CR1_RE,
        Usart = USART_CR1_UE
    } peripheral_t;

    typedef enum USART_PeripheralDMARequest : uint32_t
    {
        TransmitterRequest = USART_CR3_DMAT,
        ReceiverRequest = USART_CR3_DMAR
    } dma_req_t;

    typedef enum USART_Interrupt : uint32_t
    {
        TX_Complete = USART_CR1_TCIE,
        TX_Data_Register_Empty = USART_CR1_TXEIE,
        RX_Date_Ready = USART_CR1_RXNEIE,
    } intr_t;

private:
    volatile uint32_t SR;   /*!< USART Status register,                   Address offset: 0x00 */
    volatile uint32_t DR;   /*!< USART Data register,                     Address offset: 0x04 */
    volatile uint32_t BRR;  /*!< USART Baud rate register,                Address offset: 0x08 */
    volatile uint32_t CR1;  /*!< USART Control register 1,                Address offset: 0x0C */
    volatile uint32_t CR2;  /*!< USART Control register 2,                Address offset: 0x10 */
    volatile uint32_t CR3;  /*!< USART Control register 3,                Address offset: 0x14 */
    volatile uint32_t GTPR; /*!< USART Guard time and prescaler register, Address offset: 0x18 */
public:
    static USART *get_instance(USART_TypeDef *usart_base)
    {
        return static_cast<USART *>(static_cast<void *>(usart_base));
    }

    inline void set_baudrate(uint32_t baudrate)
    {
        uint32_t baud = (uint32_t)(Core::clock / baudrate);
        BRR = baud;
    }

    inline void enable_peripheral(peripheral_t peripheral)
    {
        CR1 |= peripheral;
    }

    inline void disable_peripheral(peripheral_t peripheral)
    {
        CR1 &= ~peripheral;
    }

    inline void start()
    {
        CR1 |= peripheral_t::Usart;
    }

    inline void stop()
    {
        CR1 &= ~peripheral_t::Usart;
    }

    inline void enable_interrupt(intr_t interrupt)
    {
        CR1 |= interrupt;
    }

    inline void disable_interrupt(intr_t interrupt)
    {
        CR1 &= ~interrupt;
    }

    inline void enable_dma_request(dma_req_t dma_request)
    {
        CR3 |= dma_request;
    }

    inline void disable_dma_request(dma_req_t dma_request)
    {
        CR3 &= ~dma_request;
    }

    /**
     * @brief Transmit character
     * If data register is not empty then character will be transmitted after current transaction
     * @param ch character to be transmitted
     */
    inline void tx_char(uint8_t ch)
    {
        while (!(SR & USART_SR_TXE))
            ;
        DR = ch;
    }

    /**
     * @brief Transmit string 
     *
     * @param str pointer to NULL terminated string
     */
    inline void tx_str(const uint8_t *str)
    {
        while (*str)
        {
            tx_char(*str);
            str++;
        }
    }

    /**
     * @brief Receive a character
     * The function will wait for the receiver to receive a charater and then return the received data
     * @return uint8_t 
     */
    inline uint8_t rx_char(){
        while(!(SR & USART_SR_RXNE));
        return DR;
    }
};
