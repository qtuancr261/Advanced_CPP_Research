.model small
.stack 100h
.data
    pNhap db 0ah, 0dh, "Nhap vao mot gia tri: $"
    pXuat db 0ah, 0dh, "Cac Gia tri vua nhap: $"
    mang db 10 DUP(?)
    heso db 10

.code
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    hienThiGiaTri macro
        local hienThi
        lea si, mang
        hienThi:
        mov dx, [si]
        add dl, 30h
        mov ah, 02h
        int 21h
        mov dl, 20h
        int 21h
        inc si
        loop hienThi  
    endm
    ;----------------------------------------------------------
    ; Nhap vao mot mang cac so nguyen duong < 10 , ket thuc khi nhan Enter, xuat ra cac so vua nhap
    xor cx, cx
    lea si, mang
    nhap:
    int21h pNhap, 09h
    mov ah, 01h
    int 21h
    cmp al, 0dh
    je thoat
    xor ah, ah
    sub al, 30h
    mov [si], ax
    inc cx
    inc si
    jmp nhap
    thoat:
    int21h pXuat, 09h
    hienThiGiaTri 
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ah, 4ch ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
