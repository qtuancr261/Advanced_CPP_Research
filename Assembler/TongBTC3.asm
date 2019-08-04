; multi-segment executable file template.
.Model Small
.Stack 100h
.Data   
    ; add your data here!
    pnhapA db " Nhap vao a: $"
    pnhapB db " Nhap vao b: $"
    pketQua db "   Ket qua a + b : $" 
.Code 
 Main Proc
    cout MACRO thongBao
        lea dx, thongBao
        mov ah, 09h
        int 21h
        ENDM    
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    ; add your code here          
    cout pnhapA       ; hien nhap a             
    mov ah, 01h
    int 21h        ; nhap a
    mov bl, al     ; luu ma ASCII cua a vao bl
    sub bl, 30h    ; tru di cho 30H
    
    cout pnhapB       ; hien nhap b
    mov ah, 01h
    int 21h        ; nhap b
    sub al, 30h    ; tru di cho 30H
    add al, bl     ; cong hai ma ASCII(da tru di 30H) cua a (bl) va b (al)
    mov ah, 0      ; xoa ah de AX chua chinh xac ma so da cong
    mov bl, 10
    div bl         ; AX/BL thuong luu trong AL, du luu trong AH
    push ax        ; dua thuong va du vao stack
    
    cout pketQua       ; in ra thong bao ket qua
    pop dx         ; nap ket qua tu stack vao dx
    add dl, 30h    ; dl chua thuong, 
    mov ah, 02h
    int 21h        ; hien thuong
    
    mov dl, dh     ; dh chua du, chuyen phan du vao al
    add dl, 30h
    mov ah, 02h
    int 21h        ; hien phan du
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
 Main Endp
 End Main

; set entry point and stop the assembler.
