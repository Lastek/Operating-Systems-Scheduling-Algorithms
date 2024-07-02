#include "util.h"
/**
 * return 1 if match, 0 otherwise
 */
int double_cmp(double x, double y, double precision)
{
    x *= precision;
    y *= precision;
    x = std::round(x);
    y = std::round(y);
    if (x == y)
    {
        return 1;
    }
    else
        return 0;
}