; multi-segment executable file template.
; doc mot ky tu tu ban phim va hien len man hinh thong qua cac ham 
; cua ngat 21h
data segment
    ; add your data here!  
    numA db 100
    numC db 40
    charA db ?
    pkey db "Nhap vao mot ky tu bat ky: $"
    pLog db "Ky tu ban vua nhap la: $"
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
    mov ah, 09H
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 08H    ; nhap 1 ky tu tu ban phim, ma ASCII cua ky tu nhap
    int 21h        ; vao se duoc luu trong AL
    
    mov charA, al  ; luu ma ky tu vua nhap vao bien charA
    
    lea dx, pLog   ; nap dia chi offset cua pLog vao DX
    mov ah, 09H    ; lenh hien thi chuoi cua ngat 21h
    int 21h
    
    mov dl, charA  ; dua ma ASCII cua ky tu nhap vao DL
    mov ah, 02H    ; lenh hien ky tu len man hinh, ma ky tu duoc chua tai DL
    int 21h         
             
    mov ax, 4ch ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
