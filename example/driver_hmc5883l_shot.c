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
 * @file      driver_hmc5883l_shot.c
 * @brief     driver hmc5883l shot source file
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

#include "driver_hmc5883l_shot.h"

static hmc5883l_handle_t gs_handle;        /**< hmc5883l handle */

/**
 * @brief  shot example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hmc5883l_shot_init(void)
{
     uint8_t res;
    
    /* link interface function */
    DRIVER_HMC5883L_LINK_INIT(&gs_handle, hmc5883l_handle_t);
    DRIVER_HMC5883L_LINK_IIC_INIT(&gs_handle, hmc5883l_interface_iic_init);
    DRIVER_HMC5883L_LINK_IIC_DEINIT(&gs_handle, hmc5883l_interface_iic_deinit);
    DRIVER_HMC5883L_LINK_IIC_READ(&gs_handle, hmc5883l_interface_iic_read);
    DRIVER_HMC5883L_LINK_IIC_WRITE(&gs_handle, hmc5883l_interface_iic_write);
    DRIVER_HMC5883L_LINK_DELAY_MS(&gs_handle, hmc5883l_interface_delay_ms);
    DRIVER_HMC5883L_LINK_DEBUG_PRINT(&gs_handle, hmc5883l_interface_debug_print);
    
    /* hmc5883l init */
    res = hmc5883l_init(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: init failed.\n");
        
        return 1;
    }
    
    /* set average sample */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_SHOT_DEFAULT_AVERAGE_SAMPLE);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set data output rate */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_SHOT_DEFAULT_DATA_OUTPUT_RATE);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set mode */
    res = hmc5883l_set_mode(&gs_handle, HMC5883L_SHOT_DEFAULT_MODE);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gain */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_SHOT_DEFAULT_GAIN);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set enable high speed iic */
    res = hmc5883l_enable_high_speed_iic(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: enable high speed iic failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hmc5883l_shot_read(float m_gauss[3])
{
    int16_t raw[3];
    
    /* read x,y,z data */
    if (hmc5883l_single_read(&gs_handle, (int16_t *)raw, m_gauss) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hmc5883l_shot_deinit(void)
{
    /* close hmc5883l */
    if (hmc5883l_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
