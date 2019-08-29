include console.inc

.data
    b1 db ?
    b2 db ?
    b3 db ?
    w1 dw 20
    w2 dw ?
    w3 dw ?
    d1 dd 30
    d2 dd ?
    d3 dd ?
    q1 dq ?
    q2 dq ?
    q3 dq ?
.code

addthree macro a,b,c
    if type a eq 0 and type b eq 0 and type c eq 0
        outstrln "***Macro addthree*** all const aren't allowed"
        jmp fin
    elseif type a ne 0
        ifdif <a>,<eax>
            push eax
        endif
        mov eax, dword ptr b
        add eax, dword ptr c
        if type a eq 1
            ifdif <a>,<eax>
                mov a,al
                pop eax
            endif
        elseif type a eq 2
            ifdif <a>,<eax>
                mov a,ax
                pop eax
            endif
        elseif type a eq 4
            ifdif <a>,<eax>
                mov a,eax
                pop eax
            endif
        endif
        ;==========================elseif type b ne 0
        
        ;==========================
    endif
    fin:
endm


Start:
    
    addthree bl,bl,3
    outword bl
        
    newline
    mov ecx, type b1
    outintln ecx
    mov ecx, type w1
    outintln ecx
    mov ecx, type d1
    outintln ecx
    mov ecx, type q1
    outintln ecx
    
    exit
end Start
    
    
    
    newline
    mov ecx, type b1
    outintln ecx
    mov ecx, type w1
    outintln ecx
    mov ecx, type d1
    outintln ecx
    mov ecx, type q1
    outintln ecx
    
    
;;==========if 1st or 2nd is constants==========
    push ebx
    push ecx
        mov ecx,offset a ;????
        mov bl,[ecx]
        cmp bl,'0'
        jb nocon
        cmp bl,'9'
        ja nocon
        jmp pass1
        nocon:
            outstrln 'op1 is var or reg'
        pass1:
    pop ecx
    pop ebx




;==================some errors==================
local fin
    ifb <a>
        outstrln '***Macro addthree*** 1st arg is missed'
        jmp fin
    endif
    ifb <b>
        outstrln '***Macro addthree*** 2nd arg is missed'
        jmp fin
    endif
    ifb <c>
        outstrln '***Macro addthree*** 3rd arg is missed'
        jmp fin
    endif












