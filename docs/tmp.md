# isometric:

In order to create the isometric image, we will need some more concepts about Rotation matrix
![rotation_matrix](https://www.google.com/search?q=rotation+matrix&client=ubuntu&hs=kFe&channel=fs&source=lnms&tbm=isch&sa=X&ved=2ahUKEwj5zYnClKzyAhVUOs0KHYljAVgQ_AUoAXoECAEQAw#imgrc=6UsslNI2H8sJIM)

Using this concept about the lenght of each part of the triangle, we can conclude this rotation Matrix equation

![first](https://wikimedia.org/api/rest_v1/media/math/render/svg/fe4ee3f1ce8e028da5bd4219c9dc7fc2216543e4)
![second](https://wikimedia.org/api/rest_v1/media/math/render/svg/76cd56d49699c53e95cee42a40b340e0a167e078)

```
x1 = x0*cos(z0) - y0*sin(z0)
y1 = x0*cos(z0) + y0*sin(z0)
```

# Breseham line:
[If you want to check the theory of this algorithm, click here](https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/)

[Algorithm in C language](https://www.thecrazyprogrammer.com/2017/01/bresenhams-line-drawing-algorithm-c-c.html)

```
#include<iostream.h>
#include<graphics.h>
 
void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
 
dx=x1-x0;
dy=y1-y0;
 
x=x0;
y=y0;
 
p=2*dy-dx;
 
while(x<x1)
{
if(p>=0)
{
putpixel(x,y,7);
y=y+1;
p=p+2*dy-2*dx;
}
else
{
putpixel(x,y,7);
p=p+2*dy;
}
x=x+1;
}
}
 
int main()
{
int gdriver=DETECT, gmode, error, x0, y0, x1, y1;
initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
 
cout<<"Enter co-ordinates of first point: ";
cin>>x0>>y0;
 
cout<<"Enter co-ordinates of second point: ";
cin>>x1>>y1;
drawline(x0, y0, x1, y1);
 
return 0;
}
```

## Resources

* [Rotation Matrix, math part](https://www.youtube.com/watch?v=Ta8cKqltPfU)
* [Rotation Matrix, wikipedia](https://en.wikipedia.org/wiki/Rotation_matrix)
