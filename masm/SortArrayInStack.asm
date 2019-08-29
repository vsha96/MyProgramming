include console.inc
.data
    
.code
    
sort proc
    push ebp
    mov ebp,esp
    push eax
    push ebx
    push ecx
    push edx
        n equ dword ptr [ebp+8] ;size of array
    mov ecx,n
    outstrln 'Enter elements'
    fill:
    ; !!!equ -> push ebx
    sub esp,4 ; create array with size n
    inint ebx
    mov [esp],ebx
    loop fill
        origin equ dword ptr ebp-20 ;origin of array
    ;===show array====
        mov ecx,n
        mov ebx,ebp
        sub ebx,4*5
        outstr 'created array '
        show:
        outint [ebx]
        outchar ' '
        sub ebx,4
        loop show
    ;=================
                ;start sort
                cmp n,1
                je pass
                    mov ecx,n
                    dec ecx
                    mov ebx,ebp
                    sub ebx,4*5
                    ;now we are targeting at origin of array
                    move:
                        mov eax,ecx
                        push ebx
                        compare:
                            mov edx,[ebx]
                            cmp edx,[ebx-4]
                            jl noreplace
                            xchg edx,[ebx-4]
                            mov [ebx],edx
                            noreplace:
                            sub ebx,4
                        loop compare
                        pop ebx
                        mov ecx,eax
                    loop move   
                pass: 
    ;===show array====
        mov ecx,n
        mov ebx,ebp
        sub ebx,4*5
        newline
        outstr 'sorted array  '
        show2:
        outint [ebx]
        outchar ' '
        sub ebx,4
        loop show2
    ;=================          
    mov ecx,n
    unfill:
    add esp,4
    loop unfill
    pop edx
    pop ecx
    pop ebx
    pop eax
    pop ebp
    
    ret 4
sort endp
    
start:
    outstr "Enter array's size "
    inint eax
    push eax
    call sort
    
    exit
end start
