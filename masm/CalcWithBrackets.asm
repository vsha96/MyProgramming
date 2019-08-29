include console.inc
.data
    res dd 0
    ten dw 10
.code
number:
        sub eax,eax ; r=0
        ;mov ebx,10 ; 10
    again:
        inchar cl ; input next char
        cmp cl,'0'
        jb result
        cmp cl,'9'
        ja result        
        sub cl,'0' ; char -> c
        mul ten ;ebx ; r=r*10
        movzx ecx, cl
        add eax, ecx ; r=r+c
        jmp again
    result:
        ;outchar cl
        ;outintln eax
    RET
input:
        call number
        ;======================
        cmp cl,'('
        je saveres
        jmp next1
            saveres:
                                ;outstr 'pushed'
                                ;outint ebx
                                ;outstrln '//'
                call calculator
        next1:                                          
        ;======================
        
    RET
calculator:
        sub ebx,ebx
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
            cmp cl,')'
            je brack
            jne showres
        plus:
            xchg eax,ebx  
            push ebx ; �������� ��������� �� ������                                      
            call input
            pop ebx
            add eax,ebx
            jo error
            jmp calc
        minus:
            xchg eax,ebx
            push ebx
            call input
            pop ebx
            sub ebx,eax
            xchg eax,ebx
            jo error
            jmp calc
        multi: ; multiplication
            xchg eax,ebx
            push ebx
            call input
            pop ebx
            mov edx, 0
            imul ebx
            jo error
            jmp calc
        divi: ; divide
            xchg eax,ebx
            call input
            xchg eax,ebx
            mov edx, 0
            div ebx ; there is error if there are negative numbers
            jo error
            jmp calc
        brack:
            inchar cl
            RET
            jmp calc
    showres:
    RET
    
start:
    call calculator


    newline
    outstr ' result = '
    outint eax
        jmp ex
        error:
        outstrln 'error overflow'
        ex:
    exit
end start