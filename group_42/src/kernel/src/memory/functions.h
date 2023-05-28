//#include <stdint.h>
#include <stdlib.h>
//#include "memory.h"

void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
