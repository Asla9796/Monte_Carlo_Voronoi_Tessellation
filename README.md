## Simulation of grain growth using Monte Carlo technique
- Simulation of grain growth using Monte Carlo technique on a microstructure prepared using Voronoi tessellation 
- Monte Carlo technique is for grain growth especially attractive as
  - the statistical behavior of the atoms is properly reproduced
  - microstructural evolution depends only on the real topology of the grains and not on any kind of geometric simplification.
  - Read more on Monte Carlo simulations [here](http://www.scielo.br/scielo.php?script=sci_arttext&pid=S1516-14391999000300004)
- Initial microstructure is prepare using Voronoi tesselation which produces controllable grain sizes and grain boundaries that obeys physical laws (Read more [here](https://onlinelibrary.wiley.com/doi/abs/10.1002/nme.4897))
- Voronoi tessellation is peformed using inbuilt MATLAB functions, in the file 'mat_voronoi_gen.m' which is then imported as an image into C++ and manipulated using OpenCV libraries
- Code written in C++
