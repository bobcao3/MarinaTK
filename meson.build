project('MarinaTK', 'cpp',
  version : '0.0.0',
  license : 'APACHE',
  cpp_std: 'c17')
add_global_arguments('-W', language : 'cpp')
add_global_arguments('-Wall', language : 'cpp')
add_global_arguments('-Wextra', language : 'cpp')
add_global_arguments('-Werror', language : 'cpp')

glm_dep = dependency('glm')

scenegraph_sources = [
    'src/sceneGraph/sceneGraph.cpp',
    'src/sceneGraph/geometry.cpp'
]
scenegraph = shared_library('MTKSceneGraph', scenegraph_sources, dependencies: glm_dep, install: true)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : scenegraph,
                 version : '0.0',
                 name : 'libmtkscenegraph',
                 filebase : 'mtkscenegraph',
                 description : 'A Scene Graph library for MarinaTK')

