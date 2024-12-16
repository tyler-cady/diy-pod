cmake_minimum_required(VERSION 3.16)
project(Bootloader Version 0.1.0 LANGUAGES C) 

add_executable(bootloader)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain.cmake)

target_sources(bootloader PRIVATE
    src/main.c
    src/init.c 
    src/usb.c
    src/bootloader.c
    src/flash.c
)

target_include_directories(bootloader PRIVATE
    include
    configs 
)

# linker script
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/configs/bootloader.ld)
target_link_options(bootloader PRIVATE 
    -T ${LINKER_SCRIPT} # use the bootloader linker script
    -W1,--gc-sections   # remove unused sections from the final binary
    )

# set the compiler flags
target_compile_options(bootloader PRIVATE
    -mlongcalls 
    -mtext-section-literals
    -ffunction-sections
    -fdata-sections
    -Os                     # optimize for size
    -g3                     # Debug
    -ggdb                   # Debug    
    -gdwarf-4   
    -Wall
    -Wextra
)

set_target_properties(bootloader PROPERTIES C_STANDARD 11)
add_custom_command(Target bootloader POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex bootloader bootloader.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary bootloader bootloader.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:bootloader>
    COMMENT "Building bootloader"
    VERBATIM
)
 