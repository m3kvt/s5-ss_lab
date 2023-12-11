#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_FILES 100
typedef struct File
{
    char name[MAX_NAME_LENGTH];
    char content[1024];
} File;
typedef struct Directory
{
    char name[MAX_NAME_LENGTH];
    struct Directory *subdirectories[MAX_FILES];
    File files[MAX_FILES];
    int num_subdirectories;
    int num_files;
} Directory;
void createDirectory(Directory *parent, const char *name)
{
    if (parent->num_subdirectories < MAX_FILES)
    {
        Directory *newDirectory = (Directory *)malloc(sizeof(Directory));
        strcpy(newDirectory->name, name);
        newDirectory->num_subdirectories = 0;
        newDirectory->num_files = 0;
        parent->subdirectories[parent->num_subdirectories++] = newDirectory;
        printf("Directory '%s' created.\n", name);
    }
    else
        printf("Directory limit reached. Cannot create '%s'.\n", name);
}
void createFile(Directory *parent, const char *name, const char *content)
{
    if (parent->num_files < MAX_FILES)
    {
        File newFile;
        strcpy(newFile.name, name);
        strcpy(newFile.content, content);
        parent->files[parent->num_files++] = newFile;
        printf("File '%s' created.\n", name);
    }
    else
        printf("File limit reached. Cannot create '%s'.\n", name);
}
void listContents(Directory *dir)
{
    printf("Contents of directory '%s':\n", dir->name);
    printf("Subdirectories:\n");
    for (int i = 0; i < dir->num_subdirectories; i++)
    {
        printf("- %s\n", dir->subdirectories[i]->name);
    }
    printf("Files:\n");
    for (int i = 0; i < dir->num_files; i++)
    {
        printf("- %s\n", dir->files[i].name);
    }
}
int main()
{
    Directory root;
    strcpy(root.name, "root");
    root.num_subdirectories = 0;
    root.num_files = 0;
    char dirName[MAX_NAME_LENGTH];
    printf("Enter the name of the directory: ");
    scanf("%s", dirName);
    createDirectory(&root, dirName);
    char fileName[MAX_NAME_LENGTH];
    printf("Enter the name of a file: ");
    scanf("%s", fileName);
    char fileContent[1024];
    printf("Enter the content of the file: ");
    scanf("%s", fileContent);
    createFile(&root, fileName, fileContent);

    listContents(&root);
    return 0;
}
