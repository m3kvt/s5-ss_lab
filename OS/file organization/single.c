#include <stdio.h>
#include <string.h>
void main()
{
    int nf = 0, i = 0, ch;
    char mdname[10], fname[10][10], name[10];
    printf("Enter the directory name: ");
    scanf("%s", mdname);
    do
    {
        printf("Enter file name to be created:");
        scanf("%s", name);
        for (i = 0; i < nf; i++)
        {
            if (!strcmp(name, fname[i]))
                break;
        }
        if (i == nf)
            strcpy(fname[nf++], name);
        else
            printf("There is already %s\n", name);
        printf("Do you want to enter another file(yes - 1 or no - 0):");
        scanf("%d", &ch);
    } while (ch == 1);
    printf("Directory name is:%s\n", mdname);
    printf("Files names are...\n");
    for (i = 0; i < nf; i++)
        printf("%s\n", fname[i]);
}
