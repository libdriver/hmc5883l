### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. HMC5883L

#### 3.1 Command Instruction

1. Show hmc5883l chip and driver information.

   ```shell
   hmc5883l (-i | --information)
   ```

2. Show hmc5883l help.

   ```shell
   hmc5883l (-h | --help)
   ```

3. Show hmc5883l pin connections of the current board.

   ```shell
   hmc5883l (-p | --port)
   ```

4. Run hmc5883l register test.

   ```shell
   hmc5883l (-t reg | --test=reg)
   ```

5. Run hmc5883l read test, num means test times.

   ```shell
   hmc5883l (-t read | --test=read) [--times=<num>]
   ```

6. Run hmc5883l read function, num means read times.

   ```shell
   hmc5883l (-e read | --example=read) [--times=<num>]
   ```

7. Run hmc5883l shot function, num means read times.

   ```shell
   hmc5883l (-e shot | --example=shot) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
hmc5883l -i

hmc5883l: chip is Honeywell HMC5883L.
hmc5883l: manufacturer is Honeywell.
hmc5883l: interface is IIC.
hmc5883l: driver version is 2.0.
hmc5883l: min supply voltage is 2.2V.
hmc5883l: max supply voltage is 3.6V.
hmc5883l: max current is 0.10mA.
hmc5883l: max temperature is 85.0C.
hmc5883l: min temperature is -30.0C.
```

```shell
hmc5883l -p

hmc5883l: SCL connected to GPIOB PIN8.
hmc5883l: SDA connected to GPIOB PIN9.
```

```shell
hmc5883l -t reg

hmc5883l: chip is Honeywell HMC5883L.
hmc5883l: manufacturer is Honeywell.
hmc5883l: interface is IIC.
hmc5883l: driver version is 2.0.
hmc5883l: min supply voltage is 2.2V.
hmc5883l: max supply voltage is 3.6V.
hmc5883l: max current is 0.10mA.
hmc5883l: max temperature is 85.0C.
hmc5883l: min temperature is -30.0C.
hmc5883l: start register test.
hmc5883l: hmc5883l_set_average_sample/hmc5883l_get_average_sample test.
hmc5883l: set average sample 1.
hmc5883l: check average sample ok.
hmc5883l: set average sample 2.
hmc5883l: check average sample ok.
hmc5883l: set average sample 4.
hmc5883l: check average sample ok.
hmc5883l: set average sample 8.
hmc5883l: check average sample ok.
hmc5883l: hmc5883l_set_data_output_rate/hmc5883l_get_data_output_rate test.
hmc5883l: set data output rate 0.75.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 1.5.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 3.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 7.5.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 15.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 30.
hmc5883l: check data output rate ok.
hmc5883l: set data output rate 75.
hmc5883l: check data output rate ok.
hmc5883l: hmc5883l_set_mode/hmc5883l_get_mode test.
hmc5883l: set mode normal.
hmc5883l: check mode ok.
hmc5883l: set mode positive bias.
hmc5883l: check mode ok.
hmc5883l: set mode negative bias.
hmc5883l: check mode ok.
hmc5883l: hmc5883l_set_gain/hmc5883l_get_gain test.
hmc5883l: set gain 1370.
hmc5883l: check gain ok.
hmc5883l: set gain 1090.
hmc5883l: check gain ok.
hmc5883l: set gain 820.
hmc5883l: check gain ok.
hmc5883l: set gain 660.
hmc5883l: check gain ok.
hmc5883l: set gain 440.
hmc5883l: check gain ok.
hmc5883l: set gain 390.
hmc5883l: check gain ok.
hmc5883l: set gain 330.
hmc5883l: check gain ok.
hmc5883l: set gain 230.
hmc5883l: check gain ok.
hmc5883l: hmc5883l_enable_high_speed_iic.
hmc5883l: check enable high speed iic ok.
hmc5883l: hmc5883l_disable_high_speed_iic.
hmc5883l: check disable high speed iic ok.
hmc5883l: finish register test.
```

```shell
hmc5883l -t read --times=3

hmc5883l: chip is Honeywell HMC5883L.
hmc5883l: manufacturer is Honeywell.
hmc5883l: interface is IIC.
hmc5883l: driver version is 2.0.
hmc5883l: min supply voltage is 2.2V.
hmc5883l: max supply voltage is 3.6V.
hmc5883l: max current is 0.10mA.
hmc5883l: max temperature is 85.0C.
hmc5883l: min temperature is -30.0C.
hmc5883l: start read test.
hmc5883l: single read test.
hmc5883l: single read x 508.7.
hmc5883l: single read y 464.1.
hmc5883l: single read z -178.1.
hmc5883l: single read x 514.8.
hmc5883l: single read y 435.5.
hmc5883l: single read z -175.7.
hmc5883l: single read x 512.4.
hmc5883l: single read y 439.2.
hmc5883l: single read z -176.9.
hmc5883l: continuous read test.
hmc5883l: continuous read x 512.4.
hmc5883l: continuous read y 441.6.
hmc5883l: continuous read z -176.9.
hmc5883l: continuous read x 508.7.
hmc5883l: continuous read y 441.6.
hmc5883l: continuous read z -176.9.
hmc5883l: continuous read x 512.4.
hmc5883l: continuous read y 439.2.
hmc5883l: continuous read z -175.7.
hmc5883l: gain test.
hmc5883l: set gain 1370.
hmc5883l: single read x 305.9.
hmc5883l: single read y 262.8.
hmc5883l: single read z -105.1.
hmc5883l: single read x 308.1.
hmc5883l: single read y 260.6.
hmc5883l: single read z -105.1.
hmc5883l: single read x 494.9.
hmc5883l: single read y 428.5.
hmc5883l: single read z -173.7.
hmc5883l: set gain 1090.
hmc5883l: single read x 623.8.
hmc5883l: single read y 543.7.
hmc5883l: single read z -215.3.
hmc5883l: single read x 627.4.
hmc5883l: single read y 542.8.
hmc5883l: single read z -217.1.
hmc5883l: single read x 493.1.
hmc5883l: single read y 426.0.
hmc5883l: single read z -175.7.
hmc5883l: set gain 820.
hmc5883l: single read x 657.6.
hmc5883l: single read y 564.9.
hmc5883l: single read z -229.4.
hmc5883l: single read x 660.0.
hmc5883l: single read y 566.1.
hmc5883l: single read z -229.4.
hmc5883l: single read x 514.8.
hmc5883l: single read y 447.7.
hmc5883l: single read z -178.1.
hmc5883l: set gain 660.
hmc5883l: single read x 638.4.
hmc5883l: single read y 550.2.
hmc5883l: single read z -221.9.
hmc5883l: single read x 638.4.
hmc5883l: single read y 547.2.
hmc5883l: single read z -223.4.
hmc5883l: single read x 500.1.
hmc5883l: single read y 428.6.
hmc5883l: single read z -176.3.
hmc5883l: set gain 440.
hmc5883l: single read x 746.8.
hmc5883l: single read y 647.0.
hmc5883l: single read z -261.0.
hmc5883l: single read x 746.8.
hmc5883l: single read y 651.5.
hmc5883l: single read z -263.3.
hmc5883l: single read x 501.7.
hmc5883l: single read y 435.8.
hmc5883l: single read z -177.1.
hmc5883l: set gain 390.
hmc5883l: single read x 573.4.
hmc5883l: single read y 483.8.
hmc5883l: single read z -194.6.
hmc5883l: single read x 570.9.
hmc5883l: single read y 483.8.
hmc5883l: single read z -194.6.
hmc5883l: single read x 501.8.
hmc5883l: single read y 435.2.
hmc5883l: single read z -176.6.
hmc5883l: set gain 330.
hmc5883l: single read x 596.9.
hmc5883l: single read y 518.1.
hmc5883l: single read z -209.1.
hmc5883l: single read x 596.9.
hmc5883l: single read y 518.1.
hmc5883l: single read z -209.1.
hmc5883l: single read x 493.9.
hmc5883l: single read y 424.2.
hmc5883l: single read z -172.7.
hmc5883l: set gain 230.
hmc5883l: single read x 709.0.
hmc5883l: single read y 604.6.
hmc5883l: single read z -247.9.
hmc5883l: single read x 709.0.
hmc5883l: single read y 609.0.
hmc5883l: single read z -252.3.
hmc5883l: single read x 495.9.
hmc5883l: single read y 435.0.
hmc5883l: single read z -174.0.
hmc5883l: finish read test
```

```shell
hmc5883l -e read --times=3

1/3
x is 524.600.
y is 448.960.
z is -159.820.
2/3
x is 528.260.
y is 444.080.
z is -159.820.
3/3
x is 525.820.
y is 440.420.
z is -158.600.
```

```shell
hmc5883l -e shot --times=3

1/3
x is 567.300.
y is 423.340.
z is -135.420.
2/3
x is 566.080.
y is 420.900.
z is -137.860.
3/3
x is 568.520.
y is 422.120.
z is -132.980.
```

```shell
hmc5883l -h

Usage:
  hmc5883l (-i | --information)
  hmc5883l (-h | --help)
  hmc5883l (-p | --port)
  hmc5883l (-t reg | --test=reg)
  hmc5883l (-t read | --test=read) [--times=<num>]
  hmc5883l (-e read | --example=read) [--times=<num>]
  hmc5883l (-e shot | --example=shot) [--times=<num>]

Options:
  -e <read | shot>, --example=<read | shot>
                                 Run the driver example.
  -h, --help                     Show the help.
  -i, --information              Show the chip information.
  -p, --port                     Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                                 Run the driver test.
      --times=<num>              Set the running times.([default: 3])
```

