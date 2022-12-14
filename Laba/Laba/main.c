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

int ArrayFromFile(int** array, int* size,  int language) {
    char filename[100];
    char filepath[200];
    char dir_in[300];
    printf(language == 0 ? "Введите путь к вашему файлу. Например: D:\\github_files\\source\\\n" : "Enter the path to your file. For example: D:\\github_files\\source\\\n");
    printf("Вводите: ");
    gets(dir_in);
    printf(language == 0 ? "Введите название файла. Например: input.txt\n" : "Enter a file name. For example: input.txt\n");
    printf("Вводите: ");
    gets(filename);
    strcpy_s(filepath, sizeof filepath, dir_in);
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
        printf(language == 0 ? "Полученный массив: " : "Resulting array: \n");
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

int BubbleSort(int* array, int size) {
    int temp = 0, swaps = 0;
    if (size != -1) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (array[i] > array[j]) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    swaps++;
                }
            }
        }
    }
    return swaps;
}

void InsertionSort(int* array, int size) {
    int a, j;
    int insswaps = 0;
    for (int i = 1; i < size; i++) {
        a = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > a) {
            array[j + 1] = array[j];
            j = j - 1;
            insswaps++;
        }
        array[j + 1] = a;
    }
}

msort_swaps = 0;
int MergerSort(int* array, int size) {
    int step = 1;
    int* m1 = (int*)malloc(size * sizeof(int));
    if (!m1) return -1;
    int* m2 = (int*)malloc(size * sizeof(int));
    if (!m2) return -1;
    while (step < size) {
        int i, s1, e1, s2, e2;
        for (i = 0; (i + step - 1) < (size - 1); i += 2 * step) {
            s1 = i;
            e1 = i + step - 1;
            s2 = e1 + 1;
            (i + 2 * step - 1) < (size - 1) ? (e2 = i + 2 * step - 1) : (e2 = size - 1);
            Mergersort(array, s1, e1, s2, e2, m1, m2);
        }
        step = step << 1;
    }
    return msort_swaps;
}

int Mergersort(int* array, int s1, int e1, int s2, int e2, int* m1, int* m2) {
    int len1 = e1 - s1 + 1;
    int len2 = e2 - s2 + 1;
    int p1 = 0;
    int p2 = 0;
    int p = s1;
    memcpy(m1, array + s1, sizeof(int) * len1);
    memcpy(m2, array + s2, sizeof(int) * len2);
    while (p1 < len1 && p2 < len2) {
        if (m1[p1] < m2[p2]) {
            array[p++] = m1[p1++];
        }
        else {
            array[p++] = m2[p2++];
        }
        msort_swaps++;
    }
    while (p1 < len1) {
        array[p++] = m1[p1++];
        msort_swaps++;
    }
    while (p2 < len2) {
        array[p++] = m2[p2++];
        msort_swaps++;
    }
    return 0;
}

void ShellSort(int* array, int size) {
    int temp, imp;
    int shellswaps = 0;
    for (int i = size / 2; i > 0; i /= 2) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < size / i; k++) {
                imp = k;
                while ((imp > 0) && array[imp * i + j] < array[(imp - 1) * i + j]) {
                    temp = array[imp * i + j];
                    array[imp * i + j] = array[(imp - 1) * i + j];
                    array[(imp - 1) * i + j] = temp;
                    imp = imp - 1;
                    shellswaps++;
                }
            }
        }
    }
    return shellswaps;
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

void CompareSort(int* array, int size, int (*sorts[4])(int*, int), int language) {
    char* title[TWO_SIZE][5] = {
        {"Сортировка","Время","Замедление","Перестановки","Увел. Перестановки"},
        {"Sort","Time","Time Ratio","Swaps","Swaps Ratio"},
    };
    char* ssorts[4] = { "Bubble sort" , "Vibor sort", "Quick sort", "Merge sort" };
    int sort_comp_debug = FOUR_SIZE;
    int* times = (int*)malloc(sizeof(int) * sort_comp_debug);
    int* timeratio = (int*)malloc(sizeof(int) * sort_comp_debug);
    int* swaps = (int*)malloc(sizeof(int) * sort_comp_debug);
    int* swapratio = (int*)malloc(sizeof(int) * sort_comp_debug);
    int time;

    int* testarr = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < sort_comp_debug; i++) {
        for (int k = 0; k < size; k++) {
            testarr[k] = array[k];
        }
        time = clock();
        swaps[i] = sorts[i](testarr, size);
        time = clock() - time;
        times[i] = time;
    }
    int mintime = times[0];
    for (int i = 0; i < sort_comp_debug; i++) {
        if (times[i] < mintime)
            mintime = times[i];
    }
    if (mintime == 0)
        mintime = 1;
    for (int i = 0; i < sort_comp_debug; i++) {
        timeratio[i] = times[i] / mintime;
    }
    int minswap = swaps[0];
    for (int i = 0; i < sort_comp_debug; i++) {
        if (swaps[i] < minswap)
            minswap = swaps[i];
    }
    if (minswap == 0)
        minswap = 1;
    for (int i = 0; i < sort_comp_debug; i++) {
        swapratio[i] = swaps[i] / minswap;
    }
    int column_len[5] = { strlen(title[language][0]), strlen(title[language][1]), strlen(title[language][2]), strlen(title[language][3]), strlen(title[language][4]) };
    for (int i = 0; i < sort_comp_debug; i++) {
        if (strlen(ssorts[i]) > column_len[0])
            column_len[0] = strlen(ssorts[i]);
    }
    for (int i = 0; i < sort_comp_debug; i++) {
        if (intlen(times[i]) > column_len[1])
            column_len[1] = intlen(times[i]);
    }
    for (int i = 0; i < sort_comp_debug; i++) {
        if (intlen(timeratio[i]) > column_len[2])
            column_len[2] = intlen(timeratio[i]);
    }
    for (int i = 0; i < sort_comp_debug; i++) {
        if (intlen(swaps[i]) > column_len[3])
            column_len[3] = intlen(swaps[i]);
    }
    for (int i = 0; i < sort_comp_debug; i++) {
        if (intlen(swapratio[i]) > column_len[4])
            column_len[4] = intlen(swapratio[i]);
    }
    //printf("%d\n", column_len[0]);
    //system("pause");

    for (int k = 0; k < 5; k++) {
        printf("|%s", title[language][k]);
        for (int i = 0; i < column_len[k] - strlen(title[language][k]); i++) {
            printf(" ");
        }
    }
    printf("|\n");
    for (int l = 0; l < sort_comp_debug; l++) {
        printf("|%s", ssorts[l]);
        for (int i = 0; i < column_len[0] - strlen(ssorts[l]); i++) {
            printf(" ");
        }
        printf("|%d", times[l]);
        for (int i = 0; i < column_len[1] - intlen(times[l]); i++) {
            printf(" ");
        }
        printf("|%d", timeratio[l]);
        for (int i = 0; i < column_len[2] - intlen(timeratio[l]); i++) {
            printf(" ");
        }
        printf("|%d", swaps[l]);
        for (int i = 0; i < column_len[3] - intlen(swaps[l]); i++) {
            printf(" ");
        }
        printf("|%d", swapratio[l]);
        for (int i = 0; i < column_len[4] - intlen(swapratio[l]); i++) {
            printf(" ");
        }
        printf("|\n");
    }
}

void EfficiencySort(int (*sorts[4])(int*, int), int language) {
    int sort_vibor;
    int tests;
    char* titles[TWO_SIZE][THREE_SIZE] = {
        {"Кол-во элементов","Время","Увеличение"},
        {"Number of elements","Time","Compare"},
    };
    printf(language == 0 ? "1: Сортировка пузырьком\n2: Сортировка Шелла\n3: Сортировка вставками\n4: Сортировка слиянием\n" : 
        "1: Bubble Sort\n2: Shell Sort\n3: InsertionSort\n4: Merger Sort\n");
    printf(language == 0 ? "Выберете сортировку: " : "Enter sort: ");
    scanf_s("%d", &sort_vibor);
    printf(language == 0 ? "Введите количество проверок: " : "Enter number of tests: ");
    scanf_s("%d", &tests);
    int* numberofelement = (int*)malloc(sizeof(int) * tests);
    int* times = (int*)malloc(sizeof(int) * tests);
    int* timeratio = (int*)malloc(sizeof(int) * tests);
    printf(language == 0 ? "Введите размеры данных: " : "Enter numbers of elements: ");
    for (int i = 0; i < tests; i++) {
        scanf_s(" %d", &numberofelement[i]);
    }
    int time;
    for (int i = 0; i < tests; i++) {
        time = clock();
        int* array = (int*)malloc(sizeof(int) * numberofelement[i]);
        for (int k = 0; k < numberofelement[i]; k++) {
            array[k] = -100 + rand() % (abs(-100 - 100) + 1);
        }
        sorts[sort_vibor - 1](array, numberofelement[i]);
        time = clock() - time;
        times[i] = time;
        free(array);
    }
    int mintime = times[0];
    for (int i = 0; i < tests; i++) {
        if (times[i] < mintime)
            mintime = times[i];
    }
    if (mintime == 0)
        mintime = 1;
    for (int i = 0; i < tests; i++) {
        timeratio[i] = times[i] / mintime;
    }

    int column_len[3] = { strlen(titles[language][0]), strlen(titles[language][1]), strlen(titles[language][2]) };

    for (int i = 0; i < tests; i++) {
        if (intlen(numberofelement[i]) > column_len[0])
            column_len[0] = intlen(numberofelement[i]);
        if (intlen(times[i]) > column_len[1])
            column_len[1] = intlen(times[i]);
        if (intlen(timeratio[i]) > column_len[2])
            column_len[2] = intlen(timeratio[i]);
    }

    for (int k = 0; k < 3; k++) {
        printf("|%s", titles[language][k]);
        for (int i = 0; i < column_len[k] - strlen(titles[language][k]); i++) {
            printf(" ");
        }
    }
    printf("|\n");
    for (int l = 0; l < tests; l++) {
        printf("|%d", numberofelement[l]);
        for (int i = 0; i < column_len[0] - intlen(numberofelement[l]); i++) {
            printf(" ");
        }
        printf("|%d", times[l]);
        for (int i = 0; i < column_len[1] - intlen(times[l]); i++) {
            printf(" ");
        }
        printf("|%d", timeratio[l]);
        for (int i = 0; i < column_len[2] - intlen(timeratio[l]); i++) {
            printf(" ");
        }
        printf("|\n");
    }

}

int intlen(int a) {
    int i = 1;
    if (a < 0)
        i++;
    a = abs(a);
    while (a >= 10) {
        i++;
        a /= 10;
    }
    return i;
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

    char* menu[TWO_SIZE][FOUR_SIZE] = { 
        { "Режим эксперимента","Алгоритмы", "Настройки", "Выход"},
        {"Experiment mode","Algorithms","Settings","Exit"} };
    
    char* algorithms[TWO_SIZE][THREE_SIZE] = {
        { "Поиск", "Сортировки", "Назад" }, 
        { "Search","Sorts","Back" } };
   
    char* search[TWO_SIZE][THREE_SIZE] = {
        { "Наивный поиск","Бинарный поиск", "Назад" }, 
        { "Stupid search","Binary search","Back" } };
    
    char* sorts[TWO_SIZE][FIVE_SIZE] = {
        { "Пузырьковая сортировка","Сортировка вставками", "Сортировка слиянием", "Сортировка Шелла" ,"Назад" }, 
        { "Bubble sort","Insertion sort", "Merger sort", "Shello sort", "Back"} };
    
    char* settings[TWO_SIZE][FIVE_SIZE] = {
        {"Язык", "Задать массив", "Посмотреть текущий массив", "Изменить путь до рабочей директории" ,"Назад"}, 
        {"Language","Set array","Check our array", "Change the path to the working directory" ,"Back"}};
    
    char* setarrayact[TWO_SIZE][FOUR_SIZE] = {
        {"Ручной ввод","Сгенерировать случайно","Прочитать из файла", "Назад"}, 
        {"Manual enter","Random array","Read from file", "Back"} };
    
    char* exp[TWO_SIZE][THREE_SIZE] = {
        {"Сравнение сортировок", "Эффективность", "Назад"}, 
        {"Compare sorts", "Efficiency", "Back"} };

    char* file[TWO_SIZE][THREE_SIZE] = { 
        {"Файл ввода", "Файл вывода", "Назад"}, 
        {"Input file", "Output file", "Back"}};

    char* lngs[TWO_SIZE] = { "Русский","English" };
    int* array = NULL;
    int arrsize = -1;

    int language = RUS;

    FILE* input_file = NULL;
    FILE* output_file = NULL;
    FILE* in_file = NULL;
    char dir_in[300];
    char dir_out[300];
    errno_t error;
    int (*allsorts[4])(int*, int) = { BubbleSort , ShellSort , InsertionSort , MergerSort };
    exit_flag = 0;
    incase_flag = 1;

    while (!exit_flag) {
        system("cls");
        GenerateMenu(&choose_pos, menu[language], &cursorPos, hStdOut, FOUR_SIZE, NONE_TITLE);
        switch (choose_pos) {
        case 0: // Exp
            incase_flag = 1;
            while (incase_flag >= 1) {
                system("cls");
                GenerateMenu(&choose_pos, exp[language], &cursorPos, hStdOut, THREE_SIZE, NONE_TITLE);
                switch (choose_pos) {
                case 0:
                    system("cls");
                    if (arrsize == -1) {
                        printf(language == 0 ? "Массив не определен. Перейдите в <<Настройки>> и задайте массив.\n" : 
                            "The array is not defined. Go to <<Settings>> and set the array.\n");
                    }
                    else {
                        CompareSort(array, arrsize, allsorts, language);
                    }
                    system("pause");
                    break;
                case 1:
                    system("cls");
                    if (arrsize == -1) {
                        printf(language == 0 ? "Массив не определен. Перейдите в <<Настройки>> и задайте массив.\n" :
                            "The array is not defined. Go to <<Settings>> and set the array.\n");
                    }
                    else {
                        EfficiencySort(allsorts, language);
                    }
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    incase_flag = 0;
                    break;
                }
            }
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
                GenerateMenu(&choose_pos, settings[language], &cursorPos, hStdOut, FIVE_SIZE, NONE_TITLE);
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
                            PrintArray(array, arrsize, language);
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

                case 3:
                    system("cls");

                    GenerateMenu(&choose_pos, file[language],
                        &cursorPos, hStdOut, 3, NONE_TITLE);
                    switch (choose_pos) {
                    case 0:
                        system("cls");
                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = TRUE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);

                        printf(language == 0 ? "Введите расположение файла: " : "Input filepath: ");
                        scanf_s(" ");
                        gets(dir_in);
                        system("cls");

                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        break;
                    case 1:
                        system("cls");
                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = TRUE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);

                        printf(language == 0 ? "Введите расположение файла: " : "Output filepath: ");
                        scanf_s(" ");
                        gets(dir_out);
                        system("cls");

                        GetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        structCursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(hStdOut, &structCursorInfo);
                        break;
                    case 2:
                        break;
                    }
                    printf("Input file: %s\nOutput file: %s\n", dir_in, dir_out);
                    system("pause");
                    break;
                case 4: // back
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