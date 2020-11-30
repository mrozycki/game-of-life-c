#include <stdio.h>

#include "canvas.h"
#include "game_of_life.h"

int main() {
    const int animation_size = 500;
    struct board* max = board_load("max.gol");
    struct board* current = board_create(animation_size, animation_size);
    board_paste(max, current, (animation_size - max->width)/2, (animation_size - max->height)/2);
    board_free(max);

    struct canvas* canvas = canvas_create(2 * current->width, 2 * current->height);
    struct board* next = board_create(animation_size, animation_size);

    char pbm_filename[13];
    for (int i = 0; i < 200; ++i) {
        render(canvas, current);
        sprintf(pbm_filename, "max/%03d.pbm", i);
        printf("%s\n", pbm_filename);
        save_pbm(canvas, pbm_filename);

        next_generation(current, next);
        void* temp = current;
        current = next;
        next = temp;
    }

    board_free(current);
    board_free(next);
    canvas_free(canvas);
    return 0;
}