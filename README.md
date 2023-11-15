# proyecto_WL55IC1
Ejemplo de uso de sensores I2C, GPS y SPI con la tarjate STM

Sensores utilizados:

MPU9250:
          - solo se leen los datos del acelerometro mpu6050.
          - por agregar el soporte al magnetometro.
TMP102:
          - sensor de temperatura.
GPS:
          - Ublox 6M - por agregar

se reciben mensajes TLV por UART1, y se devuelve el mensaje por UART2, estructura TLV que simula el medidor de agua.

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

