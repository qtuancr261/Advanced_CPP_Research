.Model Small
.Stack 100h
.Data
    pNhapA db " Nhap vao a: $"
    pNhapB db " Nhap vao b: $"
    pKetQua db " Ket qua a*b = $"
.Code
Main Proc 
; set segment registers:
    mov ax, @data
    mov ds, ax
    mov es, ax
    ; add your code here
    cout MACRO thongbao
    lea dx, thongbao
    mov ah, 09h
    int 21h
    ENDM
    
    cout pNhapA
    mov ah, 01h
    int 21h
    mov bl, al   ; chuyen ma ASCII vua nhan vao bl
    sub bl, 30h  ; tru 30h
    
    cout pNhapB
    mov ah, 01h
    int 21h
    sub al, 30h  ; tru 30h
    mul bl       ; nhan bl voi al, ket qua luu trong ax
    mov bl, 10
    div bl       ; chia ax cho bl, thuong luu trong al, du trong ax
    push ax      ; push thuong va du vao stack
    
    cout pKetQua
    pop dx       ; pop thuong va du ra dx(dl chua thuong, dh chua du) 
    add dl, 30h  ; cong thuong voi 30h de ra ky tu can xuat
    mov ah, 02h
    int 21h
    
    mov dl, dh   ; dua du qua dl
    add dl, 30h  ; cong du voi 30h de ra ky tu can xuat
    mov ah, 02h
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main Endp
End Main
