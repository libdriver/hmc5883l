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
 * @file      driver_hmc5883l_shot.h
 * @brief     driver hmc5883l shot header file
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

#ifndef DRIVER_HMC5883L_SHOT_H
#define DRIVER_HMC5883L_SHOT_H

#include "driver_hmc5883l_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup hmc5883l_example_driver
 * @{
 */

/**
 * @brief hmc5883l shot example default definition
 */
#define HMC5883L_SHOT_DEFAULT_AVERAGE_SAMPLE   HMC5883L_AVERAGE_SAMPLE_8           /**< average 8 sample */
#define HMC5883L_SHOT_DEFAULT_DATA_OUTPUT_RATE HMC5883L_DATA_OUTPUT_RATE_15        /**< 15Hz output rate */
#define HMC5883L_SHOT_DEFAULT_MODE             HMC5883L_MODE_NORMAL                /**< normal mode */
#define HMC5883L_SHOT_DEFAULT_GAIN             HMC5883L_GAIN_820                   /**< gain 820 */

/**
 * @brief  shot example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t hmc5883l_shot_init(void);

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t hmc5883l_shot_deinit(void);

/**
 * @brief      shot example read
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t hmc5883l_shot_read(float m_gauss[3]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
