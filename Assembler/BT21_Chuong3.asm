.Model Small
.Stack 100h
.Data
    pNhapSo db 0ah, 0dh, "Nhap vao mot so n (1<= n <= 360): $"
    pKetQua db 0ah, 0dh, "Tong N = 1+2+...+n = $"
    so db 4
       db ?
       db 4 DUP(?)
    heso dw 10
.Code
Main Proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;--------------------------
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;--------------------------
tinhTriThapPhan MACRO so, heso
    LOCAL tinh, thoat
    xor ax, ax
    mov bx, 2
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
;--------------------------
hienThiGiaTri MACRO heso
    pop ax
    xor cx, cx
    xor dx, dx
chia:div heso
    push dx
    inc cx
    cmp ax, 0
    je hienThi
    xor dx, dx
    jmp chia
hienThi:
    pop dx
    add dl, 30h
    mov ah, 02h
    int 21h
    loop hienThi
endm         
    ; add your code here
    int21h pNhapSo, 09h
    int21h so, 0ah
    tinhTriThapPhan so, heso
    pop cx
    xor ax, ax
cong:add ax, cx
    loop cong
    push ax
    
    int21h pKetQua, 09h
    hienThiGiaTri heso
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endm

end Main ; set entry point and stop the assembler.
