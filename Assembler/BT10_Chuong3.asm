.Model Small
.Stack 100h
.Data
    pNhapThapPhan db "Nhap vao mot so thap phan <=255: $"
    pNhiPhan db 0ah, 0dh, "Ma nhi phan: $"
    pThapLucPhan db 0ah, 0dh, "Ma hex: $"
    so db 10
       db ?
       db 10 DUP(?) 
    giaTri dw ?
    heSo db ?
.code
main proc
    mov ax, data
    mov ds, ax
    mov es, ax
;-----------------------
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;-----------------------
    int21h pNhapThapPhan, 09h
    int21h so, 0ah
    
    mov heSo, 10
    call tinhTriThapPhan
    
    int21h pNhiPhan, 09h
    mov heSo, 2
    call hienThiGiaTri   
    
    int21h pThapLucPhan, 09h
    mov heSo, 16
    call hienThiGiaTri
    
    mov ax, 4ch ; exit to operating system.
    int 21h    
main endp
;-------------------------------------------
tinhTriThapPhan proc Near/Far
    xor ax, ax
    mov bx, 2
    mov al, so[bx]; che do dia chi truc tiep
tinh:sub al, 30h
    inc bx
    cmp so[bx], 0dh
    je thoat
    mul heso
    add al, so[bx]
    jmp tinh
thoat: mov giaTri, ax; che do dia chi thanh ghi
    ret
tinhTriThapPhan endp    
;-------------------------------------------
hienThiGiaTri proc Near/Far
    mov ax, giaTri  ; che do dia chi truc tiep
    xor cx, cx
    xor dx, dx
lap:div heSo
    mov dl, ah ; che do dia chi thanh ghi
    push dx
    inc cx
    xor ah, ah
    cmp al, 0
    je hienThi
    jmp lap
hienThi:pop dx
    cmp dl, 10
    jae he16
    add dl, 30h
    jmp ngat
he16:add dl, 37h
ngat:mov ah, 02h
     int 21h
     loop hienThi
     ret
hienThiGiaTri endp            
end main
