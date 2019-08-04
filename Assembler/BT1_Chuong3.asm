.Model Small
.Stack 100h
.Data
    pNhap db "Nhap vao mot so nhi phan 8 bit: $"
    pThapPhan db 0ah, 0dh, "Gia tri thap phan: $"
    so db 9
       db ?
       db 9 DUP(?)
    heso db 02h
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

timTri MACRO
    xor ax, ax
    mov bl, 2
    mov al, so[2]
tinh:sub al, 30h    
    inc bx
    cmp so[bx], 0dh
    je ra
    mul heso
    add al, so[bx]
    jmp tinh
ra: 
endm

    mov bx, 01
    cout pNhap, 09h
    cout so, 0ah
    timTri
    xor bx, bx
    mov bl, 10
    div bl
    push ax
    cout pThapPhan, 09h
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
