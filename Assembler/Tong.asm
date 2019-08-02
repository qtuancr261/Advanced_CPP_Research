; multi-segment executable file template.

data segment
    ; add your data here!
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    mov ax, 0
    mov cx, 99
lap:add ax, cx
    loop lap 
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
