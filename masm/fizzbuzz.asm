include console.inc
.data
    fizz db 'fizz'
    f db 3
    buzz db 'buzz'
    b db 5
    bf db 15
.code
Start:
    inint ecx ; input n
    mov eax,0 ;
    mov edx,0 ; i=0
    mov ebx,ecx ; n -> ebx
again:
    inc edx ; i:=i+1
    mov ebx,ecx ; n -> ebx
    
    mov eax,edx ; j:=i
    
    div bf
    cmp ah,0
    jz bufi
    mov eax,edx
    
    div f; j/3
    cmp ah,0
    jz fi
    mov eax,edx
        
    div b; j/5
    cmp ah,0
    jz bu
    mov eax,edx
    
    outintln eax
    jmp ag
fi:
    outstrln 'fizz'
    jmp ag
bu:
    outstrln 'buzz'
    jmp ag
bufi:
    outstrln 'fizzbuz'
    jmp ag 
ag: 
    sub ebx,edx ; n-i again
    jnz again
    exit
end Start