# ComauSmartSix C++ library
This is a C++ library that allows a programmer to control the Comau Smart Six robot manipulator through a C++ program.

## Use
### Server
In order to start using the library, you need to install the programmes under the *server* folder on your Comau Smart Six. You can use Winc4g software to open the PDL files and transfer them to the manipulator.

### Client
In your C++ program, you just need to import *RobotComau.h*, create an object of that class (specifying IP and port of the robot) and start using its methods.

An example of a program using the library is provided (file *main.cpp*).

## Documentation
Unfortunately, there is no official documentation of this library. However, if you go through the code, you will find some useful comments that explain how the library works. Moreover, if you are lucky enough to know Italian, a detailed explanation of the library is available in my thesis [here](http://www.davidevaleriani.it/pub/TesiTriennale.pdf).

## Video
Three videos showing different applications of the library are available on my YouTube channel:

- [Moving the manipulator along a square trajectory](https://www.youtube.com/watch?v=G0NI2mqA2xA)
- [Move a cylinder over a cube](https://www.youtube.com/watch?v=Sc2YGcCQXVM)
- [Robot waiter: serve water with the Comau Smart Six](https://www.youtube.com/watch?v=oyJ-pXyIe_I)

## Disclaimer
The library is protected by the MIT Licence: you can use it and share it "as is" at your own risk.
If you are using this code, please cite my thesis (that one day I'll have the time to translate in English).
> Valeriani, D. (2010). *Development of a software library for programming the Comau Smart Six robot manipulator* (Unpublished undergraduate dissertation). University of Parma, Parma.
