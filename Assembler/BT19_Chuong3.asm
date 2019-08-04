.Model Small
.Stack 100h
.Data
    soA db 3
        db ?
        db 3 DUP(?)
    soB db 3
        db ?
        db 3 DUP(?)
    pNhapSo db 0ah, 0dh, " Nhap vao mot so : $"
    pKetQua db 0ah, 0dh, " UCLN: $"
    heso db 10        

.Code
Main Proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;------------------------------
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;------------------------------
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
thoat:push ax
endm
;-----------------------------
hienThiGiaTri MACRO heso
   LOCAL tinh, hienThi
   mov ax, bx
   xor cx, cx
   xor dx, dx
tinh:div heso
   mov dl, ah
   push dx
   inc cx
   cmp al, 0
   je hienThi
   xor ah, ah
   jmp tinh
hienThi: pop dx
   add dl, 30h
   mov ah, 02h
   int 21h
   loop hienThi                 
endm

    
;-----------------------------    
    ; add your code here
    int21h pNhapSo, 09h
    int21h soA, 0ah
    tinhTriThapPhan soA, heso
    
    int21h pNhapSo, 09h
    int21h soB, 0ah
    tinhTriThapPhan soB, heso
    
    pop ax
    pop bx
soSanh:cmp ax, bx
    jb ganB
    jmp chia
ganB:xchg ax, bx
chia:div bl
    cmp ah, 0
    je hienThi
    mov al, ah
    xor ah, ah
    jmp soSanh
hienThi:
    int21h pKetQua, 09h        
    hienThiGiaTri heso
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endm


end Main ; set entry point and stop the assembler.
