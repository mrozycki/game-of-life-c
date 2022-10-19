Game of Life
============

Game of Life animation generator written in C, as a teaching resource.

Compiling
---------

The project uses CMake, so you will have to have it installed, as well as
some C compiler (e.g. gcc, clang or msvc). 

If you use a C/C++ IDE, you might be able to import the directory as a CMake
project, which should allow you to handle building and running the project
through the tools provided by the IDE.

If you would rather do it through command line, you'll need to:

1. Create a build folder, where the generated files and binaries will be stored:

    ```
    mkdir -p build/debug
    ```

2. Move to the build folder and initialize the CMake target:

    ```
    cd build/debug
    cmake ../.. -DCMAKE_BUILD_TYPE=Debug
    cd -
    ```

3. Now you can build the project using:

    ```
    cmake --build build/debug
    ```

Steps 1 and 2 need to be done once for every target. The example above will
create a debug target, which will produce an unoptimized binary with debug
symbols, making it easy to run it in a debugger. If you would like to produce
a release target (optimized, with debug symbols stripped), do the same,
but replace `debug`/`Debug` with `release`/`Release`.

Step 3 needs to be repeated every time you make changes to the code.

Running
-------

Before running the program you will have to create a directory for the output 
frames. At this point this directory name is hard coded into the program, so it 
needs to be called `out`, and it needs to be located in your working directory.

```
mkdir out
```

After that you can run the program from the build directory, providing the path
to the gol file you want to generate your animation from:

```
build/debug/gol max.gol
```

After that the frames of the animation will be places in the out folder.

Putting the frames together
---------------------------

The program generates individual frames, which now have to be merged into an
animation. If you would like to create a GIF, you can use `convert`, which
requires you to have imagemagick installed:

```
convert out/* out.gif
```

For larger animations GIF might not be the right format, so you can instead
generate an MP4 file with ffmpeg:

```
ffmpeg -i out/%03d.pbm -f mp4 -pix_fmt yuv420p -c:v libx264 out.mp4
```
