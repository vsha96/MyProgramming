include console.inc
 
.code
Start:  mov ecx, 5

again:  outstrln 'Hello World'
        dec ecx
        jnz again

        exit
        end Start