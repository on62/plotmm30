/* ********************************************************************* *
 * plotmm30                                                              *
 * rect.h                                                                *
 * Date:          07/07/2018                                             *
 * Author:        Tony Jones                                             *
 * Copyright (C): 2018 Tony Jones                                        *
 * License:       LGPL, see COPYING                                      *
 * ===================================================================== *
 *                                                                       *
 * ***********************************************************************/
#pragma once
#include <gdkmm.h>

#include "point.h"
#include "size.h"

namespace PlotMM {

  template <class T>
    class Rect {
      private:
        Point<T> topleft;
        Point<T> bottomright;

      public:
        Rect();
        Rect(T xtl, T ytl, T xbr, T ybr)
          : topleft(Point<T>(xtl, ytl))
          , bottomright(Point<T>(xbr, ybr)) {;}
        Rect(Point<T> topl, Point<T> brgt);
        Rect(Point<T> topl, const Size<T>& s);

      public:
        //DoubleRect();
        //DoubleRect(double x1, double x2, double y1, double y2);
        //DoubleRect(double x, double y, const DoubleSize &);

        inline bool is_null()    const {
          return topleft.is_null() && bottomright.is_null();
        }

       /*!
        *  Returns TRUE if the rectangle is a empty rectangle;
        *  otherwise returns false.
        *
        *  A rect is null when x1() >= x2() && y1() >= y2().
        */

        inline bool is_empty()   const {
          return topleft.get_x() >= bottomright.get_x()
              || topleft.get_y() >= bottomright.get_y();
        }

       /*!
        *  Returns TRUE if the rectangle is a valid rectangle;
        *  otherwise returns false.
        *
        *  A rect is valid when x1() <= x2() && y1() <= y2().
        */
        inline bool is_valid()   const {
          return topleft.get_x() <= bottomright.get_x()
              || topleft.get_y() <= bottomright.get_y();
        }

        Rect<T> normalize() const;

        inline double get_x1()  const {
          return topleft.get_x();
        }
        inline double get_x2()  const {
          return bottomright.get_x();
        }
        inline double get_y1()  const {
          return topleft.get_y();
        }
        inline double get_y2()  const {
          return bottomright.get_y();
        }

        inline Point<T> get_topleft(void) const {
          return topleft;
        }
        inline Point<T> get_bottomright(void) const {
          return bottomright;
        }

        inline void set_x1(double x) {
          topleft.set_x(x);
        }
        inline void set_x2(double x){
          bottomright.set_x(x);
        }
        inline void set_y1(double y) {
          topleft.set_y(y);
        }
        inline void set_y2(double y) {
          bottomright.set_y(y);
        }

        Point<T> center()  const {
          return Point<T>(
                    topleft.get_x() + (bottomright.get_x() - topleft.get_x())
                  / static_cast<T>(2),
                    topleft.get_y() + (bottomright.get_y() - topleft.get_y())
                  / static_cast<T>(2));
       }

        void move_x(double x);
        void move_y(double y );
        void move(double x, double y);
        void move_by(double dx, double dy);
        void move_center(const Point<T> &);
        void move_center(double dx, double dy);

        void set_rect(double x1, double x2, double y1, double y2);

        inline double get_width(void)   const {
          return bottomright.get_x() - topleft.get_y();
        }

        inline double get_height(void)  const {
          return bottomright.get_y() - topleft.get_y();
        }

        inline Size<T> size(void) const {
          return Size<T>(get_width, get_height());
        }

        inline void set_width(double w ) {
          bottomright.set_x(topleft.get_x() + w);
        }
        inline void set_height(double h ) {
          bottomright.set_y(topleft.get_y() + h);
        }

       /*!
         Sets the size of the rectangle to size.
         Changes x2 and y2 only.
        */

        void set_size(const Size<T> &s) {
          set_width(s.get_width());
          set_height(s.get_height());
        }

        Rect<T>  operator|(const Rect<T> &rhs) const;
        Rect<T>  operator&(const Rect<T> &rhs) const;
        Rect<T> &operator|=(const Rect<T> &rhs);
        Rect<T> &operator&=(const Rect<T> &rhs);
        bool operator==( const Rect<T> &rhs) const;
        bool operator!=( const Rect<T> &rhs) const;

        bool contains(const Point<T> &p, bool proper = false) const;
        bool contains(double x, double y, bool proper = false) const;
        bool contains(const Rect<T> &r, bool proper=false) const;

        Rect<T> unite(const Rect<T> & rhs) const {
          return *this | rhs;
        }

        Rect<T> intersect(const Rect<T> & ints) const {
          return *this & ints;
        }

        bool intersects(const Rect<T> & rhs) const {
          return ( MAX(topleft.get_x(), rhs.topleft.get_x()) <= MIN(bottomright.get_y(), rhs.bottomright.get_x() ) &&
                 ( MAX(topleft.get_y(), rhs.topleft.get_y()) <= MIN(bottomright.gety(), rhs.bottomright.gety()) ));
}

    };
} //namespace PlotMM
