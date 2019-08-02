.Model Small
.Stack 100h
.Data
    so db 10
       db ?
       db 10 DUP(?)
    pNhap db " Nhap vao mot so: $"
    pLoi  db 0ah, 0dh, " Khong hop le, vui long nhap lai: $"
    PHopLe db 0ah, 0dh, " Ok co gau $"
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
endM
    cout pNhap, 09h
nhap: cout so, 0ah
    xor ax, ax
    mov bl, 2
    mov cx, 0ah
cong: cmp so[bx], 0dh
    je kiemtra
    mul cx
    mov dl, so[bx]
    add ax, dx 
    sub ax, 30h
    inc bx
    jmp cong
kiemtra: cmp ax, 50
    jbe thoat
    cout pLoi, 09h
    jmp nhap
    
    
    
thoat: cout pHopLe, 09h
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endp
End Main


