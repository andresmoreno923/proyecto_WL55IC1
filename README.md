# proyecto_WL55IC1
Example of using I2C, GPS and SPI sensors with the STM card

Sensors used:

MPU9250:
- Only the data from the mpu6050 accelerometer are read.
- for adding support to the magnetometer.
  
TMP102:
- temperature sensor.
  
GPS:
- Ublox 6M - to be added

TLV messages are received through UART1, and the message is returned through UART2, a TLV structure that simulates the water meter.

# Microcontroller features

STM32WL55JC microcontroller multiprotocol LPWAN dual-core 32-bit (Arm® Cortex®-M4/M0+ at 48 MHz) in UFBGA73 package featuring:

- Ultra-low-power MCU
- RF transceiver (150 MHz to 960 MHz frequency range) supporting LoRa®, (G)FSK, (G)MSK, and BPSK modulations
- 256-Kbyte Flash memory and 64-Kbyte SRAM
- True random number generator (RNG)
- 3 user LEDs
- 3 user buttons and 1 reset push-button
- 32.768 kHz LSE crystal oscillator
- 32 MHz HSE on-board oscillator
- Board connectors:
  - USB with Micro-B
  - MIPI® debug connector
  - ARDUINO® Uno V3 expansion connector
  - ST morpho extension pin headers for full access to all STM32WL I/Os
- Delivered with SMA antenna
- Flexible power-supply options: ST-LINK, USB VBUS, or external sources
- On-board STLINK-V3 debugger/programmer with USB re-enumeration capability: mass storage, Virtual COM port, and debug port
- Comprehensive free software libraries and examples available with the STM32CubeWL MCU Package
- Support of a wide choice of Integrated Development Environments (IDEs) including IAR Embedded Workbench®, MDK-ARM, and STM32CubeIDE
- Suitable for rapid prototyping of end nodes based on LoRaWAN®, Sigfox™, wM-Bus, and many other proprietary protocols
- Fully open hardware platform
- 
# Pinout

## Pins Legend

![Texto alternativo](/img/pinout_legend_2017-06-28-2.png)

## Arduino-compatible headers

![Texto alternativo](/img/nucleo_wl55jc_arduino_left_2021_2_1.png)

![Texto alternativo](/img/nucleo_wl55jc_arduino_right_2021_2_1.png)

## Morpho headers

![Texto alternativo](/img/nucleo_wl55jc_morpho_left_2021_2_1.png)

![Texto alternativo](/img/nucleo_wl55jc_morpho_right_2021_2_1.png)

