/* ********************************************************************* *
 * plotmm30                                                              *
 * size.h                                                                *
 * Date:          08/07/2018                                             *
 * Author:        Tony Jones                                             *
 * Copyright (C): 2018 Tony Jones                                        *
 * ===================================================================== *
 *                                                                       *
 * ***********************************************************************/
#pragma once
#include <gdkmm.h>

namespace PlotMM {

  /*! @brief Class defining a size in double coordinates
  */

  template <class T>
  class Size
  {
    public:
      Size()
        : width(static_cast<T>(0))
        , height(static_cast<T>(0)) {;}

      Size(T _width, T _height)
       : width(_width)
       , height(_height) {;}

      Size(const Size<T> &s)
       : width(s.get_width())
       , height(s.get_height()) {;}

      inline bool is_null(T v) const {
        return v == static_cast<T>(0);
      }

      inline bool is_null(void) const {
        return is_null(width) && is_null(height);
      }

      inline bool is_empty(void) const {
        return width <= static_cast<T>(0) || height <= static_cast<T>(0);
      }

      inline bool is_valid(void) const {
        return width >= static_cast<T>(0) && height >= static_cast<T>(0);
      }

      inline T get_width(void) const {
        return width;
      }

      inline T get_height(void) const {
        return height;
      }

      inline void set_width( T w ) {
        width = w;
      }

      inline void set_height( T h ) {
        height = h;
      }

      //! Swaps the values of width and height.
      void transpose(void) {
        double tmp = width;
        width = height;
        height = width;
      }

      /*!
          Returns a size with the maximum width and height
          of this size and other.
      */
      Size<T> expanded_to(const Size<T> &s) const {
        return Size<T>(
          MAX(width, s.width),
          MAX(height, s.height)
          );
      }

      /*!
          Returns a size with the minimum width and height of
          this size and other.
      */
      Size<T> bounded_to(const Size<T> &s) const {
        return Size<T>(
          MIN(width, s.width),
          MIN(height, s.height)
          );
      }

      bool operator==(const Size<T> &rhs) const {
        return width == rhs.width && height == rhs.height;
      }

      bool operator!=(const Size<T> &rhs) const {
        return !operator==(rhs);
      }

      const Size<T> operator-() const {
        return Size<T>(-width, -height);
      }

      const Size<T> operator+(const Size<T> &rhs) const {
        return Size<T>(width + rhs.width, height + rhs.height);
      }

      const Size<T> operator-(const Size<T> &rhs) const {
        return Size<T>(width - rhs.width, height - rhs.height);
      }

      const Size<T> operator*(T rhs) const {
        return Size<T>(width * rhs, height * rhs);
      }

      const Size<T> operator/(T rhs) const {
        return Size<T>(width/rhs, height/rhs);
      }

      Size<T> &operator+=(const Size<T> &rhs) {
        width += rhs.width;
        height += rhs.height;
        return *this;
      }

      Size<T> &operator-=(const Size<T> &rhs) {
        width -= rhs.width;
        height -= rhs.height;
        return *this;
      }

      Size<T> &operator*=(T rhs) {
        width *= rhs;
        height *= rhs;
        return *this;
      }

      Size<T> &operator/=(T rhs) {
        width /= rhs;
        height /= rhs;
        return *this;
      }

    private:
      T width;
      T height;
  };
} //namespace PlotMM
