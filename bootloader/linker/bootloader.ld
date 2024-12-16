/**
* Linker file for the bootloader
* ESP32s3:
    * 128 bit data bus and SIMD instructions
    * 384 kb ROM
    * 512 kb SRAM
    * 16 kb SRAM in RTC
    
*/


MEMORY
{
    IRAM0 :    ORIGIN = 0x40080000, LENGTH = 0x20000   /* 128 KB Instruction RAM */
    DRAM0 :    ORIGIN = 0x3FFAE000, LENGTH = 0x20000   /* 128 KB Data RAM */
    RTC_FAST : ORIGIN = 0x50000000, LENGTH = 0x4000    /* 16 KB RTC SRAM */
    FLASH :    ORIGIN = 0x1000,     LENGTH = 0x7000    /* Bootloader in Flash */
}

STACK_SIZE = 0x2000; 

SECTIONS
{
    .text :
    {
        
    } > rom 
}