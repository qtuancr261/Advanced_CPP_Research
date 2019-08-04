.Model Small
.Stack 100h
.Data
    pNhap db 0ah, 0dh, "Nhap vao mot so nguyen khong am: $"
    soA db 4
        db ?
        db 4 DUP(?)
    soB db 4
        db ?
        db 4 DUP(?)
    pKetQua db 0ah, 0dh, "Tong cua hai so vua nhap: $"
    ketQua dw ?
    pLoi db 0ah, 0dh, "Tong cua hai so nhap vao > 129, hay nhap lai.... $"
    heSo db 10 
.code 
; set segment registers:
main proc
    mov ax, data
    mov ds, ax
    mov es, ax
;------------------------------------
int21h MACRO diaChi, lenh
    mov ah, lenh
    lea dx, diaChi
    int 21h
endm
;-----------------------------------
tinhTriThapPhan MACRO so, heSo
    LOCAL tinh, thoat
    xor ax, ax
    mov bx, 2
    mov al, so[bx]
tinh: sub al, 30h
    inc bx
    cmp so[bx], 0dh
    je thoat
    mul heSo
    add al, so[bx]
    jmp tinh
thoat: push ax
    endm
;-----------------------------------
hienThiGiaTri MACRO giaTri,heSo
    LOCAL lap, hienThi
    mov ax, giaTri
    xor cx, cx
    xor dx, dx
lap:div heSo
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
      
;----------------------------------- 
nhap:int21h pNhap, 09h
    int21h soA, 0ah
    tinhTriThapPhan soA, heSo
    
    int21h pNhap, 09h
    int21h soB, 0ah
    tinhTriThapPhan soB, heSo
    
    pop ax
    pop dx
    add ax, dx
    mov ketQua, ax
    int21h pKetQua, 09h
    hienThiGiaTri ketQua, heSo
    cmp ketQua, 129
    jbe thoat
    int21h pLoi, 09h
    jmp nhap
thoat:mov ax, 4ch ; exit to operating system.
    int 21h    
main endp
end main
