.Model Small
.Stack 100h
.Data
    array db 10 DUP(?)
    pNhap db 0ah, 0dh, " Nhap phan tu cua mang: $"
    pXuat db 0ah, 0dh, " Mang vua nhap vao: $"

.Code
Main Proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
cout MACRO thongbao, lenh
    lea dx, thongbao
    mov ah, lenh
    int 21h
endm
    ; add your code here
    mov bx, 0
nhap: cout pNhap, 09h
    mov ah, 01h
    int 21h
    mov array[bx], al
    inc bx
    cmp bx, 0ah
    jb nhap               
    
    cout pXuat, 09h
    mov bx, 0
xuat: mov dl, array[bx]
    mov ah, 02h
    int 21h
    mov dl, 20h; ky tu space
    int 21h
    inc bx
    cmp bx, 9
    jbe xuat     
    mov ax, 4c00h ; exit to operating system.
    int 21h    
    Main endp
end Main

