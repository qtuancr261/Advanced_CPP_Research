.Model Small
.Stack 100h
.Data
    pNhapDayNhiPhan db "Nhap vao mot so nhi phan 8 bit: $"
    pThapPhan db 0ah, 0dh, "Ma thap phan: $"
    pThapLucPhan db 0ah, 0dh, "Ma hexa: $"
    so db 9       ; luu lai day nhi phan 8 bit
       db ?
       db 9 DUP(?)
    heSo db ?  ; luu lai co so cua he 2, 8, 10, 16
    giaTri dw ? ; luu lai gia tri thap phan
.Code
Main Proc    
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
;-------------------------------------------------
int21h MACRO diaChi, lenh; MACRO danh cho lenh 09h va 0ah cua ngat 21h
    lea dx, diaChi
    mov ah, lenh
    int 21h
endm
;-------------------------------------------------------
    mov heSo, 2                ; so nhap vao (hoac xuat ra) co he so dat tai day
    int21h pNhapDayNhiPhan, 09h
    int21h so, 0ah
    call tinhTriThapPhan       ; chuyen sang gia tri thap phan
    
    int21h pThapPhan, 09h
    mov heSo, 10
    call hienThiGiaTri         ; hien thi ma DEC
    
    int21h pThapLucPhan, 09h
    mov heSo, 16
    call hienThiGiaTri         ; hien thi ma HEX
    
    mov ax, 4ch ; exit to operating system.
    int 21h    
Main endp
;---------------------------------------------
tinhTriThapPhan Proc Near/Far
    xor ax, ax
    mov bx, 2 ;     so[bx], bat dau lay tu phan tu thu 2
    mov al, so[2]
tinh:sub al, 30h    
    inc bx;         tang chi so
    cmp so[bx], 0dh;neu so[bx] = ENTER thi dung viec tinh gia tri
    je ra
    mul heSo ;      ax <- al*heSo
    add al, so[bx] ;al <- al+so[bx]
    jmp tinh
ra: mov giaTri, ax ;luu lai gia tri tinh duoc vao bien dw giaTri
    RET
    tinhTriThapPhan endp
;---------------------------------------------
hienThiGiaTri proc Near/Far
    mov ax, giaTri ; dua gia tri da tinh duoc vao ax
    xor cx, cx
    xor dx, dx
lap: div heSo        ; ax/bl, ah <- du, al <- thuong
    mov dl, ah     ; dua phan du vao dl roi dua vao stack
    push dx
    inc cx         ; moi lan dua du vao stack thi tang cx len 1
    xor ah, ah     ; xoa ah, gia tri hien tai cua ax = al(phan thuong)
    cmp al, 0      ; neu thuong phep chia = 0 thi bat dau hien thi len man hinh gia tri
    je hienThi
    jmp lap
hienThi: pop dx    ; bat dau dua cac gia tri la phan du cua phep chia ra dx 
    cmp dl, 10     ; neu phan du >= 10 thi chuyen sang che do doi sang he 16
    jae he16
    add dl, 30h
    jmp ngat
he16:add dl, 37h
ngat:mov ah, 02h
    int 21h
    loop hienThi
    ret
    hienThiGiaTri endp
;---------------------------------------------
end Main
