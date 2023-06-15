#include "canvas.h"

Error connect_dots(Dot point1, Dot point2, Canvas canvas)
{
    if (canvas.field == NULL)
    {
        return ERR_NO_FIELD;
    }

    canvas.field->addLine(point1.x, point1.y, point2.x, point2.y, QPen(Qt::black, 3));

    return OK;
}

static void fit_point_to_canvas(Dot &point, Canvas canvas)
{
    point.x += canvas.width / 2;
    point.y += canvas.height / 2;
}

static void fit_points_to_canvas(Points &points, Canvas canvas)
{
    for (int i = 0; i < points.len; i++)
    {
        fit_point_to_canvas(points.data[i], canvas);
    }
}

void fit_figure_to_canvas(Figure &figure, Canvas canvas)
{
    fit_points_to_canvas(figure.points, canvas);
}

static Error draw_figure_side(const LinkDots &link, const Points &points, Canvas canvas)
{
    if (points.data == NULL)
    {
        return ERR_MEMORY_ALLOCATE;
    }

    if (canvas.field == NULL)
    {
        return ERR_NO_FIELD;
    }

    if (link.point_begin < 0 || link.point_end >= points.len)
    {
        return ERR_DATA;
    }

    Dot point1 = points.data[link.point_begin];
    Dot point2 = points.data[link.point_end];

    Error rc = connect_dots(point1, point2, canvas);

    return rc;
}


Error draw_object(const Points &points, const Links &links, Canvas canvas)
{
    if ((points.data == NULL) || (links.data == NULL))
    {
        return ERR_MEMORY_ALLOCATE;
    }

    if (canvas.field == NULL)
    {
        return ERR_NO_FIELD;
    }

    Error rc = OK;

    for (int i = 0; rc == OK && i < links.len; i++)
    {
        rc = draw_figure_side(links.data[i], points, canvas);
    }

    return rc;
}

Error draw_figure(Figure figure, Canvas canvas)
{
    if ((is_null(figure.points)) || (is_null(figure.links)))
    {
        return ERR_MEMORY_ALLOCATE;
    }

    if (canvas.field == NULL)
    {
        return ERR_NO_FIELD;
    }

    fit_points_to_canvas(figure.points, canvas);

    clear_canvas(canvas);

    Error rc = draw_object(figure.points, figure.links, canvas);

    return rc;
}

void clear_canvas(Canvas canvas)
{
    canvas.field->clear();
}
