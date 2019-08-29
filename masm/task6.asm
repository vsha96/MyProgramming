include console.inc
.data
    s db ?
.code
start:
    outstrln '=Enter a string terminating by "."='
    sub ebx,ebx
    filling:
    inchar s[ebx]
    cmp s[ebx],'.'
    je stopfilling
    inc ebx
    jmp filling
    stopfilling:
    
        mov s[1][ebx],0
        outstrln '=created string='
        outstrln offset s
;=============check=============
mov edi,offset s
check1:
            mov bl,[edi]
            cmp bl,'.'
            je movoper1
            ;!!!!!!there is error
    if bl GE '0' and bl LE '9'
        jmp checked1
    elseif bl GE 'a' and bl LE 'z'
        jmp checked1
    elseif bl GE 'A' and bl LE 'Z'
        jmp checked1
    else
        jmp movoper2
    endif
checked1:
    inc edi
    jmp check1
;=============/check=============
jmp pass11
movoper1:
;=========1 operator=========
        mov ebx, offset s
        oper1:
            mov al,[ebx]
            cmp al,'.'
            je next3
                cmp al,'A'
                jb pass
                cmp al,'Z'
                ja pass
                add al,32
                mov [ebx],al
            pass:
            inc ebx
        jmp oper1
        next3:
    outstrln '=corrected string='
    outstrln offset s
;=========/1 operator=========
pass11:
jmp pass22
movoper2:
;=========2 operator=========
        mov edi, offset s
        mov esi, offset s
        cld
        mov bl,[edi]
        cmp bl,'.'
        je pass1
        inc esi
            ;sub ecx,ecx
        oper2:
            mov bl,[edi]
            mov cl,[esi]
            cmp cl,'.'
            je pass1
            cmp bl,cl
            jne step
                ;if s[i]=s[i+1]
                mov ecx,edi ;save start position before delete
                inc edi
                checknext:
                    inc esi
                    mov cl,[esi]
                    cmp bl,cl
                    jne delete
                jmp checknext
                delete:
                    lodsb
                    stosb
                    cmp cl,0
                    je reset
                    mov cl,[edi] ;we need to seize 0 after dot (for outstr)  
                jmp delete
                reset:
                mov edi,ecx ;reset start position
                inc ecx
                mov esi,ecx
            
            step:
            inc edi
            inc esi
        jmp oper2
        
        pass1:
        outstrln '=corrected string='
        outstrln offset s
;=========/2 operator=========
pass22:

    exit
end start






;=============check=============
mov edi,offset s
check1:
            mov bl,[edi]
            cmp bl,'.'
            je movoper1
            ;!!!!!!there is error
    if bl GE '0' and bl LE '9'
        jmp checked1
    elseif bl GE 'a' and bl LE 'z'
        jmp checked1
    elseif bl GE 'A' and bl LE 'Z'
        jmp checked1
    else
        jmp movoper2
    endif
checked1:
    inc edi
    jmp check1
;=============/check=============




;=============check1=============  
    ;checked1:
    ;    outstrln '1)Correct string'
    jmp passE
        fail1: outstr '1)Incorrect string'
    passE:
;=============check1=============

