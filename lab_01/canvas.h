#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>

#include "error_list.h"
#include "polygon.h"
#include "figure.h"

using GraphCanvas = QGraphicsScene;

struct Canvas
{
    GraphCanvas *field;
    double width;
    double height;
};

void fit_figure_to_canvas(Figure &figure, Canvas canvas);
Error draw_object(const Points &points, const Links &links, Canvas canvas);
Error draw_figure(Figure figure, Canvas canvas);
Error connect_dots(Dot point1, Dot point2, Canvas canvas);
void clear_canvas(Canvas canvas);

#endif // CANVAS_H
