#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i, j, r;

void timer(int SIZE) {
    int i, j, r;
    int** a = (int**)malloc(SIZE * sizeof(int*));
    int** b = (int**)malloc(SIZE * sizeof(int*));
    int** c = (int**)malloc(SIZE * sizeof(int*));

    for (i = 0; i < SIZE; i++)
    {
        a[i] = (int*)malloc(SIZE * sizeof(int));
        b[i] = (int*)malloc(SIZE * sizeof(int));
        c[i] = (int*)malloc(SIZE * sizeof(int));
    }

    // Запускаем таймер


    srand(time(NULL)); // инициализируем параметры генератора случайных чисел
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
            b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
        }
    }
    clock_t start, end; // объявляем переменные для определения времени выполнения
    double cpu_time_used;


    start = clock();

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            int elem_c = 0;
            for (r = 0; r < SIZE; r++)
            {
                elem_c += a[i][r] * b[r][j]; // считаем элемент результата
            }
            c[i][j] = elem_c;
        }
    }

    // Заканчиваем таймер
    end = clock();
    cpu_time_used = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;

    printf("%d\t%f\n", SIZE, cpu_time_used);
    for (i = 0; i < SIZE; i++)
    {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}



int main()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Размер\tВремя выполнения (мс)\n");
    printf("---------------------------\n");

    timer(100);
    timer(200);
    timer(400);
    timer(1000);
    timer(2000);
    timer(4000);
    timer(10000);

    return 0;
}