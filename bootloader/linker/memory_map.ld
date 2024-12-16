/* memory_map.ld */ 

MEMORY 
{
    bootrom     (rx)  : ORIGIN = 0x00001000, LENGTH = 0x00004000   /* 16 KB Bootloader */
    approm      (rx)  : ORIGIN = 0x00010000, LENGTH = 0x00100000   /* Application (up to 1 MB) */
    iram        (rwx) : ORIGIN = 0x40080000, LENGTH = 0x00020000   /* 128 KB Instruction RAM */
    dram        (rwx) : ORIGIN = 0x3FFAE000, LENGTH = 0x00020000   /* 128 KB Data RAM */
    rtc_sram    (rwx) : ORIGIN = 0x50000000, LENGTH = 0x00004000   /* 16 KB RTC SRAM */

}

__bootrom_start__ = ORIGIN(bootrom);
__bootrom_size__  = LENGTH(bootrom);
__aaprom_start__  = ORIGIN(approm);
__approm_size__   = LENGTH(approm);
__iram_start__    = ORIGIN(iram);
__iram_size__     = LENGTH(iram);
__dram_start__    = ORIGIN(dram);
__dram_size__     = LENGTH(dram);
__rtc_sram_start__= ORIGIN(rtc_sram);
__rtc_sram_size__ = LENGTH(rtc_sram);