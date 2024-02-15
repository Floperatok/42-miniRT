# <div align="center">⚙️ miniRT (a [42](https://42perpignan.fr/) project) ⚙️</div>

Subject : <a href=asset/en.subject.pdf>en.miniRT_subject.pdf<a/>

## Work in progress...

## Usage
Download `miniRT` and enter the repo:
```sh
git clone https://github.com/Floperatok/42-miniRT.git && cd 42-miniRT
```
For linux users, you will need to install the following packages:
```sh
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```
For Mac and Windows user you can refer to the unofficial [minilibx doc](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) and modify the Makefile.

Init and update the submodules:
```sh
git submodule init && git submodule update
```
Compile the project:
```sh
make
```
