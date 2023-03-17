#ifndef SELECTOR_H
#define SELECTOR_H

#include "canvas.h"
#include "change.h"

enum Actions {
    DRAW,
    LOAD,
    SCALE,
    SPIN,
    MOVE,
    QUIT
};


struct Event
{
    Canvas canvas;
    Change change;
    const char *file_name;
};

Error select_action(Actions action, Event event);

#endif // SELECTOR_H
