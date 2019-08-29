include console.inc
.data
    res dd 0
.code
number:
        sub eax,eax ; r=0
        mov ebx,10 ; 10
    again:
        inchar cl ; input next char
        cmp cl,'0'
        jb result
        cmp cl,'9'
        ja result        
        sub cl,'0' ; char -> c
        mul ebx ; r=r*10
        movzx ecx, cl
        add eax, ecx ; r=r+c
        jmp again
    result:
        ;outintln eax
    RET
input:
        call number
        jmp calc
        ;======================
                ;jmp next1
        cmp cl,'('
        je saveeax
        ;jmp next1
saveeax:   
        inchar bl
        push eax
        sub eax,eax
        jmp start
next1:  
        ;======================
        
    RET
    
start:
    call input
calc:
        
        cmp cl,'+'
        je plus
        cmp cl,'-'
        je minus
        cmp cl,'*'
        je multi ; multiplication
        cmp cl,'/'
        je divi ; divide
        jne showres
    plus:
        mov res,eax
        call number
        mov ebx,res
        add eax,ebx
        jo error
        jmp calc
    minus:
        mov res,eax
        call number
        mov ebx,res
        sub ebx,eax
        xchg eax,ebx
        jo error
        jmp calc
    multi: ; multiplication
        mov res,eax
        call number
        mov ebx,res
        mov edx, 0
        imul ebx
        jo error
        jmp calc
    divi: ; divide
        mov res,eax
        call number
        mov ebx,res
        xchg eax,ebx
        mov edx, 0
        div ebx ; there is error if there are negative numbers
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








