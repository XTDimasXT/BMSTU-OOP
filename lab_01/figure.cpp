#include "figure.h"
#include "polygon.h"

Figure figure_init(void)
{
    Figure figure;

    points_init(figure.points);
    center_init(figure.center);
    links_init(figure.links);

    return figure;
}

void center_init(Dot &center)
{
    center.x = 0;
    center.y = 0;
    center.z = 0;
}

void figure_free(Figure &figure)
{
    free_points(figure.points);
    free_links(figure.links);
}

Error read_figure(Figure &figure, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    figure = figure_init();

    Error rc = read_points(figure.points, file);

    if (rc == OK)
    {
        rc = read_dots_connections(figure.links, file);

        if (rc != OK)
        {
            free_points(figure.points);
        }
    }

    return rc;
}

Error load_figure(Figure &figure, const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    Figure temp_figure;

    Error rc = read_figure(temp_figure, file);

    fclose(file);

    if (rc == OK)
    {
        figure_free(figure);
        figure = temp_figure;
    }

    return rc;
}



Error spin_figure(Figure &figure, Dot center, Change spin_angles)
{
    return spin_points(figure.points, center, spin_angles);
}


Error scale_figure(Figure &figure, Dot center, Change scale_koefs)
{
    return scale_points(figure.points, center, scale_koefs);
}


Error move_figure(Figure &figure, Dot &center, Change movements)
{
    return move_points(figure.points, center, movements);
}
