/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-14     muaxiaohei   first version
 */

#include <rtthread.h>
#include "drv_common.h"

void rt_hw_us_delay(rt_uint32_t us)
{
    uint64_t total_delay_ticks, us_ticks, start, now, delta, reload;

    start = SysTick->CNT;
    reload = SysTick->CMP;
    us_ticks = SystemCoreClock / 8000000UL;
    total_delay_ticks = (uint32_t)us * us_ticks;
    RT_ASSERT(total_delay_ticks < reload);

    do{
        now = SysTick->CNT;
        delta = start > now ? start - now : reload + start - now;
    }while(delta < total_delay_ticks);
}
