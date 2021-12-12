/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/20  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_hmc5883l_basic.h"
#include "driver_hmc5883l_shot.h"
#include "driver_hmc5883l_register_test.h"
#include "driver_hmc5883l_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
uint16_t g_len;            /**< uart buffer length */

/**
 * @brief     hmc5883l full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t hmc5883l(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            hmc5883l_info_t info;
            
            /* print hmc5883l info */
            hmc5883l_info(&info);
            hmc5883l_interface_debug_print("hmc5883l: chip is %s.\n", info.chip_name);
            hmc5883l_interface_debug_print("hmc5883l: manufacturer is %s.\n", info.manufacturer_name);
            hmc5883l_interface_debug_print("hmc5883l: interface is %s.\n", info.interface);
            hmc5883l_interface_debug_print("hmc5883l: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            hmc5883l_interface_debug_print("hmc5883l: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            hmc5883l_interface_debug_print("hmc5883l: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            hmc5883l_interface_debug_print("hmc5883l: max current is %0.2fmA.\n", info.max_current_ma);
            hmc5883l_interface_debug_print("hmc5883l: max temperature is %0.1fC.\n", info.temperature_max);
            hmc5883l_interface_debug_print("hmc5883l: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            hmc5883l_interface_debug_print("hmc5883l: SCL connected to GPIOB PIN8.\n");
            hmc5883l_interface_debug_print("hmc5883l: SDA connected to GPIOB PIN9.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show hmc5883l help */
            
            help:
            
            hmc5883l_interface_debug_print("hmc5883l -i\n\tshow hmc5883l chip and driver information.\n");
            hmc5883l_interface_debug_print("hmc5883l -h\n\tshow hmc5883l help.\n");
            hmc5883l_interface_debug_print("hmc5883l -p\n\tshow hmc5883l pin connections of the current board.\n");
            hmc5883l_interface_debug_print("hmc5883l -t reg\n\trun hmc5883l register test.\n");
            hmc5883l_interface_debug_print("hmc5883l -t read\n\trun hmc5883l read test.times means test times.\n");
            hmc5883l_interface_debug_print("hmc5883l -c read <times>\n\trun hmc5883l read function.times means read times.\n");
            hmc5883l_interface_debug_print("hmc5883l -c shot <times>\n\trun hmc5883l shot function.times means read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 3)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                /* run reg test */
                if (hmc5883l_register_test())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 4)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                /* run read test */
                if (hmc5883l_read_test(atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float m_gauss[3];
                
                res = hmc5883l_basic_init();
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    hmc5883l_interface_delay_ms(1000);
                    res = hmc5883l_basic_read((float *)m_gauss);
                    if (res)
                    {
                        hmc5883l_basic_deinit();
                        
                        return 1;
                    }
                    hmc5883l_interface_debug_print("hmc5883l: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
                    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
                    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
                }
                hmc5883l_basic_deinit();
                
                return 0;
            }
            /* shot function */
            else if (strcmp("shot", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float m_gauss[3];
                
                times = atoi(argv[3]);
                res = hmc5883l_shot_init();
                if (res)
                {
                    return 1;
                }
                for (i=0; i<times; i++)
                {
                    hmc5883l_interface_delay_ms(1000);
                    res = hmc5883l_shot_read((float *)m_gauss);
                    if (res)
                    {
                        hmc5883l_shot_deinit();
                        
                        return 1;
                    }
                    hmc5883l_interface_debug_print("hmc5883l: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
                    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
                    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
                }
                hmc5883l_shot_deinit();
                
                return 0;
                
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register hmc5883l fuction */
    shell_init();
    shell_register("hmc5883l", hmc5883l);
    uart1_print("hmc5883l: welcome to libdriver hmc5883l.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("hmc5883l: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("hmc5883l: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("hmc5883l: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("hmc5883l: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("hmc5883l: param is invalid.\n");
            }
            else
            {
                uart1_print("hmc5883l: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
