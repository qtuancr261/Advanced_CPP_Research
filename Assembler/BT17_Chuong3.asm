.model small
.stack 100h

.data 
    pNhapA db 0ah, 0dh, "Nhap vao a: $"
    pNhapB db 0ah, 0dh, "Nhap vao b: $"
    pXuatKetQua db 0ah, 0dh, "Gia tri trung binh cong: $"
    pXuatPhanThapPhan db ".5$"
    
    so db 3
       db ?
       db 3 DUP(?)
    heso db 10
    phandu db 0   
.code segment
main proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    ; add your code here
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    ;----------------------------------------------------------
    tinhTriThapPhan macro so
        local tinh, thoat
        xor ax, ax
        mov bx, 2 ; che do dia chi tuc thoi
    tinh:
        add al, so[bx]
        sub al, 30h
        inc bx
        cmp so[bx], 0dh
        je thoat
        mul heso
        jmp tinh
    thoat:
        push ax       
    endm
    ;---------------------------------------------------------
    hienThiGiaTri macro
        local chia, hienThi 
        pop ax
        xor cx, cx
        xor dx, dx
    chia:
        div heso
        mov dl, ah
        push dx
        inc cx
        cmp al, 0
        je hienThi
        xor ah, ah
        jmp chia
    hienThi:
        pop dx
        add dl, 30h
        mov ah, 02h
        int 21h
        loop hienThi 
    endm
    
  
    int21h pNhapA, 09h
    int21h so, 0ah    
    tinhTriThapPhan so ; tinh gia tri thap phan cua a
    int21h pNhapB, 09h
    int21h so, 0ah
    tinhTriThapPhan so ; tinh gia tri thap phan cua b   
    pop ax
    pop bx
    add ax, bx
    mov heso, 2
    div heso           ; (a+b)/2
    mov phandu, ah     ; luu lai phan du
    xor ah, ah
    push ax            ; dua thuong vao stack
    mov heso, 10
    int21h pXuatKetQua, 09h ; xuat ra phan thuong
    hienThiGiaTri
    cmp phandu, 0
    je thoat
    int21h pXuatPhanThapPhan, 09h  
    thoat:
    mov ax, 4c00h ; exit to operating system.
    int 21h    
main endp

end main ; set entry point and stop the assembler.
