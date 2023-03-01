# Procedural-Terrain-Generator
OpenGL project for course Computer Graphics

<img src="./part1/media/scene1.png">
<img src="./part1/media/scene2.png">
<img src="./part1/media/mesh.png">

YouTube Link: https://www.youtube.com/watch?v=lYt6dlfu3L8

This program can randomly generate height value and normal vector for each vertex of a mesh to produce a mountain topography. To simulate terrains in real world, the color of each vertex of the terrain was generated based on the height value. A fog effect was also implemented to enhance the sense of reality. 

The algorithm I chose for generating the height map is like the algorithm used for image filters. Firstly the program will generate a random height value for each point. Then a kernel will be applied to each point to smooth this extremely random terrain to a realistic terrain.

The noise function always gives the same output value for certain inputs. Every time we run the application the seed will change so we can generate the terrain randomly but once the application running, it will never change.

Then the algorithm will use cosine interpolation to calculate height values between every two points.

To make the terrain more realistic the algorithm will generate multiple noise effects and add them together to be the final output. Octivas is the number of noise effects used in the algorithm. More plateaus and flat surfaces will be generated if we increase this number. 

This is the class used for generating normal vector for each vertex. The key concept of this algorithm is to calculate the normal of one vertex according to the height values of all its neighbor vertices.

To make the landscape more realistic, I also made a color generator to assign different colors to vertexes of different height level. I also implemented a fog effect by mixing the terrain color with the sky color in the fragment shader according to the distance between the scene and the camera.
