#include <libgeometry/geometry.h>
#include <stdio.h>

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
