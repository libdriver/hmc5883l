### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(hmc5883l REQUIRED)
```

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
./hmc5883l -i

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
./hmc5883l -p

hmc5883l: SCL connected to GPIO3(BCM).
hmc5883l: SDA connected to GPIO2(BCM).
```

```shell
./hmc5883l -t reg

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
./hmc5883l -t read --times=3

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
hmc5883l: single read x -267.2.
hmc5883l: single read y 198.9.
hmc5883l: single read z 196.4.
hmc5883l: single read x -266.0.
hmc5883l: single read y 214.7.
hmc5883l: single read z 195.2.
hmc5883l: single read x -263.5.
hmc5883l: single read y 218.4.
hmc5883l: single read z 194.0.
hmc5883l: continuous read test.
hmc5883l: continuous read x -263.5.
hmc5883l: continuous read y 213.5.
hmc5883l: continuous read z 192.8.
hmc5883l: continuous read x -264.7.
hmc5883l: continuous read y 211.1.
hmc5883l: continuous read z 190.3.
hmc5883l: continuous read x -263.5.
hmc5883l: continuous read y 202.5.
hmc5883l: continuous read z 195.2.
hmc5883l: gain test.
hmc5883l: set gain 1370.
hmc5883l: single read x -157.7.
hmc5883l: single read y 121.2.
hmc5883l: single read z 116.8.
hmc5883l: single read x -160.6.
hmc5883l: single read y 127.8.
hmc5883l: single read z 113.2.
hmc5883l: single read x -257.7.
hmc5883l: single read y 204.4.
hmc5883l: single read z 186.9.
hmc5883l: set gain 1090.
hmc5883l: single read x -323.8.
hmc5883l: single read y 249.3.
hmc5883l: single read z 238.3.
hmc5883l: single read x -259.4.
hmc5883l: single read y 195.0.
hmc5883l: single read z 190.4.
hmc5883l: single read x -261.3.
hmc5883l: single read y 197.8.
hmc5883l: single read z 188.6.
hmc5883l: set gain 820.
hmc5883l: single read x -348.9.
hmc5883l: single read y 274.5.
hmc5883l: single read z 244.0.
hmc5883l: single read x -267.2.
hmc5883l: single read y 212.3.
hmc5883l: single read z 191.5.
hmc5883l: single read x -264.7.
hmc5883l: single read y 209.8.
hmc5883l: single read z 194.0.
hmc5883l: set gain 660.
hmc5883l: single read x -331.4.
hmc5883l: single read y 247.8.
hmc5883l: single read z 244.7.
hmc5883l: single read x -264.5.
hmc5883l: single read y 194.6.
hmc5883l: single read z 188.5.
hmc5883l: single read x -267.5.
hmc5883l: single read y 202.2.
hmc5883l: single read z 185.4.
hmc5883l: set gain 440.
hmc5883l: single read x -392.7.
hmc5883l: single read y 311.0.
hmc5883l: single read z 279.2.
hmc5883l: single read x -258.8.
hmc5883l: single read y 211.1.
hmc5883l: single read z 188.4.
hmc5883l: single read x -261.0.
hmc5883l: single read y 199.8.
hmc5883l: single read z 192.9.
hmc5883l: set gain 390.
hmc5883l: single read x -302.1.
hmc5883l: single read y 222.7.
hmc5883l: single read z 215.0.
hmc5883l: single read x -271.4.
hmc5883l: single read y 197.1.
hmc5883l: single read z 186.9.
hmc5883l: single read x -266.2.
hmc5883l: single read y 209.9.
hmc5883l: single read z 186.9.
hmc5883l: set gain 330.
hmc5883l: single read x -315.1.
hmc5883l: single read y 251.5.
hmc5883l: single read z 221.2.
hmc5883l: single read x -257.5.
hmc5883l: single read y 203.0.
hmc5883l: single read z 184.8.
hmc5883l: single read x -257.5.
hmc5883l: single read y 193.9.
hmc5883l: single read z 187.9.
hmc5883l: set gain 230.
hmc5883l: single read x -378.4.
hmc5883l: single read y 274.0.
hmc5883l: single read z 269.7.
hmc5883l: single read x -265.4.
hmc5883l: single read y 200.1.
hmc5883l: single read z 187.1.
hmc5883l: single read x -265.4.
hmc5883l: single read y 208.8.
hmc5883l: single read z 182.7.
hmc5883l: finish read test.
```

```shell
./hmc5883l -e read --times=3

1/3
x is -169.580.
y is 231.800.
z is 328.180.
2/3
x is -169.580.
y is 231.800.
z is 328.180.
3/3
x is -169.580.
y is 231.800.
z is 328.180.
```

```shell
./hmc5883l -e shot --times=3

1/3
x is -175.680.
y is 234.240.
z is 325.740.
2/3
x is -168.360.
y is 239.120.
z is 323.300.
3/3
x is -167.140.
y is 233.020.
z is 325.740.
```

```shell
./hmc5883l -h

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

