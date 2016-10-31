A small tool written in assembler that puts your Windows computer's display to sleep. Overall, a programming excercise.

It needs to be compiled with [nasm](http://www.nasm.us) and linked with [MinGW](https://sourceforge.net/projects/mingw/), like so:
```bash
nasm -fwin32 ldpoweroff.asm
gcc -o ldpoweroff.exe ldpoweroff.obj
strip ldpoweroff.exe
```
