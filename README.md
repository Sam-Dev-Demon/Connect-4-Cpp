# Connect 4 Version 2
I wrote the code again from scratch, but with more knowledge. I made a simple AI bot to play Connect 4 in AI mode. I've made several changes to the UI and color palette of the game. Most importantly, it took me damn lot of effort. I guess I'll go for bigger projects now. Comparing with my previous version, I think I've done a good job. Still, this code is a mess ngl. 

## Dependencies
So, you'll need SFML version 3.1.0 to run this project. About C++ compiler, refer to SFML official website. You may also need to modify CMakeLists.txt according to your needs but be sure you know what you're upto, cause I'm not too sure about that. The workspace file you'll see will help you only if you're a notepad++ user. You can literally compile it on cmd with two simple cmake commands given you've sorted all the dependencies.

###### For generating build files :
cmake -S. -B build -G "MinGW Makefiles"

###### For building project exe :
cmake --build build --parallel

#### Link to SFML : https://www.sfml-dev.org/download/sfml/3.1.0/
