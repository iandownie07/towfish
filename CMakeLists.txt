cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})


# Initialize the SDK
pico_sdk_init()


add_executable(uart
        pico_uart.cpp
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(uart pico_stdlib hardware_uart hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(uart)

# add url via pico_set_program_url
#example_auto_set_url(uart)
