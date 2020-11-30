#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "canvas.h"

enum cell { DEAD, ALIVE };

struct board {
    int width;
    int height;
    enum cell* cells;
};

struct board* board_create(int width, int height);
struct board* board_load(const char* path);
void board_free(struct board* board);
void board_print(struct board* board);

void board_clear(struct board* board, enum cell state);
void board_paste(struct board* source, struct board* destination, int x, int y);

enum cell is_alive(struct board* board, int x, int y);
void set_alive(struct board* board, int x, int y, enum cell status);

enum cell next_state(enum cell current_state, int neighbors_count);
int count_neighbors(struct board* board, int x, int y);
enum cell next_cell_state(struct board* board, int x, int y);
void next_generation(struct board* current, struct board* next);

void render(struct canvas* canvas, struct board* board);

#endif