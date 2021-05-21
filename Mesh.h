#if !defined (_MESH_CLASS)
#define _MESH_CLASS

#include "supportClass.h"


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
		nVerts	= 0;
		vert	= NULL;
	}
	~Face()
	{
		if(vert !=NULL)
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
		numVerts	= 0;
		pt		= NULL;
		numFaces	= 0;
		face		= NULL;

		rotateZ = 0;
	}
	~Mesh()
	{
		if (pt != NULL)
		{
			delete[] pt;
		}	
		if(face != NULL)
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
	void CreateShape1(float fSize,int nSegment);
	void CreateShape2(float fLength, float fRadius, float fHeight,int nSegment);
	void CreateShape3(float fLength, float fRadius,  float fHeight, float coreWidth, int nSegment);
	void CreateShape4(float fSizeSquare, float fHeight,float fLength);
	void SetColor(int colorIdx);
	void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness);
	void CalculateFacesNorm();
	void Draw();
};

#endif