.model small
.stack 100h

.data
    pNhapKichThuoc db 0ah, 0dh, "Nhap vao kich thuoc cua mang (toi da la 20): $"
    pNhapPhanTu db 0ah, 0dh, "Nhap phan tu: $"
    pXuatMax db 0ah, 0dh, "Max = $"
    pXuatMin db 0ah, 0dh, "Min = $"
    mang dw 20 DUP(?)
    giaTri db 4
           db ?
           db 4 DUP(?)
    max dw 0
    min dw 0
    heso dw 10       
    kichthuoc dw 0
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
    endm
    
    ;------------------------------------------------------------        
    int21h pNhapKichThuoc, 09h
    int21h giaTri, 0ah
    tinhTriThapPhan giaTri
    pop kichthuoc
    
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
    mov ax, [si] ; dat max vao ax
    mov bx, [si] ; dat min vao bx
    mov cx, kichThuoc
    timMaxMin:
    cmp [si], ax
    jb ganMin
    mov ax, [si]
    ganMin:
    cmp [si], bx
    ja keTiep
    mov bx, [si]
    keTiep:
    add si, 2
    loop timMaxMin
    mov max, ax
    mov min, bx
    int21h pXuatMax, 09h
    hienThi max
    int21h pxuatMin, 09h
    hienThi min
    
    mov ah, 4ch ; exit to operating system.
    int 21h    
main endp

end main ; set entry point and stop the assembler.
