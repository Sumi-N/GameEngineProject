Every Casting is using either reinterpre_cast or static_cast in the program
    for example: NewHeapManager.cpp

I Remade a heapmanager for this project.
    for example: NewHeapManager.h NewHeapManager.cpp

Most BitArray instruction is done by either biwise operation or intrinsic instruction
    for example: BitArray.cpp line 7, 13, 20, 25

Defineed Macro for some of the magic numbers
    for example: FixedSizeAllocator.h line 3~6

Inline some of the small functions
    for example: FixedSizeAllocator.h Line 36~65

Have a guard banding in Debug builld
    for example: NewHeapManager.h Line 8~22

Minimum block size for FixedSizeAllocator is 200, and it is customizable in MemorySystem
    for example: MemorySystem.cpp Line 4~12