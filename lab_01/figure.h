#ifndef FIGURE_H
#define FIGURE_H

#include "dot.h"
#include "polygon.h"

struct Figure
{
    Points points;
    Links links;
    Dot center;
};

Figure figure_init(void);

Error load_figure(Figure &figure, const char *filename);

Error read_figure(Figure &figure, FILE *file);

void figure_free(Figure &figure);

Error spin_figure(Figure &figure, Dot center, Change spin_angles);

Error move_figure(Figure &figure, Dot &center, Change movements);

Error scale_figure(Figure &figure, Dot center, Change scale_koefs);

void center_init(Dot &center);

#endif // FIGURE_H
