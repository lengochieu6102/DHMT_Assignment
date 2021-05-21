/*
*	Assignment: Do Hoa May Tinh - DHBK
*	Ten: Le NGoc Hieu
*	MSSV: 1812164
*	Lop: L01
*/


#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <windows.h>
#include <gl.h>
#include <glut.h>

#define M_PI 3.14159265358979323846

using namespace std;

//supportClass
#pragma region
class Point3
{
public:
	float x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Point3& p)
	{
		x = p.x; y = p.y; z = p.z;
	}
	Point3() { x = y = z = 0; }
	Point3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}

};
class Color3
{
public:
	float r, g, b;
	void set(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}
	void set(Color3& c)
	{
		r = c.r; g = c.g; b = c.b;
	}
	Color3() { r = g = b = 0; }
	Color3(float red, float green, float blue)
	{
		r = red; g = green; b = blue;
	}

};
class Point2
{
public:
	Point2() { x = y = 0.0f; } // constructor 1
	Point2(float xx, float yy) { x = xx; y = yy; } // constructor 2
	void set(float xx, float yy) { x = xx; y = yy; }
	float getX() { return x; }
	float getY() { return y; }
	void draw() {
		glBegin(GL_POINTS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
	}
private:
	float 	x, y;
};
class IntRect
{
public:
	IntRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	IntRect(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(int left, int right, int bottom, int top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void draw() {
		glRecti(l, b, r, t);
		glFlush();
	} // draw this rectangle using OpenGL
	int  getWidth() { return (r - l); }
	int  getHeight() { return (t - b); }
private:
	int	l, r, b, t;
};


class RealRect
{
public:
	RealRect() { l = 0; r = 100; b = 0; t = 100; } // constructor
	RealRect(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	void set(float left, float right, float bottom, float top)
	{
		l = left; r = right; b = bottom; t = top;
	}
	float  getWidth() { return (r - l); }
	float  getHeight() { return (t - b); }
	void RealRect::draw() {
		glRectf(l, b, r, t);
		glFlush();
	};// draw this rectangle using OpenGL
private:
	float	l, r, b, t;
};

class Vector3
{
public:
	float	x, y, z;
	void set(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	void set(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	void flip()
	{
		x = -x; y = -y; z = -z;
	}
	void normalize();
	Vector3() { x = y = z = 0; }
	Vector3(float dx, float dy, float dz)
	{
		x = dx; y = dy; z = dz;
	}
	Vector3(Vector3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	Vector3 cross(Vector3 b);
	float dot(Vector3 b);
};

Vector3 Vector3::cross(Vector3 b)
{
	Vector3 c(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x);
	return c;
}
float Vector3::dot(Vector3 b)
{
	return x*b.x + y*b.y + z*b.z;
}
void Vector3::normalize()
{
	float temp = sqrt(x*x + y*y + z*z);
	x = x/temp;
	y = y/temp;
	z = z/temp;
}
#pragma endregion

//Mesh
#pragma region

class VertexID
{
public:
	int		vertIndex;
	int		colorIndex;
};

class Face
{
public:
	int		nVerts;
	VertexID*	vert;
	Vector3		facenorm;

	Face()
	{
		nVerts = 0;
		vert = NULL;
	}
	~Face()
	{
		if (vert != NULL)
		{
			delete[] vert;
			vert = NULL;
		}
		nVerts = 0;
	}
};

class Mesh
{
public:
	int		numVerts;
	Point3*		pt;

	int		numFaces;
	Face*		face;

	float slideX, slideY, slideZ;
	float rotateX, rotateY, rotateZ;

public:
	Mesh()
	{
		numVerts = 0;
		pt = NULL;
		numFaces = 0;
		face = NULL;

		rotateZ = 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}
		if (face != NULL)
		{
			delete[] face;
		}
		numVerts = 0;
		numFaces = 0;
	}
	void DrawWireframe();
	void DrawColor();

	void CreateTetrahedron();
	void CreateCube(float	fSize);
	void CreateCylinder(int nSegment, float fHeight, float fRadius);
	void CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ);
	void CreateShape1(float fSize, int nSegment);
	void CreateShape2(float fLength, float fRadius, float fHeight, int nSegment);
	void CreateShape3(float fLength, float fRadius, float fHeight, float coreWidth, int nSegment);
	void CreateShape4(float fSizeSquare, float fHeight, float fLength);
	void SetColor(int colorIdx);
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
	void CalculateFacesNorm();
	void Draw();
};


#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = { { 1.0, 0.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0,  0.0, 1.0 },
{ 1.0, 1.0,  0.0 },{ 1.0, 0.0, 1.0 },{ 0.0, 1.0, 1.0 },
{ 0.3, 0.3, 0.3 },{ 0.5, 0.5, 0.5 },{ 0.9,  0.9, 0.9 },
{ 1.0, 0.5,  0.5 },{ 0.5, 1.0, 0.5 },{ 0.5, 0.5, 1.0 },
{ 0.0, 0.0, 0.0 },{ 1.0, 1.0, 1.0 } };


void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts = nSegment * 2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight / 2, 0);
	for (i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight / 2;
		pt[i + 1].set(x, y, z);

		y = -fHeight / 2;
		pt[i + 1 + nSegment].set(x, y, z);
	}
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	numFaces = nSegment * 3;
	face = new Face[numFaces];

	idx = 0;
	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if (i < nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i + 1;
		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if (i < nSegment - 1)
			face[idx].vert[2].vertIndex = i + 2 + nSegment;
		else
			face[idx].vert[2].vertIndex = 1 + nSegment;
		face[idx].vert[1].vertIndex = i + 1 + nSegment;
		idx++;
	}

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts = 4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces = 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;


	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;


	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			/*ic = f % COLORNUM;*/

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ) {
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);

	numFaces = 6;
	face = new Face[numFaces];

	//Right face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Left face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}

void Mesh::CreateShape1(float fSize, int nSegment) {
	float fHeight = fSize;
	float fRadius_in = fSize / 6;
	float fRadius_out = 2 * fRadius_in;
	//nSegment=40;
	float fWidth = fSize / 6;
	float fLength = fSize;
	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;
	int numVerts = nSegment * 4 + 4 + 8;

	pt = new Point3[numVerts];

	for (i = 0; i < nSegment; i++) {
		x = fRadius_in * cos(fAngle*i);
		y = fRadius_in * sin(fAngle*i) + fHeight - fRadius_out;
		//inner circle near
		z = fWidth / 2;
		pt[i].set(x, y, z);

		//inner circle far
		z = -fWidth / 2;
		pt[i + nSegment].set(x, y, z);

		if (i <= nSegment / 2) {
			//outer circle top near
			x = fRadius_out * cos(fAngle*i);
			y = fRadius_out * sin(fAngle*i) + fHeight - fRadius_out;
			z = fWidth / 2;
			pt[i + 2 * nSegment].set(x, y, z);

			//outer circle top far
			z = -fWidth / 2;
			pt[i + 3 * nSegment].set(x, y, z);
		}
		else {
			x = fRadius_in * cos(fAngle*i);
			y = fWidth;
			z = fWidth / 2;
			pt[i + 2 * nSegment].set(x, y, z);

			z = -fWidth / 2;
			pt[i + 3 * nSegment].set(x, y, z);
		}
	}
	/*pt[numVerts - 2].set(fRadius_in*cos(PI), fWidth, fWidth / 2);
	pt[numVerts - 1].set(fRadius_in*cos(PI), fWidth, fWidth / 2);*/

	pt[nSegment * 4 + 0].set(fRadius_out, fWidth, fWidth / 2);
	pt[nSegment * 4 + 1].set(fRadius_out, fWidth, -fWidth / 2);
	pt[nSegment * 4 + 2].set(-fRadius_out, fWidth, -fWidth / 2);
	pt[nSegment * 4 + 3].set(-fRadius_out, fWidth, fWidth / 2);

	pt[nSegment * 4 + 4 + 0].set(fLength / 2, fWidth, fWidth / 2);
	pt[nSegment * 4 + 4 + 1].set(fLength / 2, fWidth, -fWidth / 2);
	pt[nSegment * 4 + 4 + 2].set(-fLength / 2, fWidth, -fWidth / 2);
	pt[nSegment * 4 + 4 + 3].set(-fLength / 2, fWidth, fWidth / 2);
	pt[nSegment * 4 + 4 + 4].set(fLength / 2, 0, fWidth / 2);
	pt[nSegment * 4 + 4 + 5].set(fLength / 2, 0, -fWidth / 2);
	pt[nSegment * 4 + 4 + 6].set(-fLength / 2, 0, -fWidth / 2);
	pt[nSegment * 4 + 4 + 7].set(-fLength / 2, 0, fWidth / 2);

	//Face
	numFaces = nSegment / 2 * 4 + nSegment / 2 * 3 + 12;
	face = new Face[numFaces];
	idx = 0;
	//phan loi
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1;
		else
			face[idx].vert[1].vertIndex = 0;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}
	//phan tren o gan
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 1;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}
	//vom tren dinh
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + 2 * nSegment + 1;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 2 * nSegment;
		else
			face[idx].vert[1].vertIndex = 2 * nSegment + 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}
	//phan tren o xa
	for (i = 0; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + nSegment;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1 + nSegment;
		else
			face[idx].vert[1].vertIndex = nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2 * nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2 * nSegment;

		idx++;
	}
	//hcn trai phia truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment / 2;
	face[idx].vert[1].vertIndex = 2 * nSegment + nSegment / 2;
	face[idx].vert[2].vertIndex = 4 * nSegment + 3;
	face[idx].vert[3].vertIndex = 2 * nSegment + nSegment / 2 + 1;
	idx++;

	//hcn phai phia truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 3 * nSegment - 1;
	face[idx].vert[2].vertIndex = 4 * nSegment + 0;
	face[idx].vert[3].vertIndex = 2 * nSegment;
	idx++;

	//hcn trai mat ben
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2 * nSegment + nSegment / 2;
	face[idx].vert[1].vertIndex = 3 * nSegment + nSegment / 2;
	face[idx].vert[2].vertIndex = 4 * nSegment + 2;
	face[idx].vert[3].vertIndex = 4 * nSegment + 3;
	idx++;

	//hcn phai mat ben
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegment;
	face[idx].vert[1].vertIndex = 2 * nSegment;
	face[idx].vert[2].vertIndex = 4 * nSegment + 0;
	face[idx].vert[3].vertIndex = 4 * nSegment + 1;
	idx++;

	//hcn trai mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegment + nSegment / 2;
	face[idx].vert[1].vertIndex = nSegment + nSegment / 2;
	face[idx].vert[2].vertIndex = 3 * nSegment + nSegment / 2 + 1;
	face[idx].vert[3].vertIndex = 4 * nSegment + 2;
	idx++;

	//hcn phai mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment;
	face[idx].vert[1].vertIndex = 3 * nSegment;
	face[idx].vert[2].vertIndex = 4 * nSegment + 1;
	face[idx].vert[3].vertIndex = 4 * nSegment - 1;
	idx++;

	///////////////////////////
	// hinh hop duoi
	// mat ben phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 1;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 0;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 4;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 5;
	idx++;

	//mat ben trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 3;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 2;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 6;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 7;
	idx++;

	//mat phia truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 0;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 3;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 7;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 4;
	idx++;

	//mat phia sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 2;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 1;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 5;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 6;
	idx++;

	//mat duoi 
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 6;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 5;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 4;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 7;
	idx++;

	//mat tren 
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment + 4 + 0;
	face[idx].vert[1].vertIndex = 4 * nSegment + 4 + 1;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 2;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 + 3;
	idx++;


}

void Mesh::CreateShape2(float fLength, float fRadius, float fHeight, int nSegment) {
	numVerts = nSegment * 2 + 4;
	pt = new Point3[numVerts];
	int i, idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	pt[nSegment * 2 + 0].set(fLength / 2, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 1].set(fLength / 2, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 2].set(-fLength / 2, fHeight / 2, fRadius);
	pt[nSegment * 2 + 3].set(-fLength / 2, -fHeight / 2, fRadius);
	for (i = 0; i < nSegment / 2; i++) {
		x = fLength / 2 + fRadius*cos(-PI / 2 + i*fAngle);
		y = fHeight / 2;
		z = fRadius *sin(PI / 2 + i*fAngle);
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	for (i = nSegment / 2; i < nSegment; i++) {
		x = -fLength / 2 + fRadius*cos(-PI / 2 + i*fAngle);
		y = fHeight / 2;
		z = fRadius *sin(PI / 2 + i*fAngle);
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	numFaces = nSegment + 4;
	face = new Face[numFaces];
	idx = 0;

	for (i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < nSegment / 2 - 1) {
			face[idx].vert[1].vertIndex = i + 1;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else {
			face[idx].vert[1].vertIndex = nSegment * 2 + 0;
			face[idx].vert[2].vertIndex = nSegment * 2 + 1;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = nSegment / 2; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < nSegment - 1) {
			face[idx].vert[1].vertIndex = i + 1;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else {
			face[idx].vert[1].vertIndex = nSegment * 2 + 2;
			face[idx].vert[2].vertIndex = nSegment * 2 + 3;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}
	//mat tren
	face[idx].nVerts = nSegment + 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 0;
	for (i = i + 1; i < nSegment + 1; i++) {
		face[idx].vert[i].vertIndex = i - 1;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 2;
	idx++;

	//mat duoi
	face[idx].nVerts = nSegment + 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = 2 * nSegment - 1 - i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 1;
	for (i = i + 1; i < nSegment + 1; i++) {
		face[idx].vert[i].vertIndex = 2 * nSegment - i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 3;
	idx++;

	//mat truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = nSegment * 2 + 2;
	face[idx].vert[2].vertIndex = nSegment * 2 + 3;
	face[idx].vert[3].vertIndex = nSegment;
	idx++;

	//mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 0;
	face[idx].vert[1].vertIndex = nSegment * 2 + 1;
	face[idx].vert[2].vertIndex = nSegment / 2 + nSegment;
	face[idx].vert[3].vertIndex = nSegment / 2;

}

void Mesh::CreateShape3(float fLength, float fRadius, float fHeight, float coreWidth, int nSegment) {

	numVerts = nSegment * 2 + 4 + 16;
	pt = new Point3[numVerts];
	int i, idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	pt[nSegment * 2 + 0].set(fLength / 2, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 1].set(fLength / 2, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 2].set(-fLength / 2, fHeight / 2, fRadius);
	pt[nSegment * 2 + 3].set(-fLength / 2, -fHeight / 2, fRadius);
	////////////////
	//core
	//hcn lon, phia tren
	pt[nSegment * 2 + 4].set(fLength / 2 - fRadius, fHeight / 2, fRadius);
	pt[nSegment * 2 + 5].set(fLength / 2 - fRadius, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 6].set(-fLength / 2 + 2 * fRadius, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 7].set(-fLength / 2 + 2 * fRadius, fHeight / 2, fRadius);

	//hcn lon, phia duoi
	pt[nSegment * 2 + 8].set(fLength / 2 - fRadius, -fHeight / 2, fRadius);
	pt[nSegment * 2 + 9].set(fLength / 2 - fRadius, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 10].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 11].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, fRadius);

	//hcn nho, phia tren
	pt[nSegment * 2 + 12].set(fLength / 2 - fRadius, fHeight / 2, coreWidth / 2);
	pt[nSegment * 2 + 13].set(fLength / 2 - fRadius, fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 14].set(-fLength / 2 + 2 * fRadius, fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 15].set(-fLength / 2 + 2 * fRadius, fHeight / 2, coreWidth / 2);

	//hcn nho, phia duoi
	pt[nSegment * 2 + 16].set(fLength / 2 - fRadius, -fHeight / 2, coreWidth / 2);
	pt[nSegment * 2 + 17].set(fLength / 2 - fRadius, -fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 18].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 19].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, coreWidth / 2);



	for (i = 0; i < nSegment / 2; i++) {
		x = fLength / 2 + fRadius*cos(-PI / 2 + i*fAngle);
		y = fHeight / 2;
		z = fRadius *sin(PI / 2 + i*fAngle);
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	for (i = nSegment / 2; i < nSegment; i++) {
		x = -fLength / 2 + fRadius*cos(-PI / 2 + i*fAngle);
		y = fHeight / 2;
		z = fRadius *sin(PI / 2 + i*fAngle);
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i + nSegment].set(x, y, z);
	}

	numFaces = nSegment + 14;
	face = new Face[numFaces];
	idx = 0;

	for (i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < nSegment / 2 - 1) {
			face[idx].vert[1].vertIndex = i + 1;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else {
			face[idx].vert[1].vertIndex = nSegment * 2 + 0;
			face[idx].vert[2].vertIndex = nSegment * 2 + 1;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for (i = nSegment / 2; i < nSegment; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];

		face[idx].vert[0].vertIndex = i;
		if (i < nSegment - 1) {
			face[idx].vert[1].vertIndex = i + 1;
			face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		}
		else {
			face[idx].vert[1].vertIndex = nSegment * 2 + 2;
			face[idx].vert[2].vertIndex = nSegment * 2 + 3;
		}
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}


	//mat truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = nSegment * 2 + 2;
	face[idx].vert[2].vertIndex = nSegment * 2 + 3;
	face[idx].vert[3].vertIndex = nSegment;
	idx++;

	//mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 0;
	face[idx].vert[1].vertIndex = nSegment * 2 + 1;
	face[idx].vert[2].vertIndex = nSegment / 2 + nSegment;
	face[idx].vert[3].vertIndex = nSegment / 2;
	idx++;


	//mat tren 1
	face[idx].nVerts = nSegment / 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 0;
	face[idx].vert[i + 1].vertIndex = nSegment * 2 + 4 + 1;
	face[idx].vert[i + 2].vertIndex = nSegment * 2 + 4;

	idx++;


	//mat tren 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 13;
	face[idx].vert[1].vertIndex = nSegment * 2 + 5;
	face[idx].vert[2].vertIndex = nSegment * 2 + 6;
	face[idx].vert[3].vertIndex = nSegment * 2 + 14;

	idx++;

	//mat tren 3
	face[idx].nVerts = nSegment / 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = nSegment / 2 + i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 2;
	face[idx].vert[i + 1].vertIndex = nSegment * 2 + 7;
	face[idx].vert[i + 2].vertIndex = nSegment * 2 + 6;

	idx++;


	//mat tren 4
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 4;
	face[idx].vert[1].vertIndex = nSegment * 2 + 12;
	face[idx].vert[2].vertIndex = nSegment * 2 + 15;
	face[idx].vert[3].vertIndex = nSegment * 2 + 7;

	idx++;

	//mat duoi 1
	face[idx].nVerts = nSegment / 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = 2 * nSegment - 1 - i - nSegment / 2;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 8;
	face[idx].vert[i + 1].vertIndex = nSegment * 2 + 9;
	face[idx].vert[i + 2].vertIndex = nSegment * 2 + 1;

	idx++;


	//mat duoi 2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 9;
	face[idx].vert[1].vertIndex = nSegment * 2 + 17;
	face[idx].vert[2].vertIndex = nSegment * 2 + 18;
	face[idx].vert[3].vertIndex = nSegment * 2 + 10;

	idx++;

	//mat duoi 3
	face[idx].nVerts = nSegment / 2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = 2 * nSegment - 1 - i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 10;
	face[idx].vert[i + 1].vertIndex = nSegment * 2 + 11;
	face[idx].vert[i + 2].vertIndex = nSegment * 2 + 3;

	idx++;


	//mat duoi 4
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 8;
	face[idx].vert[1].vertIndex = nSegment * 2 + 11;
	face[idx].vert[2].vertIndex = nSegment * 2 + 19;
	face[idx].vert[3].vertIndex = nSegment * 2 + 16;

	idx++;

	//mat trong 1 
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 12;
	face[idx].vert[1].vertIndex = nSegment * 2 + 13;
	face[idx].vert[2].vertIndex = nSegment * 2 + 17;
	face[idx].vert[3].vertIndex = nSegment * 2 + 16;

	idx++;


	//mat trong2
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 18;
	face[idx].vert[1].vertIndex = nSegment * 2 + 17;
	face[idx].vert[2].vertIndex = nSegment * 2 + 13;
	face[idx].vert[3].vertIndex = nSegment * 2 + 14;

	idx++;


	//mat trong3
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 14;
	face[idx].vert[1].vertIndex = nSegment * 2 + 15;
	face[idx].vert[2].vertIndex = nSegment * 2 + 19;
	face[idx].vert[3].vertIndex = nSegment * 2 + 18;

	idx++;


	//mat trong 4
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment * 2 + 12;
	face[idx].vert[1].vertIndex = nSegment * 2 + 13;
	face[idx].vert[2].vertIndex = nSegment * 2 + 17;
	face[idx].vert[3].vertIndex = nSegment * 2 + 16;

	idx++;

}

void Mesh::CreateShape4(float fSizeSquare, float fHeight, float fLength) {
	numVerts = 16;
	pt = new Point3[numVerts];
	int i, idx;
	float x, y, z;

	//Chan cot phai
	pt[0].set(fLength / 2, -fHeight / 2, fSizeSquare / 2);
	pt[1].set(fLength / 2, -fHeight / 2, -fSizeSquare / 2);
	pt[2].set(fLength / 2 - fSizeSquare, -fHeight / 2, -fSizeSquare / 2);
	pt[3].set(fLength / 2 - fSizeSquare, -fHeight / 2, fSizeSquare / 2);

	//Goc phai
	pt[4].set(fLength / 2, fHeight / 2, fSizeSquare / 2);
	pt[5].set(fLength / 2, fHeight / 2, -fSizeSquare / 2);
	pt[6].set(fLength / 2 - fSizeSquare, fHeight / 2 - fSizeSquare, -fSizeSquare / 2);
	pt[7].set(fLength / 2 - fSizeSquare, fHeight / 2 - fSizeSquare, fSizeSquare / 2);

	//Goc ttrai
	pt[8].set(-fLength / 2, fHeight / 2, fSizeSquare / 2);
	pt[9].set(-fLength / 2, fHeight / 2, -fSizeSquare / 2);
	pt[10].set(-fLength / 2 + fSizeSquare, fHeight / 2 - fSizeSquare, -fSizeSquare / 2);
	pt[11].set(-fLength / 2 + fSizeSquare, fHeight / 2 - fSizeSquare, fSizeSquare / 2);

	//Chan cot trai
	pt[12].set(-fLength / 2, -fHeight / 2, fSizeSquare / 2);
	pt[13].set(-fLength / 2, -fHeight / 2, -fSizeSquare / 2);
	pt[14].set(-fLength / 2 + fSizeSquare, -fHeight / 2, -fSizeSquare / 2);
	pt[15].set(-fLength / 2 + fSizeSquare, -fHeight / 2, fSizeSquare / 2);


	numFaces = 14;
	face = new Face[numFaces];
	idx = 0;

	//day cot phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 2;
	face[idx].vert[2].vertIndex = 1;
	face[idx].vert[3].vertIndex = 0;
	idx++;

	//mat 1 cot phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 1;
	face[idx].vert[2].vertIndex = 5;
	face[idx].vert[3].vertIndex = 4;
	idx++;

	//mat 2 cot phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3;
	face[idx].vert[1].vertIndex = 0;
	face[idx].vert[2].vertIndex = 4;
	face[idx].vert[3].vertIndex = 7;
	idx++;


	//mat 3 cot phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 7;
	face[idx].vert[1].vertIndex = 6;
	face[idx].vert[2].vertIndex = 2;
	face[idx].vert[3].vertIndex = 3;
	idx++;


	//mat 4 cot phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 1;
	face[idx].vert[1].vertIndex = 2;
	face[idx].vert[2].vertIndex = 6;
	face[idx].vert[3].vertIndex = 5;
	idx++;

	//mat 1 thanh ngang
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4;
	face[idx].vert[1].vertIndex = 5;
	face[idx].vert[2].vertIndex = 9;
	face[idx].vert[3].vertIndex = 8;
	idx++;

	//mat 2 thanh ngang
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 11;
	face[idx].vert[2].vertIndex = 7;
	face[idx].vert[3].vertIndex = 4;
	idx++;

	//mat 3 thanh ngang
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 6;
	face[idx].vert[1].vertIndex = 7;
	face[idx].vert[2].vertIndex = 11;
	face[idx].vert[3].vertIndex = 10;
	idx++;

	//mat 4 thanh ngang
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 5;
	face[idx].vert[1].vertIndex = 6;
	face[idx].vert[2].vertIndex = 10;
	face[idx].vert[3].vertIndex = 9;
	idx++;

	//mat 1 cot trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 11;
	face[idx].vert[1].vertIndex = 8;
	face[idx].vert[2].vertIndex = 12;
	face[idx].vert[3].vertIndex = 15;
	idx++;

	//mat 2 cot trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 14;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 11;
	face[idx].vert[3].vertIndex = 15;
	idx++;


	//mat 3 cot trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 9;
	face[idx].vert[1].vertIndex = 10;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 13;
	idx++;


	//mat 4 cot trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 8;
	face[idx].vert[1].vertIndex = 9;
	face[idx].vert[2].vertIndex = 13;
	face[idx].vert[3].vertIndex = 12;
	idx++;

	//day tru trai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 12;
	face[idx].vert[1].vertIndex = 13;
	face[idx].vert[2].vertIndex = 14;
	face[idx].vert[3].vertIndex = 15;
	idx++;
}

// Tim vector phap tuyen pp Newell
void Mesh::CalculateFacesNorm()
{
	for (int f = 0; f < numFaces; f++)
	{
		float mx = 0, my = 0, mz = 0;
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int iv = face[f].vert[v].vertIndex;
			int next = face[f].vert[(v + 1) % face[f].nVerts].vertIndex;
			mx += (pt[iv].y - pt[next].y) * (pt[iv].z + pt[next].z);
			my += (pt[iv].z - pt[next].z) * (pt[iv].x + pt[next].x);
			mz += (pt[iv].x - pt[next].x) * (pt[iv].y + pt[next].y);
		}
		face[f].facenorm.set(mx, my, mz);
		face[f].facenorm.normalize();
	}
}

void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

#pragma endregion

//File main
//Tham so
#pragma region
int		screenWidth = 1000;
int		screenHeight = 600;

Mesh	keDo;
Mesh	giaDo1;
Mesh	giaDo2;
Mesh	goiDo1;
Mesh	goiDo2;
Mesh	thanhTruot;
Mesh	thanhChuU;
Mesh	chot1_cube;
Mesh	chot1_tru;
Mesh	chot2_cube;
Mesh	chot2_tru;
Mesh	chot3_tru;
Mesh	tayQuay;
Mesh	thanhLienKet;
Mesh	banQuay;

//Ke do
float keDoSizeX = 3;
float keDoSizeY = 0.1;
float keDoSizeZ = 1;

//Gia do 1
float giaDo1SizeX = 0.5;
float giaDo1SizeY = 2;
float giaDo1SizeZ = 0.1;

//Gia do 2
float giaDo2SizeX = 3;
float giaDo2SizeY = 0.8;
float giaDo2SizeZ = 0.1;

//Goi do 1,2
float goiDoSize = 0.9;

//Thanh truot
float ttHeight = 10;
float ttRadius = goiDoSize / 6;

//Ban quay
float bqHeight = 0.2;
float bqRadius = 0.8;
float bqRotateStep = 5;

//Tay quay
float tayQuayRadius = bqRadius / 7;
float tayQuayLength = bqRadius - 2 * tayQuayRadius;
float tayQuayHeight = 0.15;

//Chot 2
float chot2CubeSize = tayQuayRadius;
float chot2TruRadius = chot2CubeSize * 0.65;
float chot2TruHeight = bqHeight + tayQuayRadius + chot2CubeSize * 2 + 0.05;
float chot2Space = tayQuayRadius + tayQuayLength / 2;
float chot2SpaceStep = tayQuayLength / 20;

//Thanh lien ket
float thanhLienKetCoreWidth = chot2CubeSize * 2;
float thanhLienKetRadius = thanhLienKetCoreWidth;
float thanhLienketLength = 0.8*giaDo1SizeY * 2 - thanhLienKetRadius * 2;
float thanhlienKetHeight = tayQuayHeight;

//Chot3 
float chot3Height = bqHeight + tayQuayHeight + chot2CubeSize + 0.05;
float chot3Radius = thanhLienKetRadius / 2;

//Chot1
float chot1CubeSize = thanhLienKetRadius / 2;
float chot1TruRadius = chot1CubeSize*0.65;
float chot1TruHeight = chot1CubeSize * 2 + 0.05;

//Thanh chu U
float thanhChuUSize = (2 * goiDoSize / 3 - bqHeight - tayQuayHeight - thanhlienKetHeight) * 2;
float thanhChuULength = thanhChuUSize * 2 + chot1CubeSize * 2;
float thanhChuUHeight = thanhChuULength * 3;

//Thanh chu U, thanh truot, chot 1 khi rotate
float posXRotate = 0;

//nen
float sizeGach = 2.7;
int idxGach = 1;;


int	nSegment = 30;

double angle = 0;

bool view2D = false;
bool bWireFrame = false;
bool bLight1 = true;

// Tham so cho camera
float camera_angle;
float camera_height;
float camera_dis;
float camera_X, camera_Y, camera_Z;
float lookAt_X, lookAt_Y, lookAt_Z;

bool bCamera = true;

#pragma endregion

void drawAxis()
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glEnd();
}

void drawKedo() {
	glPushMatrix();

	glTranslated(0, keDoSizeY, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	keDo.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		keDo.DrawWireframe();
	else {
		keDo.Draw();
		//fix bug? Tao lao
		keDo.DrawColor();
		//
	}

	glPopMatrix();
}

void drawGiaDo1() {
	glPushMatrix();

	glTranslated(0, keDoSizeY + giaDo1SizeY, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	giaDo1.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		giaDo1.DrawWireframe();
	else
		giaDo1.Draw();

	glPopMatrix();
}

void drawGiaDo2() {
	glPushMatrix();

	glTranslated(0, keDoSizeY + 2 * giaDo1SizeY + giaDo2SizeY, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	giaDo2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		giaDo2.DrawWireframe();
	else
		giaDo2.Draw();

	glPopMatrix();
}

void drawGoiDo1() {
	glPushMatrix();

	glTranslatef(-0.8*giaDo2SizeX, keDoSizeY + 2 * giaDo1SizeY + giaDo2SizeY, giaDo2SizeZ);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 100.0;
	goiDo1.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		goiDo1.DrawWireframe();
	else
		goiDo1.Draw();

	glPopMatrix();
}

void drawGoiDo2() {
	glPushMatrix();

	glTranslatef(0.8*giaDo2SizeX, keDoSizeY + 2 * giaDo1SizeY + giaDo2SizeY, giaDo2SizeZ);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 100.0;
	goiDo2.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		goiDo2.DrawWireframe();
	else
		goiDo2.Draw();

	glPopMatrix();
}

void drawThanhTruot() {
	glPushMatrix();

	glTranslatef(posXRotate, keDoSizeY + 2 * giaDo1SizeY + giaDo2SizeY, giaDo2SizeZ + 4 * ttRadius);
	glRotatef(90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat shininess = 20;
	thanhTruot.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		thanhTruot.DrawWireframe();
	else
		thanhTruot.Draw();

	glPopMatrix();
}

void drawBanQuay() {
	glPushMatrix();

	glTranslatef(0, keDoSizeY * 2 + 0.9*giaDo1SizeY, giaDo1SizeZ * 2);
	glRotatef(banQuay.rotateZ, 0, 0, 1);
	glRotatef(90, 1, 0, 0);


	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 100.0;
	banQuay.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		banQuay.DrawWireframe();
	else
		banQuay.Draw();

	glPopMatrix();
}

void drawTayQuay() {
	glPushMatrix();

	glTranslatef(0, keDoSizeY * 2 + 0.9*giaDo1SizeY + bqRadius / 2 - tayQuayLength / 2 - tayQuayRadius, giaDo1SizeZ + bqHeight + tayQuayHeight / 2);
	glRotatef(banQuay.rotateZ, 0, 0, 1);
	glTranslatef(0, tayQuayLength / 2 + tayQuayRadius, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 100.0;
	tayQuay.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		tayQuay.DrawWireframe();
	else
		tayQuay.Draw();

	glPopMatrix();
}

void drawChot2Cube() {
	glPushMatrix();
	float posX = chot2Space * cos((banQuay.rotateZ + 90) * M_PI / 180);
	float posY = keDoSizeY * 2 + 0.9*giaDo1SizeY + chot2Space * sin((banQuay.rotateZ + 90) * M_PI / 180);
	float posZ = giaDo1SizeZ + bqHeight + tayQuayHeight + chot2CubeSize;
	glTranslatef(posX, posY, posZ);
	glRotatef(thanhLienKet.rotateZ, 0, 0, 1);

	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	chot2_cube.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot2_cube.DrawWireframe();
	else
		chot2_cube.Draw();

	glPopMatrix();
}

void drawChot2Tru() {
	glPushMatrix();
	float posX = chot2Space * cos((banQuay.rotateZ + 90) * M_PI / 180);
	float posY = keDoSizeY * 2 + 0.9*giaDo1SizeY + chot2Space * sin((banQuay.rotateZ + 90) * M_PI / 180);
	float posZ = giaDo1SizeZ + chot2TruHeight / 2;
	glTranslatef(posX, posY, posZ);
	glRotatef(90, 1, 0, 0);
	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	chot2_tru.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot2_tru.DrawWireframe();
	else
		chot2_tru.Draw();

	glPopMatrix();
}

void drawThanhLienKet() {
	glPushMatrix();
	float spaceChot3_BanQuay = 0.9*giaDo1SizeY - 0.2*giaDo1SizeY - thanhLienKetRadius;
	float temp1 = chot2Space*sin(banQuay.rotateZ*M_PI / 180);
	float temp2 = chot2Space*cos(banQuay.rotateZ*M_PI / 180);
	thanhLienKet.rotateZ = atan(temp1 / (temp2 + spaceChot3_BanQuay)) * 180 / M_PI;

	//Thanh chu U, thanh truot, chot 1 khi rotate
	posXRotate = -thanhLienketLength*sin(thanhLienKet.rotateZ*M_PI / 180);
	///////////

	glTranslatef(0, 2 * keDoSizeY + giaDo1SizeY - (thanhLienketLength / 2), giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight / 2);
	glRotatef(thanhLienKet.rotateZ, 0, 0, 1);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-thanhLienketLength / 2, 0, 0);


	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat shininess = 100.0;
	thanhLienKet.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		thanhLienKet.DrawWireframe();
	else
		thanhLienKet.Draw();

	glPopMatrix();
}

void drawChot3() {
	glPushMatrix();

	glTranslatef(0, keDoSizeY * 2 + giaDo1SizeY - thanhLienketLength / 2, giaDo1SizeZ + chot3Height / 2);
	glRotatef(90, 1, 0, 0);
	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	chot3_tru.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot3_tru.DrawWireframe();
	else
		chot3_tru.Draw();

	glPopMatrix();
}

void drawChot1Cube() {
	glPushMatrix();
	float posY = 2 * keDoSizeY + 0.2*giaDo1SizeY + thanhLienKetRadius + thanhLienketLength*cos(thanhLienKet.rotateZ*M_PI / 180);
	float posZ = giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight + chot1CubeSize;
	glTranslatef(posXRotate, posY, posZ);
	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	chot1_cube.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot1_cube.DrawWireframe();
	else
		chot1_cube.Draw();

	glPopMatrix();
}

void drawThanhChuU() {
	glPushMatrix();

	glTranslatef(posXRotate, keDoSizeY * 2 + giaDo1SizeY * 2 + giaDo2SizeY - ttRadius - thanhChuUHeight / 2, giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight + chot1CubeSize);
	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	thanhChuU.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		thanhChuU.DrawWireframe();
	else
		thanhChuU.Draw();

	glPopMatrix();
}

void drawChot1Tru() {
	glPushMatrix();

	float posY = 2 * keDoSizeY + 0.2*giaDo1SizeY + thanhLienKetRadius + thanhLienketLength*cos(thanhLienKet.rotateZ*M_PI / 180);
	float posZ = giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight + chot1CubeSize;
	glTranslatef(posXRotate, posY, posZ);
	glRotatef(90, 1, 0, 0);
	// He so cua vat the
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat shininess = 100.0;
	chot1_tru.setupMaterial(ambient, diffuse, specular, shininess);

	if (bWireFrame)
		chot1_tru.DrawWireframe();
	else
		chot1_tru.Draw();

	glPopMatrix();
}

void drawAllFigure() {
	drawKedo();
	drawGiaDo1();
	drawGiaDo2();
	drawGoiDo1();
	drawGoiDo2();
	drawThanhTruot();
	drawBanQuay();
	drawTayQuay();
	drawChot2Cube();
	drawChot2Tru();
	drawThanhLienKet();
	drawChot3();
	drawChot1Cube();
	drawChot1Tru();
	drawThanhChuU();
}

void drawVienGach1(float size, float gachPosX, float gachPosZ) {
	float x = gachPosX;
	float z = gachPosZ;
	float ringWidth = size / 5;

	float round = ringWidth / 7;
	float angle = M_PI / (2 * nSegment);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.4*cos(i*angle), 0, z + size*0.4*sin(i*angle));
		glVertex3f(x + size*0.4*cos((i + 1)*angle), 0, z + size*0.4*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4 - round)*cos((i + 1)*angle), 0, z + (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4 - round)*cos((i)*angle), 0, z + (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.6*cos(i*angle), 0, z + size*0.6*sin(i*angle));
		glVertex3f(x + size*0.6*cos((i + 1)*angle), 0, z + size*0.6*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4)*cos((i + 1)*angle), 0, z + (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4)*cos((i)*angle), 0, z + (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.6*cos(i*angle), 0, z + size*0.6*sin(i*angle));
		glVertex3f(x + size*0.6*cos((i + 1)*angle), 0, z + size*0.6*sin((i + 1)*angle));
		glVertex3f(x + (size*0.6 + round)*cos((i + 1)*angle), 0, z + (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.6 + round)*cos((i)*angle), 0, z + (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

	x = gachPosX + size;
	z = gachPosZ + size;

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.4*cos(i*angle), 0, z - size*0.4*sin(i*angle));
		glVertex3f(x - size*0.4*cos((i + 1)*angle), 0, z - size*0.4*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4 - round)*cos((i + 1)*angle), 0, z - (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4 - round)*cos((i)*angle), 0, z - (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.6*cos(i*angle), 0, z - size*0.6*sin(i*angle));
		glVertex3f(x - size*0.6*cos((i + 1)*angle), 0, z - size*0.6*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4)*cos((i + 1)*angle), 0, z - (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4)*cos((i)*angle), 0, z - (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.6*cos(i*angle), 0, z - size*0.6*sin(i*angle));
		glVertex3f(x - size*0.6*cos((i + 1)*angle), 0, z - size*0.6*sin((i + 1)*angle));
		glVertex3f(x - (size*0.6 + round)*cos((i + 1)*angle), 0, z - (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.6 + round)*cos((i)*angle), 0, z - (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

}

void drawVienGach2(float size, float gachPosX, float gachPosZ) {
	float x = gachPosX + size;
	float z = gachPosZ;
	float ringWidth = size / 5;

	float round = ringWidth / 7;
	float angle = M_PI / (2 * nSegment);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.4*cos(i*angle), 0, z + size*0.4*sin(i*angle));
		glVertex3f(x - size*0.4*cos((i + 1)*angle), 0, z + size*0.4*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4 - round)*cos((i + 1)*angle), 0, z + (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4 - round)*cos((i)*angle), 0, z + (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.6*cos(i*angle), 0, z + size*0.6*sin(i*angle));
		glVertex3f(x - size*0.6*cos((i + 1)*angle), 0, z + size*0.6*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4)*cos((i + 1)*angle), 0, z + (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.4)*cos((i)*angle), 0, z + (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size*0.6*cos(i*angle), 0, z + size*0.6*sin(i*angle));
		glVertex3f(x - size*0.6*cos((i + 1)*angle), 0, z + size*0.6*sin((i + 1)*angle));
		glVertex3f(x - (size*0.6 + round)*cos((i + 1)*angle), 0, z + (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x - (size*0.6 + round)*cos((i)*angle), 0, z + (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

	x = gachPosX;
	z = gachPosZ + size;

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.4*cos(i*angle), 0, z - size*0.4*sin(i*angle));
		glVertex3f(x + size*0.4*cos((i + 1)*angle), 0, z - size*0.4*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4 - round)*cos((i + 1)*angle), 0, z - (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4 - round)*cos((i)*angle), 0, z - (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.6*cos(i*angle), 0, z - size*0.6*sin(i*angle));
		glVertex3f(x + size*0.6*cos((i + 1)*angle), 0, z - size*0.6*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4)*cos((i + 1)*angle), 0, z - (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.4)*cos((i)*angle), 0, z - (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size*0.6*cos(i*angle), 0, z - size*0.6*sin(i*angle));
		glVertex3f(x + size*0.6*cos((i + 1)*angle), 0, z - size*0.6*sin((i + 1)*angle));
		glVertex3f(x + (size*0.6 + round)*cos((i + 1)*angle), 0, z - (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x + (size*0.6 + round)*cos((i)*angle), 0, z - (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

}

void drawVienGach3(float size, float gachPosX, float gachPosZ) {
	float x = gachPosX;
	float z = gachPosZ;
	float ringWidth = size / 5;

	float round = ringWidth / 7;
	float angle = M_PI / (2 * nSegment);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z);
	glVertex3f(x + size*0.6, 0, z);
	glVertex3f(x + size*0.6, 0, z + size);
	glVertex3f(x + size*0.4, 0, z + size);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x, 0, z + size*0.4);
	glVertex3f(x, 0, z + size*0.6);
	glVertex3f(x + size, 0, z + size*0.6);
	glVertex3f(x + size, 0, z + size*0.4);
	glEnd();



	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z + size*0.4);
	glVertex3f(x + (size*0.4 - round), 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + size*0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z + size*0.4);
	glVertex3f(x + (size*0.4 - round), 0, z + (size*0.4 - round));
	glVertex3f(x + (size*0.4 - round), 0, z + 0);
	glVertex3f(x + size*0.4, 0, z);
	glEnd();


	x = gachPosX + size;
	z = gachPosZ;
	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z + size*0.4);
	glVertex3f(x - (size*0.4 - round), 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + size*0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z + size*0.4);
	glVertex3f(x - (size*0.4 - round), 0, z + (size*0.4 - round));
	glVertex3f(x - (size*0.4 - round), 0, z + 0);
	glVertex3f(x - size*0.4, 0, z);
	glEnd();

	x = gachPosX;
	z = gachPosZ + size;
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z - size*0.4);
	glVertex3f(x + (size*0.4 - round), 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - size*0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z - size*0.4);
	glVertex3f(x + (size*0.4 - round), 0, z - (size*0.4 - round));
	glVertex3f(x + (size*0.4 - round), 0, z - 0);
	glVertex3f(x + size*0.4, 0, z);
	glEnd();

	x = gachPosX + size;
	z = gachPosZ + size;
	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z - size*0.4);
	glVertex3f(x - (size*0.4 - round), 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - size*0.4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z - size*0.4);
	glVertex3f(x - (size*0.4 - round), 0, z - (size*0.4 - round));
	glVertex3f(x - (size*0.4 - round), 0, z - 0);
	glVertex3f(x - size*0.4, 0, z);
	glEnd();
}

void drawVienGach4(float size, float gachPosX, float gachPosZ) {
	float x = gachPosX + size / 2;
	float z = gachPosZ + size / 2;
	float ringWidth = size / 5;
	float midCircleRadius = size / 6;
	float largeCircleRadius = midCircleRadius + ringWidth;
	float anpha = atan((0.1*size) / largeCircleRadius);
	float round = ringWidth / 7;
	float templength = size / 2 - largeCircleRadius;
	int M = 4 * nSegment;
	float angle = 2 * M_PI / M;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0, 0, 0);
	for (int i = 0; i < M; i++) {
		if ((i*angle >= anpha && i*angle < M_PI / 2 - anpha) || (i*angle >= M_PI / 2 + anpha && i*angle < M_PI - anpha) ||
			(i*angle >= M_PI + anpha && i*angle < 3 * M_PI / 2 - anpha) || (i*angle >= 3 * M_PI / 2 + anpha && i*angle < 2 * M_PI - anpha)) {
			glBegin(GL_POLYGON);
			glVertex3f(x + largeCircleRadius*cos(i*angle), 0, z + largeCircleRadius*sin(i*angle));
			glVertex3f(x + largeCircleRadius*cos((i + 1)*angle), 0, z + largeCircleRadius*sin((i + 1)*angle));
			glVertex3f(x + (largeCircleRadius + round)*cos((i + 1)*angle), 0, z + (largeCircleRadius + round)*sin((i + 1)*angle));
			glVertex3f(x + (largeCircleRadius + round)*cos((i)*angle), 0, z + (largeCircleRadius + round)*sin((i)*angle));
			glEnd();
		}
	}
	for (int i = 0; i < M; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + midCircleRadius*cos(i*angle), 0, z + midCircleRadius*sin(i*angle));
		glVertex3f(x + midCircleRadius*cos((i + 1)*angle), 0, z + midCircleRadius*sin((i + 1)*angle));
		glVertex3f(x + (midCircleRadius - round)*cos((i + 1)*angle), 0, z + (midCircleRadius - round)*sin((i + 1)*angle));
		glVertex3f(x + (midCircleRadius - round)*cos((i)*angle), 0, z + (midCircleRadius - round)*sin((i)*angle));
		glEnd();

	}

	x = gachPosX;
	z = gachPosZ;
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z + templength);
	glVertex3f(x + (size*0.4 - round), 0, z + templength);
	glVertex3f(x + (size*0.4 - round), 0, z);
	glVertex3f(x + size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + templength, 0, z + size*0.4);
	glVertex3f(x + templength, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + size*0.4);
	glEnd();

	x = gachPosX + size;
	z = gachPosZ + size;
	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z - templength);
	glVertex3f(x - (size*0.4 - round), 0, z - templength);
	glVertex3f(x - (size*0.4 - round), 0, z);
	glVertex3f(x - size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - templength, 0, z - size*0.4);
	glVertex3f(x - templength, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - size*0.4);
	glEnd();

	x = gachPosX + size;
	z = gachPosZ;
	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z + templength);
	glVertex3f(x - (size*0.4 - round), 0, z + templength);
	glVertex3f(x - (size*0.4 - round), 0, z);
	glVertex3f(x - size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - templength, 0, z + size*0.4);
	glVertex3f(x - templength, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + (size*0.4 - round));
	glVertex3f(x, 0, z + size*0.4);
	glEnd();

	x = gachPosX;
	z = gachPosZ + size;
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z - templength);
	glVertex3f(x + (size*0.4 - round), 0, z - templength);
	glVertex3f(x + (size*0.4 - round), 0, z);
	glVertex3f(x + size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + templength, 0, z - size*0.4);
	glVertex3f(x + templength, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - (size*0.4 - round));
	glVertex3f(x, 0, z - size*0.4);
	glEnd();

	glColor3f(0.6, 0.6, 0.6);
	x = gachPosX + size / 2;
	z = gachPosZ + size / 2;

	for (int i = 0; i < M; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x + midCircleRadius*cos(i*angle), 0, z + midCircleRadius*sin(i*angle));
		glVertex3f(x + midCircleRadius*cos((i + 1)*angle), 0, z + midCircleRadius*sin((i + 1)*angle));
		glVertex3f(x + largeCircleRadius*cos((i + 1)*angle), 0, z + largeCircleRadius*sin((i + 1)*angle));
		glVertex3f(x + largeCircleRadius*cos((i)*angle), 0, z + largeCircleRadius*sin((i)*angle));
		glEnd();
	}

	x = gachPosX;
	z = gachPosZ;
	glBegin(GL_POLYGON);
	glVertex3f(x + size*0.4, 0, z + templength + round);
	glVertex3f(x + size*0.6, 0, z + templength + round);
	glVertex3f(x + size*0.6, 0, z);
	glVertex3f(x + size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + templength + round, 0, z + size*0.4);
	glVertex3f(x + templength + round, 0, z + size*0.6);
	glVertex3f(x, 0, z + size*0.6);
	glVertex3f(x, 0, z + size*0.4);
	glEnd();

	x = gachPosX + size;
	z = gachPosZ + size;
	glBegin(GL_POLYGON);
	glVertex3f(x - size*0.4, 0, z - (templength + round));
	glVertex3f(x - size*0.6, 0, z - (templength + round));
	glVertex3f(x - size*0.6, 0, z);
	glVertex3f(x - size*0.4, 0, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x - (templength + round), 0, z - size*0.4);
	glVertex3f(x - (templength + round), 0, z - size*0.6);
	glVertex3f(x, 0, z - size*0.6);
	glVertex3f(x, 0, z - size*0.4);
	glEnd();
}

void drawVienGach(float size, float gachPosX, float gachPosZ) {

	switch (idxGach)
	{
	case 0:
		drawVienGach1(size, gachPosX, gachPosZ);
		break;
	case 1:
		drawVienGach2(size, gachPosX, gachPosZ);
		break;
	case 2:
		drawVienGach3(size, gachPosX, gachPosZ);
		break;
	case 3:
		drawVienGach4(size, gachPosX, gachPosZ);
		break;
	default:
		break;
	}
	idxGach = (idxGach + 1) % 4;
}

void drawNen() {
	glDisable(GL_LIGHTING);
	idxGach = 1;
	for (float posX = -45; posX < 45; posX += sizeGach) {
		for (float posZ = -40; posZ < 40; posZ += sizeGach) {
			drawVienGach(sizeGach, posX, posZ);
		}
	}
	glEnable(GL_LIGHTING);
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.5;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.5;
		//if (camera_height < 0)
		//	camera_height = 0;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle += 5;
		break;
	case GLUT_KEY_LEFT:
		camera_angle -= 5;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	float fRInc;
	float fAngle;
	switch (key)
	{
	case '1':
		banQuay.rotateZ += bqRotateStep;
		if (banQuay.rotateZ > 360)
			banQuay.rotateZ -= 360;
		break;
	case '2':
		banQuay.rotateZ -= bqRotateStep;
		if (banQuay.rotateZ < 0)
			banQuay.rotateZ += 360;
		break;
	case '3':
		chot2Space += chot2SpaceStep;
		if (chot2Space > tayQuayRadius + tayQuayLength)
			chot2Space = tayQuayRadius + tayQuayLength;
		break;
	case '4':
		chot2Space -= chot2SpaceStep;
		if (chot2Space < tayQuayRadius)
			chot2Space = tayQuayRadius;
		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'v':
	case 'V':
		view2D = !view2D;
		break;
	case 'd':
	case 'D':
		bLight1 = !bLight1;
		break;
	case '+':
		camera_dis += 0.5;
		break;
	case '-':
		camera_dis -= 0.5;
		break;
	}
	glutPostRedisplay();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat light_position0[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	if (bLight1 == true)
	{
		glEnable(GL_LIGHT1);
		GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat position1[] = { -10.0, 10.0, -10.0, 0.0 };

		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
		glLightfv(GL_LIGHT1, GL_POSITION, position1);
	}
	else
		glDisable(GL_LIGHT1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera_X = camera_dis * sinf(camera_angle * M_PI / 180);
	camera_Y = camera_height;
	camera_Z = camera_dis * cosf(camera_angle * M_PI / 180);


	if (camera_dis == 0)
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, sinf(camera_angle * M_PI / 180), 0, cosf(camera_angle * M_PI / 180));
	}
	if (view2D) {
		gluLookAt(0, 15, 0, 0, 0, 0, 0, 0, 1);
	}
	else
	{
		gluLookAt(camera_X, camera_Y, camera_Z, lookAt_X, lookAt_Y, lookAt_Z, 0, 1, 0);
	}


	glViewport(0, 0, screenWidth, screenHeight);
	drawAllFigure();
	drawNen();

	glEnable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	camera_angle = -30;  // Góc quay camera xung quanh trục Oy
	camera_height = 4; // Chiều cao camera so với mặt phẳng xOz
	camera_dis = 10;	// Khoảng cách đến trục Oy

	lookAt_X = 0;
	lookAt_Y = 1;
	lookAt_Z = 0;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	const float ar = (float)screenWidth / (float)screenHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 1.5, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light_ambient0[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void print() {
	cout << "1  :  Xoay ban quay nguoc chieu kim dong ho" << endl
		<< "2 : Xoay ban quay cung chieu kim dong ho" << endl
		<< "3, 4 : Dieu chinh vi tri cua chot 2" << endl
		<< "W, w : Chuyen doi qua lai giua che do khung day va to mau" << endl
		<< "V, v : Chuyen doi qua lai giua hai che do nhin khac nhau" << endl
		<< "D, d : Bat / tat nguon sang thu hai" << endl
		<< "+ : Tang khoang cach camera" << endl
		<< "- : Giam khoang cach camera" << endl
		<< "up arrow : Tang chieu cao camera" << endl
		<< "down arrow : Giam chieu cao camera" << endl
		<< "<-: Quay camera theo chieu kim dong ho" << endl
		<< "-> : Quay camera nguoc chieu kim dong ho" << endl;
}

void create() {
	keDo.CreateCuboid(keDoSizeX, keDoSizeY, keDoSizeZ);
	keDo.SetColor(2);
	keDo.CalculateFacesNorm();

	giaDo1.CreateCuboid(giaDo1SizeX, giaDo1SizeY, giaDo1SizeZ);
	giaDo1.SetColor(2);
	giaDo1.CalculateFacesNorm();

	giaDo2.CreateCuboid(giaDo2SizeX, giaDo2SizeY, giaDo2SizeZ);
	giaDo2.SetColor(2);
	giaDo2.CalculateFacesNorm();

	goiDo1.CreateShape1(goiDoSize, nSegment);
	goiDo1.SetColor(0);
	goiDo1.CalculateFacesNorm();

	goiDo2.CreateShape1(goiDoSize, nSegment);
	goiDo2.SetColor(0);
	goiDo2.CalculateFacesNorm();

	thanhTruot.CreateCylinder(nSegment, ttHeight, ttRadius);
	thanhTruot.SetColor(6);
	thanhTruot.CalculateFacesNorm();

	banQuay.CreateCylinder(nSegment, bqHeight, bqRadius);
	banQuay.SetColor(0);
	banQuay.CalculateFacesNorm();

	tayQuay.CreateShape2(tayQuayLength, tayQuayRadius, tayQuayHeight, nSegment);
	tayQuay.SetColor(9);
	tayQuay.CalculateFacesNorm();

	chot2_cube.CreateCube(chot2CubeSize);
	chot2_cube.SetColor(0);
	chot2_cube.CalculateFacesNorm();

	chot2_tru.CreateCylinder(nSegment, chot2TruHeight, chot2TruRadius);
	chot2_tru.SetColor(6);
	chot2_tru.CalculateFacesNorm();

	thanhLienKet.CreateShape3(thanhLienketLength, thanhLienKetRadius, thanhlienKetHeight, thanhLienKetCoreWidth, nSegment);
	thanhLienKet.SetColor(1);
	thanhLienKet.CalculateFacesNorm();

	chot3_tru.CreateCylinder(nSegment, chot3Height, chot3Radius);
	chot3_tru.SetColor(6);
	chot3_tru.CalculateFacesNorm();

	chot1_cube.CreateCube(chot1CubeSize);
	chot1_cube.SetColor(0);
	chot1_cube.CalculateFacesNorm();

	chot1_tru.CreateCylinder(nSegment, chot1TruHeight, chot1TruRadius);
	chot1_tru.SetColor(6);
	chot1_tru.CalculateFacesNorm();

	thanhChuU.CreateShape4(thanhChuUSize, thanhChuUHeight, thanhChuULength);
	thanhChuU.SetColor(7);
	thanhChuU.CalculateFacesNorm();

}

int _tmain(int argc, _TCHAR* argv[])
{
	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Le Ngoc Hieu - 1812164"); // open the screen window

	print();
	create();

	myInit();

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return 0;
}

