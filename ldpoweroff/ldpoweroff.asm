; ----------------------------------------------------------------------------
; ldpoweroff.asm
;
; This is a Win32 console program that puts the display into standby
; then exits.  It needs to be linked with a C library.
; ----------------------------------------------------------------------------

global  _main
extern  _FindWindowA@8
extern  _PostMessageA@16
extern  _ExitProcess@4

section .data
    classname: db  'Progman', 0
    hProgman : dd  0
    
section .text
_main:
    push    dword 0
    push    dword classname
    call    _FindWindowA@8
    
    or      eax, eax
    jz      .quit
    
    mov     [hProgman], eax
    push dword 2
    push dword 61808
    push dword 274
    push dword [hProgman]
    call _PostMessageA@16
    
.quit   xor eax, eax
    push eax
    call _ExitProcess@4
    ret
