# Blue Pill - SysTick programming

![Build Passing](https://img.shields.io/badge/build-passing-brightgreen) [![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

Configure the systick timer to generate periodic interrupts. Use this timer for generating accurate delay function.

## SysTick Timer

The processor has a 24 bit system timer, SysTick, that counts down from the reload value to zero, reloads and counts down on the subsequent clocks.\
System Tick Time (SysTick) generates interrupt requests on regular basis. This allows an os to perform context switching to support multitasking. For applications that do not require an OS, the SysTick can be used for time keeping, time measurement or as an interrupt source for tasks that need to be executed regularly.\
SysTick register can only be accessed using word access.

### Control flow
![Control flow diagram for SysTick timer](https://github.com/csrohit/bluepill-baremetal-projects/blob/main/systick/resources/filled.png "SysTick timer - control flow diagram")

1. Program the reload value:\
   The reload value can be loaded by setting `LOAD` register. This value is set to 1 less that the number of clock cycles needed for the interrupt as the timer counts both reload value as well as zero. e.g. If the SysTick interrupt is required every 100 clock pulses, set RELOAD to 99.
2. Clear current value:\
   This register can be accessed using `VAL` variable. Bits *24:31* are reserved and 24 bit value can be read from bits *23:0*. Writing any value this register sets it to zero along with setting `COUNT_FLAG` to zero.
3. Configure SysTick and start:
   1. Select clock source-\
        Clock source can be set using `CLKSOURCE` bit (2) of `CTRL` register.\
        0 - AHB/8\
        1 - Processor Clock (AHB)
   2. Enable Tick interrupt-\
        To enable Tick interrupt set `TICKINT` bit (2) of `CTRL` register.
   3. Start SysTick timer-\
        `ENABLE` bit (0) of `CTRL` register enables the counter. When `ENABLE` is set to 1, the counter loads the `RELOAD` value from the `LOAD` register and then counts down. On reaching 0, it sets the `COUNTFLAG` to 1 and optionally asserts the `SysTick` depending on the value of `TICKINT`. It then loads the `RELOAD` value again, and begins counting.

## Project Working

This project configures SysTick timer and uses it to generate time accurate delay for blinking an LED. The onboard LED connected to pin C13 blinks every second.

## Dependencies

* **make**\
    Make utility is required for configuring and building this project. You can install make on linux by running command:

    ```bash
    sudo apt install build-essential
    ```

* **gcc-arm-none-eabi toolchain**\
    ARM cross-platform toolchain is required to build applications for arm mcus. Toolchain can be installed by running following command:

    ```bash
    sudo apt install gcc-arm-none-eabi
    ```

* **openocd**\
    It is an Open On Circuit Debugging tool used to flash and debug arm micro controllers. You can install openocd on linux by running command:

   ```bash
   sudo apt install openocd -y
   ```

* **Cortex Debug extension**\
    This extension for VSCode is helpful for debugging the application on Blue Pill. The contents of registers as well as memory are visible in the context menu.
    Launch VS Code Quick Open (Ctrl+P), paste the following command, and press enter.

     ```bash
    ext install marus25.cortex-debug
    ```

## Project Structure

* `src` directory contains all source files for the project
* `include` directory contains all header files for the project

### Source file description

* `STM32F103C8TX_FLASH.ld`  - linker script
* `src\main.c` - application code
* `src\startup_stm32f103c8tx.s` - assembly startup script for blue pill board
* `system_stm32f1xx.c` - clock configuration and system initialization functions
* `STM32F103.svd` - contains the description of the system contained in Arm Cortex-M processor-based microcontrollers, in particular, the memory mapped registers of peripherals. 

## Run Locally

Running the project is super easy. Just clone, build, and flash.

### Clone the project

1. Using https

    ```bash
    git clone https://github.com/csrohit/bluepill-baremetal-projects.git
    cd bluepill-baremetal-projects/systick
    ```

2. Using ssh

    ```bash
    git clone git@github.com:csrohit/bluepill-baremetal-projects.git
    cd bluepill-baremetal-projects/systick
    ```

## Configuration

All the configuration required for building this project is given below.

1. Build output directory
    In `Makefile`, output directory can be configured using variable `BUILD_DIR`.

2. Build type
    In `Makefile`, build type can be configured using variable`DEBUG`. Possible values are `Debug` and `Release`.

3. Binary name
    In `CMakeLists.txt`, output binary name can be configured using `project(<binary-name>)` macro.
    ** update above info in `.vscode/launch.json` as well for debugging to work.

## Build

Run following command in terminal to generate flashable binaries for blue pill board. Build files will be written to **Build Output Directory** as configured.

```bash
make all
```

## Flash

1. Connect STlink to PC and blue pill board using swd headers.
2. Put blue pill board in programming mode.
3. Run following to flash board with binary.

```bash
make flash
```

## Output

Onboard led connected to Pin C13 can be observed to be blinking every second.

## Debug

Click in `Run and Debug` option in VsCode sidebar. Then launch `Cortex Debug` target.

Happy debugging....
