#include "gdt.h"

#define GDT_ENTRIES 5

IJI_OS::GDT::gdt_entry_t gdt[GDT_ENTRIES];
IJI_OS::GDT::gdt_ptr_t gdt_ptr;


void IJI_OS::GDT::init_gdt() asm ("init_gdt");


extern "C" {
    extern void gdt_flush(uint32_t);
}


void IJI_OS::GDT::init_gdt()
{
    
    gdt_ptr.limit = sizeof( IJI_OS::GDT::gdt_entry_t) * GDT_ENTRIES - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    
    gdt_set_gate(0, 0, 0, 0, 0);            
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); 

   
    
    gdt_flush((uint32_t)&gdt_ptr);
}


void IJI_OS::GDT::gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}