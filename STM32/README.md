# Easy "clone and go" repository for a libopencm3 based project.

See the youtube tutorial: https://www.youtube.com/watch?v=YEGKD6JQJyM&ab_channel=LowLevelLearning

#### Instructions Setup
```bash
sudo apt-get update

cd /lowlevel_project
sudo apt-get install stlink-tools gcc-arm-none-eabi cmake libusb-1.0-0-dev -y
git clone https://github.com/texane/stlink stlink-repo
cd stlink-repo
make -j1

cd ..
git clone --branch v1.7.0 https://github.com/stlink-org/stlink.git
cd stlink/
make -j1

cd ..
git clone https://github.com/libopencm3/libopencm3-template.git
cd libopencm3
make TARGETS='stm32/f0 stm32/f4' -j1

cd ..

git clone https://github.com/libopencm3/libopencm3-examples.git

sudo reboot
```

#### Flash to the STM microcontroller
Create a folder were the code be implemented in the embedded systems. The `STM32/my-project/` folder is brovided for the example. To compile the STM32 programs using `make` command:
```bash
cd ..
cd /STM32/my-project
make
```
To get information about your connected ST-Link programmer and STM32 device using the command:
```bash
st-info --probe
```

The output provided shows that the device is recognized:

```bash
Found 1 stlink programmers
 serial: 563f6c06657248543049223f
openocd: "\x56\x3f\x6c\x06\x65\x72\x48\x54\x30\x49\x22\x3f"
  flash: 65536 (pagesize: 1024)
   sram: 8192
 chipid: 0x0440
  descr: F0 device
```

To get more information about your device, you can try using the following commands:

Display the serial code of the device:
```bash
st-info --serial
```

Display the hex escaped serial code of the device:
```bash
st-info --hla-serial
```

Display the amount of flash memory available in the device:
```bash
st-info --flash
```

Display the amount of SRAM memory available in the device:
```bash
st-info --sram
```

Display the page size of the device:
```bash
st-info --pagesize
```

Display the chip ID of the device:
```bash
st-info --chipid
```

Display the textual description of the device:
```bash
st-info --descr
```

The final step is to flash your project:
```bash
st-flash --reset write blink-led.bin 0x8000000
```

### Debug mode

See the youtube for the detail instructions: https://www.youtube.com/watch?v=_1u7IOnivnM&ab_channel=LowLevelLearning

Install the enssesary library:

```bash
sudo apt-get install openocd gdb-multiarch -y
```

Usage:

```bash
openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f0x.cfg
gdb-multiarch ./blink-led.elf
```