cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())

doxyfile = configure_file(input: 'Doxyfile.in',
                          output: 'Doxyfile',
                          configuration: cdata,
                          install: false)

datadir = join_paths(get_option('datadir'), 'doc', 'sceneGraph')

html_target = custom_target('marina-tool-kit-docs',
                            input: doxyfile,
                            output: 'html',
                            command: [doxygen, doxyfile],
                            install: true,
                            install_dir: datadir)

