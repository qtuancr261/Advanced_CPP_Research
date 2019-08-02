.model Small
.stack 100h
.data
    pNhapSoA db 0ah, 0dh, "Nhap vao a(a>=0): $"
    pNhapSoB db 0ah, 0dh, "Nhap vao b(b<=99): $" 
    pHienThiDu db 0ah, 0dh, "Du cua phep chia a/b: $"
    pHienThiThuong db 0ah, 0dh, "Thuong cua phep chia a/b: $"
    soA db 5
        db ?
        db 5 DUP(?)
    soB db 5
        db ?
        db 5 DUP(?)
    heso db 10
    ;giaTri dw ?
.code
Main Proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
tinhTriThapPhan MACRO so
    LOCAL tinh, thoat
    xor ax, ax
    mov bx, 2   ; che do dia chi thuc thoi
    mov al, so[bx]
tinh:sub al, 30h
    inc bx
    cmp so[bx], 0dh
    je thoat
    mul heso
    add al, so[bx]
    jmp tinh
thoat: push ax
endm
;--------------------------------------------------
hienThiGiaTri MACRO
    LOCAL lap, hienThi 
    pop ax
    xor cx, cx
    xor dx, dx
lap:div heso
    mov dl, ah
    push dx
    inc cx
    xor ah, ah
    cmp al, 0
    je hienThi
    jmp lap
hienThi:pop dx
    add dl, 30h
    mov ah, 02h
    int 21h
    loop hienThi
endm
    ; add your code here
    int21h pNhapSoA, 09h
    int21h soA, 0ah
    tinhTriThapPhan soA
    
    int21h pNhapSoB, 09h
    int21h soB, 0ah
    tinhTriThapPhan soB
    
    pop dx
    pop ax
    div dl
    mov dl, ah
    xor ah, ah
    push ax
    push dx
    
    int21h pHienThiDu, 09h
    hienThiGiaTri
    int21h pHienThiThuong, 09h
    hienThiGiaTri
    
    mov ah, 4ch ; exit to operating system.
    int 21h    
Main endp

end Main ; set entry point and stop the assembler.
