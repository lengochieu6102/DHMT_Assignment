#include "stdafx.h"
#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius)
{
	numVerts=nSegment*2 + 2;
	pt = new Point3[numVerts];

	int		i;
	int		idx;
	float	fAngle = 2*PI/nSegment;
	float	x, y, z;

	pt[0].set(0, fHeight/2, 0);
	for(i = 0; i<nSegment; i++)
	{
		x = fRadius* cos(fAngle*i);
		z = fRadius* sin(fAngle*i);
		y = fHeight/2;
		pt[i+1].set(x, y, z);

		y = -fHeight/2;
		pt[i +1 + nSegment].set(x, y, z);
	}
	pt[numVerts-1].set(0, -fHeight/2, 0);

	numFaces= nSegment*3;
	face = new Face[numFaces];

	idx = 0;
	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = 0;
		if(i < nSegment -1)
			face[idx].vert[1].vertIndex = i + 2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = i + 1;
		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		
		face[idx].vert[0].vertIndex = i+1;
		if(i <nSegment - 1)
			face[idx].vert[1].vertIndex = i+2;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + nSegment;

		idx++;
	}

	for(i = 0; i<nSegment; i++)
	{
		face[idx].nVerts = 3;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = numVerts - 1;
		if(i < nSegment -1)
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

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
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
	float fRadius_in = fSize/6;
	float fRadius_out = 2*fRadius_in;
	//nSegment=40;
	float fWidth = fSize/6;
	float fLength = fSize;
	int		i;
	int		idx;
	float	fAngle = 2 * PI / nSegment;
	float	x, y, z;
	int numVerts = nSegment * 4 + 4 + 8 ;

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

		if (i <= nSegment/2) {
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
		face[idx].vert[0].vertIndex = i+1;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i;
		else
			face[idx].vert[1].vertIndex = 1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2*nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2*nSegment;

		idx++;
	}
	//vom tren dinh
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i +2*nSegment +1;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i +2*nSegment;
		else
			face[idx].vert[1].vertIndex = 2*nSegment +1;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex +  nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex +  nSegment;

		idx++;
	}
	//phan tren o xa
	for (i = 0; i < nSegment ; i++) {
		face[idx].nVerts = 4;
		face[idx].vert = new VertexID[face[idx].nVerts];
		face[idx].vert[0].vertIndex = i + nSegment;

		if (i <nSegment - 1)
			face[idx].vert[1].vertIndex = i + 1 + nSegment;
		else
			face[idx].vert[1].vertIndex = nSegment;
		face[idx].vert[2].vertIndex = face[idx].vert[1].vertIndex + 2* nSegment;
		face[idx].vert[3].vertIndex = face[idx].vert[0].vertIndex + 2* nSegment;

		idx++;
	}
	//hcn trai phia truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = nSegment/2;
	face[idx].vert[1].vertIndex = 2*nSegment + nSegment/2;
	face[idx].vert[2].vertIndex = 4*nSegment + 3;
	face[idx].vert[3].vertIndex = 2 * nSegment + nSegment / 2 + 1;
	idx++;

	//hcn phai phia truoc
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 0;
	face[idx].vert[1].vertIndex = 3* nSegment -1;
	face[idx].vert[2].vertIndex = 4 * nSegment + 0;
	face[idx].vert[3].vertIndex = 2 * nSegment;
	idx++;

	//hcn trai mat ben
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 2* nSegment + nSegment/2;
	face[idx].vert[1].vertIndex = 3* nSegment + nSegment/2;
	face[idx].vert[2].vertIndex = 4 * nSegment + 2;
	face[idx].vert[3].vertIndex = 4 * nSegment + 3;
	idx++;

	//hcn phai mat ben
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3*nSegment ;
	face[idx].vert[1].vertIndex = 2*nSegment;
	face[idx].vert[2].vertIndex = 4 * nSegment + 0;
	face[idx].vert[3].vertIndex = 4 * nSegment + 1;
	idx++;

	//hcn trai mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 3 * nSegment + nSegment/2;
	face[idx].vert[1].vertIndex = nSegment + nSegment/2;
	face[idx].vert[2].vertIndex = 3 * nSegment + nSegment/2+1;
	face[idx].vert[3].vertIndex = 4 * nSegment + 2;
	idx++;

	//hcn phai mat sau
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex =  nSegment;
	face[idx].vert[1].vertIndex = 3 * nSegment ;
	face[idx].vert[2].vertIndex = 4 * nSegment + 1;
	face[idx].vert[3].vertIndex = 4 * nSegment -1;
	idx++;

	///////////////////////////
	// hinh hop duoi
	// mat ben phai
	face[idx].nVerts = 4;
	face[idx].vert = new VertexID[face[idx].nVerts];
	face[idx].vert[0].vertIndex = 4 * nSegment +4 + 1;
	face[idx].vert[1].vertIndex = 4 * nSegment +4 + 0;
	face[idx].vert[2].vertIndex = 4 * nSegment +4 + 4;
	face[idx].vert[3].vertIndex = 4 * nSegment +4 + 5;
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
	face[idx].vert[0].vertIndex = 4 * nSegment +  4+ 0;
	face[idx].vert[1].vertIndex = 4 * nSegment +  4 + 1;
	face[idx].vert[2].vertIndex = 4 * nSegment + 4 + 2;
	face[idx].vert[3].vertIndex = 4 * nSegment + 4 +3;
	idx++;


}

void Mesh::CreateShape2(float fLength, float fRadius,float fHeight , int nSegment) {
	numVerts = nSegment * 2 + 4;
	pt = new Point3[numVerts];
	int i, idx;
	float fAngle = 2 * PI / nSegment;
	float x, y, z;

	pt[nSegment * 2 + 0].set(fLength/2, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 1].set(fLength/2, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 2].set(-fLength / 2, fHeight / 2, fRadius);
	pt[nSegment * 2 + 3].set(-fLength / 2, -fHeight / 2, fRadius);
	for (i = 0; i < nSegment / 2; i++) {
		x = fLength / 2 + fRadius*cos(-PI/2 + i*fAngle);
		y = fHeight / 2;
		z = fRadius *sin(PI / 2 + i*fAngle);
		pt[i].set(x, y, z);

		y = -fHeight / 2;
		pt[i+nSegment].set(x, y, z);
	}

	for (i = nSegment/2; i < nSegment; i++) {
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

	for (i = nSegment/2; i < nSegment; i++) {
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
	face[idx].nVerts = nSegment+2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment/2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[i].vertIndex = nSegment*2+0;
	for (i = i + 1; i < nSegment+1; i++) {
		face[idx].vert[i].vertIndex = i-1;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 2;
	idx++;

	//mat duoi
	face[idx].nVerts = nSegment + 2;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = 2*nSegment-1-i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 1;
	for (i = i + 1; i < nSegment + 1; i++) {
		face[idx].vert[i].vertIndex = 2* nSegment-i;
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
	face[idx].vert[3].vertIndex = nSegment/2;

}

void Mesh::CreateShape3(float fLength, float fRadius,float fHeight, float coreWidth, int nSegment) {
	
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
	pt[nSegment * 2 + 6].set(-fLength / 2 + 2*fRadius, fHeight / 2, -fRadius);
	pt[nSegment * 2 + 7].set(-fLength / 2 + 2*fRadius, fHeight / 2, fRadius);

	//hcn lon, phia duoi
	pt[nSegment * 2 + 8].set(fLength / 2 - fRadius, -fHeight / 2, fRadius);
	pt[nSegment * 2 + 9].set(fLength / 2 - fRadius, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 10].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, -fRadius);
	pt[nSegment * 2 + 11].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, fRadius);

	//hcn nho, phia tren
	pt[nSegment * 2 + 12].set(fLength / 2 - fRadius, fHeight / 2, coreWidth/2);
	pt[nSegment * 2 + 13].set(fLength / 2 - fRadius, fHeight / 2, -coreWidth/2);
	pt[nSegment * 2 + 14].set(-fLength / 2 + 2 * fRadius, fHeight / 2, -coreWidth/2);
	pt[nSegment * 2 + 15].set(-fLength / 2 + 2 * fRadius, fHeight / 2, coreWidth/2);

	//hcn nho, phia duoi
	pt[nSegment * 2 + 16].set(fLength / 2 - fRadius, -fHeight / 2, coreWidth / 2);
	pt[nSegment * 2 + 17].set(fLength / 2 - fRadius, -fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 18].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, -coreWidth / 2);
	pt[nSegment * 2 + 19].set(-fLength / 2 + 2 * fRadius, -fHeight / 2, coreWidth/2);



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
	face[idx].nVerts = nSegment/2 + 3;
	face[idx].vert = new VertexID[face[idx].nVerts];
	for (i = 0; i < nSegment / 2; i++) {
		face[idx].vert[i].vertIndex = i;
	}
	face[idx].vert[i].vertIndex = nSegment * 2 + 0;
	face[idx].vert[i+1].vertIndex = nSegment * 2 + 4 + 1;
	face[idx].vert[i+2].vertIndex = nSegment * 2 + 4;
	
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
	for (i = 0; i < nSegment/2; i++) {
		face[idx].vert[i].vertIndex = nSegment/2+i;
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
		face[idx].vert[i].vertIndex = 2 * nSegment - 1 - i -nSegment/2;
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
	pt[6].set(fLength / 2 -fSizeSquare, fHeight / 2-fSizeSquare, -fSizeSquare / 2);
	pt[7].set(fLength / 2 -fSizeSquare, fHeight / 2-fSizeSquare, fSizeSquare / 2);

	//Goc ttrai
	pt[8].set(-fLength / 2, fHeight / 2, fSizeSquare / 2);
	pt[9].set(-fLength / 2, fHeight / 2, -fSizeSquare / 2);
	pt[10].set(-fLength / 2 + fSizeSquare, fHeight / 2 - fSizeSquare, -fSizeSquare / 2);
	pt[11].set(-fLength / 2 + fSizeSquare, fHeight / 2 - fSizeSquare, fSizeSquare / 2);

	//Chan cot trai
	pt[12].set(-fLength / 2, -fHeight / 2, fSizeSquare / 2);
	pt[13].set(-fLength / 2, -fHeight / 2,	-fSizeSquare / 2);
	pt[14].set(-fLength / 2 + fSizeSquare, -fHeight / 2, -fSizeSquare / 2);
	pt[15].set(-fLength / 2 + fSizeSquare, -fHeight / 2, fSizeSquare / 2);


	numFaces =  14;
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
