# nucleo32f042-keeb-proto
Prototype STM32 firmware targeted towards use in a custom keyboard

# Usage
Developed on Debian Buster. No guarantees that this will work on your machine.

# To build
`$ make`

## Assumptions
- `make` is installed
- `arm-none-eabi-gcc` and `arm-none-eabi-objcopy` are in path

# To load
- Start the GDB server, and leave it running: `$ st-util`
- In another terminal: `$ arm-none-eabi-gdb`

## Assumptions
- `st-link` is installed (https://github.com/stlink-org/stlink/)
- `arm-none-eabi-gdb` is on path
