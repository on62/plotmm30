/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * PlotMM Widget Library
 * Copyright (C) 2004   Andy Thaller
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 *****************************************************************************/
/* ported from qwt */
#pragma once

#include <vector>
#include <math.h>

namespace PlotMM {

  double ceil_125(double x);
  double floor_125(double x);
  double array_min (double *array, int size);
  double array_max( double *array, int size);
  void twist_array(double *array, int size);
  void twist_array(std::vector<double> &);
  int check_mono(double *array, int size);
  void lin_space(double *array, int size, double xmin, double xmax);
  void log_space(double *array, int size, double xmin, double xmax);
  void lin_space(std::vector<double>&,int size,double xmin,double xmax);
  void log_space(std::vector<double>&,int size,double xmin,double xmax);
  void vector_from_c(std::vector<double> &array,const double *c, int size);

  extern const double LogMin;
  extern const double LogMax;

  inline int iround( double d )
  {
    return static_cast<int> (round( d ));
  }

  /*! Return the sign of the input parameter.
   *
   * \param x the value to be checked.
   * \return an integer value: 1 if x is positive, -1 if x is negative and
   *         0 if x is zero.
   */
  template <class T>
    inline int SIGN(const T& x)
    {
      const T Zero = static_cast<T>(0.0);

      return (x > Zero) ? 1 : (x < Zero) ? -1 : 0;
    }            

  /*! Copy an array into another
   *
   *  \param dest Destination
   *  \param src Source
   *  \param n Number of elements  
   */
  template <class T>
    void copy_array(T *dest, T *src, int n) 
    {
      int i;
      for (i = 0; i < n; i++ )
        dest[i] = src[i];
    }

  /*! Sort two values in ascending order
   *
   *  \param x1 First input value
   *  \param x2 Second input value
   *  \param xmax Greater value
   *  \param xmin Smaller value
   */
  template <class T>
    void sort_values(const T& x1, const T& x2, T& xmin, T& xmax)
    {
      T buffer;

      if (x2 < x1)
      {
        buffer = x1;
        xmin = x2;
        xmax = buffer;
      }
      else
      {
        xmin = x1;
        xmax = x2;
      }
    }

  //! Sort two values in ascending order 
  template <class T>
    void sort_values(T& x1, T& x2)
    {
      T buffer;

      if (x2 < x1)
      {
        buffer = x1;
        x1 = x2;
        x2 = buffer;
      }
    }

  /*! Limit a value to fit into a specified interval.
   *  This template is agnostic with respect to the
   *  order of the bounds. It does require the
   *  greater/less than operators to be defined for
   *  the data type 'T'.
   *
   *  \param x Input value
   *  \param x1 First interval boundary
   *  \param x2 Second interval boundary  
   */
  template <class T>
    inline T value_limits(const T& val, const T& bound1, const T& bound2)
    {
      T val_min, val_max;

      val_min = std::min(bound1, bound2);
      val_max = std::max(bound1, bound2);

      return (val > val_max) ? val_max :
             (val < val_min) ? val_min :
             val;
    }

} // namespace PlotMM
