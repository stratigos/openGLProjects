### OpenGL projects I made for college classes

Circa 2004, unfortunately developed in Windows, using Microsoft Visual Studio :-/

##### Includes

###### To run the executable

glut32.dll
: place in ~\Windows\System

###### To compile source

glut.h
: place in ~\MicrosoftVisualStudio\VC98\lib

When compiling, go to project -> settings -> link and add the following four library names to object/library modules:
* opengl32.lib
* glaux.lib
* glu32.lib
* glut32.lib

Recently, I was able to download glut32.dll here: http://user.xmission.com/~nate/glut.html
