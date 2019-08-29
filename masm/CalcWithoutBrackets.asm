include console.inc
.data
    res dd 0
.code
number:
        sub eax,eax ; r=0
        mov ecx,10 ; 10
    again:
        inchar bl ; input char
        sub bl,'0' ; char -> c
        jb result
        mul ecx ; r=r*10
        movzx ebx, bl
        add eax, ebx ; r=r+c
        jmp again
    result:
        ;outintln eax
    RET
    
start:
    call number
calc:
    inchar bl
        cmp bl,'+'
        je plus
        cmp bl,'-'
        je minus
        cmp bl,'*'
        je multi ; multiplication
        cmp bl,'/'
        je divi ; divide
        jne showres
    plus:
        inchar bl
        mov res,eax
        call number
        mov ebx,res
        add eax,ebx
        jo error
        jmp calc
    minus:
        inchar bl
        mov res,eax
        call number
        mov ebx,res
        sub ebx,eax
        xchg eax,ebx
        jo error
        jmp calc
    multi: ; multiplication
        inchar bl
        mov res,eax
        call number
        mov ebx,res
        mov edx, 0
        imul ebx
        jo error
        jmp calc
    divi: ; divide
        inchar bl
        mov res,eax
        call number
        mov ebx,res
        xchg eax,ebx
        mov edx, 0
        div ebx
        jo error
        jmp calc
showres:
    outintln eax
    ; сделать скобки
        jmp ex
        error:
        outstrln 'error overflow'
        jmp ex      
ex:
    exit
end start




