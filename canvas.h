#ifndef CANVAS_H
#define CANVAS_H

struct canvas {
    int width;
    int height;
    char* pixels;
};

struct canvas* canvas_create(int width, int height);
void canvas_free(struct canvas* canvas);
void print_pbm(struct canvas* canvas);
void save_pbm(struct canvas* canvas, const char* path);

char get_pixel(struct canvas* canvas, int x, int y);
void set_pixel(struct canvas* canvas, int x, int y, char color);
void rect(struct canvas* canvas, int x, int y, int w, int h, char color);


#endif