.Model Small
.Stack 100h
.Data
 buffer db 10 
        db ?
        db 10 DUP(' ')
 pNhap  db "Nhap vao mot so: $"
 pLoi   db 0ah, 0dh, "So nhap ko hop le, nhap lai: $"
 pHopLe db 0ah, 0dh, "So nhap vao la hop le $"
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
    cout pNhap, 09h
nhaplai:    cout buffer, 0ah
    
    cmp buffer[3], 0dh
    je hople
    cout pLoi, 09h
    jmp nhaplai
hople: cout pHopLe, 09h   
    ;xor bx, bx
	;mov bl, buffer[1]
	;mov buffer[bx+2], '$'
	;mov dx, offset buffer + 2
	;mov ah, 9
	;int 21h
    
    
thoat:    mov ax, 4c00h ; exit to operating system.
    int 21h    
Main endp
End Main
