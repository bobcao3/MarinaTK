project('MarinaTK', 'cpp',
  version : '0.0.0',
  license : 'APACHE',
  default_options : ['c_std=c11', 'cpp_std=c++17'])
add_global_arguments('-W', language : 'cpp')
add_global_arguments('-Wall', language : 'cpp')
add_global_arguments('-Wextra', language : 'cpp')
# add_global_arguments('-Werror', language : 'cpp')

pkg_mod = import('pkgconfig')
doxygen = find_program('doxygen', required : false)

cdata = configuration_data()
cdata.set('VERSION', meson.project_version())

if find_program('dot', required : false).found()
  cdata.set('HAVE_DOT', 'YES')
else
  cdata.set('HAVE_DOT', 'NO')
endif

# Dependencies
glm_dep = dependency('glm')
cunit_dep = dependency('cunit')
thread_dep = dependency('threads')
sdl2_dep = dependency('SDL2')

# The Library
mtk_sources = [
    'src/sceneGraph/sceneGraph.cpp',
    'src/sceneGraph/sceneNode.cpp',
    'src/sceneGraph/geometry.cpp',
    'src/renderer/SDL2_renderer.cpp',
    'src/ui/layout.cpp'
]
incdir = include_directories('include')
mtk = shared_library('mtk', mtk_sources, dependencies: [glm_dep, thread_dep, sdl2_dep], install: true, include_directories : incdir)

pkg_mod.generate(libraries : mtk,
                 version : '0.0',
                 name : 'libmtk',
                 filebase : 'mtk',
                 description : 'A Scene Graph library for MarinaTK')

# Document
if doxygen.found()
    subdir('doc')
endif

# Test
sceneGraphTest = executable('sceneGraphTest', 'tests/testSceneGraph.cpp', dependencies: [cunit_dep, glm_dep], include_directories : incdir, link_with : mtk)
test('Scene Graph Test', sceneGraphTest)

# Demo
demoSDL2Renderer = executable('demoSDL2Renderer', 'tests/demoSDL2Renderer.cpp', dependencies: [glm_dep, thread_dep, sdl2_dep], include_directories : incdir, link_with : mtk)
demoLayout = executable('demoLayout', 'tests/demoLayout.cpp', dependencies: [glm_dep, thread_dep, sdl2_dep], include_directories : incdir, link_with : mtk)
