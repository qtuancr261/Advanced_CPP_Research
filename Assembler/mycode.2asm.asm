; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "Nap ten cua ban: $"
    pinfo db "Ten cua ban la: $"
    pname db 100
          db ?
          db 100 DUP(?)
         
    
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

    ; add your code here
            
    lea dx, pkey
    mov ah, 09h
    int 21h        ; output string at ds:dx
    
    lea dx, pname
    mov ah, 0ah
    int 21h
    
    lea dx, pinfo
    mov ah, 09h
    int 21h
    
    lea dx, pname
    mov ah, 09h
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
