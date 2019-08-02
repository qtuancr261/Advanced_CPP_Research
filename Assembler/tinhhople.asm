; multi-segment executable file template.

data segment
    text   DB 13,10,'nhap a: $'
    text1  DB 13,10,'khong hop le.Moi nhap lai: $'
    text2  DB 13,10,'so a hop le$'
    dulieu DB 101         ;doc toi da 100 ky tu
           DB ?           ;chua so ky tu nhan duoc
           DB 101 DUP(?)  ;ma ascii cua ky tu nhan duoc
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    mov ah,09h
    lea dx,text
    int 21h         ;hien nhap a
lap:mov ah,0Ah
    lea dx,dulieu   
    int 21h         ;nhap a(luu trong dx) 
    
    mov ax,dx       ;chuyen du lieu dx qua ax 
    mov bx,10       ;gan bx=10
    div bx          ;chia dx:ax/bx, du luu trong dx, thuong luu trong ax   
    add ax,30h      ;cong ax cho 30h 
    add dx,30h      ;cong dx cho 30h
    add ax,dx       ;cong ax voi dx
          
    cmp ax,30h
    jb  lap         ;neu a nho hon 31h thi nhap lai
    cmp ax,39h
    ja  lap         ;neu a lon hon 39h thi nhap lai
    
    mov ah,09h
    lea dx,text2
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
