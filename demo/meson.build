demo_sources = [
  'main.cc'
]

gnome = import('gnome')

#plotmm_sources += gnome.compile_resources('plotmm30-resources',
#  'plotmm.gresource.xml',
#  include_directories: plotmm_incdir,
#  c_name: 'plotmm'
#)

#demo_sources += plotmm_sources

executable(
    'plotmm', demo_sources,
    dependencies: plotmm_deps,
    include_directories: plotmm_incdir,
    link_with: plotmm30_lib,
    build_rpath: demo_lib,
    install: true,
)                 

