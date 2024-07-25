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
 * @file      driver_hmc5883l_read_test.c
 * @brief     driver hmc5883l read test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-20
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/20  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/02  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_hmc5883l_read_test.h"

static hmc5883l_handle_t gs_handle;        /**< hmc5883l handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t hmc5883l_read_test(uint32_t times)
{
    uint8_t res; 
    uint8_t i;
    int16_t raw[3];
    float m_gauss[3];
    hmc5883l_info_t info;
    
    /* link interface function */
    DRIVER_HMC5883L_LINK_INIT(&gs_handle, hmc5883l_handle_t);
    DRIVER_HMC5883L_LINK_IIC_INIT(&gs_handle, hmc5883l_interface_iic_init);
    DRIVER_HMC5883L_LINK_IIC_DEINIT(&gs_handle, hmc5883l_interface_iic_deinit);
    DRIVER_HMC5883L_LINK_IIC_READ(&gs_handle, hmc5883l_interface_iic_read);
    DRIVER_HMC5883L_LINK_IIC_WRITE(&gs_handle, hmc5883l_interface_iic_write);
    DRIVER_HMC5883L_LINK_DELAY_MS(&gs_handle, hmc5883l_interface_delay_ms);
    DRIVER_HMC5883L_LINK_DEBUG_PRINT(&gs_handle, hmc5883l_interface_debug_print);
    
    /* get hmc5883l info */
    res = hmc5883l_info(&info);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip information */
        hmc5883l_interface_debug_print("hmc5883l: chip is %s.\n", info.chip_name);
        hmc5883l_interface_debug_print("hmc5883l: manufacturer is %s.\n", info.manufacturer_name);
        hmc5883l_interface_debug_print("hmc5883l: interface is %s.\n", info.interface);
        hmc5883l_interface_debug_print("hmc5883l: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        hmc5883l_interface_debug_print("hmc5883l: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        hmc5883l_interface_debug_print("hmc5883l: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        hmc5883l_interface_debug_print("hmc5883l: max current is %0.2fmA.\n", info.max_current_ma);
        hmc5883l_interface_debug_print("hmc5883l: max temperature is %0.1fC.\n", info.temperature_max);
        hmc5883l_interface_debug_print("hmc5883l: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* hmc5883l init */
    res = hmc5883l_init(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: init failed.\n");
       
        return 1;
    }
    
    /* set average sample 8 */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_AVERAGE_SAMPLE_8);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 75 data output rate */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_75);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = hmc5883l_set_mode(&gs_handle, HMC5883L_MODE_NORMAL);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 820 gain */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_820);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }    
    
    /* enable high speed iic */
    res = hmc5883l_enable_high_speed_iic(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: enable high speed iic failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start read test */
    hmc5883l_interface_debug_print("hmc5883l: start read test.\n");
    
    /* single read test */
    hmc5883l_interface_debug_print("hmc5883l: single read test.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s*/
        hmc5883l_interface_delay_ms(1000);
    
        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* continuous read test */
    hmc5883l_interface_debug_print("hmc5883l: continuous read test.\n");

    /* start continuous read */
    res = hmc5883l_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: start continuous read failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    for (i=0; i<times; i++)
    {
        /* delay 1 s*/
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_continuous_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: continuous read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: continuous read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: continuous read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: continuous read z %.1f.\n", m_gauss[2]);
    }

    /* stop continuous read */
    res = hmc5883l_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: stop continuous read failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }

    /* gain test */
    hmc5883l_interface_debug_print("hmc5883l: gain test.\n");

    /* set gain 1370 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_1370);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 1370.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s*/
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result*/
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 1090 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_1090);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 1090.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s*/
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 820 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_820);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 820.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s*/
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 660 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_660);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 660.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s */
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 440 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_440);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 440.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s */
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 390 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_390);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }        
    hmc5883l_interface_debug_print("hmc5883l: set gain 390.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s */
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 330 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_330);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 330.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s */
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* set gain 230 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_230);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 230.\n");
    for (i=0; i<times; i++)
    {
        /* delay 1 s */
        hmc5883l_interface_delay_ms(1000);

        /* single read */
        res = hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss);
        if (res != 0)
        {
            hmc5883l_interface_debug_print("hmc5883l: single read failed.\n");
            (void)hmc5883l_deinit(&gs_handle);
            
            return 1;
        }

        /* print result */
        hmc5883l_interface_debug_print("hmc5883l: single read x %.1f.\n", m_gauss[0]);
        hmc5883l_interface_debug_print("hmc5883l: single read y %.1f.\n", m_gauss[1]);
        hmc5883l_interface_debug_print("hmc5883l: single read z %.1f.\n", m_gauss[2]);
    }

    /* finish read test */
    hmc5883l_interface_debug_print("hmc5883l: finish read test.\n");
    (void)hmc5883l_deinit(&gs_handle);
    
    return 0;
}
