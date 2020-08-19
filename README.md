liboptaudio
===========

[![builds.sr.ht status](https://builds.sr.ht/~alextee/zrythm.svg)](https://builds.sr.ht/~alextee/liboptaudio?)

liboptaudio (lib optimized audio) is a library for
optimized audio subroutines, such as applying gain
on a float buffer and mixing float buffers.

Until version 1.0 is released, the API is subject
to change.

# Usage

Use `#include <optaudio/optaudio.h>` in your C/C++
project and add a dependency to the library using
the pkg-config name `optaudio`.

See the header file for more info.

# Building

To build only:

    meson build
    ninja -C build

Installation:

    ninja -C build install

# Patches/Issues
Open an issue in
https://redmine.zrythm.org/projects/zrythm/issues

# License
liboptaudio is released under the GNU Affero GPLv3+.
See the file COPYING for more details. Some files,
where specified, are licensed under different
licenses.

----
Copyright (C) 2020 Alexandros Theodotou

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.  This file is offered as-is,
without any warranty.
