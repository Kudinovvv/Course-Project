#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include <string.h>


#define N 7
int grid[N][N];
int visited[N][N];
int isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}
int canPlaceBlackCell(int x, int y) {
    if (grid[x][y] > 0) {
        return 0;
    }
    if (isValid(x - 1, y) && isValid(x + 1, y) && grid[x - 1][y] > 0 && grid[x + 1][y] > 0) {
        return 0;
    }
    if (isValid(x, y - 1) && isValid(x, y + 1) && grid[x][y - 1] > 0 && grid[x][y + 1] > 0) {
        return 0;
    }
    return 1;
}
int canPlaceWhiteCell(int x, int y) {
    if (grid[x][y] > 0) {
        return 1;
    }

    return 1;
}
void dfs(int x, int y) {
    if (visited[x][y] || grid[x][y] > 0 || !canPlaceWhiteCell(x, y)) {
        return;
    }
    visited[x][y] = 1;
    if (isValid(x - 1, y)) {
        dfs(x - 1, y);
    }
    if (isValid(x + 1, y)) {
        dfs(x + 1, y);
    }
    if (isValid(x, y - 1)) {
        dfs(x, y - 1);
    }
    if (isValid(x, y + 1)) {
        dfs(x, y + 1);
    }
}
int main()
{
    system("color F0");
    setlocale(LC_ALL, "RUS");
    int i, j, answer = 0, COL = 7, ROW = 7, file_answer, rows, cols;
    srand(time(0));
    FILE* file;
    printf("Добрый день, добро пожаловать в игру головоломку \"Куромасу\"!\n Правила игры:\n - Каждое число в сетке определяет количество белых клеток вокруг этого числа.\n - Число 0 означает, что нет белые клетки вокруг данной ячейки.\n - Каждая черная клетка блокирует доступ к белым клеткам вокруг нее.\n - Цель игры - определить цвет каждой ячейки сетки, следуя правилам игры.");
    while (answer != 3)
    {
        printf("Введите число от 1-3 для выбора пункта главного меню игры: \n1. Стандартная игра.\n2. Творческий режим.\n3. Выход из игры.\nВаш ответ: ");
        scanf("%d", &answer);

        if (answer == 1)
        {
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    grid[i][j] = rand() % 5;
                    visited[i][j] = 0;
                    if (rand() % 2 == 0) {
                        grid[i][j] = -1;
                    }
                }
            }
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    if (grid[i][j] == 0 && !visited[i][j]) {
                        dfs(i, j);
                    }
                }
            }
            printf("Цвета ячеек:\n");
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    if (grid[i][j] > 0) {
                        printf("Ячейка (%d,%d): Белая\n", i, j);
                    }
                    else if (visited[i][j]) {
                        printf("Ячейка (%d,%d): Белая\n", i, j);
                    }
                    else {
                        printf("Ячейка (%d,%d): Черная\n", i, j);
                    }
                }
                printf("\n");
            }
            printf("\nИгровое поле:\n");
            for (int i = 0; i < N * 3 ; i++)
            {
                printf("_");
            }
            printf("\n");
            for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                    printf("|");  // Добавляем границу
                    if (grid[i][j] == -1) {
                        printf("X|");
                    }
                    else if (grid[i][j] > 0) {
                        printf("%d|", grid[i][j]);
                    }
                    else if (visited[i][j]) {
                        printf(".|");
                    }
                    else {
                        printf("?|");
                    }
                }
                printf("\n");
            }
            for (int i = 0; i < N * 3 ; i++)
            {
                printf("-");
            }
            printf("\n");
            file = fopen("temp.txt", "w");
            if (file == NULL)
            {
                perror("Ошибка открытия файла!\n");
                return 1;
            }
            for (int i = 0; i < ROW; i++)
            {
                for (int j = 0; j < COL; j++)
                {
                    fprintf(file, "%d ", grid[i][j]);
                }
                fprintf(file, "\n");
            }
            fclose(file);
        }
        else if (answer == 2)
        {
            int rows = 0, cols = 0, ch;
            file = fopen("temp.txt", "r");
            printf("Хотите загрузить последние сохранение?\n1. Да.\n2. Нет.\nВаш ответ: ");
            scanf("%d", &file_answer);
            if (file_answer == 1)
            {
                int matrix[10][10];
                for (int i = 0; i < 10; i++)
                {
                    for (int k = 0; k < 10; k++)
                    {
                        matrix[i][k] = 0;
                    }
                }
                if (file == NULL)
                {
                    printf("Не удалось открыть файл.\n");
                    return 1;
                }

                char sym[5] = "";
                char s = '\0';

                int r = 0;
                int l = 0;


                while (s != EOF)
                {
                    s = fgetc(file);

                    if (s == ' ' || s == '\n' || s == EOF)
                    {
                        int len = strlen(sym);
                        matrix[r][l] = atoi(sym);

                        for (int x = 0; x < len + 1; x++)
                            sym[x] = '\0';

                        if (s == '\n')
                        {
                            l = 0;
                            r++;
                        }
                        else if (s == EOF)
                            break;
                        else
                            l++;
                    }
                    else
                    {
                        sym[strlen(sym)] = s;
                    }

                }

                int len_r = 0; //Макс длина строки
                int len_c = 0; //Макс дли

                for (int i = 0; i < 10; i++)
                {
                    int mt = matrix[i][0];
                    int mc = matrix[0][i];

                    if (mt != 0)
                        len_r++;

                    if (mc != 0)
                        len_c++;

                }

                printf("%i %i\n", len_r, len_c);
                for (i = 0; i < len_c; i++) {
                    for (j = 0; j < len_r; j++) {
                        if (matrix[i][j] == 0 && !visited[i][j]) {
                            dfs(i, j);
                        }
                    }
                }
                printf("Цвета ячеек:\n");
                for (i = 0; i < len_c; i++) {
                    for (j = 0; j < len_r; j++) {
                        if (matrix[i][j] > 0) {
                            printf("Ячейка (%d,%d): Белая\n", i, j);
                        }
                        else if (visited[i][j]) {
                            printf("Ячейка (%d,%d): Белая\n", i, j);
                        }
                        else {
                            printf("Ячейка (%d,%d): Черная\n", i, j);
                        }
                    }
                    printf("\n");
                }
                printf("\nИгровое поле:\n");
                for (int i = 0; i < len_c * 5 - 3 ; i++)
                {
                    printf("_");
                }
                printf("\n");
                for (i = 0; i < len_c; i++) {
                    for (j = 0; j < len_r; j++) {
                        if (matrix[i][j] == -1) {
                            printf("|X| ");
                        }
                        else if (matrix[i][j] > 0) {
                            printf("|%d| ", matrix[i][j]);
                        }
                        else if (visited[i][j]) {
                            printf("|.| ");
                        }
                        else {
                            printf("|?| ");
                        }
                    }
                    printf("\n");
                    
                }
                for (int i = 0; i < len_r * 5 - 8; i++)
                {
                    printf("-");
                }
                printf("\n");
                
            }
            else if (file_answer == 2)
            {
                file = fopen("temp.txt", "w");
                printf("Введите размер таблицы: ");
                scanf("%d", &COL);
                ROW = COL;
                for (i = 0; i < COL; i++) {
                    for (j = 0; j < ROW; j++) {
                        printf("Введите число для ячейки [%d][%d]: ", i, j);
                        scanf("%d", &grid[i][j]);
                    }
                }
                for (i = 0; i < COL; i++) {
                    for (j = 0; j < ROW; j++) {
                        if (grid[i][j] == 0 && !visited[i][j]) {
                            dfs(i, j);
                        }
                    }
                }
                printf("Цвета ячеек:\n");
                for (i = 0; i < COL; i++) {
                    for (j = 0; j < ROW; j++) {
                        if (grid[i][j] > 0) {
                            printf("Ячейка (%d,%d): Белая\n", i, j);
                        }
                        else if (visited[i][j]) {
                            printf("Ячейка (%d,%d): Белая\n", i, j);
                        }
                        else {
                            printf("Ячейка (%d,%d): Черная\n", i, j);
                        }
                    }
                    printf("\n");
                }
                
                printf("\nИгровое поле:\n");
                for (int i = 0; i < COL * 5 ; i++)
                {
                    printf("_");
                }
                printf("\n");
                for (i = 0; i < COL; i++) {
                    for (j = 0; j < ROW; j++) {
                        if (grid[i][j] == -1) {
                            printf("|X| ");
                        }
                        else if (grid[i][j] > 0) {
                            printf("|%d| ", grid[i][j]);
                        }
                        else if (visited[i][j]) {
                            printf("|.| ");
                        }
                        else {
                            printf("|?| ");
                        }
                    }
                    printf("\n");
                }
                for (int i = 0; i < ROW * 5; i++)
                {
                    printf("-");
                }
                printf("\n");
                if (file == NULL) {
                    perror("Ошибка открытия файла!\n");
                    return 1;
                }
                for (int i = 0; i < ROW; i++)
                {
                    for (int j = 0; j < COL; j++)
                    {
                        fprintf(file, "%d ", grid[i][j]);
                    }
                    fprintf(file, "\n");
                }
                fclose(file);
                return 0;
            }
            else
            {
                printf("Невернй ввод! Нужно выводить число 1, или 2. Пожалуйста, попробуйте ещё раз.\n");
            }
        }
        else if (answer == 3)
        {
            break;
        }
        else
        {
            printf("Неверный ввод. Попробуйте еще раз.\n");
        }
        return 0;
    }
}
