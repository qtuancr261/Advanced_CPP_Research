.model small
.stack 100h

.data
    pNhapKichThuoc db 0ah, 0dh, "Nhap vao kich thuoc cua mang (toi da la 20): $"
    pNhapPhanTu db 0ah, 0dh, "Nhap phan tu: $"
    pXuatMang db 0ah, 0dh, "Mang sau khi da sap xep tang dan: $"
    mang dw 20 DUP(?)
    giaTri db 4
           db ?
           db 4 DUP(?)
    max dw 0
    min dw 0
    heso dw 10       
    kichthuoc dw 0
    kichthuoc2 dw 0
    dem dw 0
.code segment
main proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
    ;-------------------------------------------------------------
    int21h macro diachi, lenh
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    tinhTriThapPhan macro str
        local tinh, thoat
        xor ax, ax
        mov bx, 2
        tinh:
        xor dx, dx
        mov dl, str[bx]
        sub dl, 30h
        add ax, dx
        inc bx
        cmp str[bx], 0dh
        je thoat
        mul heso
        jmp tinh
        thoat:
        push ax
    endm
    hienThi macro giatri
        local hienSo, tachSo
        mov ax, giatri
        xor cx, cx
        tachSo:
        xor dx, dx
        div heso
        push dx
        inc cx
        cmp ax, 0
        je hienSo
        jmp tachSo
        hienSo:
        pop dx
        add dl, 30h
        mov ah, 02h
        int 21h 
        loop hienSo
        mov dl, 20h
        int 21h 
    endm
    
    ;------------------------------------------------------------        
    int21h pNhapKichThuoc, 09h
    int21h giaTri, 0ah
    tinhTriThapPhan giaTri
    pop ax
    mov kichthuoc, ax
    mov kichthuoc2, ax
    
    lea si, mang
    mov cx, kichThuoc
    nhapMang:   
    int21h pNhapPhanTu, 09h
    int21h giaTri, 0ah
    tinhTriThapPhan giaTri
    pop [si]
    add si, 2
    loop nhapMang
    ;------------------------------------------------------------
    lea si, mang
    lap1:
    dec kichthuoc2
    inc dem
    mov di, si
    mov cx, kichthuoc2
    cmp cx, 0
    je thoatSapXep
    mov dx, kichthuoc
    lap2:
    add di, 2
    mov ax, [si] ; dat x1 vao ax
    mov bx, [di] ; dat x2 vao bx
    ;mov cx, kichThuoc
    cmp ax, bx
    jb keTiep
    xchg ax, [di]
    xchg bx, [si]
    keTiep:
    loop lap2
    add si, 2
    cmp dem, dx
    jb lap1
    ;-------------------------------------------------
    thoatSapXep:
    int21h pXuatMang, 09h
    lea si, mang
    mov cx, kichthuoc
    xuatMang:
    mov dem, cx
    hienThi [si]
    add si, 2
    mov cx, dem
    loop xuatMang
    
    
    mov ah, 4ch ; exit to operating system.
    int 21h    
main endp

end main ; set entry point and stop the assembler.
