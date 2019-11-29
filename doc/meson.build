cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())

doxyfile = configure_file(input: 'Doxyfile.in',
                          output: 'Doxyfile',
                          configuration: cdata,
                          install: false)

doxyfile_mcss = configure_file(input: 'Doxyfile-mcss', output: 'Doxyfile-mcss', copy: true, install: false)

doxygen_py = join_paths(meson.source_root(), './doc/m.css/documentation/doxygen.py')

xml_target = custom_target('marina-tool-kit-docs',
                            input: doxyfile_mcss,
                            output: 'doc',
                            command: [doxygen_py, doxyfile_mcss],
                            install: true,
                            install_dir: get_option('datadir'))

