INSTALL & RUN ===========================

In the root folder simply run :

mkdir build
cd build
cmake ..
cmake .
make
./command_line


COMMAND LINE USAGE ======================

Before using an image within the command line, you must load the image through
the "load_image" function.
For example :

> load_image flower.jpg flowers

The first parameter is the image location, the second one is the image name
within the command line.
You can display this image :

> display_image flowers

Then you can compute the regions through the "find_region" function using
the loaded image above :

> find_region flowers 100 100 50 flowers_region

The first parameter is the image input, that must be loaded before.

The two next parameters (100 and 100) are the pixel location, i.e., respectively row and column
indexes.

The fourth parameter (50 here) is the maximum distance (the colour difference) for which
two pixels are considered to belong to the same region. The distance is simply the euclidian distance.
For example let the pixel p0 = (50,50,100), and let the pixel p1 = (60,50,100).
Here ||p0 - p1|| = 10 < 50, so p1 and p0 will belong to the same region if p1 is contiguous
to p0.

The fifth parameter is the result name, i.e., the set of pixels name. This result is simply a 2D
binnary array image that can be displayed by "display_pixels" function :

> display_pixels flowers_region

displays_function can take in parameter only a result from either "find_region" or "find_perimeter".

Let's see now "find_perimeter" function :

> find_perimeter flowers_region flowers_perimeter

The first parameter is the input which must be the find_region output, the second parameter
is the output name that is the same type as find_region output.

You can write results to files :

> save_pixels flowers_region flowers_region.png

In a binnary image here.

Or by running :

> save_pixels_txt flowers_region flowers_region.txt

In a text file.

