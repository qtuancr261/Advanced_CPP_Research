.Model Small
.Stack 100h
.Data
    pNhapSo db 0ah, 0dh, "Nhap vao mot so n (1=< n <= 8): $"    
    pKetQua db 0ah, 0dh, "Giai thua n! = $"
    heso dw 10
.code
Main Proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;---------------------------
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;---------------------------
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
hienThi: pop dx
    add dl, 30h
    mov ah, 02h
    int 21h
    loop hienThi
endm
;------------------------------------------
    ; add your code here
    int21h pNhapSo, 09h
    mov ah, 01h
    int 21h
    sub al, 30h
    
    xor ah, ah
    mov cx, ax
    mov ax, 1
nhan:mul cx
    loop nhan
    push ax
    int21h pKetQua, 09h
    hienThiGiaTri heso
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endm


end Main ; set entry point and stop the assembler.
