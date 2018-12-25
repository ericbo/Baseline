# Baseline Game Engine

## Introduction
Baseline will hopefully become a primitive game engine developed on my freetime. I have zero experience with game engines. Seeing as how I have spent fat to many hours playing games, I figured I would try my hand at creating one. The first logical place to start, in my mind at least, is the graphics API. For this particular engine, the focus will be the [Vulkan API](https://www.khronos.org/vulkan/).

As a naturally curious person, I prefer to experiment with tools before committing to anything. Therefore expect the infancy of this project to be a hard coded mess. As I get more comfortable with the Vulkan API, I will begin to do some reasurch on game engines while working on this code in parallel. Hopefully if I do not lose interest due to other responsibilities, this project will become something interesting.

## Getting Started
### Ubuntu 18.04
**Note:** These instructions are not generic. The GPU that was used to compile this code was the Intel UHD Graphics 620 (Kabylake GT2). Additional steps might have to be taken when developing with other GPU's.

#### Installing Dependencies
Install the [Vulkan SDK](https://vulkan.lunarg.com/doc/sdk/latest/linux/getting_started.html) by executing the following commands:
```
# Add the correct PPA for the vulkan SDK on their offical download page.

sudo apt update
sudo apt install lunarg-vulkan-sd
```
Other possible dependencies include:
```
sudo apt-get install libpng-dev
sudo apt-get install mesa-vulkan-drivers vulkan-utils
```

#### Compiling from Source
```
mkdir debug
cd debug
cmake ..
make
```

You should now have an executable called `baseline` in your debug folder. This will startup the engine with some default behaviours. As development progresses, baseline will eventually be an API designed to be imported by other projects.


## Resources
Bellow is a list of resources I stumbled across while working on this project. They may prove useful for other who wish to use this codebase.
- https://developer.nvidia.com/vulkan-driver
- https://askubuntu.com/questions/774131/installing-nvidia-vulkan-drivers-for-16-04