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

#include <stdio.h>

#include "optaudio/optaudio.h"
#include "simd_funcs.h"

/**
 * Optimized routine for mixing buffer with gain.
 *
 * This function may choose SSE over AVX if the pointers are
 * aligned to 16 byte boundary instead of 32 byte boundary to
 * reduce time to process.
 *
 * @param[in,out] dst Pointer to destination buffer, which
 *   gets updated.
 * @param[in] src Pointer to source buffer (not updated).
 * @param nframes Number of samples to process.
 * @param gain Gain to apply.
 */
void
optaudio_mix_buffers_with_gain (
  float *       dest,
  const float * src,
  unsigned int  nframes,
  float         gain)
{
#ifdef HAVE_AVX
  mix_buffers_with_gain_avx (dest, src, nframes, gain);
#elif defined (HAVE_SSE)
  mix_buffers_with_gain_sse (dest, src, nframes, gain);
#else
  mix_buffers_with_gain_fallback (dest, src, nframes, gain);
#endif
}
