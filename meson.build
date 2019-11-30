project('MarinaTK', 'cpp', 'c',
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
cunit_dep = dependency('cunit')
glm_dep = dependency('glm')
thread_dep = dependency('threads')
sdl2_dep = dependency('sdl2')
sdl2_ttf_dep = dependency('SDL2_ttf')

mtk_dep = [glm_dep, thread_dep, sdl2_ttf_dep, sdl2_dep]

# The Library
mtk_sources = [
    'src/sceneGraph/geometry.cpp',
    'src/backend/SDL2/SDL2.cpp',
    'src/backend/SDL2/SDL_FontCache/SDL_FontCache.c',
    'src/ui/layout.cpp',
    'src/components/window.cpp',
    'src/components/container.cpp',
    'src/components/grid.cpp',
]
incdir = include_directories('include')
mtk = shared_library('mtk', mtk_sources, dependencies: mtk_dep, install: true, include_directories : incdir)

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
testGeometry = executable('testGeometry', 'tests/testGeometry.cpp', dependencies: [cunit_dep, glm_dep], include_directories : incdir, link_with : mtk)
test('GeometryTest', testGeometry)

# Demo
demoSDL2Renderer = executable('demoSDL2Renderer', 'tests/demoSDL2Renderer.cpp', dependencies: mtk_dep, include_directories : incdir, link_with : mtk)
demoLayout = executable('demoLayout', 'tests/demoLayout.cpp', dependencies: mtk_dep, include_directories : incdir, link_with : mtk)
demoComponents = executable('demoComponents', 'tests/demoComponents.cpp', dependencies: mtk_dep, include_directories : incdir, link_with : mtk)
demoComponents2 = executable('demoComponents2', 'tests/demoComponents2.cpp', dependencies: mtk_dep, include_directories : incdir, link_with : mtk)
