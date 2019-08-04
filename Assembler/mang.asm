.model small
.stack 100h
.data 
    mang db 10 DUP(?)
    pkey db "press any key...$"

.code segment
main proc
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
        
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax   
    
    lea si, mang
    mov ah, 01h
    int 21h
    

   
    int21h pkey, 09h  
    
    mov ah, 4ch
    int 21h    
main endp
end  main
