#include <OS_class.h>
#include "test.h"
#include"keyboard/keyboard.h"
#include"memory/functions.h"
#include"PIT/pit.h"


void IJI_OS::write_string(const char *string){
 
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }
}

void IJI_OS::next_line(){
    address = next_address;
    next_address = next_address + 160;

}

void IJI_OS::write_char( char c){
    tmp = tmp+1;
    *address++ = c;
    *address++ = color;
    *address = 0x0B;
}
void IJI_OS::write_integer(char* string, uint32_t a){
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }

    char reverseDigits[64];
    int counter = 0;
    while (a>0){
        char nextDigit = a%10+'0';
        reverseDigits[counter] = nextDigit;
        a = a/10;
        counter = counter + 1;
    }
    counter = counter-1;
    while (counter>=0){
           *address++ = reverseDigits[counter];
            *address++ = color;
            counter = counter-1;
        }
    }
 
void IJI_OS::write_hexadecimal(char* string, uint32_t a){
    if(tmp>3500){
        clearScreen();
        line = 0;
    }
   
    while( *string != 0 )
    {
        *address++ = *string++;
        *address++ = color;
        tmp = tmp+1;
    }
    char reverseDigits[64];
    char nextDigit;
    int counter = 0;
    while (a>0){
        int leftovers = a%16;
        if (leftovers < 10){
            nextDigit = leftovers + '0';
        }
        else{
            nextDigit = leftovers - 10 + 'a';
        }
        reverseDigits[counter] = nextDigit;
        a = a/16;
        counter = counter + 1;
    }
    counter = counter-1;
    while (counter>=0){
           *address++ = reverseDigits[counter];
            *address++ = color;
            counter = counter-1;
        }
 
}

void IJI_OS::interrupt_handler_3(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt   3");
    next_line();
}
void IJI_OS::interrupt_handler_2(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt  2");
    next_line();
}
void IJI_OS::interrupt_handler_1(UiAOS::CPU::ISR::registers_t regs){
    write_string_2("interrupt 1");
    next_line();
}

void IJI_OS::init(){
        clearScreen();
        write_string_2( "Hello World!");
        next_line();

    }