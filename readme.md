This project is offically archived. The reason for that is because the goals are too loose
and too vauge, and if i ever want to figure out what I want to do with this project then I will unarchive it.

This project is currently being remade from the ground up, becuase of that many features are missing.
This is a super ambitious project.

If you have any questions or anything of that sort, please email: sawyerp06@gmail.com

HOW TO COMPILE: Scroll down to see how compile and run PMUT

Warning for any one compiling this project: this project uses libraries that are not inside
of pmut, for information on how to install these libraries. please scroll down.

Warning for non-linux users: this uses the the X Window System linker flags, you may have to switch out some of the CMAKE_CXX_FLAGS(the linker options to be specific) for something that can compile on your system. 

What PMUT(Porter Multi Use Terminal) is or will be.
PMUT as the acronym infers is meant to have multiple uses,
the following are set in stone goals:

- PMUT Networking: simple(basic chatboxes) and advance(fullblown multiplier) networking. when I say fullblown multiplayer I mean
letting apps interact with PMUT, to avoid doing networking at all. There are of course security problems with that but I have a few("stolen")
ideas that can improve security.

- PMUT File manipulation: edit files, move, remove, and making files. I will also(and any contributors) include directory manipulation to.

- PMUT Live app manipulation: think of this like cheat engine but you can also export an instance of an app from RAM into a file.

- PMUT's Custom console: this console will be using opengl(glfw and glew) to render it

-- how to compile PMUT --
please note that when building use ninja - https://ilyas-hamadouche.medium.com/build-your-c-projects-faster-using-ninja-3d7af9b418fc

run ./gen_build_run.sh

-- the ubuntu or debian way ---

How to install GLFW ====:

make a folder which will hold
a temporary build of GLFW.

then type in the terminal(while in the dir):

$ git clone https://github.com/glfw/glfw.git

$ cmake . -G Ninja

$ ninja

$ sudo ninja install

then your done!

How to install GLEW ====:

go http://glew.sourceforge.net/ click the link named TGZ then choose where to
install the tarball, put it in a temporary build folder that will hold glew

WARNING: Do not install the github source, some files are usally missing or
not setup correctly.

then type in the terminal(while in the dir):

$ make 

$ sudo make install

then your done!

How to install freetype ====:

$ sudo apt-get install freetype*

How to install glm ====:

$ sudo apt-get install libglm-dev
