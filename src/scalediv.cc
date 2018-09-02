/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * PlotMM Widget Library
 * Copyright (C) 2004   Andy Thaller
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 *****************************************************************************/
/* ported from qwt */

#include <cmath>
#include <cstdlib>

#include "scalediv.h"
#include "supplemental.h"

namespace PlotMM {

  static const double step_eps = 1.0e-3;
  static const double border_eps = 1.0e-10;

  static bool range_limits(double &val, double v1, double v2,
      double eps_rel = 0.0, double eps_abs = 0.0)
  {
    bool rv = true;
    double vmin = std::min(v1, v2);
    double vmax = std::max(v1, v2);
    double delta_min = std::max(std::abs(eps_rel * vmin), std::abs(eps_abs));
    double delta_max = std::max(std::abs(eps_rel * vmax), std::abs(eps_abs));

    if (val < vmin)
    {
      if (val < vmin - delta_min)
        rv = false;

      val = vmin;
    }
    else if (val > vmax)
    {
      if (val > vmax + delta_max)
        rv = false;

      val = vmax;
    }
    return rv;
  }


  //! Construct a ScaleDiv instance.
  ScaleDiv::ScaleDiv() :
    d_lBound(0.0),
    d_hBound(0.0),
    d_majStep(0.0),
    d_log(false)
  {
  }

  /*!
    \brief Build a scale width major and minor divisions
    If no fixed step width is specified or if it is set to 0, the
    major step width will be calculated automatically according to the
    the value of maxMajSteps. The maxMajSteps parameter has no effect
    if a fixed step size is specified. The minor step width is always
    calculated automatically.

    If the step width is to be calculated automatically, the algorithm
    tries to find reasonable values fitting into the scheme {1,2,5}*10^n
    with an integer number n for linear scales.

    For logarithmic scales, there are three different cases
    <ol>
    <li>If the major step width is one decade, the minor marks
    will fit into one of the schemes {1,2,...9}, {2,4,6,8}, {2,5} or {5},
    depending on the maxMinSteps parameter.
    <li>If the major step size spans
    more than one decade, the minor step size will be {1,2,5}*10^n decades
    with a natural number n.
    <li>If the whole range is less than one decade, a linear scale
    division will be built.
    </ol>

    \param x1 first boundary value
    \param x2 second boundary value
    \param maxMajSteps max. number of major step intervals
    \param maxMinSteps max. number of minor step intervals
    \param log logarithmic division (true/false)
    \param step  fixed major step width. Defaults to 0.0.
    \param ascend if true, sort in ascending order from min(x1, x2)
    to max(x1, x2). If false, sort in the direction
    from x1 to x2. Defaults to true.
    \return True if the arrays have been allocated successfully.
    \warning For logarithmic scales, the step width is measured in decades.
    */
  bool ScaleDiv::rebuild(double x1, double x2,
      int maxMajSteps, int maxMinSteps, bool log, double step, bool ascend)
  {
    int rv;

    d_lBound = std::min(x1, x2);
    d_hBound = std::max(x1, x2);
    d_log = log;

    if (d_log)
      rv = build_log_div_(maxMajSteps,maxMinSteps,step);
    else
      rv = build_lin_div_(maxMajSteps, maxMinSteps, step);

    if ((!ascend) && (x2 < x1))
    {
      d_lBound = x1;
      d_hBound = x2;
      twist_array(majMarks_);
      twist_array(minMarks_);
    }

    return rv;
  }

  /*!
    \brief Build a linear scale division in ascending order

    If the 'step' parameter is set to 0.0, this function
    cal[culates the step width automatically according to
    the value of 'maxSteps'. MaxSteps must be greater than or
    equal to 2. It will be guessed if an invalid value is specified.

    The maximum possible number of steps is   limited to 10000.
    The maxSteps parameter has no effect if a fixed step width is
    specified.

    \param maxSteps max. number of step intervals
    \param step -- fixed step width
    \return true if array has been successfully resized
    \warning This function uses the data members d_lBound and d_hBound
    and assumes that d_hBound > d_lBound.
    */
  bool ScaleDiv::build_lin_div_(int maxMajSteps, int maxMinSteps, double step)
  {
    int nMaj, nMin, minSize, i0,i,k;
    double val, mval;
    double firstTick, lastTick;
    double minStep;

    // parameter range check
    maxMajSteps = std::max(1, maxMajSteps);
    maxMinSteps = std::max(0, maxMinSteps);
    step = std::abs(step);

    // detach arrays
    if (d_lBound == d_hBound) {
      majMarks_.clear();
      minMarks_.clear();
      return true;
    }
    //
    // Set up major divisions
    //
    if (step == 0.0)
      d_majStep = ceil_125(std::abs(d_hBound - d_lBound) * 0.999999
          / static_cast<double>(maxMajSteps));
    else
      d_majStep = step;

    if (d_majStep == 0.0)
      return true;

    firstTick = ceil( (d_lBound - step_eps * d_majStep) / d_majStep) * d_majStep;
    lastTick = floor( (d_hBound + step_eps * d_majStep) / d_majStep) * d_majStep;

    nMaj = std::min(10000, static_cast<int>(floor ((lastTick - firstTick) / d_majStep + 0.5)) + 1);

    lin_space(majMarks_, nMaj, firstTick, lastTick);

    //
    // Set up minor divisions
    //
    if (maxMinSteps < 1) // no minor divs
      return true;

    minStep = ceil_125( d_majStep  /  static_cast<double>(maxMinSteps) );

    if (minStep == 0.0)
      return true;

    nMin = std::abs(static_cast<int>(floor(d_majStep / minStep + 0.5))) - 1; // # minor steps per interval

    // Do the minor steps fit into the interval?
    if ( std::abs(static_cast<double>(nMin +  1) * minStep - d_majStep)
        >  step_eps * d_majStep)
    {
      nMin = 1;
      minStep = d_majStep * 0.5;
    }

    // Are there minor ticks below the first major tick?
    if (majMarks_[0] > d_lBound )
      i0 = -1;
    else
      i0 = 0;

    double buffer[nMin * (nMaj + 1)];
    // resize buffer to the maximum possible number of minor ticks

    // calculate minor ticks
    minSize = 0;
    for (i = i0; i < static_cast<int>(majMarks_.size()); i++)
    {
      if (i >= 0)
        val = majMarks_[i];
      else
        val = majMarks_[0] - d_majStep;

      for (k=0; k< nMin; k++)
      {
        mval = (val += minStep);
        if (range_limits(mval, d_lBound, d_hBound, border_eps))
        {
          buffer[minSize] = mval;
          minSize++;
        }
      }
    }
    vector_from_c(minMarks_, buffer, minSize);

    return true;
  }

  /*!
    \brief Build a logarithmic scale division
    \return True if memory has been successfully allocated
    \warning This function uses the data members d_lBound and d_hBound
    and assumes that d_hBound > d_lBound.
    */
  bool ScaleDiv::build_log_div_(int maxMajSteps, int maxMinSteps, double majStep)
  {
    double firstTick, lastTick;
    double lFirst, lLast;
    double val, sval, minStep, minFactor;
    int nMaj, nMin, minSize, i, k, k0, kstep, kmax, i0;
    int rv = true;
    double width;

    std::vector<double> buffer;


    // Parameter range check
    maxMajSteps = std::max(1, std::abs(maxMajSteps));
    maxMinSteps = std::max(0, std::abs(maxMinSteps));
    majStep = std::abs(majStep);

    // boundary check
    range_limits(d_hBound, LogMin, LogMax);
    range_limits(d_lBound, LogMin, LogMax);

    // detach arrays
    majMarks_.clear();
    minMarks_.clear();

    if (d_lBound == d_hBound) return true;

    // scale width in decades
    width = log10(d_hBound) - log10(d_lBound);

    // scale width is less than one decade -> build linear scale
    if (width < 1.0)
    {
      rv = build_lin_div_(maxMajSteps, maxMinSteps, 0.0);
      // convert step width to decades
      if (d_majStep > 0)
        d_majStep = log10(d_majStep);

      return rv;
    }

    //
    //  Set up major scale divisions
    //
    if (majStep == 0.0)
      d_majStep = ceil_125( width * 0.999999 / static_cast<double>(maxMajSteps));
    else
      d_majStep = majStep;

    // major step must be >= 1 decade
    d_majStep = std::max(d_majStep, 1.0);


    lFirst = ceil((log10(d_lBound) - step_eps * d_majStep) / d_majStep) * d_majStep;
    lLast = floor((log10(d_hBound) + step_eps * d_majStep) / d_majStep) * d_majStep;

    firstTick = pow(10.0, lFirst);
    lastTick = pow(10.0, lLast);

    nMaj = std::min(10000, static_cast<int>(floor (std::abs(lLast - lFirst) / d_majStep + 0.5)) + 1);

    log_space(majMarks_, nMaj, firstTick, lastTick);

    //
    // Set up minor scale divisions
    //

    if ((majMarks_.size() < 1) || (maxMinSteps < 1))
      return true; // no minor marks

    if (d_majStep < 1.1)            // major step width is one decade
    {
      if (maxMinSteps >= 8)
      {
        k0 = 2;
        kmax = 9;
        kstep = 1;
        minSize = (majMarks_.size() + 1) * 8;
      }
      else if (maxMinSteps >= 4)
      {
        k0 = 2;
        kmax = 8;
        kstep = 2;
        minSize = (majMarks_.size() + 1) * 4;
      }
      else if (maxMinSteps >= 2)
      {
        k0 = 2;
        kmax = 5;
        kstep = 3;
        minSize = (majMarks_.size() + 1) * 2;
      }
      else
      {
        k0 = 5;
        kmax = 5;
        kstep = 1;
        minSize = (majMarks_.size() + 1);
      }

      // resize buffer to the max. possible number of minor marks
      buffer.clear();

      // Are there minor ticks below the first major tick?
      if ( d_lBound < firstTick )
        i0 = -1;
      else
        i0 = 0;

      minSize = 0;
      for (i = i0; i < static_cast<int>(majMarks_.size()); i++)
      {
        val = (i >= 0) ? majMarks_[i] : majMarks_[0] / pow(10.0, d_majStep);

        for (k = k0; k <= kmax; k+=kstep)
        {
          sval = val * static_cast<double>(k);
          if (range_limits(sval, d_lBound, d_hBound, border_eps))
          {
            buffer.push_back(sval);
            minSize++;
          }
        }
      }
      // copy values into the min_marks array
      minMarks_ = buffer;
    }
    else                // major step > one decade
    {
      // substep width in decades, at least one decade
      minStep = ceil_125( (d_majStep - step_eps * (d_majStep / static_cast<double>(maxMinSteps)))
          /  static_cast<double>(maxMinSteps) );
      minStep = std::max(1.0, minStep);

      // # subticks per interval
      nMin = static_cast<int>(floor (d_majStep / minStep + 0.5)) - 1;

      // Do the minor steps fit into the interval?
      if ( std::abs( static_cast<double>(nMin + 1) * minStep - d_majStep)  >  step_eps * d_majStep)
        nMin = 0;

      if (nMin < 1)
        return true;      // no subticks

      // resize buffer to max. possible number of subticks
      buffer.clear();

      // substep factor = 10^substeps
      minFactor = std::max(pow(10.0, minStep), 10.0);

      // Are there minor ticks below the first major tick?
      i0 = (d_lBound < firstTick ) ? -1 : 0;

      minSize = 0;
      for (i = i0; i < static_cast<int>(majMarks_.size()); i++)
      {
        val = (i >= 0) ? majMarks_[i] : firstTick / pow(10.0, d_majStep);

        for (k = 0; k < nMin; k++)
        {
          sval = (val *= minFactor);
          if (range_limits(sval, d_lBound, d_hBound, border_eps))
          {
            buffer.push_back(sval);
            minSize++;
          }
        }
      }
      minMarks_= buffer;
    }

    return rv;
  }

  /*!
    \brief Equality operator
    \return true if this instance is equal to s
    */
  int ScaleDiv::operator==(const ScaleDiv &s) const
  {
    int rVal =
      (d_lBound == s.d_lBound)   &&
      (d_hBound == s.d_hBound)   &&
      (d_log == s.d_log)         &&
      (d_majStep == s.d_majStep) &&
      (majMarks_ == s.majMarks_) &&
      (minMarks_ == s.minMarks_);
    return rVal;
    // if (d_lBound != s.d_lBound) return 0;
    // if (d_hBound != s.d_hBound) return 0;
    // if (d_log != s.d_log) return 0;
    // if (d_majStep != s.d_majStep) return 0;
    // if (majMarks_ != s.majMarks_) return 0;
    // return (minMarks_ == s.minMarks_);
  }

  /*!
    \brief Inequality
    \return true if this instance is not equal to s
    */
  int ScaleDiv::operator!=(const ScaleDiv &s) const
  {
    return (!(*this == s));
  }

  //! Detach the shared data and set everything to zero.
  void ScaleDiv::reset()
  {
    // detach arrays
    majMarks_.clear();
    minMarks_.clear();

    d_lBound = 0.0;
    d_hBound = 0.0;
    d_majStep = 0.0;
    d_log = false;
  }

} //namespace PlotMM
