# Copyright (C) 2019-2020 Alexandros Theodotou <alex at zrythm dot org>
#
# This file is part of liboptaudio
#
# liboptaudio is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# liboptaudio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with liboptaudio.  If not, see <https://www.gnu.org/licenses/>.

if get_option ('tests')
  e = executable (
    'test_exe', 'test.c',
    include_directories: inc,
    link_with: optaudio,
    c_args: optaudio_cflags,
    )
  test ('fallback', e, args: ['fallback'])
  test ('avx', e, args: ['avx'])
  test ('sse', e, args: ['sse'])
endif
