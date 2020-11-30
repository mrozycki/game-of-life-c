#include "game_of_life.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct board* board_create(int width, int height) {
    struct board* board = malloc(sizeof(struct board));
    board->width = width;
    board->height = height;
    board->cells = malloc(width * height * sizeof(enum cell));
    return board;
}

struct board* board_load(const char* path) {
    struct board* board = malloc(sizeof(struct board));
    FILE* file = fopen(path, "r");
    fscanf(file, "%d %d", &board->width, &board->height);
    int board_size = board->width * board->height;
    board->cells = malloc(board_size * sizeof(enum cell));
    for (int i = 0; i < board_size; ++i) {
        fscanf(file, "%d", &(board->cells[i]));
    }
    fclose(file);
    return board;
}

void board_free(struct board* board) {
    free(board->cells);
    free(board);
}

void board_print(struct board* board) {
    printf("%d %d\n", board->width, board->height);
    for (int j = 0; j < board->height; ++j) {
        for (int i = 0; i < board->width; ++i) {
            printf("%d ", is_alive(board, i, j));
        }
        printf("\n");
    }
    printf("\n");
}


enum cell is_alive(struct board* board, int x, int y) {
    if (x >= 0 && x < board->width && y >= 0 && y <= board->height) {
        return board->cells[y * board->width + x];
    }
    return DEAD;
}

void set_alive(struct board* board, int x, int y, enum cell status) {
    if (x >= 0 && x < board->width && y >= 0 && y <= board->height) {
        board->cells[y * board->width + x] = status;
    }
}

enum cell next_state(enum cell alive, int neighbors_count) {
    return (alive && neighbors_count == 2) || neighbors_count == 3;
}

int count_neighbors(struct board* board, int x, int y) {
    int count = 0;
    for (int j = y-1; j <= y+1; ++j) {
        for (int i = x-1; i <= x+1; ++i) {
            count += is_alive(board, i, j);
        }
    }
    return count - is_alive(board, x, y);
}

enum cell next_cell_state(struct board* board, int x, int y) {
    return next_state(is_alive(board, x, y), count_neighbors(board, x, y));
}

void next_generation(struct board* current, struct board* next) {
    assert(current->width == next->width && current->height == next->height);
    for (int j = 0; j < current->height; ++j) {
        for (int i = 0; i < current->width; ++i) {
            set_alive(next, i, j, next_cell_state(current, i, j));
        }
    }
}

void render(struct canvas* canvas, struct board* board) {
    int cell_width = canvas->width / board->width;
    int cell_height = canvas->height / board->height;

    rect(canvas, 0, 0, canvas->width, canvas->height, 0);
    for (int j = 0; j < board->height; ++j) {
        for (int i = 0; i < board->width; ++i) {
            rect(canvas, i*cell_width, j*cell_height, cell_width, cell_height, is_alive(board, i, j));
        }
    }
}