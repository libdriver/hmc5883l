<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver HMC5883L

[English](/README.md) | [ 简体中文](/README_CN.md)

The Honeywell HMC5883L is a surface-mount, multi-chip module designed for low-field magnetic sensing with a digital interface for applications such as low-cost compassing and magnetometry. The HMC5883L includes our state-of-the-art, high-resolution HMC118X series magneto-resistive sensors plus an ASIC containing amplification, automatic degaussing strap drivers, offset cancellation, and a 12-bit ADC that enables 1° to 2° compass heading accuracy. The I2C serial bus allows for easy interface. The HMC5883L is a 3.0x3.0x0.9mm surface mount 16-pin leadless chip carrier (LCC). Applications for the HMC5883L include Mobile Phones, Netbooks, Consumer Electronics, Auto Navigation Systems, and Personal Navigation Devices.

LibDriver HMC5883L is the full function driver of HMC5883L launched by LibDriver.It provides continuous mode magnetic field strength reading, single mode magnetic field reading and other functions.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver HMC5883L source files.

/interface includes LibDriver HMC5883L IIC platform independent template。

/test includes LibDriver HMC5883L driver test code and this code can test the chip necessary function simply。

/example includes LibDriver HMC5883L sample code.

/doc includes LibDriver HMC5883L offline document.

/datasheet includes HMC5883L datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_basic_init();
if (res)
{
    return 1;
}

...


for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_basic_read((float *)m_gauss);
    if (res)
    {
        hmc5883l_basic_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

hmc5883l_basic_deinit();

return 0;
```

#### example shot

```C
uint8_t res;
uint8_t i;
float m_gauss[3];

res = hmc5883l_shot_init();
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    hmc5883l_interface_delay_ms(1000);
    res = hmc5883l_shot_read((float *)m_gauss);
    if (res)
    {
        hmc5883l_shot_deinit();

        return 1;
    }
    hmc5883l_interface_debug_print("hmc5883l: x is %0.3f.\n", m_gauss[0]);
    hmc5883l_interface_debug_print("hmc5883l: y is %0.3f.\n", m_gauss[1]);
    hmc5883l_interface_debug_print("hmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

hmc5883l_shot_deinit();

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/hmc5883l/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (C) LibDriver 2015-2021 All rights reserved 



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com