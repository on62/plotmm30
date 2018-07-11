/* ********************************************************************* *
 * plotmm30                                                              *
 * point.h                                                               *
 * Date:          08/07/2018                                             *
 * Author:        Tony Jones                                             *
 * Copyright (C): 2018 Tony Jones                                        *
 * ===================================================================== *
 *                                                                       *
 * ***********************************************************************/
#pragma once
#include <gdkmm.h>

namespace PlotMM {

  template <class T>
    class Point {
      private:
        T x;
        T y;

      public:
        Point()
          : x(static_cast<T>(0))
          , y(static_cast<T>(0)) {;}

        Point(T _x, T _y)
          : x(_x)
          , y(_y) {;}

        Point(const Gdk::Point &p)
          : x(static_cast<T>(p.get_x()))
          , y(static_cast<T>(p.get_y())) {;}

        Point(const Point<T>& cp)
          : x(static_cast<T>(cp.get_x()))
          , y(static_cast<T>(cp.get_y())) {;}

        ~Point() {;}

        bool is_null(T v) const {
          return v == static_cast<T>(0);
        }

        inline bool is_null() const {
          return is_null(x) && is_null(y);
        }

        inline bool is_equal(T lhs, T rhs) const {
          return lhs == rhs;
        }

        inline T get_x(void) const {
          return x;
        }

        inline T get_y(void) const {
          return y;
        }

        inline void set_x(T _x) {
          x = _x;
        }

        inline void set_y(T _y) {
          y = _y;
        }

        // ///////////////////////////////////////////////////////////////
        // Operator overloads.

        bool operator==(const Point<T>& rhs) const {
          return is_equal(x, rhs.get_x()) && is_equal(y, rhs.get_y());
        }

        bool operator!=(const Point<T>& rhs) const {
          return ! (is_equal(x, rhs.get_x()) && is_equal(y, rhs.get_y()));
        }

        const T operator-() const {
          return Point<T>(-x, -y);
        }

        const Point<T> operator+(const Point<T>& rhs) const {
          return Point<T>(x + rhs.get_x(), y + rhs.get_y());
        }

        const Point<T> operator-(const Point<T>& rhs) const {
          return Point<T>(x - rhs.get_x(), y - rhs.get_y());
        }

        const Point<T> operator*(const T rhs) const {
          return Point<T>( x * rhs, y * rhs );
        }

        const Point<T> operator/(const T rhs) const {
          return Point<T>( x/rhs, y/rhs ); //TODO: Handle Div by zero
        }

        Point<T> &operator+=(const Point<T>& rhs) const {
          x += rhs.get_x();
          y += rhs.get_y();
          return *this;
        }

        Point<T> &operator-=(const Point<T>& rhs) const {
          x -= rhs.get_y();
          y -= rhs.get_y();
          return *this;
        }

        Point<T> &operator*=(T rhs) {
          x *= rhs;
          y *= rhs;
          return *this;
        }

        Point<T> &operator/=(T rhs) {
          x /= rhs;
          y /= rhs;
          return *this;
        }

    }; // class Point<T>

} //namespace PlotMM
