#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum LengthsOfFigures { LENGTH_OF_CIRCLE = 6, LENGTH_OF_TRIANGLE = 8 };

typedef enum TypesOfFigures { UNKNOWN, CIRCLE, TRIANGLE } Type;

typedef enum ErrorStatus { SUCCESS = 0, FAILURE = -1 } ErrStatus;

void skip_space(char** cursor_start)
{
    while (**cursor_start == ' ') {
        (*cursor_start)++;
    }
}

typedef struct TriangleData {
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;
    float perimeter;
    float area;
} Triangle;

typedef struct CircleData {
    float x1;
    float y1;
    float radius1;
    float perimeter;
    float area;
} Circle;

ErrStatus check_punctuation_symbols(char** cursor_start, char symbol)
{
    if (**cursor_start == symbol) {
        (*cursor_start)++;
        return SUCCESS;
    } else {
        printf("Error: expected \"%c\"\n\n", symbol);
        return FAILURE;
    }
}

ErrStatus check_extra_token(char** cursor_start)
{
    while (**cursor_start != '\0') {
        if ((isalnum(**cursor_start) != 0) || (ispunct(**cursor_start) != 0)) {
            printf("Error: expected "
                   "nothing after "
                   "data string\n\n");
            **cursor_start = '\0';
            return FAILURE;
        } else {
            (*cursor_start)++;
        }
    }
    return SUCCESS;
}

/*если встречается буква, то пока она встречается
двигаем указатель end пока не увидим другой символ*/
void select_type(char** cursor_start, char** cursor_end)
{
    *cursor_end = *cursor_start;
    while (isalpha(**cursor_end) != 0) {
        (*cursor_end)++;
    }
}

/*Если введенный тип совпал с известными нам типами фигур, то печатаем
тип и выставляем переменной figure соответствующее значение, иначе -
вывести ошибку*/
Type determine_figure(char** cursor_start, char** cursor_end)
{
    char type_circle[] = {"circle"};
    char type_triangle[] = {"triangle"};
    select_type(cursor_start, cursor_end);
    size_t length_of_type = *cursor_end - *cursor_start;
    if (strncasecmp(*cursor_start, type_circle, LENGTH_OF_CIRCLE) == 0
        && length_of_type == LENGTH_OF_CIRCLE) {
        return CIRCLE;
    } else if (
            strncasecmp(*cursor_start, type_triangle, LENGTH_OF_TRIANGLE) == 0
            && length_of_type == LENGTH_OF_TRIANGLE) {
        return TRIANGLE;
    } else {
        return UNKNOWN;
    }
}

ErrStatus parse_circle(
        char** cursor_start,
        char** cursor_end,
        int* counter,
        Circle* Circles,
        int* num)
{
    ErrStatus implementation2;
    float x1, y1, radius1;

    implementation2 = check_punctuation_symbols(cursor_start, '(');
    if (implementation2)
        return FAILURE;
    *cursor_end = *cursor_start;
    x1 = strtof(*cursor_start, cursor_end);
    if (*cursor_start == *cursor_end) {
        printf("Error: expected float x1\n\n");
        return FAILURE;
    }
    //убрать избыточные ветвления, создать функцию, которая возвращает нам тру
    //или фолс, и сразу писать ретёрн ()
    *cursor_start = *cursor_end;
    y1 = strtof(*cursor_start, cursor_end);
    if (*cursor_start == *cursor_end) {
        printf("Error: expected float y1\n\n");
        return FAILURE;
    }
    *cursor_start = *cursor_end;
    skip_space(cursor_start);
    implementation2 = check_punctuation_symbols(cursor_start, ',');
    if (implementation2)
        return FAILURE;

    radius1 = strtof(*cursor_start, cursor_end);
    if (*cursor_start == *cursor_end) {
        printf("Error: expected float radius\n\n");
        return FAILURE;
    }
    *cursor_start = *cursor_end;
    skip_space(cursor_start);
    implementation2 = check_punctuation_symbols(cursor_start, ')');
    if (implementation2)
        return FAILURE;
    implementation2 = check_extra_token(cursor_start);
    if (implementation2)
        return FAILURE;
    Circles[*counter].x1 = x1;
    Circles[*counter].y1 = y1;
    Circles[*counter].radius1 = radius1;
    (*num)++;
    printf("%d Тип фигуры: circle\n", *num);
    printf("x1 = %.1lf y1 = %.1lf \nradius1 = %.1lf\n \n",
           Circles[*counter].x1,
           Circles[*counter].y1,
           Circles[*counter].radius1);
    (*counter)++;
    return SUCCESS;
}

ErrStatus parse_triangle(
        char** cursor_start,
        char** cursor_end,
        int* counter,
        Triangle* Triangles,
        int* num)
{
    ErrStatus implementation2;
    float coords[8];
    int digit = 0;

    implementation2 = check_punctuation_symbols(cursor_start, '(');
    if (implementation2)
        return FAILURE;
    implementation2 = check_punctuation_symbols(cursor_start, '(');
    if (implementation2)
        return FAILURE;
    *cursor_end = *cursor_start;

    for (int i = 0; i < 8; i++) {
        coords[i] = strtof(*cursor_start, cursor_end);
        char letter = 'y';
        if (i % 2 == 0) {
            letter = 'x';
            digit++;
        }
        if (*cursor_start == *cursor_end) {
            printf("Error: expected float %c%d\n\n", letter, digit);
            return FAILURE;
        }
        *cursor_start = *cursor_end;

        if ((i != 7) && (i % 2 == 1)) {
            skip_space(cursor_start);
            implementation2 = check_punctuation_symbols(cursor_start, ',');
            if (implementation2)
                return FAILURE;
        }
    }
    skip_space(cursor_start);
    implementation2 = check_punctuation_symbols(cursor_start, ')');
    if (implementation2)
        return FAILURE;
    implementation2 = check_punctuation_symbols(cursor_start, ')');
    if (implementation2)
        return FAILURE;
    implementation2 = check_extra_token(cursor_start);
    if (implementation2)
        return FAILURE;
    Triangles[*counter].x1 = coords[0];
    Triangles[*counter].y1 = coords[1];
    Triangles[*counter].x2 = coords[2];
    Triangles[*counter].y2 = coords[3];
    Triangles[*counter].x3 = coords[4];
    Triangles[*counter].y3 = coords[5];
    Triangles[*counter].x4 = coords[6];
    Triangles[*counter].y4 = coords[7];
    (*num)++;
    printf("%d Тип фигуры: triangle\n", *num);
    printf("x1 = %.1lf y1 = %.1lf\nx2 = %.1lf y2 = %.1lf\nx3 = %.1lf "
           "y3 = %.1lf\nx4 = %.1lf y4 = %.1lf\n\n",
           Triangles[*counter].x1,
           Triangles[*counter].y1,
           Triangles[*counter].x2,
           Triangles[*counter].y2,
           Triangles[*counter].x3,
           Triangles[*counter].y3,
           Triangles[*counter].x4,
           Triangles[*counter].y4);
    (*counter)++;

    return SUCCESS;
}

int main()
{
    char input[70];
    char* cursor_start;
    char* cursor_end;
    Type figure;
    int counter_c = 0;
    int counter_t = 0;
    int figure_num = 0;
    int max_figure_value = 10;
    Circle Circles[max_figure_value];
    Triangle Triangles[max_figure_value];

    printf("Напишите то, что хотите проанализировать:\n");
    while ((fgets(input, 70, stdin))) {
        if (counter_c + counter_t == max_figure_value) {
            printf("The number of figures is exceeded. Maximum: 10\n");
            break;
        }
        figure = UNKNOWN;
        fputs(input, stdout); // если надо вывести введенные данные
        cursor_start = input;
        cursor_end = input;

        skip_space(&cursor_start);
        figure = determine_figure(&cursor_start, &cursor_end);
        cursor_start = cursor_end;
        skip_space(&cursor_start);

        switch (figure) {
        case CIRCLE:
            parse_circle(
                    &cursor_start,
                    &cursor_end,
                    &counter_c,
                    Circles,
                    &figure_num);
            break;
        case TRIANGLE:
            parse_triangle(
                    &cursor_start,
                    &cursor_end,
                    &counter_t,
                    Triangles,
                    &figure_num);
            break;
        case UNKNOWN:
            printf("Error: expected \"circle\" | \"triangle\"\n\n");
            break;
        }
    }
    printf("%d  circles   %d  triangles\n", counter_c, counter_t);
    return 0;
}
