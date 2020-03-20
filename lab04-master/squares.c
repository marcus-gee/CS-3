#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "list.h"
#include "sdl_wrapper.h"
#include "vector.h"
#include "polygon.h"
#include "network_util.h"

List *make_square() {
    List *sq = list_init(4, free);
    Vector *v = malloc(sizeof(*v));
    v->x = v->y = +1;
    list_add(sq, v);
    v = malloc(sizeof(*v));
    *v = (Vector) {-1, +1};
    list_add(sq, v);
    v = malloc(sizeof(*v));
    v->x = v->y = -1;
    list_add(sq, v);
    v = malloc(sizeof(*v));
    *v = (Vector) {+1, -1};
    list_add(sq, v);
    return sq;
}

List *me;
List *them;

void move(List *who, char *dir) {
    Vector translation;

    if (strcmp(dir, "up") == 0) {         translation = (Vector){0, 1};  }
    else if (strcmp(dir, "down") == 0) {  translation = (Vector){0, -1}; }
    else if (strcmp(dir, "left") == 0) {  translation = (Vector){-1, 0}; }
    else if (strcmp(dir, "right") == 0) { translation = (Vector){1, 0};  }
    else { exit(0); }

    polygon_translate(who, translation);
}

void on_key(char key, KeyEventType type, double held_time) {
    if (type == KEY_PRESSED) {
        switch (key) {
            case UP_ARROW:    move(me, "up"); break;
            case DOWN_ARROW:  move(me, "down"); break;
            case LEFT_ARROW:  move(me, "left"); break;
            case RIGHT_ARROW: move(me, "right"); break;
        }
    }
}


int main(int argc, char **argv){
    // Create a shape
    List *a = make_square();
    List *b = make_square();

    // Translate to the center of area
    Vector center = {.x = 10.0, .y = 5.0};
    polygon_translate(a, (Vector){1, 2});
    polygon_translate(b, (Vector){19, 2});

    me = a;
    them = b;

    // Setup view
    Vector min = VEC_ZERO;
    Vector max = vec_add(center, center);
    sdl_init(min, max);

    sdl_on_key(on_key);

    // Move shape
    while (!sdl_is_done()) {
        sdl_clear();
        sdl_draw_polygon(a, (RGBColor) {1, 0, 0});
        sdl_draw_polygon(b, (RGBColor) {0, 0, 1});
        sdl_show();
    }

    return 0;
}
