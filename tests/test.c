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

#include "helper.h"

#include <time.h>
#include <optaudio/optaudio.h>

#include "simd_funcs.h"

#define NUM_FRAMES 128

/** 10ms. */
#define TRIGGER_USEC 10000

/**
 * @return Number of iterations.
 */
static long
mix_buffers_with_gain_timed (
  void (* func_ptr) (float *, const float *, unsigned int, float))
{
  float out[NUM_FRAMES];
  float in[NUM_FRAMES];
  for (int i = 0; i < NUM_FRAMES; i++)
    {
      in[i] = 0.3f;
    }

  long iterations = 0, usec = 0, trigger = TRIGGER_USEC;
  clock_t before = clock();
  do {
    func_ptr (out, in, NUM_FRAMES, 2.f);

    clock_t difference = clock() - before;
    usec = difference * 1000000 / CLOCKS_PER_SEC;
    iterations++;
  } while ( usec < trigger );

  printf (
    "Time taken %ld seconds %ld milliseconds %ld microseconds "
    "(%ld iterations)\n",
    usec/1000000, usec%1000000, usec % 1000, iterations);

  return iterations;
}

int main (
  int argc, const char* argv[])
{
  if (strcmp (argv[0], "fallback"))
    {
      printf ("fallback\n");
      /*long fallback =*/
        mix_buffers_with_gain_timed (
          mix_buffers_with_gain_fallback);
    }
#ifdef HAVE_AVX
  else if (strcmp (argv[0], "avx"))
    {
      printf ("avx\n");
      /*long avx =*/
        mix_buffers_with_gain_timed (
          mix_buffers_with_gain_avx);
      /*oa_assert (avx > fallback);*/
    }
#endif
#ifdef HAVE_SSE
  else if (strcmp (argv[0], "sse"))
    {
      printf ("sse\n");
      /*long sse =*/
        mix_buffers_with_gain_timed (
          mix_buffers_with_gain_sse);
      /*oa_assert (sse > fallback);*/
    }
#endif

  /*oa_assert_cmpfloat_with_epsilon (out[0], 0.6f, 0.0001f);*/

  return 0;
}
