.Model Small
.Stack 100h
.Data
    pNhapSoPhanTu db 0ah, 0dh, "Nhap vao so phan tu cua mang: $"  
    pNhapPhanTu db 0ah, 0dh, "Phan tu: $"
    pKetQua db 0ah, 0dh, "Tong cua cac phan tu chan trong mang: $"
    so db 4
       db ?
       db 4 DUP(?)
  heso dw 10
  he2  dw 2
  soPhanTu dw ?
.Code 
Main proc
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
int21h MACRO diachi, lenh
    lea dx, diachi
    mov ah, lenh
    int 21h
endm
;-------------------------------------------------
tinhTriThapPhan MACRO so
    LOCAL tinh, thoat
    xor ax, ax
    mov di, 2
    mov al, so[di]
tinh:sub ax, 30h
    inc di
    cmp so[di], 0dh
    je thoat
    mov bl, so[di]
    mul heso
    add ax, bx
    jmp tinh
thoat: 
endm
;--------------------------------------------------
hienThiGiaTri MACRO
   LOCAL lap, hienThi
   mov ax, bx
   xor cx, cx
   xor dx, dx
lap:div heso
    push dx
    inc cx
    cmp ax, 0
    je hienThi
    xor dx, dx
    jmp lap
hienThi:pop dx
        add dl, 30h
        mov ah, 02h
        int 21h
        loop hienThi     
    
endm
;--------------------------------------------------
kiemTraChanLe MACRO giaTri
    LOCAL tiepTuc
    pop ax
    mov cx, ax
    xor dx, dx
    div he2
    cmp dx, 0
    jne tiepTuc
    add bx, cx  
tiepTuc:
endm
;-------------------------------------------------
    int21h pNhapSoPhanTu, 09h
    int21h so, 0ah
    tinhTriThapPhan so
    mov soPhanTu, ax
    xor si, si
    
 nhap:
    int21h pNhapPhanTu, 09h
    int21h so, 0ah
    tinhTriThapPhan so
    push ax
    inc si
    cmp si, soPhanTu
    je tinhTongChan
    jmp nhap
tinhTongChan:
    xor si, si
    xor bx, bx
tinh:
    kiemTraChanLe 
    inc si
    cmp si, soPhanTu
    je hienThi
    jmp tinh
hienThi:
    int21h pKetQua, 09h
    hienThiGiaTri         
    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endp


end Main ; set entry point and stop the assembler.
