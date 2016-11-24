lv2plug
=======

lv2plug is a template-based wrapper for writing [LV2][1] plugins. Se the `monosynth` directory for example usage.

System requirements
-------------------
 * GCC version 5 or later (C++14)
 * The LV2 SDK
 * Maike version 0.10.4 or later
 * PHP

Compiling and installing
------------------------
The project is almost header-only, but has some startup code in static libraries. Also, it features a Maike target hook that needs to be compiled. The project is compiled by running maike from the project root directory.

    $ maike

This will write stuff to the `__targets` directory. The file `targetlv2spec.so` needs to be copied to a location where Maike looks for target hooks. See the [Maike reference][1] for more information about that. The include files in the `__targets` direcory and the static libraries should be copied into the usual places.

Configuring Maike for use with this library
-------------------------------------------
By default, Maike sets the C++ version to at least C++11. If the compiler by default uses a later version, that version is used. This means that for GCC version 5, the version has to be explicitly pushed to C++14. Assuming there is no `maikeconfig.json` in the current directory (you may `cd` to `monosynth`), a suitable configuration file can be done by invoking Maike with appropriate options

    $ maike --configdump=maikeconfig.json --no-sysvars --hooks-config='targetcxx_default:["cxxversion_min":201402]'

You will also need to install the target hook for generating the LV2 manifest, and the plug-in descriptor file.

    $ maike --configdump=maikeconfig.json --no-sysvars --hooks-load='targetlv2spec:.lv2spec'

If you did this in the `monosynth` directory, you should now be able to compile the `monosynth` example.

    $ maike

Test the example with

    $ ./install.sh && jalv.gtk http://example.org/monosynth

[1]: http://lv2plug.in
[2]: https://milasudril.github.io/maike/plugsearchpath.html
