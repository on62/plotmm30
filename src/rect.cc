/* ********************************************************************* *
 * plotmm30                                                              *
 * rect.cc                                                                *
 * Date:          09/07/2018                                             *
 * Author:        Tony Jones                                             *
 * Copyright (C): 2018 Tony Jones                                        *
 * License:       LGPL, see COPYING                                      *
 * ===================================================================== *
 *                                                                       *
 * ***********************************************************************/

#include "point.h"
#include "size.h"
#include "rect.h"

namespace PlotMM {
/*!
  Returns a normalized rectangle, i.e. a rectangle that has a non-negative
  width and height.

  It swaps x1 and x2 if x1() > x2(), and swaps y1 and y2 if y1() > y2().
*/

template <class T>
Rect<T> Rect<T>::normalize() const
{
    Rect<T> rv;

    // if right < left, then rectangle is mirrored
    // and width is negative, therefore we need top
    // swap left and right.
    if ( bottomright.get_x() < topleft.get_x() )
    {
        rv.topleft.set_x(bottomright.get_x());
        rv.bottomright.set_x(bottomright.get_x());
    }
    else
    {
        rv.topleft.set_x(topleft.get_x());
        rv.bottomright.set_x(bottomright.get_x());
    }

    // if bottom < top, then rectangle is upside down,
    // therefore we swap top and bottom.
    if ( bottomright.get_y() < topleft.get_y() )
    {
        rv.topleft.set_y(bottomright.get_y());
        rv.bottomright.set_y(topleft.get_y());
    }
    else
    {
        rv.topleft.set_y(topleft.get_y());
        rv.bottomright.set_y(bottomright.get_y());
    }

    return rv;
}

/*!
  Returns the bounding rectangle of this rectangle and rectangle other.
  The bounding rectangle of a nonempty rectangle and an empty or
  invalid rectangle is defined to be the nonempty rectangle.
*/

template <class T>Rect<T>
Rect<T>::operator|(const Rect<T> &rhs) const
{
    if ( !is_valid() )
        return rhs;

    if ( !rhs.is_valid() )
        return *this;

    return Rect(MIN(topleft.get_x(), rhs.topleft.get_x()), MAX(bottomright.get_x(), rhs.bottomright.get_x()),
        MIN(topleft.get_y(), rhs.topleft.get_y()), MAX(bottomright.get_y(), rhs.bottomright.get_y()) );
}

/*!
  Returns the intersection of this rectangle and rectangle other.
  Returns an empty rectangle if there is no intersection.
*/

template <class T>
Rect<T> Rect<T>::operator&(const Rect<T> &rhs) const
{
    return Rect<T>(MAX(topleft.get_x(), rhs.topleft.get_x()), MIN(bottomright.get_x(), rhs.bottomright.get_x()),
        MAX(topleft.get_y(), rhs.topleft.get_y()), MIN(bottomright.get_y(), rhs.bottomright.get_y()));
}

} //namespace PlotMM
