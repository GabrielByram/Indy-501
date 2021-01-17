This was a group project between me and 3 other students in CPT_S 122 at WSU in April and May, 2020. We modeled our gameplay after the classic Atari racing game, Indy 500. This is our spiritual sequel to it, in a sense. We utilized SFML graphics.

Note: The gameplay in the video demo appears choppy because of recording issues. The actual gameplay is smooth.

Students:
Aayush Bajoria, Lab Section 14
Gabriel Byram, Lab Section 5
Steven Subianto, Lab Section 3
Oliver Rogers, Lab Section 14

Instructions for running this game:

(After downloading SFML)

Make sure you are in debug properties.

SFML Setup:
Under Project Properties - Linker - Input - Additional Dependicies; add the following
winmm.lib
opengl32.lib
openal32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
freetype.lib
sfml-graphics-s-d.lib
sfml-window-s-d.lib
sfml-system-s-d.lib
sfml-audio-s-d.lib
sfml-network-s-d.lib
ws2_32.lib

Under Project Properties - Linker - General - Additional Library Directories;
Make sure to include the SFML-2.5.1\lib folder included

Under Project Properties - C/C++ - General - Additional Include Directories;
Make sure to include the SFML-2.5.1\include folder included

Under Priject Properties - C/C++ - Preprocessor - Preprocessor Definitions;
Add SFML_STATIC
