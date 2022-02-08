This is a collection of small programs used in a novel image processing algorith.
Each folder represents a different stage in the algorithm.
CMakeLists.txt are also provided for building the programs with cmake and make.
All stages use the OpenCV library and were originally run on a Raspberry Pi 3.
The folder nubmbers represent subsequent steps in the process.
Those in folders numbered 4a-f are experimental. The project as a whole is to
be considered as experimental and relatively old.

In order to be used the openCV library must already be present on your syste
-- either compiled from source or obtained via your linux distribution's repositories, assuming all other packages are present for C++ programs. Please
see OpenCV website for an install tutorial and packages required.
Once other prerequisites are met, run "cmake ." followed by "make" and as
long as there are no other errors, the programs can be run.
They wll usually require a source image argument to run. No images are provided
, however this project was based on designing a novel image processing 
algorithm for detecting veins beneath the skin in the presence of a NIR light
source.
Bear in mind this use case as well as the fact that it is very amateurishly 
designed.
