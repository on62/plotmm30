# Plotmm30
Update of Mod-PlotMM (Plotmm), a gtkmm plotting library, to gtkmm-3.0

plotmm30 is a port of Mod-Plotmm, and seaks to update to the latest versions Gtkmm 3.2x releases.

The code has been ported to the meson/ninja build system using the Gnome Builder IDE making easy flatpak
distribution straight forward, along with more traditional library builds. This port also builds plotmm30 as
both shared and static libraries with pkg-config 'plotmm30-<version>.pc' output to enable 'easy' integration
with other projects and build systems.

### Note: This version is currently only tested on Fedora linux.

Copyright:
 * Copyright (C) 2018 Tony Jones

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL


Original README

# Mod-PlotMM
Update of Plotmm, a gtkmm plotting library, to gtkmm-3.0

Plotmm is a plotting library for use with Gtk and Gtkmm.  The original code was written by Andy Thaller and can be found at http://plotmm.sourceforge.net/.  The last update of the original code was in 2005 and this useful plotting libary unfortunately no longer compiles with gtkmm-3.0.

In order to make the library compatible with gtkmm-3.0, the code was modified and rewritten.  The majority of the original design and functionality remain, although the code has been edited heavily in some places.

No change to the original software license is intended in this revision and the original copyright notices of Andy Thaller remain in the code.

PlotMM Widget Library
 * Copyright (C) 2004   Andy Thaller
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL


Information regarding the changes made to the original code can be obtained from Jim Charlton, charltn@gmail.com

The package provided is configured for compilation on the Linux (Ubuntu) OS.  I am using version 14.01.1 of Ubuntu. The Makefile has two targets (debug and release).  "debug" will produce a small test program, bin/Debug/myprog, which will test the code in a simple program.  The code that is executed is in main.cc.  The "release" target will generate the library bin/Release/plotmm.so that you can link it to your code as a library.

I have also installed gtkmm/osx on the MAC OS X (version 10.10) and this code also compiles on that system.  Information on compling on MAC OS X can be obtained by writing to me (charltn@gmail.com).
