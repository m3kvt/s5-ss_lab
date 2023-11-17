#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void passOne(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]);
void display();

int main()
{
    
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    passOne(label, opcode, operand, code, mnemonic);

    return 0;
}

void passOne(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]) 
{
    int locctr, start, length;

    FILE *fp1, *fp2, *fp3, *fp4, *fp5;                                   

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("output.txt", "w");
    fp5 = fopen("length.txt", "w");

    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);              

    if (strcmp(opcode, "START") == 0) {  
        start = atoi(operand);                                      
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);    
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);          
    } 
    else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {

        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }

        fscanf(fp2, "%s\t%s", code, mnemonic);

        while (strcmp(code, "END") != 0) {
            if (strcmp(opcode, code) == 0) {                        
                locctr += 3;
                break;
            }
            fscanf(fp2, "%s\t%s", code, mnemonic);
        }

        
        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        }
               
        else if (strcmp(opcode, "RESW") == 0) {
            locctr += (3 * (atoi(operand)));                        
        }
                
        else if (strcmp(opcode, "BYTE") == 0) {
            ++locctr;
        }
                
        else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        }
        
        
        fscanf(fp1, "%s\t%s\t%s" , label , opcode , operand);
    }
    
    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    display();
    
    length = locctr - start;
    fprintf(fp5, "%d", length);
    fclose(fp5);
    printf("\nThe length of the code : %d\n", length);
}

void display() {

    char str;
    FILE *fp1, *fp2, *fp3;   

    //1. Output Table
    printf("\n\nThe contents of Output Table :\n\n");
    fp2 = fopen("output.txt", "r");
    str = fgetc(fp2);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp2);
    }
    fclose(fp2);

    // 2. Symtable
    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("symtab.txt", "r");
    str = fgetc(fp3);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(fp3);
    }
    fclose(fp3);
}


/*#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
	FILE *f1,*f2,*f3,*f4;
	
	int lc,sa,l,op1,o,len;
	char m1[20],la[20],op[20],otp[20];
	f1=fopen("input.txt",'r');
	f3=fopen("symtab.txt",'w');
	fscanf(f1,"%s%s%d",la,m1,&op1);
	if(strcmp(m1,"START")==0){
	 sa=op1;
	 lc=sa;
	 printf("\t%s\t%s\t%d\n",la,m1,op1);
	}
	else
	 lc=0;
	fscanf(f1,"%s %s",la,m1);
	while(!feof(f1)){
		fscanf(f1,"%s",op);
		printf("\n%d\t%s\t%s\n%s",lc,la,m1,op);
		if(strcmp(la,"-")!=0){
			fprintf(f3,"\n%d\t%s\n",lc,la);
		}
		f2=fopen("optab.txt","r");
		fscanf(f2,"%s%d",otp,&o);
		while(!feof(f2)){
			if(strcmp(m1,otp)==0){
				lc=lc+3;
				break;
			}
			fscanf(f2,"%s%d",otp,&o);
		}
		fclose(f2);
		if(strcmp(m1,"WORD")==0){
			lc=lc+3;
		}
		else if(strcmp(m1,"RESW")==0){
			op1=atoi(op);
			lc=lc+(3*op1);
		}
		else if(strcmp(m1,"BYTE")==0){
			if(op[0]=='X'){
				lc=lc+1;
			}
			else{
				len=strlen(op)-2;
				lc=lc+len;
			}
		}
		else if(strcmp(m1,"RESB")==0){
			op1=atoi(op);
			lc=lc+op1;
		}
		fscanf(f1,"%s%s",la,m1);
	}
	if(strcmp(m1,"END")==0){
		printf("Program length= %d\n",lc-sa);
	}
	fclose(f1);
	fclose(f3);
	}
		*/


