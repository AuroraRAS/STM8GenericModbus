# STM8 Modbus RTU UART Communication

This project implements a Modbus RTU slave device specifically designed for the STM8 microcontroller series. It uniquely enables the reading and writing of any memory address within the STM8 microcontroller via Modbus RTU commands, making it extremely versatile for applications needing direct access to hardware memory. The software handles UART communication interrupts, processes Modbus messages, and manages frame timeouts using a hardware timer.

## Features

- **Direct Memory Access via Modbus:** Enables reading and writing directly to any memory address within the STM8 microcontroller using Modbus RTU commands.
- **UART Communication:** Configurable baud rate for UART communication.
- **Modbus RTU Protocol:** Comprehensive handling of standard and custom Modbus functions to interact with microcontroller memory.
- **Frame Timeout Detection:** Utilizes TIM4 to effectively detect the end of Modbus frames.
- **EEPROM Configuration:** Includes a script to calculate and store configuration parameters into EEPROM, optimizing setup time and flexibility.

## Prerequisites

- **SDCC Compiler:** Utilizes the Small Device C Compiler (SDCC) to build the project.
- **stm8flash:** Employed to flash the compiled firmware onto STM8 devices.
- **Make (optional):** Helps automate the compilation and flashing processes.
- **Bash Shell:** Needed for executing configuration scripts.

## Hardware Requirements

- STM8 microcontroller (e.g., STM8S003F3)
- ST-Link V2 programmer
- UART communication setup (e.g., RS485 transceiver for Modbus operations)

## Software Setup

1. **Install SDCC Compiler:**
   ```
   sudo apt-get install sdcc
   ```

2. **Install stm8flash:**
   ```
   git clone https://github.com/vdudouyt/stm8flash.git
   cd stm8flash
   make
   sudo make install
   ```

3. **Clone the Repository:**
   ```
   git clone https://github.com/AuroraRAS/STM8GenericModbus.git
   cd STM8GenericModbus
   ```

## Configuration

Before compiling and flashing the software, configure the UART and Modbus settings using the provided script. This script tailors the necessary UART and timer settings based on specified parameters (Modbus address, baud rate, and master clock frequency) and prepares them for EEPROM storage.

1. **Run the Configuration Script from the project root:**
   ```
   chmod +x conf.sh
   ./conf.sh
   ```

## Compilation

To compile the source code for the STM8 microcontroller:

```
sdcc -mstm8 --out-fmt-ihx main.c
```

This command compiles the `main.c` file and produces an Intel HEX file, ready to be flashed to the microcontroller.

## Flashing

To flash the compiled firmware to the microcontroller, use the following command:

```
stm8flash -c stlinkv2 -p stm8s003f3 -s flash -w main.ihx
```

Additionally, to write the configuration EEPROM:

```
stm8flash -c stlinkv2 -p stm8s003f3 -s eeprom -w env.eeprom
```

## Usage

After successful flashing, the STM8 device operates as a Modbus slave. It can respond to Modbus queries by reading from or writing to any specified memory address within the microcontroller, according to the Modbus RTU protocol.

## Troubleshooting

If you encounter issues with flashing or operation, ensure all connections are secure, the correct microcontroller part number is used in commands, and that the STM8 device is powered correctly.
