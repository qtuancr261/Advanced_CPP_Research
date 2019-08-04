.Model Small
.Stack 100h
.Data
    pNhapHex db "Nhap vao mot so hex co toi da 2 chu so: $"
    pNhiPhan db 0ah, 0dh, "Ma nhi phan: $"
    pThapPhan db 0ah, 0dh, "Ma thap phan: $"
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
    int21h pNhapHex, 09h
    int21h so, 0ah
    
    mov heSo, 16
    call tinhTriThapPhan
    
    int21h pNhiPhan, 09h
    mov heSo, 2
    call hienThiGiaTri   
    
    int21h pThapPhan, 09h
    mov heSo, 10
    call hienThiGiaTri
    
    mov ax, 4ch ; exit to operating system.
    int 21h    
main endp
;-------------------------------------------
tinhTriThapPhan proc Near/Far
    xor ax, ax
    mov bx, 2
    mov al, so[bx]
tinh:cmp so[bx], 61h
    jb kyTuHoa
    sub al, 57h
    jmp tiepTuc
kyTuHoa: cmp so[bx], 41h
    jb kySo
    sub al, 37h
    jmp tiepTuc
kySo:sub al, 30h
tiepTuc:inc bx
    cmp so[bx], 0dh
    je thoat
    mul heso
    add al, so[bx]
    jmp tinh
thoat: mov giaTri, ax
    ret
tinhTriThapPhan endp    
;-------------------------------------------
hienThiGiaTri proc Near/Far
    mov ax, giaTri
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
