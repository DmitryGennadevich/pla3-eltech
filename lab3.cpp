#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <fstream>
using namespace std;
//Функция кодирования
int encode(size_t codeKey, size_t numOfAlphabet, string alphabet, const char *inputFile, const char *outputFile) {
    char S; // считанный символ
     FILE *f, *g;
        f = fopen(inputFile, "r+"); // открытие файла для чтения
        if (f == NULL) cout<<"Input file not found!"<<endl; // вывод сообщения в случае если файл не открыт

        g = fopen(outputFile, "r+"); // открытие файла для записи
        if (g == NULL) cout<<"Output file not found!"<<endl; // вывод сообщения в случае если файл не открыт

    if ((f != NULL) && (g != NULL)) {
    while (!feof(f)) {  // считывание пока не закончится входной файл
        fread (&S, sizeof(char), 1, f);
        for (int i = 0; i<numOfAlphabet; i++) {
            if (S == alphabet[i]) {                   // Если считанный из файла символ входит в алфавит,
                for (int k = 0; k<codeKey; k++) {     //   то увеличить символ на значение codeKey
                S = S++;
            }
            break; }
        }
        fwrite (&S, sizeof(char), 1, g); // Запись символа в выходной файл
        S = ' ';
     }

fclose(f);
fclose(g);
      
    }
}
//Функция декодирования
  int decode(size_t codeKey, size_t numOfAlphabet, string alphabet, const char *inputFile, const char *outputFile) {
    char S, S1; // Считанные символы
     FILE *f, *g;
        f = fopen(inputFile, "r+"); // открытие файла для чтения
        if (f == NULL) cout<<"Input file not found!"<<endl; // вывод сообщения в случае если файл не открыт

        g = fopen(outputFile, "r+"); // открытие файла для записи
        if (g == NULL) cout<<"Output file not found!"<<endl; // вывод сообщения в случае если файл не открыт

    if ((f != NULL) && (g != NULL)) {    
    while (!feof(f)) {   // Считывание пока не закончится входной файл
        fread (&S, sizeof(char), 1, f);
        S1 = S;
        // Search of coded characters
        for (int i = 0; i<codeKey; i++) {          // Поиск закодированных символов :
            S1 = S1--;                             //   считанный символ уменьшается codeKey-раз (переменная S1)
        }
        for (int i = 0; i<numOfAlphabet; i++) {    
            if (S1 == alphabet[i]) {               // Если S1 входит в алфавит,то это закодированный ранее символ и он подлежит декодированию
                for (int k = 0; k<codeKey; k++) {
                S = S--;
            }
            break; }
        }
        fwrite (&S, sizeof(char), 1, g);
        S = ' ';
     }

fclose(f);
fclose(g);
      
    }
}
// Main
int main(int argc, char *argv[]) {
    size_t var = 0; //ASCII код ключа кодирования
    char *key = 0; // ключ кодирования
    size_t paramLen; // длина переданного в программу параметра
    string param, param1, param2, alphabet = "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm0987654321"; // переменные для обработки считанных параметров
    int count = 0; // перменная хранит номер элемента argv[],являющегося ключем кодирования
    int error = 0; 
    int type = 0; // if type=0 then encode, if type=1 then decode
    int longAlphabetLen = 0;
         int longAlphabet = 0;
    // Считывание и обработка параметров
    for (int i = 0; i<argc; i++) {
         param.assign(argv[i]);
         param2.assign(argv[i+1]);
         paramLen = param.length();
         char string1[paramLen];
         char string2[paramLen];
         // Считывание и обработка алфавита,введеного через длинный параметр (если такой имеется)
         for (int j = 0; j<paramLen; j++) {
            if (longAlphabet == 0) string1[j] = param[j];
            if (longAlphabet == 1) { string2[longAlphabetLen] = param[j]; longAlphabetLen++; }
            if ((j == 10) && (param1.assign(string1) == "--alphabet=")) { longAlphabet = 1; error++; }
         }

         if (longAlphabet == 1) alphabet.assign(string2);
         longAlphabet = 0;
         longAlphabetLen = 0;
         // Обработка остальных параметров
         if (param == "crypt") error++;

         if ((((param == "-t") && (param2 == "decode"))) || (param == "--type=decode")) { type = 1; error = error+2; }

          if ((((param == "-t") && (param2 == "encode"))) || (param == "--type=encode")) { error = error+2; cout<<error; }

         if ((param == "-h") || (param == "--help")) { system ("Help.txt"); error++; }

         if (param == "-a") { alphabet.assign(argv[i+1]); error++; i++; }

         var = (size_t)*argv[i];
        if ((var > 48) && ((var < 58))) { key = argv[i]; error++; count = i; break;}

        if (error == 0) { cout<<"Parameters are incorrectly set!"; system ("Help.txt"); break;} // Если ни один параметр за шаг цикла не обработан согласно указанным условиям,то 
        error--;                                                                                // вывести сообщение об ошибке
        cout<<param<<endl;                                                                      
    }
    // Если не найден ключ кодирования вывести сообщение об ошибке
    if ((count == 0) && (error != 0)) {
        cout<<"Parameters are incorrectly set!"; system ("Help.txt");
    }
    // Считывание имен входного и выходного файлов
    const char *inputFile;
    const char *outputFile;
    if ((count+3) == argc) { inputFile = argv[count+1]; outputFile = argv[count+2]; } 
    if ((count+2) == argc) { inputFile = argv[count+1]; outputFile = argv[count+1]; }

    
    size_t numOfAlphabet = alphabet.length(); 
    int codeKey = atoi(key); // получение числового значения ключа кодирования
   // Кодирование или декодирование в зависимости от значения переменной type
    if (count != 0) {
      if (type == 0) encode(codeKey, numOfAlphabet, alphabet, inputFile, outputFile);
      if (type == 1) decode(codeKey, numOfAlphabet, alphabet, inputFile, outputFile);
    }



    
    return 0;
}

//*****************************************************************************