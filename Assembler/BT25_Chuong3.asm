.model small
.stack 100h
.data
    pNhapSoPhanTu db 0ah, 0dh, "Nhap vao kich thuoc cua mang(toi da la 20): $" 
    pNhapPhanTu db 0ah, 0dh, "Nhap vao mot gia tri: $"
    pXuatTongChan db 0ah, 0dh, "Tong cua cac phan tu le: $"
    giaTri db 4
            db ?
            db 4 DUP(?)
    kichThuoc dw ?
    dem dw ?
    mang dw 20 DUP(?)
    heso dw 10
.code
main proc
    mov ax, data
    mov ds, ax
    mov es, ax
    ; MACRO-------------------------------------
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    ;---------------------------
    tinhTriThapPhan macro giaTri
        local tinh, thoat
        xor ax, ax
        mov bx, 2
        tinh:
        xor dx, dx
        mov dl, giaTri[bx]
        sub dl, 30h
        add ax, dx
        inc bx
        cmp giaTri[bx], 0dh
        je thoat
        mul heso
        jmp tinh
        thoat:
        push ax
    endm
    ;---------------------------
    hienThiGiaTri macro
        local tinh, hienThi
        pop ax
        xor cx, cx
        tinh:
        xor dx, dx
        div heso
        push dx
        inc cx
        cmp ax, 0
        je hienThi
        jmp tinh
        
        hienThi:
        pop dx
        add dl, 30h
        mov ah, 02h
        int 21h
        loop hienThi
    endm
    ;-------------------------------------------
    int21h pNhapSoPhanTu, 09h
    int21h giaTri, 0ah
    tinhTriThapPhan giaTri
    pop kichThuoc         ; nhap vao kich thuoc cua mang
    
    mov cx, kichThuoc
    lea si, mang
    nhap:                 ; nhap vao tung phan tu
    int21h pNhapPhanTu, 09h
    int21h giaTri, 0ah
    tinhTriThapPhan giaTri
    pop [si]
    add si, 2
    loop nhap
    ;-------------------------------------------
    lea si, mang
    mov dem, 0
    mov bx, kichThuoc
    xor dx, dx
    duyet:
    mov ax, [si]
    test ax, 1   ; kiem tra gia tri trong ax la chan hay le
    jz keTiep   ; neu la le thi cong vao dx
    add dx, [si]
    keTiep:
    inc dem
    cmp dem, bx
    jae thoat
    add si, 2    ; tang si len 2 vi mang co kieu dw
    loop duyet
    
    thoat:
    push dx      ; dua tong cac so le vao stack
    int21h pXuatTongChan, 09h
    hienThiGiaTri  ; dua tong vao ax va hien thi ra gia tri  
    mov ax, 4c00h ; exit to operating system.
    int 21h    
main endp
end main ; set entry point and stop the assembler.
