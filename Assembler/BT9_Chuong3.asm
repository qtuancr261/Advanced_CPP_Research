.Model Small
.Stack 100h
.Data
    pNhap db "Nhap vao mot so nhi phan 8 bit: $"
    pThapPhan db 0ah, 0dh, "Gia tri o he thap phan: $"
    pThapLucPhan db 0ah, 0dh, "Gia tri o he thap luc phan: $"
    so db 9
       db ?
       db 9 DUP(?)
    heso db ?
    giaTri dw ?
.Code
Main Proc
    
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;-------------------------------------------------
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;-------------------------------------------------
timTriThapPhan MACRO coSo; chuyen doi cac he 2, 8, 16 ve thap phan
    mov heso, coSo       ; gia tri se duoc luu trong ax
    xor ax, ax
    mov bx, 2
    mov al, so[2]
tinh:sub al, 30h    
    inc bx
    cmp so[bx], 0dh
    je ra
    mul heso
    add al, so[bx]
    jmp tinh
ra: mov giaTri, ax
endm
;-------------------------------------------------
hienThiGiaTri MACRO coSo
    LOCAL lap, hienThi, he16, ngat
    mov ax, giaTri 
    xor cx, cx
    mov bx, coSo
lap: div bl
    mov dl, ah
    push dx
    inc cx
    xor ah, ah
    cmp al, 0
    je hienThi
    jmp lap
hienThi: pop dx
    cmp dl, 10
    jae he16
    add dl, 30h
    jmp ngat
he16:add dl, 37h
ngat:call con1
    ;mov ah, 02h
    ;int 21h
    loop hienThi
endm


    int21h pNhap, 09h
    int21h so, 0ah
    timTriThapPhan 2
    int21h pThapPhan, 09h
    hienThiGiaTri 10
    int21h pThapLucPhan, 09h
    hienThiGiaTri 16
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endp
con1 Proc Near/Far
    mov ah, 02h
    int 21h
    RET
    con1 endp
end Main
