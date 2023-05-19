#include <stdio.h>

int main(int argc, char *argv[]) {

    // октрытие файлов для записи в вспомогальный файл правильного варианта

    FILE *fp = fopen(argv[1], "r+");
    FILE *fp2 = fopen("output.txt", "w");
    char filename[100];

    if (fp == NULL || fp2 == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char tab = 'F';
    char TabOnNextString = 'F';
    char doubleTab = 'F';
    char tabCloseCap = 'F';
    int capsCount = 0;

    while (fgets(filename, sizeof(filename), fp) != NULL) {

        // условия исплользования табуляции
        for(int j = 0; filename[j] != '\n'; j++){
            if(filename[j] == '{'){
                TabOnNextString = 'T';
                tab = 'T';
		capsCount += 1;
            }
            if(filename[j] == '}'){
                tab = 'F';
                if(doubleTab == 'T')
                    tabCloseCap = 'T';
                doubleTab = 'F';
		capsCount -= 1;
           }
            if((filename[j] == 'i' && filename[j + 1] == 'f') ||
                (filename[j] == 'w' && filename[j + 1] == 'h' && filename[j + 2] == 'i' && filename[j + 3] == 'l' && filename[j + 4] == 'e') ||
                (filename[j] == 'd' && filename[j + 1] == 'o') || 
                (filename[j] == 's' && filename[j + 1] == 'w' && filename[j + 2] == 'i' && filename[j + 3] == 't' && filename[j + 4] == 'c' && filename[j + 5] == 'h')){
                doubleTab = 'T';
            }
        }
        
        // расстановка табуляций
	
        if(tabCloseCap == 'T'){

            fprintf(fp2, "\t%s", filename);

        }
        if(tab == 'T' && TabOnNextString == 'F'){

            if(doubleTab == 'T')
                fprintf(fp2, "\t\t%s", filename);
            else if(doubleTab == 'F')
                fprintf(fp2, "\t%s", filename);

        }
        else if(capsCount <= 0 && tab == 'F' && TabOnNextString == 'F' && tabCloseCap == 'F'){

            fprintf(fp2, "%s", filename);

        }
        else if(tab == 'T' && TabOnNextString == 'T'){

            if(doubleTab == 'T'){
                fprintf(fp2, "\t%s", filename);
                TabOnNextString = 'F';
            }else if(doubleTab == 'F'){
                fprintf(fp2, "%s", filename);
               TabOnNextString = 'F';
            }

        }

	if(capsCount > 0 && tabCloseCap == 'F' && tab == 'F' &&
        doubleTab == 'F'){
                fprintf(fp2, "\t%s", filename);
                //capsCount -= 1;
        }


        tabCloseCap = 'F';
  }
    fclose(fp);
    fclose(fp2);

    // октрытие файлов для записи в исходный файл правильного варианта

    FILE *fp_r = fopen("output.txt", "r+");
    FILE *fp_w = fopen(argv[1], "w");
    char filename2[100];

    if (fp_r == NULL || fp_w == NULL) {
        printf("Error opening file\n");
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
