/**
 * @file dma_channel.hpp
 * @author Rohit Nimkar (nehalnimkar@gmail.com)
 * @brief Declaration of functionality related to dma channel
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

#include "dma.hpp"
#include <stm32f1xx.h>
#pragma once

class DMA_Channel
{
private:
public:
    // constexpr static
    typedef uint8_t dir_t;
    constexpr static dir_t PeripheralToMemory = 0;
    constexpr static dir_t MemoryToPeripheral = 1;

    typedef uint8_t mem_peri_size_t;
    constexpr static mem_peri_size_t BIT_8 = 0x00;
    constexpr static mem_peri_size_t BIT_16 = 0x01;
    constexpr static mem_peri_size_t BIT_32 = 0x02;

    typedef uint8_t prio_t;
    constexpr static prio_t LOW = 0x00;
    constexpr static prio_t MEDIUM = 0x01;
    constexpr static prio_t HIGH = 0x02;
    constexpr static prio_t VERYHIGH = 0x03;

    typedef uint32_t intr_t;
    constexpr static intr_t TransferComplete = DMA_CCR_TCIE;
    constexpr static intr_t HalfTransferComplete = DMA_CCR_HTIE;
    constexpr static intr_t TransferError = DMA_CCR_TEIE;

private:
    /**
     * @brief Channel Configuration register
     */
    volatile uint32_t CCR;

    /**
     * @brief Number of data to be transferred (0 up to 65535).
     * This register can only be written when the channel is disabled.
     * Once the channel is enabled, this register is read-only, indicating the remaining bytes to be transmitted.
     *
     * This register decrements after each DMA transfer.
     * Once the transfer is completed, this register can either stay at zero or be reloaded automatically by the value previously programmed if the channel is configured in auto- reload mode.
     *
     * If this register is zero, no transaction can be served whether the channel is enabled or not.
     */
    volatile uint32_t CNDTR;

    /**
     * @brief Channel Peripheral address register
     * Base address of the peripheral data register from/to which the data will be read/written.
     * When PSIZE is 01 (16-bit), the PA[0] bit is ignored. Access is automatically aligned to a half- word address.
     * When PSIZE is 10 (32-bit), PA[1:0] are ignored. Access is automatically aligned to a word address.
     *
     */
    volatile uint32_t *CPAR;

    /**
     * @brief Channel Memory address register
     * Base address of the memory area from/to which the data will be read/written.
     * When MSIZE is 01 (16-bit), the MA[0] bit is ignored. Access is automatically aligned to a half-word address.
     * When MSIZE is 10 (32-bit), MA[1:0] are ignored. Access is automatically aligned to a word address.
     *
     */
    volatile uint32_t *CMAR;

public:

    inline static DMA_Channel * get_instance(DMA_Channel_TypeDef* dma_channel_base){
        return static_cast<DMA_Channel *>(static_cast<void *>(dma_channel_base));
    }
    constexpr inline void reload(uint16_t value)
    {
        CNDTR = 0x0000ffff & value;
    }

    inline void start()
    {
        CCR |= 0x01;
    }
    inline void stop()
    {
        this->CCR |= DMA_CCR_EN;
    }

    inline void set_peripheral_address(uint32_t *address)
    {
        this->CPAR = address;
    }

    inline void set_memory_address(uint32_t *address)
    {
        this->CMAR = address;
    }

    inline void enable_interrupt(intr_t interrupt)
    {
        uint32_t bits = 0;
        if ((interrupt & TransferComplete) > 0)
        {
            bits |= DMA_CCR_TCIE;
        }

        if ((interrupt & TransferError) > 0)
        {
            bits |= DMA_CCR_TEIE;
        }

        if ((interrupt & HalfTransferComplete) > 0)
        {
            bits |= DMA_CCR_HTIE;
        }

        this->CCR |= bits;
    }

    inline void disable_interrupt(intr_t interrupt)
    {
        uint32_t bits = 0;
        if (interrupt & TransferComplete)
        {
            bits |= DMA_CCR_TCIE;
        }

        if (interrupt & TransferError)
        {
            bits |= DMA_CCR_TEIE;
        }

        if (interrupt & HalfTransferComplete)
        {
            bits |= DMA_CCR_HTIE;
        }

        this->CCR &= ~bits;
    }

    inline void set_transfer_direction(dir_t direction)
    {
        if (direction == PeripheralToMemory)
        {
            this->CCR &= ~DMA_CCR_DIR;
        }
        else
        {
            this->CCR |= DMA_CCR_DIR;
        }
    }

    inline void enableCircularMode()
    {
        this->CCR |= DMA_CCR_CIRC;
    }

    inline void disableCircularMode()
    {
        this->CCR &= ~DMA_CCR_CIRC;
    }

    inline void enablePeripheralIncrementMode()
    {
        this->CCR |= DMA_CCR_PINC;
    }

    inline void disablePeripheralIncrementMode()
    {
        this->CCR &= ~DMA_CCR_PINC;
    }

    inline void enableMemoryIncrementMode()
    {
        this->CCR |= DMA_CCR_MINC;
    }

    inline void disableMemoryIncrementMode()
    {
        this->CCR &= ~DMA_CCR_MINC;
    }

    inline void set_peripheral_size(mem_peri_size_t size)
    {
        this->CCR &= DMA_CCR_PSIZE;
        this->CCR |= (size & 0b11) << DMA_CCR_PSIZE_Pos;
    }

    inline void set_memory_size(mem_peri_size_t size)
    {
        this->CCR &= DMA_CCR_MSIZE;
        this->CCR |= (size & 0b11) << DMA_CCR_MSIZE_Pos;
    }

    inline void set_priority(prio_t prio)
    {
        this->CCR &= ~DMA_CCR_PL;
        this->CCR |= (prio & 0b11) << DMA_CCR_PL_Pos;
    }
};
