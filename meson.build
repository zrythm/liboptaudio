# Copyright (C) 2020 Alexandros Theodotou <alex at zrythm dot org>
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

project (
  'liboptaudio', ['c'],
  version: '0.0.1',
  license: 'AGPLv3+',
  meson_version: '>= 0.47.0',
  default_options: [
    'warning_level=2',
    'buildtype=debug',
    'c_std=gnu11',
    ],
  )

srcs = []
subdir('inc')
subdir('src')

cc = meson.get_compiler ('c')
simd = import('unstable-simd')
prefix = get_option ('prefix')
includedir = join_paths (
  prefix, get_option('includedir'))
libdir = join_paths (prefix, get_option ('libdir'))

cdata = configuration_data ()
cdata.set_quoted (
  'PACKAGE_VERSION',
  '@VCS_TAG@')
cdata.set_quoted (
  'COMPILER',
  meson.get_compiler('c').get_id())
cdata.set_quoted (
  'PREFIX', prefix)
cdata.set_quoted (
  'COMPILER_VERSION',
  meson.get_compiler('c').version())
cdata.set_quoted (
  'CONFIGURE_LIBDIR',
  libdir)

# detect OS
os_darwin = false
os_linux = false
os_freebsd = false
os_windows = false
if host_machine.system() == 'darwin'
  os_darwin = true
elif host_machine.system() == 'linux'
  os_linux = true
elif host_machine.system() == 'freebsd'
  os_freebsd = true
elif host_machine.system() == 'windows'
  os_windows = true
endif

inc = [
  include_directories ('.'),
  include_directories ('inc'),
  ]

# Compiler flags
optaudio_cflags = [
  '-Wall',
  '-Wformat=2',
  '-Wno-missing-field-initializers',
  '-Wno-unused-parameter',
  '-Wno-sequence-point',
  '-Wignored-qualifiers',
  '-Wno-cast-function-type',
  '-Werror=cast-qual',
  '-Werror=clobbered',
  '-Werror=conversion',
  '-Werror=disabled-optimization',
  '-Werror=double-promotion',
  '-Werror=float-equal',
  '-Werror=logical-op',
  '-Werror=pointer-arith',
  '-Werror=sign-conversion',
  '-Werror=overlength-strings',
  '-Werror=stringop-truncation',
  '-Werror=missing-declarations',
  '-Werror=redundant-decls',
  '-Werror=shadow',
  '-Werror=undef',
  '-Werror=unused',
  '-Werror=strict-aliasing',
  '-fstrict-aliasing',
  '-Werror=strict-overflow',
  '-Wstrict-overflow=2',
  '-fstrict-overflow',
  '-Werror=duplicated-branches',
  '-Werror=duplicated-cond',
  '-Werror=null-dereference',
  '-Werror=init-self',
  '-Werror=jump-misses-init',
  '-Werror=missing-prototypes',
  '-Werror=nested-externs',
  '-Werror=write-strings',
  '-Werror=implicit-fallthrough',
  '-Werror=sign-compare',
  '-Werror=discarded-qualifiers',
  '-Werror=float-conversion',
  '-Werror=implicit-function-declaration',
  '-Werror=uninitialized',
  '-Werror=maybe-uninitialized',
  '-Werror=return-type',
  '-Werror=int-conversion',
  '-Werror=format-security',
  '-Werror=incompatible-pointer-types',
  '-Werror=implicit-int',
  '-Werror=multistatement-macros',
  '-Werror=switch',
  '-Werror=overflow',
  '-Werror=array-bounds',
  '-Werror=enum-compare',
  '-Werror=misleading-indentation',
  '-Werror=int-in-bool-context',
  '-Werror=type-limits',
  '-Werror=deprecated-declarations',
  ]
if os_windows
  optaudio_cflags += [
    '-D_WOE32=1',
    ]
endif
# add optimizations for x86_64
if host_machine.cpu() == 'x86_64'
  optaudio_cflags += [
    '-ffast-math',
    # this may break the backtrace
    '-fomit-frame-pointer',
    '-fstrength-reduce',
    '-DPIC',
    '-fdata-sections',
    '-ffunction-sections',
    '-mtune=generic',
    '-msse',
    '-msse2',
    '-mfpmath=sse',
    #'-fvisibility=hidden',
    ]
endif

optaudio_cflags = cc.get_supported_arguments (
  optaudio_cflags)

rval = simd.check (
  'mysimds',
  sse: 'src/sse_functions_64bit.s',
  sse2: 'src/sse_functions_64bit.s',
  sse3: 'src/sse_functions_64bit.s',
  sse41: 'src/sse_functions_64bit.s',
  avx: 'src/sse_functions_avx_linux.c',
  avx2: 'src/sse_functions_avx_linux.c',
  include_directories: [
    include_directories ('inc'),
    ],
  compiler: cc,
  )
simdlibs = rval[0]
cdata.merge_from (rval[1])

optaudio_deps = []

optaudio_deps += [
  ]

# create config.h and add to deps
tmp_h = configure_file (
  output: 'tmp.h',
  configuration: cdata,
  )
config_h_vcs = vcs_tag (
  input: tmp_h,
  output: 'optaudio-config.h',
  )
config_h_dep = declare_dependency (
  sources: config_h_vcs,
  )
optaudio_deps += config_h_dep

optaudio = static_library (
  'optaudio',
  sources: srcs,
  dependencies: [
    optaudio_deps,
    ],
  include_directories: inc,
  link_with: simdlibs,
  install: not meson.is_subproject(),
)

# this is so that it can be used as a meson
# subproject
liboptaudio_dep = declare_dependency (
  include_directories: inc,
  dependencies: optaudio_deps,
  link_with: optaudio)

if not meson.is_subproject()
  pkg_mod = import('pkgconfig')
  pkg_mod.generate(
    libraries: optaudio,
    version: meson.project_version (),
    name: 'optaudio',
    filebase: 'optaudio',
    description: 'Optimized audio operations as subroutines.',
    )
endif

subdir('tests')

summary = [
  '',
  '------',
  'liboptaudio @0@'.format(meson.project_version()),
  '',
  '  Build type: @0@'.format(
    get_option('buildtype')),
  '  Directories:',
  '            prefix: @0@'.format(prefix),
  '        includedir: @0@'.format(includedir),
  '            libdir: @0@'.format(libdir),
  '------',
  ''
]
message('\n'.join(summary))
