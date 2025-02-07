cmake_minimum_required(VERSION 3.13)

project(diy-pod)

set(DEVICE_NAME "Broton_the_photon")

# Collect all source files
file(GLOB_RECURSE SOURCES 
    "src/*.c"
)

# Define the target
add_executable(diy-pod ${SOURCES})

# Link libraries
target_link_libraries(diy-pod amba_std lib_lvgl)
)
# Include directories
target_include_directories(diy-pod PRIVATE 
    ${AMBA_SDK_PATH}/include
    ${CMAKE_SOURCE_DIR}/include
)

# Set CXX standard
set_target_properties(diy-pod PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_custom_command(TARGET diy-pod POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diy-pod.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diy-pod.bin
    COMMENT "Generating firmware binary"
)

add_custom_command(TARGET diy-pod POST_BUILD
    COMMAND particle flash --usb ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/diy-pod.bin
    COMMENT "Flashing firmware to ${DEVICE_NAME}"
)