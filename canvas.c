#include "canvas.h"

#include <stdio.h>
#include <stdlib.h>

struct canvas* canvas_create(int width, int height) {
    struct canvas* canvas = malloc(sizeof(struct canvas));
    canvas->width = width;
    canvas->height = height;
    canvas->pixels = malloc(width * height * sizeof(char));
    return canvas;
}

void canvas_free(struct canvas* canvas) {
    free(canvas->pixels);
    free(canvas);
}

void print_pbm(struct canvas* canvas) {
    printf("P1\n%d %d\n", canvas->width, canvas->height);
    for (int i = 0; i < canvas->width * canvas->height; ++i) {
        printf("%d ", canvas->pixels[i]);
    }
    printf("\n");
}

void save_pbm(struct canvas* canvas, const char* path) {
    FILE* file = fopen(path, "w");
    fprintf(file, "P1\n%d %d\n", canvas->width, canvas->height);
    for (int i = 0; i < canvas->width * canvas->height; ++i) {
        fprintf(file, "%d ", canvas->pixels[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

char get_pixel(struct canvas* canvas, int x, int y) {
    return canvas->pixels[y * canvas->width + x];
}

void set_pixel(struct canvas* canvas, int x, int y, char color) {
    canvas->pixels[y * canvas->width + x] = color;
}

void rect(struct canvas* canvas, int x, int y, int w, int h, char color) {
    for (int j = y; j < y + h; ++j) {
        for (int i = x; i < x + w; ++i) {
            set_pixel(canvas, i, j, color);
        }
    }
}
