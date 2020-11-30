#include <stdio.h>

#include "canvas.h"
#include "game_of_life.h"

int main() {
    struct board* current = board_load("max.gol");
    struct canvas* canvas = canvas_create(10 * current->width, 10 * current->height);
    struct board* next = board_create(current->width, current->height);

    char pbm_filename[13];
    for (int i = 0; i < 50; ++i) {
        render(canvas, current);
        sprintf(pbm_filename, "max/%03d.pbm", i);
        printf("%d\n", pbm_filename);
        save_pbm(canvas, pbm_filename);

        next_generation(current, next);
        void* temp = current;
        current = next;
        next = temp;
    }

    return 0;
}