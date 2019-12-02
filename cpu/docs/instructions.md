## registers
each register has a size of 16 bits.
| Name | Full Name| Opcode (bin)   | opcode (hex) |
---------------------------------------------------
| r0   | general register 0  | 000 | 0x0
| r0o  | register 0 offset   | 001 | 0x1
| r1   | general register 1  | 010 | 0x2
| r1o  | register 1 offset   | 011 | 0x3
| ip   | Instruction Pointer | 100 | 0x4
| io   | Instruction offset  | 101 | 0x5
| sp   | Stack Pointer       | 110 | 0x6
| so   | Stack Offset        | 111 | 0x7
## register format:
in instructions the opcode for instructions takes up 4 bits
the first bit specifies if it is a pointer to memory.
if reg&0b1000==0b1000 then the register points to memory.
## Ofset:
each register has a corresponding to a matching 
offset register. An instruction is calculated by
```
address=offset<<16+register
```
## Instruction format
```
---------------------------------------------------------------       -----------------------------------------
|                               |                             |       |                                       |
| Instruction Opcode (8 Bits)   | Register operands (8 bits)  |       | Optional Constant Input (16 bits)     |
---------------------------------------------------------------       -----------------------------------------
```

opcode format:
```
0          0000000
Use         Opcode
constant?
```
if use constant is 1 than a constant will be used. eg ```mov r0,0x5```
The invalid instruction is reserved as 0b01111111 and 0b11111111
## Instruction listing
| Name    | Opcode | Const Opcode |  description   |
-------------------------------------
| mov     | 0x0    | 0x80         | moves data
| jmp     | 0x1    | 0x81         | sets ip to register
| call    | 0x2    | 0x82
| ret     | 0x3    |
| push    | 0x4    |
| pop     | 0x5    |
| add     | 0x6    |
| or      | 0x7    |
| xor     | 0x8    |
| and     | 0x9    |
| out     | 0xA    | | puts data in src reg onto bus dest reg is the device id

## example program
this program puts the cpu into an infinte loop


```
opcodes            | Binary
------------------------------------
mov r0,0x4         | 80 00 00 04
jmp r0             | 01 00 00 00

```
