# CoreMark
This is a simple implememtation of CoreMark.  It is based on the Coremark component of the SDK, but does not use the component due to a number on open issues:
* TIMER initialization : in component TIMER TOP is set before the TIMER is initialized.  Not incorrect per-se, but EMLIB asserts on this.
* Multiple calls to CHIP_Init: core_portme.c was probably just copied from a Studio version 4 project.  In Studio version 5, CHIP_Init is called during system initialization.  On some devices this causes a decrease in score, on EFR32xG21 it causes hard-fault exception on 2nd call.
* Use MEM_MALLOC method.  There is a minor bug in CoreMark code.  MEM_STATIC method buffer used for memory exercises is declared as uint8 array ... contents of array are type cast to pointers, this can cause alignment bus exception if array is placed at an odd alignment.  No observed issues using malloc, not sure if alignment is guaranteed 32-bit aligned.
