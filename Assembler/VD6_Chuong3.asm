.Model Small
.Stack 100h
.Data
    pNhapA db "Nhap vao mot so: $"
    pKetQuaChan db " /So nhap vao la so chan $"
    pKetQuaLe db " /So nhap vao la so le $"

.Code
Main Proc 
; set segment registers:
    mov ax, @data
    mov ds, ax
    mov es, ax
    cout MACRO thongbao
        lea dx, thongbao
        mov ah, 09h
        int 21h
        endm
    ; add your code here
    cout pNhapA
    mov ah, 01h
    int 21h
    mov bl, 2
    div bl
    cmp ah, 0        
    je soChan
    cout pKetQuaLe
    jmp thoat
soChan: cout pKetQuaChan
    
thoat:    mov ax, 4c00h ; exit to operating system.
          int 21h    
Main endp
End Main
