.model small
.stack 100h

.data
    ; add your data here!
    heSo db 10
    nhapCD db 0ah, 0dh, "Nhap vao chieu dai: $"
    nhapCR db 0ah, 0dh, "Nhap vao chieu rong: $"
    xuongDong db 0ah, 0dh, "$"
    CD db ?
    CR db ?
    nhapKyTu db 0ah, 0dh, "Nhap vao ky tu de ve: $"
    giaTri db 3
           db ?
           db 3 DUP(?)
    kyTu db ?
.code
Main proc
; set segment registers:
    mov ax, @data
    mov ds, ax
    mov es, ax
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    tinhTri macro giatri
        local tinh, tinhXong
        xor ax, ax
        mov bx, 2
        tinh:
        add al, giatri[bx]
        sub al, 30h
        inc bx
        cmp giatri[bx], 0dh
        je tinhXong
        mul heSo
        jmp tinh
        tinhXong:
        push ax
    endm
    veHang macro chieudai
        local ve
        int21h xuongDong, 09h
        xor cx, cx
        mov cl, chieudai
        mov dl, kytu
        mov ah, 02h
        ve:
        int 21h
        loop ve
    endm
    
    ;--------------------------------------------------
    int21h nhapCD, 09h
    int21h giaTri, 0ah
    tinhTri giaTri
    pop ax
    mov CD, al
    
    int21h nhapCR, 09h
    int21h giaTri, 0ah
    tinhTri giaTri
    pop ax
    mov CR, al
    
    int21h nhapKyTu, 09h
    mov ah, 01h
    int 21h
    mov kyTu, al
    
    ;--------------------------------------------------
    xor bx,bx
    mov bl, 0
    ve:
    veHang CD
    inc bx
    cmp bl, CR
    je thoat
    jmp ve
    
     
    thoat:
    mov ax, 4c00h ; exit to operating system.
    int 21h    
main endp

end main ; set entry point and stop the assembler.
