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

#ifndef __OPTAUDIO_SIMD_FUNCS_H__
#define __OPTAUDIO_SIMD_FUNCS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "optaudio-config.h"

void
mix_buffers_with_gain_fallback (
  float *       dest,
  const float * src,
  unsigned int  nframes,
  float         gain);

#ifdef HAVE_AVX
void mix_buffers_with_gain_avx (
  float *       dest,
  const float * src,
  unsigned int  nframes,
  float         gain);
#endif

#ifdef HAVE_SSE
void mix_buffers_with_gain_sse (
  float *       dest,
  const float * src,
  unsigned int  nframes,
  float         gain);
#endif

#ifdef HAVE_SSE2
#endif

#ifdef HAVE_SSE3
#endif

#ifdef HAVE_SSSE3
#endif

#ifdef HAVE_SSE41
#endif

#ifdef HAVE_SSE42
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __OPTAUDIO_SIMD_FUNCS_H__ */
