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
 * @file      driver_hmc5883l.c
 * @brief     driver hmc5883l source file
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

#include "driver_hmc5883l.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Honeywell HMC5883L"        /**< chip name */
#define MANUFACTURER_NAME         "Honeywell"                 /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.16f                       /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                        /**< chip max supply voltage */
#define MAX_CURRENT               0.1f                        /**< chip max current */
#define TEMPERATURE_MIN           -30.0f                      /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                       /**< chip max operating temperature */
#define DRIVER_VERSION            2000                        /**< driver version */

/**
 * @brief iic address definition
 */
#define HMC5883L_ADDRESS           0x3C        /**< iic address */

/**
 * @brief chip register definition
 */
#define HMC5883L_REG_CRA          0x00      /**< cra register */
#define HMC5883L_REG_CRB          0x01      /**< crb register */
#define HMC5883L_REG_MODE         0x02      /**< mode register */
#define HMC5883L_REG_OUTXM        0x03      /**< outxm register */
#define HMC5883L_REG_OUTXL        0x04      /**< outxl register */
#define HMC5883L_REG_OUTYM        0x07      /**< outym register */
#define HMC5883L_REG_OUTYL        0x08      /**< outyl register */
#define HMC5883L_REG_OUTZM        0x05      /**< outzm register */
#define HMC5883L_REG_OUTZL        0x06      /**< outzl register */
#define HMC5883L_REG_STATUS       0x09      /**< status register */
#define HMC5883L_REG_IDA          0x0A      /**< ida register */
#define HMC5883L_REG_IDB          0x0B      /**< idb register */
#define HMC5883L_REG_IDC          0x0C      /**< idc register */

/**
 * @brief     test the chip
 * @param[in] *handle points to an hmc5883l handle structure
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
static uint8_t a_hmc5883l_test(hmc5883l_handle_t *handle)
{
    uint8_t reg, times, status;
    uint8_t buf[6];
    int16_t data;
    
    reg = 0x71;                                                                             /* set 0x71 */
    if (handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&reg, 1) != 0)     /* write cra reg */
    {
        handle->debug_print("hmc5883l: write failed.\n");                                   /* write cra failed */
      
        return 1;                                                                           /* return error */
    }
    reg = 0xA0;                                                                             /* set 0xA0 */
    if (handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&reg, 1) != 0)     /* write crb reg */
    {
        handle->debug_print("hmc5883l: write failed.\n");                                   /* write crb failed */
        
        return 1;                                                                           /* return error */
    }
    reg = 0x00;                                                                             /* set 0x00 */
    if (handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&reg, 1) != 0)    /* write mode reg */
    {
        handle->debug_print("hmc5883l: write failed.\n");                                   /* write mode failed */
        
        return 1;                                                                           /* return error */
    }
    handle->delay_ms(100);                                                                  /* wait 100 ms */
    times = 15;                                                                             /* set try 15 times */
    
    while (times != 0)                                                                      /* check the times */
    {
        if (handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_STATUS, 
                            (uint8_t *)&status, 1) != 0)                                    /* read status */
        {
            handle->debug_print("hmc5883l: read failed.\n");                                /* read status failed */
            
            return 1;                                                                       /* return error */
        }
        status = status & 0x01;                                                             /* get status bit */
        if (status == 0)                                                                    /* check status */
        {
            times--;                                                                        /* times-- */
        }
        else
        {
            break;                                                                          /* break */
        }
    }
    if (times == 0)                                                                         /* if timeout */
    {
        handle->debug_print("hmc5883l: check failed.\n");                                   /* check failed */
        
        return 1;                                                                           /* return error */
    }
    if (handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_OUTXM, (uint8_t *)buf, 6) != 0)     /* read raw data */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                    /* read failed */
        
        return 1;                                                                           /* return error */
    }
    data = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                                     /* get x data */
    if ((data <= 243) || (data > 575))                                                      /* check x data */
    {
        handle->debug_print("hmc5883l: x check failed.\n");                                 /* x data check failed */
        
        return 1;                                                                           /* return error */
    }
    data = (int16_t)(((uint16_t)buf[2] << 8) | buf[3]);                                     /* get y data */
    if ((data <= 243) || (data > 575))                                                      /* check y data */
    {
        handle->debug_print("hmc5883l: y check failed.\n");                                 /* y data check failed */
        
        return 1;                                                                           /* return error */
    }
    data = (int16_t)(((uint16_t)buf[4] << 8) | buf[5]);                                     /* get z data */
    if ((data <= 243) || (data > 575))                                                      /* check z data */
    {
        handle->debug_print("hmc5883l: z check failed.\n");                                 /* z data check failed */
        
        return 1;                                                                           /* return error */
    }
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t hmc5883l_init(hmc5883l_handle_t *handle)
{
    uint8_t id;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->debug_print == NULL)                                                  /* check debug_print */
    {
        return 3;                                                                     /* return error */
    }
    if (handle->iic_init == NULL)                                                     /* check iic_init */
    {
        handle->debug_print("hmc5883l: iic_init is null.\n");                         /* iic_init is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_deinit == NULL)                                                   /* check iic_deinit */
    {
        handle->debug_print("hmc5883l: iic_deinit is null.\n");                       /* iic_deinit is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_read == NULL)                                                     /* check iic_read */
    {
        handle->debug_print("hmc5883l: iic_read is null.\n");                         /* iic_read is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->iic_write == NULL)                                                    /* check iic_write */
    {
        handle->debug_print("hmc5883l: iic_write is null.\n");                        /* iic_write is null */
        
        return 3;                                                                     /* return error */
    }
    if (handle->delay_ms == NULL)                                                     /* check delay_ms */
    {
        handle->debug_print("hmc5883l: delay_ms is null.\n");                         /* delay_ms is null */
        
        return 3;                                                                     /* return error */
    }
    
    if (handle->iic_init() != 0)                                                      /* iic init */
    {
        handle->debug_print("hmc5883l: iic init failed.\n");                          /* iic init failed */
        
        return 1;                                                                     /* return error */
    }
    if (handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_IDA, (uint8_t *)&id, 1) != 0) /* read ida failed */
    {
        handle->debug_print("hmc5883l: read failed.\n");                              /* read failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }
    if (id != 'H')                                                                    /* check id a */
    {
        handle->debug_print("hmc5883l: first id invalid.\n");                         /* first id is invalid */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }
    if (handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_IDB, (uint8_t *)&id, 1) != 0) /* read idb failed */
    {
        handle->debug_print("hmc5883l: read failed.\n");                              /* read failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }
    if (id != '4')                                                                    /* check id b */
    {
        handle->debug_print("hmc5883l: second id invalid.\n");                        /* second id is invalid */
        (void)handle->iic_deinit();                                                   /* iid deinit */
        
        return 1;                                                                     /* return error */
    }    
    if (handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_IDC, (uint8_t *)&id, 1) != 0) /* read idc */
    {
        handle->debug_print("hmc5883l: read failed.\n");                              /* read idc failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }
    if (id != '3')                                                                    /* check id c */
    {
        handle->debug_print("hmc5883l: third id invalid.\n");                         /* third id is invalid */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }    
    if (a_hmc5883l_test(handle) != 0)                                                 /* run test */
    {
        handle->debug_print("hmc5883l: test is not passed.\n");                       /* run test failed */
        (void)handle->iic_deinit();                                                   /* iic deinit */
        
        return 1;                                                                     /* return error */
    }
    handle->inited = 1;                                                               /* flag finish initialization */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t hmc5883l_deinit(hmc5883l_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }

    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);       /* read mode config */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                    /* read mode reg */
        
        return 1;                                                                           /* return error */
    }
    prev &= ~(0x7C);                                                                        /* clear mode */
    prev &= ~(0x03);                                                                        /* clear config */
    prev |= 0x02;                                                                           /* set config */
    res = handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);      /* write mode config */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("hmc5883l: write failed.\n");                                   /* write mode failed */
        
        return 1;                                                                           /* return error */
    }    
    if (handle->iic_deinit() != 0)                                                          /* iic deinit */
    {
        handle->debug_print("hmc5883l: iic deinit failed.\n");                              /* return error */
        
        return 2;                                                                           /* iic deinit failed */
    }   
    handle->inited = 0;                                                                     /* flag close */
    
    return 0;                                                                               /* success return 0 */
}

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
uint8_t hmc5883l_set_average_sample(hmc5883l_handle_t *handle, hmc5883l_average_sample_t average_sample)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);        /* read cra config */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                    /* read cra failed */
        
        return 1;                                                                           /* return error */
    }
    prev &= ~(1<<7);                                                                        /* clear cra 7 */
    prev &= ~(3<<5);                                                                        /* clear config */
    prev |= average_sample << 5;                                                            /* set config */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* write cra config */
}

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
uint8_t hmc5883l_get_average_sample(hmc5883l_handle_t *handle, hmc5883l_average_sample_t *average_sample)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* read cra config */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                  /* return cra failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= (3 << 5);                                                                     /* get raw reg */
    *average_sample = (hmc5883l_average_sample_t)(prev >> 5);                             /* get config */

    return 0;                                                                             /* success return 0 */
}

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
uint8_t hmc5883l_set_data_output_rate(hmc5883l_handle_t *handle, hmc5883l_data_output_rate_t data_rate)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);        /* read cra config */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                    /* read cra failed */
        
        return 1;                                                                           /* return error */
    }
    prev &= ~(1 << 7);                                                                      /* clear cra 7 */
    prev &= ~(7 << 2);                                                                      /* clear config */
    prev |= data_rate << 2;                                                                 /* set config */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* write cra config */
}

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
uint8_t hmc5883l_get_data_output_rate(hmc5883l_handle_t *handle, hmc5883l_data_output_rate_t *data_rate)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* read cra config */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                  /* read cra failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= (7 << 2);                                                                     /* get raw reg */
    *data_rate = (hmc5883l_data_output_rate_t)(prev >> 2);                                /* get config */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t hmc5883l_set_mode(hmc5883l_handle_t *handle, hmc5883l_mode_t mode)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                     /* check handle */
    {
        return 2;                                                                           /* return error */
    }
    if (handle->inited != 1)                                                                /* check handle initialization */
    {
        return 3;                                                                           /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);        /* read cra config */
    if (res != 0)                                                                           /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                    /* read cra failed */
        
        return 1;                                                                           /* return error */
    }
    prev &= ~(1 << 7);                                                                      /* clear cra 7 */
    prev &= ~(3 << 0);                                                                      /* clear config */
    prev |= mode << 0;                                                                      /* set config */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* write cra config */
}

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
uint8_t hmc5883l_get_mode(hmc5883l_handle_t *handle, hmc5883l_mode_t *mode)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRA, (uint8_t *)&prev, 1);      /* read cra config */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                  /* read cra failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= 3 << 0;                                                                       /* get raw reg */
    *mode = (hmc5883l_mode_t)(prev >> 0);                                                 /* get config */
 
    return 0;                                                                             /* success return 0 */
}

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
uint8_t hmc5883l_set_gain(hmc5883l_handle_t *handle, hmc5883l_gain_t gain)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&prev, 1);      /* read config */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                  /* read crb config failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= ~(0x1F);                                                                      /* clear crb */
    prev &= ~(7 << 5);                                                                    /* clear config */
    prev |= gain << 5;                                                                    /* set gain */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&prev, 1);    /* write config */
}

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
uint8_t hmc5883l_get_gain(hmc5883l_handle_t *handle, hmc5883l_gain_t *gain)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                   /* check handle */
    {
        return 2;                                                                         /* return error */
    }
    if (handle->inited != 1)                                                              /* check handle initialization */
    {
        return 3;                                                                         /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&prev, 1);      /* read config */
    if (res != 0)                                                                         /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                  /* read crb config failed */
        
        return 1;                                                                         /* return error */
    }
    prev &= (7 << 5);                                                                     /* get raw reg */
    *gain = (hmc5883l_gain_t)(prev >> 5);                                                 /* get config */
    
    return 0;                                                                             /* success return 0 */
}

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
uint8_t hmc5883l_enable_high_speed_iic(hmc5883l_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);        /* read mode config */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                     /* read mode failed */
        
        return 1;                                                                            /* return error */
    }
    prev &= ~(0x7C);                                                                         /* clear mode bit */
    prev |= (1 << 7);                                                                        /* enable high speed iic */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);      /* write config */
}

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
uint8_t hmc5883l_disable_high_speed_iic(hmc5883l_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);        /* read mode config */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                     /* read mode failed */
        
        return 1;                                                                            /* return error */
    }
    prev &= ~(0x7C);                                                                         /* clear mode bit */
    prev &= ~(1 << 7);                                                                       /* disable high speed iic */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);      /* write config */
}

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
uint8_t hmc5883l_single_read(hmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3])
{
    uint8_t res, gain, status, prev;
    uint16_t num = 5000;
    uint8_t buf[6];
    float resolution;
    
    if (handle == NULL)                                                                           /* check handle */
    {
        return 2;                                                                                 /* return error */
    }
    if (handle->inited != 1)                                                                      /* check handle initialization */
    {
        return 3;                                                                                 /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);             /* read mode register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                          /* read mode failed */
        
        return 1;                                                                                 /* return error */
    }
    prev &= ~(0x7C);                                                                              /* clear mode bits */
    prev &= ~(0x03);                                                                              /* clear config */
    prev |= 0x01;                                                                                 /* set config */
    res = handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);            /* write mode register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("hmc5883l: write failed.\n");                                         /* write mode failed */
        
        return 1;                                                                                 /* return error */
    }
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&gain, 1);              /* read crb register */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                          /* read crb failed */
        
        return 1;                                                                                 /* return error */
    }
    gain = gain >> 5;                                                                             /* set gain */
    switch (gain)                                                                                 /* choose resolution */
    {                                                                                             /* check gain */
        case 0x00 :
        {
            resolution = 0.73f;                                                                   /* set resolution */
            
            break;                                                                                /* break */
        }
        case 0x01 :
        {
            resolution = 0.92f;                                                                   /* set resolution */
            
            break;                                                                                /* break */
        }
        case 0x02 :
        {
            resolution = 1.22f;                                                                   /* set resolution 1.22 */
            
            break;                                                                                /* break */
        }
        case 0x03 :
        {
            resolution = 1.52f;                                                                   /* set resolution 1.52 */
            
            break;                                                                                /* break */
        }
        case 0x04 :
        {
            resolution = 2.27f;                                                                   /* set resolution 2.27 */
            
            break;                                                                                /* break */
        }
        case 0x05 :
        {
            resolution = 2.56f;                                                                   /* set resolution 2.56 */
            
            break;                                                                                /* break */
        }
        case 0x06 :
        {
            resolution = 3.03f;                                                                   /* set resolution 3.03 */
            
            break;                                                                                /* break */
        }
        case 0x07 :
        {
            resolution = 4.35f;                                                                   /* set resolution 4.35 */
            
            break;                                                                                /* break */
        }
        default :                                                                                 /* unknown code */
        {
            resolution = 0.00f;                                                                   /* set resolution 0.00 */
            
            break;                                                                                /* break */
        }
    }
    while (num != 0)                                                                              /* check num */
    {
        res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_STATUS, (uint8_t *)&status, 1);     /* read status register */
        if (res != 0)                                                                             /* check result */
        {
            handle->debug_print("hmc5883l: read failed.\n");                                      /* read status failed */
            
            return 1;                                                                             /* return error */
        }
        if ((status & 0x01) != 0)                                                                 /* check status */
        {
            break;                                                                                /* break loop */
        }
        handle->delay_ms(10);                                                                     /* check 10 ms */
        num--;                                                                                    /* retry times-- */
        if (num == 0)                                                                             /* if timeout */
        {
            handle->debug_print("hmc5883l: ready bit not be set.\n");                             /* timeout */
            
            return 1;                                                                             /* return error */
        }
    }
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_OUTXM, (uint8_t *)buf, 6);              /* read raw data */
    if (res != 0)                                                                                 /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                          /* read out failed */
        
        return 1;                                                                                 /* return error */
    }
    raw[0] = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                                         /* get x raw */
    raw[1] = (int16_t)(((uint16_t)buf[2] << 8) | buf[3]);                                         /* get y raw */
    raw[2] = (int16_t)(((uint16_t)buf[4] << 8) | buf[5]);                                         /* get z raw */
    m_gauss[0] = (float)(raw[0]) * resolution;                                                    /* calculate x */
    m_gauss[1] = (float)(raw[1]) * resolution;                                                    /* calculate y */
    m_gauss[2] = (float)(raw[2]) * resolution;                                                    /* calculate z */
    
    return 0;                                                                                     /* success return 0 */
}

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
uint8_t hmc5883l_start_continuous_read(hmc5883l_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);        /* read mode register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                     /* read mode failed */
        
        return 1;                                                                            /* return error */
    }
    prev &= ~(0x7C);                                                                         /* clear mode bits */
    prev &= ~(0x03);                                                                         /* clear config */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);      /* write config */
}

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
uint8_t hmc5883l_stop_continuous_read(hmc5883l_handle_t *handle)
{
    uint8_t res, prev;
    
    if (handle == NULL)                                                                      /* check handle */
    {
        return 2;                                                                            /* return error */
    }
    if (handle->inited != 1)                                                                 /* check handle initialization */
    {
        return 3;                                                                            /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);        /* read mode register */
    if (res != 0)                                                                            /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                     /* read mode failed */
        
        return 1;                                                                            /* return error */
    }
    prev &= ~(0x7C);                                                                         /* clear mode bits */
    prev &= ~(0x03);                                                                         /* clear config */
    prev |= 1 << 1;                                                                          /* set config */
    
    return handle->iic_write(HMC5883L_ADDRESS, HMC5883L_REG_MODE, (uint8_t *)&prev, 1);      /* write config */
}

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
uint8_t hmc5883l_continuous_read(hmc5883l_handle_t *handle, int16_t raw[3], float m_gauss[3])
{
    uint8_t res, gain, status;
    uint16_t num = 5000;
    uint8_t buf[6];
    float resolution;
    
    if (handle == NULL)                                                                            /* check handle */
    {
        return 2;                                                                                  /* return error */
    }
    if (handle->inited != 1)                                                                       /* check handle initialization */
    {
        return 3;                                                                                  /* return error */
    }
    
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_CRB, (uint8_t *)&gain, 1);               /* read crb register failed */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                           /* read crb failed */
        
        return 1;                                                                                  /* return error */
    }
    gain = gain >> 5;                                                                              /* set gain */
    switch (gain)                                                                                  /* choose resolution */
    {
        case 0x00 :
        {
            resolution = 0.73f;                                                                    /* set resolution 0.73 */
            
            break;                                                                                 /* break */
        }
        case 0x01 :
        {
            resolution = 0.92f;                                                                    /* set resolution 0.92 */
            
            break;                                                                                 /* break */
        }
        case 0x02 :
        {
            resolution = 1.22f;                                                                    /* set resolution 1.22 */
            
            break;                                                                                 /* break */
        }
        case 0x03 :
        {
            resolution = 1.52f;                                                                    /* set resolution 1.52 */
            
            break;                                                                                 /* break */
        }
        case 0x04 :
        {
            resolution = 2.27f;                                                                    /* set resolution 2.27 */
            
            break;                                                                                 /* break */
        }
        case 0x05 :
        {
            resolution = 2.56f;                                                                    /* set resolution 2.56 */
            
            break;                                                                                 /* break */
        }
        case 0x06 :
        {
            resolution = 3.03f;                                                                    /* set resolution 3.03 */
            
            break;                                                                                 /* break */
        }
        case 0x07 :
        {
            resolution = 4.35f;                                                                    /* set resolution 4.35 */
            
            break;                                                                                 /* break */
        }
        default :                                                                                  /* unknown code */
        {
            resolution = 0.00f;                                                                    /* set resolution 0.00 */
            
            break;                                                                                 /* break */
        }
    }
    while (num != 0)                                                                               /* check num */
    {
        res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_STATUS, (uint8_t *)&status, 1);      /* read status register */
        if (res != 0)                                                                              /* check result */
        {
            handle->debug_print("hmc5883l: read failed.\n");                                       /* read status failed */
            
            return 1;                                                                              /* return error */
        }
        if ((status & 0x01) != 0)                                                                  /* check status */
        {
            break;                                                                                 /* break loop */
        }
        handle->delay_ms(10);                                                                      /* check 10 ms */
        num--;
        if (num == 0)                                                                              /* if timeout */
        {
            handle->debug_print("hmc5883l: ready bit not be set.\n");                              /* timeout */
            
            return 1;                                                                              /* return error */
        }
    }
    res = handle->iic_read(HMC5883L_ADDRESS, HMC5883L_REG_OUTXM, (uint8_t *)buf, 6);               /* read raw data */
    if (res != 0)                                                                                  /* check result */
    {
        handle->debug_print("hmc5883l: read failed.\n");                                           /* read out failed */
        
        return 1;                                                                                  /* return error */
    }
    raw[0] = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                                          /* get x raw */
    raw[1] = (int16_t)(((uint16_t)buf[2] << 8) | buf[3]);                                          /* get y raw */
    raw[2] = (int16_t)(((uint16_t)buf[4] << 8) | buf[5]);                                          /* get z raw */
    m_gauss[0] = (float)(raw[0]) * resolution;                                                     /* calculate x */
    m_gauss[1] = (float)(raw[1]) * resolution;                                                     /* calculate y */
    m_gauss[2] = (float)(raw[2]) * resolution;                                                     /* calculate z */
   
    return 0;                                                                                      /* success return 0 */
}

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
uint8_t hmc5883l_set_reg(hmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    } 
    
    return handle->iic_write(HMC5883L_ADDRESS, reg, buf, len);        /* write data */
}

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
uint8_t hmc5883l_get_reg(hmc5883l_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    } 
    
    return handle->iic_read(HMC5883L_ADDRESS, reg, buf, len);        /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an hmc5883l info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t hmc5883l_info(hmc5883l_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(hmc5883l_info_t));                       /* initialize hmc5883l info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
