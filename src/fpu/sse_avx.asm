section .text

global _enable_SSE
global _enable_AVX
global _enable_XSAVE

_enable_SSE:
    mov eax, 0x1
    cpuid
    test edx, 1<<26
    jz .noSSE

    mov rax, cr0
    and ax, 0xFFFB
    or ax, 0x2
    mov cr0, rax
    
    mov rax, cr4
    or ax, 3 << 9
    mov cr4, rax

    mov eax, 1          ; SSE enabled, return true
    ret
    

.noSSE:
    mov rax, 0      ; no SSE, return false
    ret


_enable_AVX:
    ;check for XSAVE
    mov eax, 0x1
    cpuid
    test ecx, 1<<26
    jz .noAVX

    mov rcx, cr4
    or rcx, 1<<18
    mov cr4, rcx

    push rax,
    push rcx,
    push rdx,

    mov ecx, 0
    xgetbv
    or eax, 7
    xsetbv

    pop rdx
    pop rcx
    pop rax

    mov eax, 0x1
    cpuid
    test ecx, 1<<28
    jz .noAVX

    push rax,
    push rcx,
    push rdx,

    xor rcx, rcx
    xgetbv
    or eax, 7
    xsetbv

    pop rdx
    pop rcx
    pop rax

    mov rax, 1      ; AVX enabled, return true
    ret

.noAVX:
    mov rax, 0      ; no AVX, return false
    ret


_disable_AVX:
    mov rcx, cr4
    or rcx, 0<<18
    mov cr4, rcx