# Baseline Game Engine

## Introduction
Baseline will hopefully become a primitive game engine developed on my free time. I have zero experience with game 
engines. Seeing as how I have spent fat to many hours playing games, I figured I would try my hand at creating one. 
The first logical place to start, in my mind at least, is the graphics API. For this particular engine, the focus will 
be the [SFML API](https://www.sfml-dev.org/index.php).

## Getting Started
### Installing Dependencies (Ubuntu)
```
sudo apt-get install libsfml-dev
```

### Compiling from Source
```
mkdir debug
cd debug
cmake ..
make
```

You should now have an executable called `baseline` in your debug folder. This will startup the engine with some default 
behaviours. As development progresses, baseline will eventually be an API designed to be imported by other projects.


## Resources
Bellow is a list of resources I stumbled across while working on this project. They may prove useful for other who wish 
to use this codebase.
- https://www.sfml-dev.org/tutorials/2.5/