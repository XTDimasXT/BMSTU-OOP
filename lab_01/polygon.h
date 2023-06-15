#ifndef POLYGON_H
#define POLYGON_H

#include "dot.h"

struct LinkDots
{
    int point_begin;
    int point_end;
};


struct Links
{
    LinkDots *data;
    int len;
};


struct Points
{
    Dot *data;
    int len;
};

Error spin_points(Points &points, Dot center, Change spin_angles);

Error scale_points(Points &points, Dot center, Change scale_koefs);

Error move_points(Points &points, Dot center, Change movements);

bool is_null(const Links &links);

bool is_null(const Points &points);

Error read_points(Points &points, FILE *file);

Error read_dots_connections(Links &links, FILE *file);

void points_init(Points &points);

void free_points(Points &points);

void links_init(Links &links);

void free_links(Links &links);

void center_init(Dot &center);

#endif // POLYGON_H
