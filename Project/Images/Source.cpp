#include <stdlib.h>     /* srand, rand */
#include<iostream>
#include <string> 
#include"Math.h"

#include "bitmap_image.hpp"
using namespace std;

const int EdgeLength = 1000;//pixels

int HalfEdge = EdgeLength / 2;
int NumOfEdges = 6;
struct Point
{
public:
	int x, y;
	Point()
	{
		x = y = 0;
	}

	Point(int X_Val, int Y_Val)
	{
		x = X_Val;
		y = Y_Val;
	}

	Point operator-(Point& B)
	{
		Point Res;
		Res.x = x - B.x;
		Res.y = y - B.y;

		return Res;
	}
};

int Absolute(int num)
{
	if (num < 0)
		return num * -1;
	else
	{
		return num;
	}
}

void DrawParameter(image_drawer& MyDrawer, Point* ShapeCorners)
{
	for (size_t i = 0; i < NumOfEdges - 1; i++)
	{
		MyDrawer.line_segment(ShapeCorners[i].x + HalfEdge, ShapeCorners[i].y + HalfEdge, ShapeCorners[i + 1].x + HalfEdge, ShapeCorners[i + 1].y + HalfEdge);

	}
	MyDrawer.line_segment(ShapeCorners[0].x + HalfEdge, ShapeCorners[0].y + HalfEdge, ShapeCorners[NumOfEdges - 1].x + HalfEdge, ShapeCorners[NumOfEdges - 1].y + HalfEdge);

}

void DrawCircle(int x, int y, int r, bitmap_image& MyImage)
{
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;

	for (i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		MyImage.set_pixel(x + x1, y + y1, palette_colormap[e_black]);
	}
}

void GetCorners(int r, Point* ShapeCorners)
{
	static const double PI = 3.1415926535;
	double angle, x1, y1;

	int index = 0;
	for (int i = 0; i < 360; i += 360 / NumOfEdges)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		ShapeCorners[index].x = x1;
		ShapeCorners[index].y = y1;
		index++;
	}
}

Point midpoint(Point A, Point B)
{
	LGVector2D AA(A.x, A.y);
	LGVector2D BB(B.x, B.y);
	LGVector2D NewVec;
	NewVec = BB - AA;
	float Mag = NewVec.getLength();
	NewVec.normalize();
	Mag /= 2;
	NewVec.setLength(Mag);
	NewVec += AA;

	Point ret;
	ret.x = NewVec.x;
	ret.y = NewVec.y;


	return ret;
}

int main()
{
	int ColorLoop = 0;
	srand(time(NULL));

	bitmap_image MyImage(EdgeLength, EdgeLength);
	image_drawer MyDrawer(MyImage);
	Point* ShapeCorners = new Point[NumOfEdges];

	GetCorners((EdgeLength / 2) - 10, ShapeCorners);
	MyDrawer.pen_color(255, 255, 255);

	for (size_t i = 0; i < EdgeLength; i++)
	{
		for (int j = 0; j < EdgeLength; j++)
		{
			MyImage.set_pixel(i, j, 0, 0, 0);
		}
	}

	//DrawParameter(MyDrawer, ShapeCorners);


	int LastIndex = 0;
	bool firsttime = true;
	Point Mid;
	Mid = ShapeCorners[0];
	for (int PixelCounter = 0; PixelCounter < 10000000; PixelCounter++)
	{
		int RandCorner = rand() % NumOfEdges;

		if (firsttime == false)
		{
			if (RandCorner == LastIndex)
			{
				while (true)
				{
					RandCorner = rand() % NumOfEdges;
					if (RandCorner != LastIndex)
						break;
				}
			}
		}
		LastIndex = RandCorner;

		Mid = midpoint(Mid, ShapeCorners[RandCorner]);
		rgb_t RainboColor = prism_colormap[(Absolute(Mid.x - HalfEdge)  ) % 1000];
		MyImage.set_pixel(Mid.x + HalfEdge, Mid.y + HalfEdge, RainboColor);
		firsttime = false;

	}

	std::string Filename = "ImageNumber_";
	Filename += std::to_string(NumOfEdges);

	Filename += ".bmp";

	MyImage.save_image(Filename);
	cout << "Saved image: " << Filename << endl;

}