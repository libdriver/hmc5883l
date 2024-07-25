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
 * @file      driver_hmc5883l_register_test.c
 * @brief     driver hmc5883l register test source file
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

#include "driver_hmc5883l_register_test.h"

static hmc5883l_handle_t gs_handle;        /**< hmc5883l handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t hmc5883l_register_test(void)
{
    uint8_t res; 
    hmc5883l_info_t info;
    hmc5883l_average_sample_t average_sample;
    hmc5883l_data_output_rate_t data_rate;
    hmc5883l_mode_t mode;
    hmc5883l_gain_t gain;
    
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
    
    /* start register test */
    hmc5883l_interface_debug_print("hmc5883l: start register test.\n");
    
    /* hmc5883l_set_average_sample/hmc5883l_get_average_sample test */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_set_average_sample/hmc5883l_get_average_sample test.\n");
    
    /* set AVERAGE_SAMPLE_1 */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_AVERAGE_SAMPLE_1);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set average sample 1.\n");
    res = hmc5883l_get_average_sample(&gs_handle, &average_sample);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check average sample %s.\n", average_sample==HMC5883L_AVERAGE_SAMPLE_1?"ok":"error");
    
    /* set AVERAGE_SAMPLE_2 */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_AVERAGE_SAMPLE_2);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }    
    hmc5883l_interface_debug_print("hmc5883l: set average sample 2.\n");
    res = hmc5883l_get_average_sample(&gs_handle, &average_sample);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check average sample %s.\n", average_sample==HMC5883L_AVERAGE_SAMPLE_2?"ok":"error");
    
    /* set AVERAGE_SAMPLE_4 */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_AVERAGE_SAMPLE_4);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set average sample 4.\n");
    res = hmc5883l_get_average_sample(&gs_handle, &average_sample);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check average sample %s.\n", average_sample==HMC5883L_AVERAGE_SAMPLE_4?"ok":"error");
    
    /* set AVERAGE_SAMPLE_8 */
    res = hmc5883l_set_average_sample(&gs_handle, HMC5883L_AVERAGE_SAMPLE_8);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set average sample 8.\n");
    res = hmc5883l_get_average_sample(&gs_handle, &average_sample);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get average sample failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check average sample %s.\n", average_sample==HMC5883L_AVERAGE_SAMPLE_8?"ok":"error");
    
    /* hmc5883l_set_data_output_rate/hmc5883l_get_data_output_rate test */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_set_data_output_rate/hmc5883l_get_data_output_rate test.\n");
    
    /* set DATA_OUTPUT_RATE_0P75 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_0P75);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 0.75.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_0P75?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_1P5 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_1P5);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 1.5.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_1P5?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_3 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_3);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 3.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_3?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_7.5 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_7P5);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 7.5.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_7P5?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_15 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_15);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 15.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_15?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_30 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_30);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 30.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_30?"ok":"error");
    
    /* set DATA_OUTPUT_RATE_75 */
    res = hmc5883l_set_data_output_rate(&gs_handle, HMC5883L_DATA_OUTPUT_RATE_75);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set data output rate 75.\n");
    res = hmc5883l_get_data_output_rate(&gs_handle, &data_rate);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get data output rate failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check data output rate %s.\n", data_rate==HMC5883L_DATA_OUTPUT_RATE_75?"ok":"error");
    
    /* hmc5883l_set_mode/hmc5883l_get_mode test */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_set_mode/hmc5883l_get_mode test.\n");
    
    /* set NORMAL */
    res = hmc5883l_set_mode(&gs_handle, HMC5883L_MODE_NORMAL);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set mode normal.\n");
    res = hmc5883l_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check mode %s.\n", mode==HMC5883L_MODE_NORMAL?"ok":"error");
    
    /* set POSITIVE_BIAS */
    res = hmc5883l_set_mode(&gs_handle, HMC5883L_MODE_POSITIVE_BIAS);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set mode positive bias.\n");
    res = hmc5883l_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check mode %s.\n", mode==HMC5883L_MODE_POSITIVE_BIAS?"ok":"error");
    
    /* set NEGATIVE_BIAS */
    res = hmc5883l_set_mode(&gs_handle, HMC5883L_MODE_NEGATIVE_BIAS);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set mode negative bias.\n");
    res = hmc5883l_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get mode failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check mode %s.\n", mode==HMC5883L_MODE_NEGATIVE_BIAS?"ok":"error");
    
    /* hmc5883l_set_gain/hmc5883l_get_gain test */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_set_gain/hmc5883l_get_gain test.\n");
    
    /* set GAIN_1370 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_1370);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 1370.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_1370?"ok":"error");
    
    /* set GAIN_1090 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_1090);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 1090.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_1090?"ok":"error");
    
    /* set GAIN_820 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_820);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 820.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_820?"ok":"error");
    
    /* set GAIN_660 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_660);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 660.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_660?"ok":"error");
    
    /* set GAIN_440 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_440);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 440.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_440?"ok":"error");
    
    /* set GAIN_390 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_390);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 390.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_390?"ok":"error");
    
    /* set GAIN_330 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_330);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: set gain 330.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_330?"ok":"error");
    
    /* set GAIN_330 */
    res = hmc5883l_set_gain(&gs_handle, HMC5883L_GAIN_230);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: set gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }    
    hmc5883l_interface_debug_print("hmc5883l: set gain 230.\n");
    res = hmc5883l_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: get gain failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check gain %s.\n", gain==HMC5883L_GAIN_230?"ok":"error");
    
    /* hmc5883l_enable_high_speed_iic */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_enable_high_speed_iic.\n");
    res = hmc5883l_enable_high_speed_iic(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: enable high speed iic failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check enable high speed iic %s.\n", res==0?"ok":"error");
    
    /* hmc5883l_disable_high_speed_iic */
    hmc5883l_interface_debug_print("hmc5883l: hmc5883l_disable_high_speed_iic.\n");
    res = hmc5883l_disable_high_speed_iic(&gs_handle);
    if (res != 0)
    {
        hmc5883l_interface_debug_print("hmc5883l: disable high speed iic failed.\n");
        (void)hmc5883l_deinit(&gs_handle);
        
        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: check disable high speed iic %s.\n", res==0?"ok":"error");
    
    /* finish register test */
    hmc5883l_interface_debug_print("hmc5883l: finish register test.\n");
    (void)hmc5883l_deinit(&gs_handle);
    
    return 0;
}
