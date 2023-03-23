#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ENCRYPTION_KEY 21

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

int main()
{
    FILE *file;
    char character;
    int option, login;
    char input[100];
    CLEAR_SCREEN;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char filename[30];
    strftime(filename, sizeof(filename), "%Y-%m-%d.txt", t);

    printf("---------DIARY---------\n");
    printf("Enter the Login PIN: ");
    scanf("%d", &login);
    if (login != 1234)
    {
        printf("\nIncorrect PIN!\n");
        return 2;
    }
    else
    {
        CLEAR_SCREEN;
    }

    printf("Enter option:\n1. New Entry\n2. Read\n");
    scanf("%d", &option);

    file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    if (option == 1)
    {
        CLEAR_SCREEN;
        printf("Enter text to append to the file: ");
        scanf(" %[^\n]", input);
        for (int i = 0; input[i] != '\0'; i++)
        {
            character = input[i];
            character = character + ENCRYPTION_KEY;
            fputc(character, file);
            fflush(file);
        }
        fputc('u', file);
        fclose(file);
    }
    if (option == 2)
    {
        CLEAR_SCREEN;
        printf("Enter the Date, you wanna read\nFormat should be YYYY-MM-DD.txt\n:");
        scanf("%s", filename);
        strcat(filename,".txt");
        file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("File Not Found!\n");
            return 3;
        }

        while ((character = fgetc(file)) != EOF)
        {
            if (character == 'u')
            {
                printf("\n");
                continue;
            }
            else
            {
                printf("%c", character - ENCRYPTION_KEY);
            }
        }
        printf("\n");
        fclose(file);
    }
    if (option == 1)
    {
        printf("\nFile encrypted successfully.\n");
    }
    else if (option == 2)
    {
        printf("File decrypted successfully.\n");
    }
    return 0;
}
