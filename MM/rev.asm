data SEGMENT
    STR1 DB 'HELLO'
    LEN EQU $-STR1
    STR2 DB 20 DUP(0)
data ENDS    

code SEGMENT 
    ASSUME CS:code, DS:data,ES:data
    START:
    MOV AX,DATA
    MOV DS,AX
    MOV ES,AX
    MOV SI,offset STR1
    MOV DI,offset STR2+(LEN-1)
    MOV CX,LEN
    
    UP:CLD 
    LODSB
    STD
    STOSB
    LOOP UP
    
    MOV AH,4CH
    INT 21H
code ENDS
END START