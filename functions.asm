section .rodata
    three dq 3.0

section .text
; e ^ (-x) + 3
global f1
f1:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16
    
    fld qword[ebp + 8]
    fchs
    fldl2e
    fmulp
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    faddp
    fscale
    fstp st1
    fld qword[three]
    faddp
    
    leave
    ret



; 2x - 2
global f2
f2:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16

    fld qword[ebp + 8]
    fld1
    fsubp
    mov dword[esp], 2
    fild dword[esp]
    fmulp

    leave
    ret
    
    
    
; 1 / x
global f3
f3:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16
    
    fld1
    fld qword[ebp + 8]
    fdivp
    
    leave
    ret



; -e ^ (-x)
global pf1
pf1:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16
    
    fld qword[ebp + 8]
    fchs
    fldl2e
    fmulp
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    faddp
    fscale
    fstp st1
    fchs
    
    leave
    ret



; 2
global pf2
pf2:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16

    mov dword[esp], 2
    fild dword[esp]

    leave
    ret
    
    
    
; -1 / x ^ 2
global pf3
pf3:
    finit
    push ebp
    mov ebp, esp
    sub esp, 16
    
    fld1
    fchs
    fld qword[ebp + 8]
    fdivp
    fld qword[ebp + 8]
    fdivp
    
    leave
    ret