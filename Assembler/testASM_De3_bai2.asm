.model small
.stack 100h
.data
    nhapVaoSo db 0ah, 0dh, "Nhap vao mot so thap phan: $"
    ketQua db 0ah, 0dh, "So N co N! < so vua nhap: $"
    dem dw ?
    heSo dw 10
    giaTri dw ?
code segment
.start:
main proc
    mov ax, data
    mov ds, ax
    mov es, ax
    ;----------------------------------------
    int21h macro lenh, diachi
        lea dx, diachi
        mov ah, lenh
        int 21h
    endm
    
    nhapSo macro 
        local nhap, thoat
        mov cx, 4
        xor dx, dx
        push dx
        nhap:
        mov ah, 01h
        int 21h
        xor ah, ah
        cmp al, 0dh
        je thoat
        sub al, 30h
        mov bx, ax
        pop ax
        mul heSo
        add ax, bx
        push ax
        loop nhap
        thoat:
    endm
    timGiaiThua macro giatri
        local tim, thoat
        mov ax, 5040
        mov bx, 7
        tim:
        xor dx, dx
        cmp ax, giatri
        jb thoat
        div bx
        dec bx
        jmp tim
        thoat:
        mov dx, bx
        add dl, 30h
        mov ah, 02h
        int 21h
         
    endm
    
    
        
    ; add your code here
    int21h 09h, nhapVaoSo
    nhapSo
    pop giaTri
    int21h 09h, ketQua
    timGiaiThua giaTri
    
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
main endp

end main ; set entry point and stop the assembler.
