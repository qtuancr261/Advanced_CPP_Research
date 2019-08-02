.Model Small
.Stack 100h
.Data
   pNhap db "Nhap vao mot so co mot chu so: $"
   pKetQua db 0ah, 0dh, "Ket qua S = 0 + 1 + .. + n = $"

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
    cout pNhap, 09h
    mov ah, 01h
    int 21h
    sub al, 30h
    mov cl, al
    xor ch, ch
    xor ax, ax
cong: add ax, cx
    loop cong
    mov bl, 10
    div bl
    push ax
    cout pKetQua, 09h
    pop dx
    add dl, 30h
    mov ah, 02h
    int 21h
    mov dl, dh
    add dl, 30h
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endp
end Main
