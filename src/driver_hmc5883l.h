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
 * @file      driver_hmc5883l.h
 * @brief     driver hmc5883l header file
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

#ifndef DRIVER_HMC5883L_H
#define DRIVER_HMC5883L_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup hmc5883l_driver hmc5883l driver function
 * @brief    hmc5883l driver modules
 * @{
 */

/**
 * @addtogroup hmc5883l_base_driver
 * @{
 */

/**
 * @brief hmc5883l average sample enumeration definition
 */
typedef enum
{
    HMC5883L_AVERAGE_SAMPLE_1 = 0x00,        /**< average sample 1 */
    HMC5883L_AVERAGE_SAMPLE_2 = 0x01,        /**< average sample 2 */
    HMC5883L_AVERAGE_SAMPLE_4 = 0x02,        /**< average sample 4 */
    HMC5883L_AVERAGE_SAMPLE_8 = 0x03,        /**< average sample 8 */
} hmc5883l_average_sample_t;

/**
 * @brief hmc5883l data output rate enumeration definition
 */
typedef enum
{
    HMC5883L_DATA_OUTPUT_RATE_0P75 = 0x00,        /**< 0.75Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_1P5  = 0x01,        /**< 1.5Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_3    = 0x02,        /**< 3Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_7P5  = 0x03,        /**< 7.5Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_15   = 0x04,        /**< 15Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_30   = 0x05,        /**< 30Hz output rate */
    HMC5883L_DATA_OUTPUT_RATE_75   = 0x06,        /**< 75Hz output rate */
} hmc5883l_data_output_rate_t;

/**
 * @brief hmc5883l mode enumeration definition
 */
typedef enum
{
    HMC5883L_MODE_NORMAL        = 0x00,        /**< normal mode */
    HMC5883L_MODE_POSITIVE_BIAS = 0x01,        /**< positive bias mode */
    HMC5883L_MODE_NEGATIVE_BIAS = 0x02,        /**< negative bias mode */
} hmc5883l_mode_t;

/**
 * @brief hmc5883l gain enumeration definition
 */
typedef enum
{
    HMC5883L_GAIN_1370 = 0x00,        /**< gain 1370 */
    HMC5883L_GAIN_1090 = 0x01,        /**< gain 1090 */
    HMC5883L_GAIN_820  = 0x02,        /**< gain 820 */
    HMC5883L_GAIN_660  = 0x03,        /**< gain 660 */
    HMC5883L_GAIN_440  = 0x04,        /**< gain 440 */
    HMC5883L_GAIN_390  = 0x05,        /**< gain 390 */
    HMC5883L_GAIN_330  = 0x06,        /**< gain 330 */
    HMC5883L_GAIN_230  = 0x07,        /**< gain 230 */
} hmc5883l_gain_t;

/**
 * @brief hmc5883l handle structure definition
 */
typedef struct hmc5883l_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} hmc5883l_handle_t;

/**
 * @brief hmc5883l information structure definition
 */
typedef struct hmc5883l_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} hmc5883l_info_t;

/**
 * @}
 */

/**
 * @defgroup hmc5883l_link_driver hmc5883l link driver function
 * @brief    hmc5883l link driver modules
 * @ingroup  hmc5883l_driver
 * @{
 */

/**
 * @brief     initialize hmc5883l_handle_t structure
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] STRUCTURE is hmc5883l_handle_t
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an hmc5883l handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_HMC5883L_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup hmc5883l_base_driver hmc5883l base driver function
 * @brief    hmc5883l base driver modules
 * @ingroup  hmc5883l_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an hmc5883l info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hmc5883l_info(hmc5883l_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t hmc5883l_init(hmc5883l_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 power down failed
 *            - 2 iic deinit failed
 *            - 3 handle is NULL
 *            - 4 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_deinit(hmc5883l_handle_t *handle);

/**
 * @brief      read data once
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_single_read(hmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3]);

/**
 * @brief     start reading data
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_start_continuous_read(hmc5883l_handle_t *handle);

/**
 * @brief     stop reading data
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_stop_continuous_read(hmc5883l_handle_t *handle);

/**
 * @brief      read data continuously
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *raw points to a raw data buffer
 * @param[out] *m_gauss points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_continuous_read(hmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3]);

/**
 * @brief     set the average sample rate
 * @param[in] *handle points to an hmc5883l handle structure
 * @param[in] average_sample is the average sample rate
 * @return    status code
 *            - 0 success
 *            - 1 set average sample failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_set_average_sample(hmc5883l_handle_t *handle, hmc5883l_average_sample_t average_sample);

/**
 * @brief      get the average sample rate
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *average_sample points to an average sample rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get average sample failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_get_average_sample(hmc5883l_handle_t *handle, hmc5883l_average_sample_t *average_sample);

/**
 * @brief     set the data output rate
 * @param[in] *handle points to an hmc5883l handle structure
 * @param[in] data_rate is the data output rate
 * @return    status code
 *            - 0 success
 *            - 1 set data output rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_set_data_output_rate(hmc5883l_handle_t *handle, hmc5883l_data_output_rate_t data_rate);

/**
 * @brief      get the data output rate
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *data_rate points to a data output rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get data output rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_get_data_output_rate(hmc5883l_handle_t *handle, hmc5883l_data_output_rate_t *data_rate);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an hmc5883l handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_set_mode(hmc5883l_handle_t *handle, hmc5883l_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_get_mode(hmc5883l_handle_t *handle, hmc5883l_mode_t *mode);

/**
 * @brief     set the chip gain
 * @param[in] *handle points to an hmc5883l handle structure
 * @param[in] gain is the chip gain
 * @return    status code
 *            - 0 success
 *            - 1 set gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_set_gain(hmc5883l_handle_t *handle, hmc5883l_gain_t gain);

/**
 * @brief      get the chip gain
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[out] *gain points to a chip gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_get_gain(hmc5883l_handle_t *handle, hmc5883l_gain_t *gain);

/**
 * @brief     enable the high speed iic
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 enable high speed iic failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_enable_high_speed_iic(hmc5883l_handle_t *handle);

/**
 * @brief     disable the high speed iic
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 disable high speed iic failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_disable_high_speed_iic(hmc5883l_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup hmc5883l_extend_driver hmc5883l extend driver function
 * @brief    hmc5883l extend driver modules
 * @ingroup  hmc5883l_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an hmc5883l handle structure
 * @param[in] reg is the iic register address
 * @param[in] *buf points to a data buffer
 * @param[in] len is the data buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t hmc5883l_set_reg(hmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an hmc5883l handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the data buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t hmc5883l_get_reg(hmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif
