### 1. chip

#### 1.1 chip info

chip name : Raspberry Pi 4B

iic pin: SCL/SDA GPIO3/GPIO2

### 2. install

#### 2.1 install info

```shell
make
```

### 3. hmc5883l

#### 3.1 command Instruction

​          hmc5883l is a basic command which can test all hmc5883l driver function:

​           -i        show hmc5883l chip and driver information.

​           -h       show hmc5883l help.

​           -p       show hmc5883l pin connections of the current board.

​           -t (reg | read <times>)

​           -t reg        run hmc5883l register test.

​           -t read      run hmc5883l read test. times means test times.

​           -c (read <times>| shot <times>)

​           -c read <times>        run hmc5883l read function. times means read times.

​           -c shot <times>         run hmc5883l shot function. times means read times.

#### 3.2 command example

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
hmc5883l: finished register test.
```

```shell
./hmc5883l -t read 3

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
hmc5883l: single read x -2.4.
hmc5883l: single read y 251.3.
hmc5883l: single read z 245.2.
hmc5883l: single read x -2.4.
hmc5883l: single read y 251.3.
hmc5883l: single read z 244.0.
hmc5883l: single read x -3.7.
hmc5883l: single read y 251.3.
hmc5883l: single read z 245.2.
hmc5883l: continuous read test.
hmc5883l: continuous read x -1.2.
hmc5883l: continuous read y 247.7.
hmc5883l: continuous read z 244.0.
hmc5883l: continuous read x -1.2.
hmc5883l: continuous read y 248.9.
hmc5883l: continuous read z 244.0.
hmc5883l: continuous read x -3.7.
hmc5883l: continuous read y 250.1.
hmc5883l: continuous read z 245.2.
hmc5883l: gain test.
hmc5883l: set gain 1370.
hmc5883l: single read x -2.2.
hmc5883l: single read y 149.7.
hmc5883l: single read z 147.5.
hmc5883l: single read x -0.7.
hmc5883l: single read y 148.2.
hmc5883l: single read z 145.3.
hmc5883l: single read x -0.7.
hmc5883l: single read y 240.2.
hmc5883l: single read z 236.5.
hmc5883l: set gain 1090.
hmc5883l: single read x -1.8.
hmc5883l: single read y 303.6.
hmc5883l: single read z 299.0.
hmc5883l: single read x -1.8.
hmc5883l: single read y 302.7.
hmc5883l: single read z 298.1.
hmc5883l: single read x -2.8.
hmc5883l: single read y 242.9.
hmc5883l: single read z 238.3.
hmc5883l: set gain 820.
hmc5883l: single read x -3.7.
hmc5883l: single read y 320.9.
hmc5883l: single read z 314.8.
hmc5883l: single read x -3.7.
hmc5883l: single read y 318.4.
hmc5883l: single read z 313.5.
hmc5883l: single read x -2.4.
hmc5883l: single read y 248.9.
hmc5883l: single read z 245.2.
hmc5883l: set gain 660.
hmc5883l: single read x -4.6.
hmc5883l: single read y 308.6.
hmc5883l: single read z 304.0.
hmc5883l: single read x -1.5.
hmc5883l: single read y 310.1.
hmc5883l: single read z 305.5.
hmc5883l: single read x -1.5.
hmc5883l: single read y 243.2.
hmc5883l: single read z 238.6.
hmc5883l: set gain 440.
hmc5883l: single read x -2.3.
hmc5883l: single read y 360.9.
hmc5883l: single read z 356.4.
hmc5883l: single read x 0.0.
hmc5883l: single read y 360.9.
hmc5883l: single read z 358.7.
hmc5883l: single read x -2.3.
hmc5883l: single read y 242.9.
hmc5883l: single read z 240.6.
hmc5883l: set gain 390.
hmc5883l: single read x -2.6.
hmc5883l: single read y 273.9.
hmc5883l: single read z 273.9.
hmc5883l: single read x -2.6.
hmc5883l: single read y 276.5.
hmc5883l: single read z 273.9.
hmc5883l: single read x -5.1.
hmc5883l: single read y 248.3.
hmc5883l: single read z 245.8.
hmc5883l: set gain 330.
hmc5883l: single read x -3.0.
hmc5883l: single read y 293.9.
hmc5883l: single read z 290.9.
hmc5883l: single read x -3.0.
hmc5883l: single read y 293.9.
hmc5883l: single read z 287.9.
hmc5883l: single read x 0.0.
hmc5883l: single read y 239.4.
hmc5883l: single read z 239.4.
hmc5883l: set gain 230.
hmc5883l: single read x 1.0.
hmc5883l: single read y 343.6.
hmc5883l: single read z 339.3.
hmc5883l: single read x 1.0.
hmc5883l: single read y 339.3.
hmc5883l: single read z 343.6.
hmc5883l: single read x 1.0.
hmc5883l: single read y 239.2.
hmc5883l: single read z 234.9.
hmc5883l: finished read test.
```

```shell
./hmc5883l -c read 3

hmc5883l: 1/3.
hmc5883l: x is 2.440.
hmc5883l: y is 237.900.
hmc5883l: z is 250.100.
hmc5883l: 2/3.
hmc5883l: x is 3.660.
hmc5883l: y is 234.240.
hmc5883l: z is 250.100.
hmc5883l: 3/3.
hmc5883l: x is 3.660.
hmc5883l: y is 234.240.
hmc5883l: z is 248.880.
```

```shell
./hmc5883l -c shot 3

hmc5883l: 1/3.
hmc5883l: x is 3.660.
hmc5883l: y is 239.120.
hmc5883l: z is 254.980.
hmc5883l: 2/3.
hmc5883l: x is 3.660.
hmc5883l: y is 239.120.
hmc5883l: z is 253.760.
hmc5883l: 3/3.
hmc5883l: x is 2.440.
hmc5883l: y is 240.340.
hmc5883l: z is 256.200.
```

```shell
./hmc5883l -h

hmc5883l -i
	show hmc5883l chip and driver information.
hmc5883l -h
	show hmc5883l help.
hmc5883l -p
	show hmc5883l pin connections of the current board.
hmc5883l -t reg
	run hmc5883l register test.
hmc5883l -t read
	run hmc5883l read test.times means test times.
hmc5883l -c read <times>
	run hmc5883l read function.times means read times.
hmc5883l -c shot <times>
	run hmc5883l shot function.times means read times.
```

