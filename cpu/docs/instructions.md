## registers
each register has a size of 16 bits.
| Name | Full Name| Opcode (bin)   |
------------------------------------
| r0   | general register 0  | 000 |
| r0o  | register 0 offset   | 001 |
| r1   | general register 1  | 010 |
| r1o  | register 1 offset   | 011 |
| ip   | Instruction Pointer | 100 |
| io   | Instruction offset  | 101 |
| sp   | Stack Pointer       | 110 |
| so   | Stack Offset        | 111 |
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
| Name    | Opcode |
----------------------
| mov     | 0x0    |
| jmp     | 0x1    |
| call    | 0x2    |
| ret     | 0x3    |
| push    | 0x4    |
| pop     | 0x5    |
| add     | 0x6    |
| adds    | 0x7    |
| or      | 0x8    |
| xor     | 0x9    |
| and     | 0xA    |

