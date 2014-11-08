CS 559 - Train Project
Andrew McOlash
cs login: mcolash

-------------------------------------------------------------------------------

1) Implemented Features

In this project I implemented the following features (in no specific order):

- Generation of curves using catmull rom splines as well as linear interpolation

- Moving train around a track, rotating around the y-axis (had problems with
  gimball-lock so did not implement in all orientations)

- Rotation of wheels implemented, works relatively well but breaks on
  sharp turns

- Train view projection to see the world through the "eyes of the train"

- Arc length parameterization of the track and movement of train (if enabled)

- Track generation of either a linear loop or with rail ties. The rails ties
  are rotated in the correct orientations and can have stilts added as well
  if desired

- Random generation of terrain - both random shape and colors

- Random population of trees in the world. Each tree is placed so that is does
  not touch any other tree or point along the track.

- Adjustment sliders and settings to change many of the values and parameters
  of the train world

-------------------------------------------------------------------------------

2) Curves created

In this project I worked on implementing two different curve types: linear and
cardinal cubic splines. These implementations are relatively straightforward with
the math. In order to implement these curves in my program, I made a custom
function genPoint(i, t) which would take in the current control point (i) and
then based off the given control point and its' neightbors. This function works
for both arc length parameterized coordinates as well those which are not.

In addition to making curves, I also generate direction vectors for the train
as it moves around the track as well as to help with the directions of the track
rail ties.

-------------------------------------------------------------------------------

3) Technical Details

In addition to the discussion of how I generated the points along the curve as
explained in the above section, I will also discuss about the terrain generation
and tree generation as I really enjoyed doing these sections of my implementation.

For the terrain generation, I generate a grid of points at evenly spaced x and z
intervals with varying random y heights. This algorithm also uses rnadomness
to choose random colors for the different sections of the grid, making an
interesting looking terrain that can be seeded. The terrain is a combination of
many triangle strips.

The tree generation section of my code uses randomness to determine the locations
of the trees, as well as the colors of their tops as well as their sizes. By using
this randomness, the trees seem a bit more naturally placed. The interesting thing
about this implementation is that my trees are only placed if they are far enough
from other trees and train tracks. This ensures that there is not overlap.

To implement my system, I keep copies of the previously generated trees, terrain
and tracks that will only be updated if certain sections of the system say that
they are "dirty" - thus eliminating a lot of the need for excessive calculations
of where to place objects.

-------------------------------------------------------------------------------

4) Other Changes

No real major changes were made to the starting code. I kept most of my functions
inside of the TrainView.cpp file as I am not too familiar with OOP and c++.

For the random terrain generation, I toggle the checkboard floor or terrain base
on the fltk widget.

-------------------------------------------------------------------------------

5) Additional Comments

Overall I feel that I got a lot of interesting and cool features implemented
and was really happy with my end result for this project. If all goes according
to plan, you should be able to simply build my code as no external libraries
were added as requirements (from the already used code).

I have attached pictures to the submission showing different sections of the code
and cool features that were added.

-------------------------------------------------------------------------------

6) Screenshot information

Screenshot 1

- What the program looks like when opened. This is the default view and settings.
  You can see the rnadom terrain as well as the trees that are made.

Screenshot 2

- This screenshot shows the track that is generated as well as the stilts and the
  train view projection.


Screenshot 3

- A better look at the geometry of the terrain.


Screenshot 4

- A top view of the world, you can see the trees as well as the terrain well in
  this shot.


Screenshot 5

- A closer look at some of the tracks at sharp turns. Also, the terrain shown
  shows the jagged edge at the edge of the map.
