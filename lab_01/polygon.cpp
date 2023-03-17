#include "polygon.h"
#include "dot.h"

Error scale_points(Points &points, Dot center, Change scale_koefs)
{
    if (points.data == NULL)
    {
        return ERR_NO_FIGURE;
    }

    Error rc = OK;

    for (int i = 0; rc == OK && i < points.len; i++)
    {
        rc = scale_dot(points.data[i], center, scale_koefs);
    }

    return rc;
}

Error move_points(Points &points, Dot center, Change movements)
{
    if (points.data == NULL)
    {
        return ERR_NO_FIGURE;
    }

    Error rc = OK;

    for (int i = 0; rc == OK && i < points.len; i++)
    {
        rc = move_dot(points.data[i], movements);
    }

    if (rc == OK)
    {
        move_dot(center, movements);
    }

    return rc;
}

Error spin_points(Points &points, Dot center, Change spin_angles)
{
    if (points.data == NULL)
    {
        return ERR_NO_FIGURE;
    }

    Error rc = OK;

    for (int i = 0; rc == OK && i < points.len; i++)
    {
        rc = spin_dot(points.data[i], center, spin_angles);
    }

    return rc;
}

bool is_null(const Links &links)
{
    return links.data == NULL;
}

bool is_null(const Points &points)
{
    return points.data == NULL;
}

static Error read_amount(int &amount, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    if (fscanf(file, "%d", &amount) != 1)
    {
        return ERR_DATA;
    }

    return OK;
}

void points_init(Points &points)
{
    points.data = NULL;
    points.len = 0;
}


void free_points(Points &points)
{
    free(points.data);
    points.len = 0;
}


static Error read_point(Dot &dot, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    if (fscanf(file, "%lf %lf %lf", &dot.x, &dot.y, &dot.z) != 3)
    {
        return ERR_DATA;
    }

    return OK;
}


static Error read_all_dots(Points &points, FILE *file)
{
    Error rc = OK;

    for (int i = 0; rc == OK && i < points.len; i++)
    {
        rc = read_point(points.data[i], file);
    }

    return rc;
}


static Error allocate_points(Points &points, int len)
{
    points.data = (Dot*) malloc(len * sizeof(Dot));
    points.len = len;

    if (points.data == NULL)
    {
        return ERR_MEMORY_ALLOCATE;
    }

    return OK;
}


Error read_points(Points &points, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    int amount = 0;
    Error rc = read_amount(amount, file);

    if (rc == OK)
    {
        rc = allocate_points(points, amount);
        if (rc == OK)
        {
            rc = read_all_dots(points, file);
            if (rc != OK)
            {
                free_points(points);
            }
        }
    }

    return rc;
}

void links_init(Links &links)
{
    links.data = NULL;
    links.len = 0;
}


void free_links(Links &links)
{
    free(links.data);
    links.len = 0;
}


static Error allocate_connections_arr(Links &links, int len)
{
    links.data = (LinkDots*) malloc(len * sizeof(LinkDots));
    links.len = len;

    if (links.data == NULL)
    {
        return ERR_MEMORY_ALLOCATE;
    }

    return OK;
}


static Error read_connection(LinkDots &link, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    if (fscanf(file, "%d %d", &link.point_begin, &link.point_end) != 2)
    {
        return ERR_DATA;
    }

    return OK;
}


Error read_dots_connections(Links &links, FILE *file)
{
    if (file == NULL)
    {
        return ERR_FILE_OPEN;
    }

    int amount = 0;
    Error rc = read_amount(amount, file);

    if (rc == OK)
    {
        rc = allocate_connections_arr(links, amount)
        if (rc == OK)
        {
            for (int i = 0; i < amount && rc == OK; i++)
            {
                rc = read_connection(links.data[i], file);
            }
            
            if (rc != OK)
            {
                free(links.data);
            }
        }
    }

    return rc;
}
