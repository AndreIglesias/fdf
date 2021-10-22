# FDF

The representation in 3D of a landscape is a critical aspect of modern mapping. For example, in these times of spatial exploration, to have a 3D representation of Mars is a prerequisite condition to its conquest. As another example, comparing various 3D repre- sentations of an area of high tectonic activity will allow you to better understand these phenomenon and their evolution, and as a result be better prepared.

## Objectives
* In this project you will discover the basics of graphic programming, and in particular how to place points in space, how to join them with segments and most importantly how to observe the scene from a particular viewpoint.
* You will also discover your first graphic library: miniLibX. This library was developed internally and includes the minimum necessary to open a window, light a pixel and deal with events linked to this window: keyboard and mouse. This project introduces you to “events” programming.

## How to run?

Compilation:
```
make
```
Run with 1 map:
```
./fdf wireframes/42.fdf
```

## File structure:

##|File|Description
---|---|---
1.0|[Makefile](./Makefile)|Makefile of the main program
2.0|[main](./src/main.c)|principal main of the program
3.0|[analyze](./src/analyze)|read map of structure
4.0|[main](./src/compute)|compute calcules of the program
5.0|[main](./src/display)|display render of the program
6.0|[wireframes](./wireframes)|directory of maps to compile
