project('plotmm30', ['cpp', 'c'],
  version: '0.1.0',
  license: 'lgpl2',
  meson_version: '>= 0.40.0',
)

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


#doc_lib = library('plotmm', plotmm_sources, include_directories: plotmm_incdir)

plotmm30_lib = both_libraries(
                   'plotmm30', plotmm_sources,
                   dependencies: plotmm_deps,
                   include_directories: plotmm_incdir,
                   install: true
                 )

pkg_mod.generate(
    libraries : plotmm30_lib,
    subdirs: headers,
    requires: plotmm_deps,
    version : '1.0',
    name : 'libplotmm30',
    filebase : 'plotmm30',
    description: 'A 2D graph plotting library for gtkmm30'
)
subdir('demo')                 
                 
doxygen = find_program('doxygen', required : false)
#if not doxygen.found()
#  error('MESON_SKIP_TEST doxygen not found.')
#endif

cdata = configuration_data()
cdata.set('VERSION', meson.project_version())

if find_program('dot', required : false).found()
  # In the real world this would set the variable
  # to YES. However we set it to NO so that the
  # list of generated files is always the same
  # so tests always pass.
  cdata.set('HAVE_DOT', 'YES')
else
  cdata.set('HAVE_DOT', 'NO')
endif

#subdir('doc')