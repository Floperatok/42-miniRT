# <div align="center">⚙️ miniRT (a [42](https://42perpignan.fr/) project) ⚙️</div>

Subject : [en.miniRT_subject.pdf](assets/en.subject.pdf)

## 📑 Introduction
School 42's `miniRT` introduces students to the world of raytracing, 3D modeling and LOTS of maths. The goal of this project is to render 3D Computer-Generated-Images with basic shapes and lightning effects using the [minilibx](https://github.com/42Paris/minilibx-linux).\
This project features spheres, cylinders and planes as well as dynamic and ambient lighting, making a full phong reflection with some specular reflection.
## Usage
Download `miniRT` and enter the repo:
```sh
git clone https://github.com/Floperatok/42-miniRT.git && cd 42-miniRT
```
For linux users, you will need to install the following packages:
```sh
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```
For Mac and Windows user you can refer to the unofficial [Minilibx doc](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) and modify the Makefile.

Compile the project:
```sh
make
```
The project is now ready to be launched !
```sh
./miniRT your_map.rt
```
You can find some pre-built maps in the `maps` directory or create your own using the following rules :
- Each line represents an object.
- There must be one and only one camera.
- There can be at most one ambient lightning.
- Each lines must have all non-obtional arguments separated with spaces or tabs. 
### Arguments list :
#### Camera :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `C` | - |
| Position | position of the camera | 3 coma separated double  | `0.0,0.0,0.0` |
| Direction | directional vector of the camera | 3 coma separated double between 0 and 1 | `0.0,0.0,1.0` |
| FOV | field of view | int between 0 and 180 | `90` |
| Screen Width | screen width in pixel | int between 0 and 10 000 | `1920` |
| Screen Height | screen height in pixel | int between 0 and 10 000 | `1080` |
#### Ambient Lightning :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `A` | - |
| Ratio | light strength | double between 0 and 1 | `0.5` |
| Color | color of the light | 3 coma separated int between 0 and 255 | `241,144,0` |
#### Diffuse Light :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `L` | - |
| Position | position of the light | 3 coma separated double  | `0.0,5.0,1.0` |
| Ratio | light strength | double between 0 and 1 | `0.5` |
| Color | color of the light | 3 coma separated int between 0 and 255 | `255,255,255` |
#### Sphere :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `sp` | - |
| Position | position of the sphere | 3 coma separated double  | `0.0,0.0,1.0` |
| Diameter | diameter of the sphere | double > 0  | `5.1` |
| Color | color of the sphere | 3 coma separated int between 0 and 255 | `0,255,0` |
| Reflect Ratio | ratio of reflection of the light on the sphere | (obtional, default `0.0`) double between 0 and 1 | `0.9` |
| Is Specular | whether or not the sphere has specular reflection | (obtional, default `0`) 0 or 1 | `1` |
#### Plane :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `pl` | - |
| Position | position of the plane | 3 coma separated double  | `0.0,-1.0,0.0` |
| Normal | normal vector of the plane | 3 coma separated double between 0 and 1 | `0.0,1.0,0.0` |
| Color | color of the plane | 3 coma separated int between 0 and 255 | `0,255,0` |
| Reflect Ratio | ratio of reflection of the light on the plane | (obtional, default `0.0`) double between 0 and 1 | `0.9` |
| Is Specular | whether or not the plane has specular reflection | (obtional, default `0`) 0 or 1 | `1` |
#### Cylinder :
| Argument | Description | Format | Example |
|-|-|-|-|
| Identifier | - | `cy` | - |
| Position | position of the cylinder | 3 coma separated double  | `0.0,0.0,1.0` |
| Direction | directional vector of the cylinder | 3 coma separated double between 0 and 1 | `0.0,1.0,0.0` |
| Diameter | diameter of the cylinder | double > 0  | `2.6` |
| Height | height/length of the cylinder | double > 0 | `4.8` |
| Color | color of the cylinder | 3 coma separated int between 0 and 255 | `0,255,255` |
| Reflect Ratio | ratio of reflection of the light on the cylinder | (obtional, default `0.0`) double between 0 and 1 | `0.1` |
| Is Specular | whether or not the cylinder has specular reflection | (obtional, default `0`) 0 or 1 | `0` |

## Perfomances
It is well known that raytracing algorithms are really slow and computing heavy, and this project is no exception. With a big window, dozens of objects more than 20 light bounce, the rendering time can easily be counted in seconds. The problem stems mainly from the fact that school 42 requires all calculations to be performed on the processor and not on the graphics card... To overcome this problem, I added a way to use multithreading during the rendering process by dividing the screen into a grid and letting each thread work on one tile of the grid in parallel. This solution saves an enormous amount of rendering time, and allows each frame to be calculated quickly enough to produce a more or less fluid video on the simplest renders.
Enable multithreading :
```sh
./miniRT your_map.rt 1
```
Press `SpaceBar` to compute the next frame with a slight change in camera rotation. \
Disable multithreading :
```sh
./miniRT your_map.rt 0
```

## Links
Articles that help me : 
- Overall raytracing : https://raytracing.github.io/books/RayTracingInOneWeekend.html
- Ray intersections : https://iquilezles.org/articles/
- Phong shading : https://www.cs.toronto.edu/~jacobson/phong-demo/ 

Videos that help me :
- Sebastian Lague - *Coding Adventure: Ray Tracing* : https://www.youtube.com/watch?v=Qz0KTGYJtUk
- Carter Semrad - *I made this 3D game with ONLY code* : https://www.youtube.com/watch?v=QhvzmskRiCk

Big thanks to [Arawyn](https://github.com/Arawyn42) for doing this wonderful project with me !