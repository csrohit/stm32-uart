#include <stm32f1xx.h>

#ifndef __DMA_H__
#define __DMA_H__
typedef enum
{
    DISABLE,
    ENABLE
} dma_channel_cmd_t;

inline void dma_channel_cmd(DMA_Channel_TypeDef *ch, dma_channel_cmd_t cmd)
{
    if(cmd == ENABLE){
        ch->CCR |= DMA_CCR_EN;
    }else{
        ch->CCR &= ~DMA_CCR_EN;
    }
}

inline void dma_channel_reload(DMA_Channel_TypeDef *ch, uint32_t new_count){
    ch->CNDTR = new_count;
}

#endif