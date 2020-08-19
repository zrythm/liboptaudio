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

#ifndef __OPTAUDIO_OPTAUDIO_H__
#define __OPTAUDIO_OPTAUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

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
  float         gain);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __OPTAUDIO_OPTAUDIO_H__ */
