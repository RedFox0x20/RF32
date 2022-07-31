# RF32 Memory map

| Start Address | End Address | Purpose |
|---------------|-------------|---------|
| 0x0000        | 0x03FF      | Real Mode IVT |
| 0x0400        | 0x04FF      | BIOS Data Area |
| 0x0500        | 0x24FF      | 2K Stack |
| 0x2500        | 0x7DFF      | Stage 2 code | 
| 0x7E00        | 0x7FFF      | 512 byte Memory map - 4 bytes counter, 10 entries |
| 0x00080000    | 0x000FFFFF  | Reserved |

Memory above 1MiB is not standardised and will be system dependant, hence why in
Stage 2 we have to use a BIOS interrupt to create a memory map stored at 0x7E00

