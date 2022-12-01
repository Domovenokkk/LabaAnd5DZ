#include <math.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define KEY_EXIT 27
#define KEY_ENTER 13
#define ARROW_KEY 224
#define KEY_SPACE 0
#define KEY_BACKSPACE 8

#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

#define ONE_SIZE 1
#define TWO_SIZE 2
#define THREE_SIZE 3
#define FOUR_SIZE 4
#define FIVE_SIZE 5

#define NONE_TITLE ""
#define RUS 0
#define ENG 1

void GenerateMenu(int* choose_pos, char** menu, COORD* cursorPos, HANDLE hStdOut, int menu_size, char* text) {
    int iKey = 67;
    int line = (text == NONE_TITLE) ? 0 : 1;
    *cursorPos = (COORD){ 0, line };
    *choose_pos = 0;
    SetConsoleCursorPosition(hStdOut, *cursorPos);
    while (iKey != KEY_ENTER) {
        switch (iKey) {
        case KEY_EXIT:
            (*choose_pos) = menu_size - 1;
            return 0;
            break;
        case KEY_ARROW_UP:
            (*choose_pos)--;
            break;
        case KEY_ARROW_DOWN:
            (*choose_pos)++;
            break;
        }

        system("cls");
        printf("%s", ((line == 1) ? text : ""));

        if (*choose_pos < 0) { *choose_pos = menu_size - 1; }
        if (*choose_pos > menu_size - 1) { *choose_pos = 0; }

        for (int i = 0; i < menu_size; i++) {
            *cursorPos = (COORD){ 3, line + i };
            SetConsoleCursorPosition(hStdOut, *cursorPos);
            printf("%s \n", menu[i]);
        }

        *cursorPos = (COORD){ 0, line + *choose_pos };
        SetConsoleCursorPosition(hStdOut, *cursorPos);
        printf("<<");
        *cursorPos = (COORD){ strlen(menu[*choose_pos]) + 3 + 1, line + *choose_pos };
        SetConsoleCursorPosition(hStdOut, *cursorPos);
        printf(">>");

        iKey = _getch();
    }
}

void SizeOfArray(int** array, int* size, int languages) {
    system("cls");
    printf(languages == 0 ? "Введите размер массива: " : "Enter the size of the array: ");
    scanf_s(" %d", size);
    *array = (int*)malloc(sizeof(int) * (*size));
}

void ManualArray(int* array, int size, int languages) {
    printf(languages == 0 ? "Введите элементы массива: " : "Enter elements of array: ");
    for (int i = 0; i < size; i++) {
        scanf_s(" %d", &array[i]);
    }
}

void RandomArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

int ArrayFromFile(int** array, int* size, int language) {
    char filename[100];
    char filepath[200];
    char dir[100];
    printf(language == 0 ? "Введите путь к вашему файлу. Например: D:\\github_files\\source\\\n" : "Enter the path to your file. For example: D:\\github_files\\source\\\n");
    gets(dir);
    printf(language == 0 ? "Введите название файла. Например: input.txt\n" : "Enter a file name. For example: input.txt\n");
    gets(filename);
    strcpy_s(filepath, sizeof filepath, dir);
    strncat_s(filepath, 100, filename, 100);
    FILE* input_file = NULL;
    errno_t error;
    int size1;
    int* mass;
    error = fopen_s(&input_file, filepath, "r+");
    if (input_file == NULL) {
        printf(language == 0 ? "Ошибка в указанном файле" : "Error in the specified file");
    }
    else {
        if (fscanf_s(input_file, "%d", &size1) != 1) {
            printf(language == 0 ? "Ошибка в получении размера массива" : "Error in getting array size");
            return 0;
        }
        mass = (int*)malloc(sizeof(int) * size1);
        for (int i = 0; i < size1; i++) {
            if (fscanf_s(input_file, "%d", &mass[i]) != 1) {
                printf(language == 0 ? "Ошибка в получении массива" : "Error getting array");
                return 0;
            }
        }
        fclose(input_file);
        printf(language == 0 ? "Полученный массив" : "Resulting array: \n");
        for (int i = 0; i < size1; i++) {
            printf("%d ", mass[i]);
        }
        *array = mass;
        *size = size1;
    }
    return 0;
}

void PrintArray(int* array, int size, int languages) {
    system("cls");
    if (size == -1) {
        printf(languages == 0 ? "Массив не определен. Перейдите в <<Настройки>> и задайте массив." : "The array is not defined. Go to <<Settings>> and set the array.");
    }
    else {
        printf(languages == 0 ? "Ваш массив: " : "Your array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}

void BubbleSort(int* array, int size) {
    int temp = 0;
    if (size != -1) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (array[i] > array[j]) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
            }
        }
    }
}

void InsertionSort(int* array, int size) {
    int a, j;
    for (int i = 1; i < size; i++) {
        a = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > a) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = a;
    }
}

void MergerSort(int* array, int size, int left, int right) {
    if (left == right) {
        return;
    }
    int middle = (left + right) / 2;
    MergerSort(array, size, left, middle);
    MergerSort(array, size, middle + 1, right);
    int i = left;
    int j = middle + 1;
    int* add_array;
    add_array = (int*)malloc(sizeof(int) * right);
    for (int step = 0; step < right - left + 1; step++) {
        if ((j > right) || ((i <= middle) && (array[i] < array[j]))) {
            add_array[step] = array[i];
            i++;
        }
        else {
            add_array[step] = array[j];
            j++;
        }
    }
    for (int step = 0; step < right - left + 1; step++) {
        array[left + step] = add_array[step];
    }
}

void ShellSort(int* array, int size) {
    int temp, imp;
    for (int i = size / 2; i > 0; i /= 2) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < size / i; k++) {
                imp = k;
                while ((imp > 0) && array[imp * i + j] < array[(imp - 1) * i + j]) {
                    temp = array[imp * i + j];
                    array[imp * i + j] = array[(imp - 1) * i + j];
                    array[(imp - 1) * i + j] = temp;
                    imp = imp - 1;
                }
            }
        }
    }
}

void StupidSearch(int* array, int size, int languages) {
    system("cls");
    if (size != -1) {
        int number, cnt = 0;
        printf(languages == 0 ? "Введите число, индекс которого вы хотите узнать: " : "Enter the number whose index you want to know: ");
        scanf_s(" %d", &number);
        printf(languages == 0 ? "Индексы найденных элементов: " : "Indexes of found elements: ");
        for (int i = 0; i < size; i++) {
            if (array[i] == number) {
                printf("%d ", i);
                cnt++;
            }
        }
        if (cnt == 0) {
            printf(languages == 0 ? "элементы не найдены" : "elements not found");
        }
    }
    else {
        printf(languages == 0 ? "Массив не определен. Перейдите в <<Настройки>> и задайте массив." : "The array is not defined. Go to <<Settings>> and set the array.");
    }
    printf("\n");
}

int CheckSort(int* array, int size) {
    int ctrl = 1;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            ctrl--;
            break;
        }
    }
    return ctrl;
}

void BinarySearch(int* array, int size, int languages) {
    if (size != -1) {
        int x;
        printf(languages == 0 ? "Введите число, индекс которого вы хотите узнать: " : "Enter the number whose index you want to know: ");
        scanf_s(" %d", &x);
        system("cls");
        int left = 0, right = size - 1;
        int flag = 0;
        while (left <= right) {
            int middle = (left + right) / 2;
            if (array[middle] == x) {
                printf(languages == 0 ? "Индексы найденных элементов: %d\n" : "Indexes of found elements: %d\n", middle);
                flag = 1;
                break;
            }
            if (array[middle] > x)
                right = middle - 1;
            else
                left = middle + 1;
        }
        printf("%s", (flag == 1 ? "" : languages == 0 ? "Элемент не найден\n" : "Element not found\n"));
    }
    else {
        printf(languages == 0 ? "Массив не определен. Перейдите в <<Настройки>> и задайте массив." : "The array is not defined. Go to <<Settings>> and set the array.");
    }
}

int main() {
    system("title Application");

    srand(time(0));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);

    SetConsoleTextAttribute(hStdOut, 4);
    system("cls");

    int choose_pos;
    int exit_flag;
    int incase_flag;
    COORD cursorPos;

    char* menu[TWO_SIZE][FOUR_SIZE] = { { "Режим эксперимента","Алгоритмы", "Настройки", "Выход"},{"Experiment mode","Algorithms","Settings","Exit"} };
    char* algorithms[TWO_SIZE][THREE_SIZE] = { { "Поиск", "Сортировки", "Назад" }, { "Search","Sorts","Back" } };
    char* search[TWO_SIZE][THREE_SIZE] = { { "Наивный поиск","Бинарный поиск", "Назад" }, { "Stupid search","Binary search","Back" } };
    char* sorts[TWO_SIZE][FIVE_SIZE] = { { "Пузырьковая сортировка","Сортировка вставками", "Сортировка слиянием", "Сортировка Шелла" ,"Назад" }, { "Bubble sort","Insertion sort", "Merger sort", "Shello sort", "Back"} };
    char* settings[TWO_SIZE][FOUR_SIZE] = { {"Язык", "Задать массив", "Посмотреть текущий массив", "Назад"}, {"Language","Set array","Check our array","Back"} };
    char* setarrayact[TWO_SIZE][FOUR_SIZE] = { {"Ручной ввод","Рандомный ввод","Прочитать из файла", "Назад"}, {"Manual enter","Random array","Read from file", "Back"} };

    char* lngs[TWO_SIZE] = { "Русский","English" };

    int* array = NULL;
    int arrsize = -1;

    int language = RUS;

    FILE* input_file = NULL;
    errno_t error;

    exit_flag = 0;
    incase_flag = 1;

    while (!exit_flag) {
        system("cls");
        GenerateMenu(&choose_pos, menu[language], &cursorPos, hStdOut, FOUR_SIZE, NONE_TITLE);
        switch (choose_pos) {
        case 0: // Exp
            system("cls");
            system("pause");
            break;
        case 1: // Alg
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                GenerateMenu(&choose_pos, algorithms[language], &cursorPos, hStdOut, THREE_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0: // Search
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        GenerateMenu(&choose_pos, search[language], &cursorPos, hStdOut, THREE_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Simple search
                            StupidSearch(array, arrsize, language);
                            system("pause");
                            break;
                        case 1: // Bin search
                            system("cls");
                            if (arrsize != -1) {
                                char* yesno[TWO_SIZE][2] = { {"Да","Нет"}, { "Yes", "No" } };
                                if (CheckSort(array, arrsize) == 1) {
                                    BinarySearch(array, arrsize, language);
                                    system("pause");
                                }
                                else {
                                    GenerateMenu(&choose_pos, yesno[language], &cursorPos, hStdOut, 2, language == 0 ? "Массив не отсортирован. Отсортировать?" : "Array not sorted. Sort it?");
                                    switch (choose_pos) {
                                    case 0:
                                        system("cls");
                                        BubbleSort(array, arrsize);
                                        PrintArray(array, arrsize, language);
                                        system("pause");
                                        break;
                                    case 1:
                                        system("cls");
                                        break;
                                    }
                                }
                            }
                            else {
                                printf(language == 0 ? "Массив не определен\n" : "Array not defined\n");
                                system("pause");
                            }
                            break;
                        case 2: //Back
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 1: // Sort
                    incase_flag = 2;
                    while (incase_flag >= 2) {
                        GenerateMenu(&choose_pos, sorts[language], &cursorPos, hStdOut, FIVE_SIZE, NONE_TITLE);
                        switch (choose_pos) {
                        case 0: // Bubble sort
                            BubbleSort(array, arrsize);
                            PrintArray(array, arrsize, language);
                            system("pause");
                            break;
                        case 1:
                            system("cls");
                            InsertionSort(array, arrsize);
                            PrintArray(array, arrsize, language);
                            system("pause");
                            break;
                        case 2:
                            system("cls");
                            MergerSort(array, arrsize, 0, arrsize - 1);
                            PrintArray(array, arrsize, language);
                            system("pause");
                            break;
                        case 3:
                            system("cls");
                            ShellSort(array, arrsize);
                            PrintArray(array, arrsize, language);
                            system("pause");
                            break;
                        case 4: //Back
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 2: // Back
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case 2: // Settings
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                GenerateMenu(&choose_pos, settings[language], &cursorPos, hStdOut, FOUR_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0: // lang
                    system("cls");
                    GenerateMenu(&choose_pos, lngs, &cursorPos, hStdOut, 2, NONE_TITLE);
                    language = choose_pos;
                    break;
                case 1: // set array
                    incase_flag = 2;
                    while (incase_flag >= 2) {

                        system("cls");
                        GenerateMenu(&choose_pos, setarrayact[language], &cursorPos, hStdOut, FOUR_SIZE, NONE_TITLE);

                        switch (choose_pos) {
                        case 0: // manual enter
                            system("cls");
                            free(array);
                            SizeOfArray(&array, &arrsize, language);
                            ManualArray(array, arrsize, language);
                            PrintArray(array, arrsize, language);
                            incase_flag = 1;
                            system("pause");
                            break;
                        case 1: // rand enter
                            system("cls");
                            free(array);
                            SizeOfArray(&array, &arrsize, language);
                            RandomArray(array, arrsize);
                            PrintArray(array, arrsize, language);
                            incase_flag = 1;
                            system("pause");
                            break;
                        case 2: // read from file
                            system("cls");
                            ArrayFromFile(&array, &arrsize, language);
                            system("pause");
                            incase_flag = 1;
                            break;
                        case 3: // back
                            system("cls");
                            incase_flag = 1;
                            break;
                        }
                    }
                    break;
                case 2: // check array
                    PrintArray(array, arrsize, language);
                    system("pause");
                    break;
                case 3: // back
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
            break;
        case 3: // Exit
            exit_flag = 1;
            break;
        }
    }

    system("cls");
    printf(language == 0 ? "Досвидания!\n" : "Goodbay!\n");
    free(array);
    system("pause");
    return 0;
}