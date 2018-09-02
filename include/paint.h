/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * PlotMM Widget Library
 * Copyright (C) 2004   Andy Thaller
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 *****************************************************************************/
#pragma once

#include <gtkmm/widget.h>
#include <cairomm/context.h>
#include <cairomm/fontoptions.h>
#include <cairo/cairo.h>
#include <gtkmm/window.h>
#include <glibmm/refptr.h>
#include <glibmm/objectbase.h>

#include "compat.h"

namespace PlotMM {

  //! @brief A class to define pens and brushes for painting
  class Paint : public PlotMM::ObjectBase
  {
    public:
      Paint();
      Paint(const Paint &c);
      virtual ~Paint();

      bool operator!=(const Paint &) const;
      bool operator==(const Paint &) const;

      void set_pen_color(const Gdk::Color &);
      void set_brush_color(const Gdk::Color &);

      void set_cr_to_pen(const Cairo::RefPtr<Cairo::Context> &);
      void set_cr_to_brush(const Cairo::RefPtr<Cairo::Context> &);

      bool filled() const { return filled_; }

    private:

      Gdk::Color pColor_, bColor_;
      int size_, sizeB_;
      bool filled_;
  };

} //namespace PlotMM
