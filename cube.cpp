#include<iostream>
#include "cube.h"

Cube::Cube(const Face& f1, const Face& f2, const Face& f3,
           const Face& f4, const Face& f5, const Face& f6)
    : Renderable({f1, f2, f3, f4, f5, f6})  // <-- magie ici
{
}

