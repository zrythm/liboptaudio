/*
 * Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of liboptaudio
 *
 * liboptaudio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liboptaudio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with liboptaudio.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "optaudio/optaudio.h"

void
mix_buffers_with_gain_fallback (
  float *      dest,
  float *      src,
  unsigned int nframes,
  float        gain)
{
  for (unsigned int i = 0; i < nframes; i++)
    {
      dest[i] += src[i] * gain;
    }
  return;
}
