Andrew McOlash and Jason Bernstein

Project Theme: Future City

Project Description: In this project, we added new and interesting buildings as well
as making hover cars and some cool graphical additions and new objects for the
graphics town world. These include surfaces of revolution, particle systems, sun
and moon, multiple shaders which added physical characteristics (physics) to
verticies, cool shaders for coloring/lighting, a skybox and interesting behaviors.
------------------------------------------------------------------------------

Requirements:

1) Moving objects: UFO, birds, Sun / Moon, flag
2) Behaviors: UFO, birds, Sun / Moon
3) Buildings: Each made 2-3 buildings plus other objects for world
4) Textures: New textures and used some from other sources listed
5) TC - listed below
6) Shaders: Got all types completed
7) Frame Rate: Good
8) Effected by time of day: UFO, only drawn at night
9) Curved surfaces texure mapping and skybox
10) Did plenty making buildings and other objects for world

------------------------------------------------------------------------------

Technical Challenges:

Andrew
- Particle System
  Generates a vector of points, updates points, move points based on particle
  velocities. Will die after a random amount of time and reset to the start
  position.
  Seen in the foutain.

- Curved Surfaces (Surface of Revolution)
  Rotate and repeat coordinates around the y-axis. Texture the surface in equally
  spaced segments (didn't get enough time to do it based on lengths correctly).
  Seen in many of the building and objects in our world.

- Billboard Shader
  Simple hack which removes the rotations from the ModelView matrix and resets
  it to the identity matrix.
  Seen in moon and sun.


Jason
- Skybox
  Skybox for the world environment. Texture quads with images of a world while
  also disabling the depth buffer to give a good sense of far off surroundings.
  Seen in the world (pretty much everywhere).

- Physics based motions
  Use a vertex shader to transform the vertices in the z direction based on
  cosine based wave motions.
  Seen in the flags.

- Worked on advanced lighting
  Used GL blending functions as well as additional lights to create a more
  realistic looking environment and make things look nicer.
  Seen in cars, streetlights, UFO, particles

------------------------------------------------------------------------------

Pride:

UFO hides at night, pretty nifty. Had fun making our buildings. Particles are
nifty too. Birds flocking all over the place makes for sweet scenery.

------------------------------------------------------------------------------

Attribution:

Andrew:

Code:
Moon Shader Tutorial code samples: http://www.raywenderlich.com/70208/opengl-es-pixel-shaders-tutorial
Billboard Shader Code: http://www.geeks3d.com/20140807/billboarding-vertex-shader-glsl/

Textures:
Hexagon Floor Texture: https://www.filterforge.com/filters/1326.jpg
Skyscraper (hexagon) Windows: http://www.patternpictures.com/wp-content/uploads/2014/05/PP28240908-Empty-repeating-windows-of-a-large-office-building.jpg
Egg Window Texture: http://thumbs.dreamstime.com/x/seamless-black-white-glass-tiles-texture-15207309.jpg



Jason:

Textures:
Picnic table: http://www.texturex.com/Wood-Textures/wood+grain+texture+table+surface+brown+stock+photo+design.jpg.php
SKYSCPR: http://www.cgtextures.com/thumbnails/textures/Buildings/HighRise/Glass/HighRiseGlass0055_2_preview.jpg
BIG_HUT: http://www.windowsofnewyork.com/windows/186-sullivan.png
Skybox: https://www.opengl.org/discussion_boards/showthread.php/144431-Skybox-with-seams

------------------------------------------------------------------------------

Overall changes we did:


Both
--------------------

Shaders and flying cars


Andrew
--------------------

Fully Created Objects:
X Buildings
  X Cool one, egg, skyscraper
X Fountain
X UFO

Shaders:
X Pond Color Responds to time of day, also UFO
X Simple global lighting shader
X Billboard shader
X Sun Shader - time based with fancy math
X Procedural Texture - Moon, blurred noise (like clouds)

Behaviors:
X UFO Movement
X Sun / Moon Movement

Textures:
X Lane markers + Intersections - Made Myself
X Brushed Metal and UFO bottom textures - Made Myself
X Textures wrapped onto surfaces

Technical Challenges:
X Particles
X Curved Surfaces (Surfaces of Revolution)
X Billboard (Sum/Moon)

X Modified ligthing to only use ambient at night (more realistic)
------------------------------------------------------------------------------

Jason
--------------------

Fully Created Objects:
X Birds
X Skybox
X Flag
X Buildings
  X "Big Hut", SkyScpr Cyllinder one

Shaders:
X Procedural Texture - Flag
X Physics based flag
X Bird Shader for Lighting

Behaviors:
X Creation of birds
X Movement of birds

Textures:
X Skybox Texture
X Window Colors

Technical Challenges:
X Physics (Flag)
X Skybox
X Surfaces of Revolution
