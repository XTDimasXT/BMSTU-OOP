#include <math.h>

#include "dot.h"

#define PI acos(-1)
#define TO_RADIANS 180

static double degrees_to_radians(const double angle)
{
    return angle * PI / TO_RADIANS;
}

static double cosinus(const double angle)
{
    return cos(degrees_to_radians(angle));
}


static double sinus(const double angle)
{
    return sin(degrees_to_radians(angle));
}

static void add(Dot &dst, Dot &src)
{
    dst.x += src.x;
    dst.y += src.y;
    dst.z += src.z;
}

static void sub(Dot &dst, Dot &src)
{
    dst.x -= src.x;
    dst.y -= src.y;
    dst.z -= src.z;
}

static void spin_x(Dot &point, const double angle)
{
    double y_tmp = point.y;
    double cos_of_angle = cosinus(angle);
    double sin_of_angle = sinus(angle);

    point.y = point.y * cos_of_angle + point.z * sin_of_angle;
    point.z = point.z * cos_of_angle - y_tmp * sin_of_angle;
}


static void spin_y(Dot &point, const double angle)
{
    double x_tmp = point.x;
    double cos_of_angle = cosinus(angle);
    double sin_of_angle = sinus(angle);

    point.x = point.x * cos_of_angle + point.z * sin_of_angle;
    point.z = point.z * cos_of_angle - x_tmp * sin_of_angle;
}


static void spin_z(Dot &point, const double angle)
{
    double x_tmp = point.x;
    double cos_of_angle = cosinus(angle);
    double sin_of_angle = sinus(angle);

    point.x = point.x * cos_of_angle + point.y * sin_of_angle;
    point.y = point.y * cos_of_angle - x_tmp * sin_of_angle;
}


Error spin_dot(Dot &point, Dot center, const Change spin_angles)
{
    sub(point, center);

    spin_x(point, spin_angles.chg_x);
    spin_y(point, spin_angles.chg_y);
    spin_z(point, spin_angles.chg_z);

    add(point, center);

    return OK;
}


Error scale_dot(Dot &point, Dot center, const Change scale)
{
    point.x = point.x * scale.chg_x + (1 - scale.chg_x) * center.x;
    point.y = point.y * scale.chg_y + (1 - scale.chg_y) * center.y;
    point.z = point.z * scale.chg_z + (1 - scale.chg_z) * center.z;

    return OK;
}


Error move_dot(Dot &point, const Change move)
{
    point.x += move.chg_x;
    point.y += move.chg_y;
    point.z += move.chg_z;

    return OK;
}
