project('plotmm30', ['cpp', 'c'],
  version: '0.1.0',
  license: 'lgpl2',
  meson_version: '>= 0.46.0',
)

i18n = import('i18n')

#glib_dep = dependency('glib-2.0')
prefix = get_option('prefix')
demo_lib = join_paths(prefix, get_option('libdir'))

plotmm_deps = [
  dependency('glib-2.0', version: '>= 2.40'),
  dependency('glibmm-2.4', required: true, version: '>= 2.56'),
  dependency('gdkmm-3.0', required: true, version: '>= 3.22'),
  dependency('gtkmm-3.0', required: true, version: '>= 3.20'),
  dependency('sigc++-2.0', required: true, version: '>= 2.10'),
  dependency('pangomm-1.4', required: true, version: '>= 2.40')
]

subdir('include')
subdir('src')

# Build the libraries (shared and static)
plotmm30_lib = both_libraries(
                   'plotmm30', plotmm_sources,
                   dependencies: plotmm_deps,
                   include_directories: plotmm_incdir,
                   install: true
                 )

# Generate the pkgconfig file 'plotmm30.pc'
pkg_mod.generate(
    libraries : plotmm30_lib,
    subdirs: headers,
    requires: plotmm_deps,
    version : '1.0',
    name : 'libplotmm30',
    filebase : 'plotmm30',
    description: 'A 2D graph plotting library for gtkmm30'
)

doxygen = find_program('doxygen', required : false)
#if not doxygen.found()
#  error('MESON_SKIP_TEST doxygen not found.')
#endif

# Build the demo applications (if build_demos = true, see meson_options.txt)
if get_option ('build_demos')
  subdir('demo')
endif

# Build the documentatin (if docs = true, see meson_options.txt)
if get_option ('docs')
  subdir('doc')
endif

meson.add_install_script('build-aux/meson/postinstall.py')
