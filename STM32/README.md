Easy "clone and go" repository for a libopencm3 based project.

see the youtube howto: https://www.youtube.com/watch?v=YEGKD6JQJyM&ab_channel=LowLevelLearning

sudo apt-get update

mkdir ~/lowlevel_project
cd ~/lowlevel_project
sudo apt-get install stlink-tools gcc-arm-none-eabi cmake libusb-1.0-0-dev -y
git clone https://github.com/texane/stlink stlink-repo
git clone https://github.com/TPODAvia/raspberry-IO.git
cd stlink-repo
make -j1

git clone --branch v1.7.0 https://github.com/stlink-org/stlink.git
cd stlink/
make -j1

git clone https://github.com/stm32duino/stm32flash
cd stm32flash/
sudo make install

# Instructions
 1. git clone --recurse-submodules https://github.com/libopencm3/libopencm3-template.git your-project
 2. cd your-project
 3. make TARGETS='stm32/f0 stm32/f4' -j1 # (Only needed once)
 cd ..
 4. make

st-flash --reset write blink-led.bin 0x8000000

It seems that you are trying to get information about your connected ST-Link programmer and STM32 device using the st-info --probe command. The output you provided shows that the device is recognized, but the chipid and description are unknown:

Found 1 stlink programmers
 serial: 303030303030303030303031
openocd: "\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x31"
  flash: 0 (pagesize: 0)
   sram: 0
 chipid: 0x0000
  descr: unknown device
To get more information about your device, you can try using the following commands:

Display the serial code of the device:
st-info --serial
Display the hex escaped serial code of the device:
st-info --hla-serial
Display the amount of flash memory available in the device:
st-info --flash
Display the amount of SRAM memory available in the device:
st-info --sram
Display the page size of the device:
st-info --pagesize
Display the chip ID of the device:
st-info --chipid
Display the textual description of the device:
st-info --descr


If you have an older git, or got ahead of yourself and skipped the ```--recurse-submodules```
you can fix things by running ```git submodule update --init``` (This is only needed once)

# Directories
* my-project contains your application
* my-common-code contains something shared.

# As a template
You should replace this with your _own_ README if you are using this
as a template.


# Debug mode

See the youtube howto: https://www.youtube.com/watch?v=_1u7IOnivnM&ab_channel=LowLevelLearning

sudo apt-get install openocd
openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f0x.cfg

sudo apt install gdb-multiarch
gdb-multiarch ./blink-led.elf