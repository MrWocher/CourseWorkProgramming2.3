#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

int countChar(char* s, char c)
{
    int res = 0;
    int i = 0;

    while (s[i] != '\0')
    {
        if (s[i] == c)
            res++;
        i++;
    }

    return res;
}

int main(int argc, char* argv[])
{
    setlocale(0, "");

    if (argc != 2) {
        printf("Введите по образцу: cformat <file name>\n");
    }
    else {
        char* path = argv[1];

        FILE* fp = fopen(path, "r");
        FILE* fp1 = fopen("output.txt", "w");

        if (fp == NULL || fp1 == NULL)
            printf("Файл не найден %s!", path);
        else
        {
            int countBrace = 0;

            while (!feof(fp))
            {
                char* s = malloc(255 + 2);
                
                fgets(s, 255, fp);

                countBrace -= countChar(s, '}');
                for (int i = 0; i < countBrace; i++)
                {
                    fprintf(fp1, "\t");
                }

                fprintf(fp1, "%s", s);

                countBrace += countChar(s, '{');
            }

            fclose(fp);
            fclose(fp1);
            
            printf("Файл отформатирован!");
            
        }
    }

    // октрытие файлов для записи в исходный файл правильного варианта

    FILE *fp_r = fopen("output.txt", "r+");
    FILE *fp_w = fopen(argv[1], "w");
    char filename2[100];

    if (fp_r == NULL || fp_w == NULL) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    while (fgets(filename2, sizeof(filename2), fp_r) != NULL) {
        fprintf(fp_w, "%s", filename2);
    }

    fclose(fp_r);
    fclose(fp_w);

    // очищаем вспомогательный файл

    FILE *fp_e = fopen("output.txt", "w");
    fclose(fp_e);


	return 0;

}