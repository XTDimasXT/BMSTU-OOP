#ifndef DOT_H
#define DOT_H

#include "change.h"
#include "error_list.h"

struct Dot
{
    double x;
    double y;
    double z;
};

Error spin_dot(Dot &point, Dot center, const Change spin_angles);
Error move_dot(Dot &point, const Change move);
Error scale_dot(Dot &point, Dot center, const Change scale);

#endif // DOT_H
