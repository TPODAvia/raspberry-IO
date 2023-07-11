To upload scripts to the ESP32 DEVKIT V1 using C++ and flash the ESP32 using only terminal, follow these steps:

1. Install the required tools
First, we need to install the required tools. We will use PlatformIO, which is a cross-platform IoT development environment, compatible with different platforms including ESP32. It is capable of replacing the Arduino IDE and can be used from the command line, making it a good choice for this task.

To install PlatformIO, you first need to install Python and its package manager pip. You can do this by running the following commands in the terminal:

```bash
sudo apt update
sudo apt install python3 python3-pip
```

Then, install PlatformIO with pip:

```bash
pip3 install platformio
```

To add PlatformIO to the PATH, open `~/.bashrc` with a text editor:

```bash
nano ~/.bashrc
```

Then, add the following line to the end of the file:

```bash
export PATH=$PATH:$HOME/.platformio/penv/bin
```

This line adds the directory where PlatformIO is installed to your PATH.

Save the file and exit the text editor (in nano, you can do this by pressing `Ctrl+X`, then `Y` to confirm, then `Enter` to save).

Finally, you have to reload `~/.bashrc` for the changes to take effect. You can do this by closing and reopening your terminal, or by running the following command:

```bash
source ~/.bashrc
```

2. Create a new project
Next, let's create a new project. Use the platformio command to create a new project. You need to specify the board id, in this case esp32dev, and the project name, which we'll call Blink.

```bash
platformio project init --board esp32dev --project-dir /home/ubuntu/lowlevel_project/raspberry-IO/ESP32/Blink
```

This will create a new directory called Blink with the necessary files for your project.

3. Write the blink script
Now navigate into the Blink directory and open the src/main.cpp file. This is where you will write your C++ code.

```bash
cd Blink
nano src/main.cpp
```
Here is a simple blink script in C++ that will blink the built-in LED on GPIO 2 randomnerdtutorials.com:

```bash
#include <Arduino.h>

void setup() 
{
  pinMode(2, OUTPUT);
}

void loop() 
{
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
}
```

Save the file and exit the editor (Ctrl+X to exit, then Y to save and Enter to confirm).

4. Upload the script to the ESP32
Finally, you can compile and upload the code to your ESP32. Connect your ESP32 to your computer via a USB cable, then run the following command:

```bash
platformio run --target upload
```

To blink an LED using registers on the ESP32, you need to directly interact with the hardware registers instead of using the Arduino functions digitalWrite() and pinMode().

The ESP32 has registers that can be used to control the GPIO pins. Here's how you can blink an LED using these registers:

```bash
#define LED_GPIO 2 //GPIO number where your LED is connected

void setup() 
{
  // Set the GPIO as output
  pinMode(LED_GPIO, OUTPUT);
}

void loop() 
{
  // Set the GPIO high
  REG_WRITE(GPIO_OUT_W1TS_REG, BIT(LED_GPIO));

  delay(1000);

  // Set the GPIO low
  REG_WRITE(GPIO_OUT_W1TC_REG, BIT(LED_GPIO));

  delay(1000);
}
```

To print "Hello World" using serial communication with the ESP32, you can use the uart_write_bytes() function to send bytes over the UART interface. This can be done by modifying the echo example from the ESP-IDF.

Create "Hello World" scripts:

```bash
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"


#define ECHO_TEST_TXD (CONFIG_EXAMPLE_UART_TXD)
#define ECHO_TEST_RXD (CONFIG_EXAMPLE_UART_RXD)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)
#define ECHO_UART_PORT_NUM      (CONFIG_EXAMPLE_UART_PORT_NUM)
#define ECHO_UART_BAUD_RATE     (CONFIG_EXAMPLE_UART_BAUD_RATE)
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)
#define BUF_SIZE (1024)

static void echo_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
};
    int intr_alloc_flags = 0;
#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif
    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    while (1) 
    {
        // Write "Hello World" to the UART
        uart_write_bytes(ECHO_UART_PORT_NUM, "Hello World\n", 12);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

void app_main(void)
{
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
```