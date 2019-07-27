# Questions

## What's `stdint.h`?

The stdint.h header defines integer types,
limits of specified width integer types,
limits of other integer types and macros for integer constant expressions.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

The following exact width integer types are defined.
intN_t
uintN_t

These functions are a cross-platform implementation of a standard data type.
uint8_t is an unsigned int of 8 bits, uint32_t is an unsigned long long,
int32_t is a signed long long, and unint16_t is an unsigned 16 bit int.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE : 1
DWORD : 4 Bytes
LONG : 4 BYTES
WORD : 2 Bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

bfSize: The size, in bytes, of the bitmap file.
biSize: The number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

The height of the bitmap, in pixels.
If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner.
If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount: The number of bits-per-pixel.
The biBitCount member of the BITMAPINFOHEADER structure determines the number of bits
that define each pixel and the maximum number of colors in the bitmap.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Because incorrect file names were added.

## Why is the third argument to `fread` always `1` in our code?

fread(<buffer>,<size>,<qty>, <file>)
Since we are reading one struct at a time, the quantity is specified as 1.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek(FILE *stream, long int offset, int whence)

-sets the file position of the stream to the given offset.

stream − This is the pointer to a FILE object that identifies the stream.
offset − This is the number of bytes to offset from whence.
whence − This is the position from where offset is added. It is specified by one of the following constants:
    SEEK_SET Beginning of file
    SEEK_CUR Current position of the file pointer
    SEEK_END End of file

## What is `SEEK_CUR`?

Current position of the file pointer


## Whodunit?

professor plum with the candlestick in the library.