include console.inc

.data
    M EQU 30
    N EQU 50
    A db M dup((10) dup(0),(N-10) dup(-1))

.code
Start:
    mov ecx, 0
    outint ecx

end Start
