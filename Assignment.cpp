//Assignment: Do Hoa May Tinh - DHBK
//Le Ngoc Hieu: 1812164

#include "stdafx.h"

#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define M_PI 3.14159265358979323846

using namespace std;


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
///////////// Tham so
//Ke do
float keDoSizeX = 3;
float keDoSizeY = 0.1;
float keDoSizeZ =1;

//Gia do 1
float giaDo1SizeX =0.5;
float giaDo1SizeY=2;
float giaDo1SizeZ = 0.1 ;

//Gia do 2
float giaDo2SizeX = 3;
float giaDo2SizeY = 0.8;
float giaDo2SizeZ = 0.1;

//Goi do 1,2
float goiDoSize = 0.9;

//Thanh truot
float ttHeight = 10;
float ttRadius = goiDoSize/6;

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
float thanhLienKetCoreWidth = chot2CubeSize*2;
float thanhLienKetRadius = thanhLienKetCoreWidth;
float thanhLienketLength = 0.8*giaDo1SizeY * 2 - thanhLienKetRadius * 2;
float thanhlienKetHeight = tayQuayHeight;

//Chot3 
float chot3Height = bqHeight + tayQuayHeight + chot2CubeSize + 0.05;
float chot3Radius = thanhLienKetRadius/2;

//Chot1
float chot1CubeSize = thanhLienKetRadius/2;
float chot1TruRadius = chot1CubeSize*0.65;
float chot1TruHeight = chot1CubeSize*2 + 0.05;

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

void drawGiaDo2(){
	glPushMatrix();

	glTranslated(0, keDoSizeY + 2*giaDo1SizeY +giaDo2SizeY , 0);

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

	glTranslatef(-0.8*giaDo2SizeX, keDoSizeY + 2*giaDo1SizeY +giaDo2SizeY, giaDo2SizeZ);
	glRotatef(90, 0,0, 1);
	glRotatef(90, 1,0, 0);

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

	glTranslatef(posXRotate, keDoSizeY + 2 * giaDo1SizeY + giaDo2SizeY, giaDo2SizeZ + 4*ttRadius);
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

	glTranslatef(0, keDoSizeY*2  + 0.9*giaDo1SizeY, giaDo1SizeZ*2);
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

	glTranslatef(0, keDoSizeY*2 + 0.9*giaDo1SizeY + bqRadius/2 - tayQuayLength/2 -tayQuayRadius, giaDo1SizeZ +bqHeight + tayQuayHeight/2);
	glRotatef(banQuay.rotateZ, 0, 0, 1);
	glTranslatef(0, tayQuayLength / 2 + tayQuayRadius, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(90,0, 0, 1);

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
	glTranslatef( posX, posY, posZ);
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
	float temp1 = chot2Space*sin(banQuay.rotateZ*M_PI/180);
	float temp2 = chot2Space*cos(banQuay.rotateZ*M_PI / 180);
	thanhLienKet.rotateZ = atan(temp1/(temp2+spaceChot3_BanQuay)) * 180 / M_PI;

	//Thanh chu U, thanh truot, chot 1 khi rotate
	posXRotate = -thanhLienketLength*sin(thanhLienKet.rotateZ*M_PI / 180);
	///////////

	glTranslatef(0,2*keDoSizeY+giaDo1SizeY- (thanhLienketLength / 2), giaDo1SizeZ+bqHeight+tayQuayHeight+thanhlienKetHeight/2);
	glRotatef(thanhLienKet.rotateZ, 0, 0, 1);
	glRotatef(-90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-thanhLienketLength/2, 0,0);
	
	
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

	glTranslatef(0,keDoSizeY*2+ giaDo1SizeY - thanhLienketLength/2	, giaDo1SizeZ + chot3Height / 2);
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
	float posY =2*keDoSizeY+ 0.2*giaDo1SizeY + thanhLienKetRadius + thanhLienketLength*cos(thanhLienKet.rotateZ*M_PI / 180);
	float posZ = giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight + chot1CubeSize;
	glTranslatef(posXRotate,posY, posZ);
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

	glTranslatef(posXRotate, keDoSizeY * 2 + giaDo1SizeY*2 + giaDo2SizeY - ttRadius - thanhChuUHeight/2, giaDo1SizeZ + bqHeight + tayQuayHeight + thanhlienKetHeight + chot1CubeSize);
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

void drawVienGach1(float size,float gachPosX,float gachPosZ) {
	float x = gachPosX;
	float z = gachPosZ;
	float ringWidth = size / 5;
	
	float round = ringWidth/7;
	float angle = M_PI/(2 * nSegment);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0,0, 0);
	
	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
			glVertex3f(x+size*0.4*cos(i*angle), 0,z+ size*0.4*sin(i*angle));
			glVertex3f(x+size*0.4*cos((i+1)*angle), 0,z+ size*0.4*sin((i+1)*angle));
			glVertex3f(x+(size*0.4 - round)*cos((i + 1)*angle), 0,z+ (size*0.4 - round)*sin((i + 1)*angle));
			glVertex3f(x+(size*0.4 - round)*cos((i)*angle), 0,z+ (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x+size*0.6*cos(i*angle), 0,z+ size*0.6*sin(i*angle));
		glVertex3f(x+size*0.6*cos((i + 1)*angle), 0,z+ size*0.6*sin((i + 1)*angle));
		glVertex3f(x+(size*0.4 )*cos((i + 1)*angle), 0,z+ (size*0.4 )*sin((i + 1)*angle));
		glVertex3f(x+(size*0.4 )*cos((i)*angle), 0,z+ (size*0.4 )*sin((i)*angle));
		glEnd();
	}
	
	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x+size*0.6*cos(i*angle), 0,z+ size*0.6*sin(i*angle));
		glVertex3f(x+size*0.6*cos((i + 1)*angle), 0,z+ size*0.6*sin((i + 1)*angle));
		glVertex3f(x+(size*0.6 + round)*cos((i + 1)*angle), 0,z+ (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x+(size*0.6 + round)*cos((i)*angle), 0, z+(size*0.6 + round)*sin((i)*angle));
		glEnd();
	}
	
	x = gachPosX + size;
	z = gachPosZ+ size;

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.4*cos(i*angle), 0,z -size*0.4*sin(i*angle));
		glVertex3f(x-size*0.4*cos((i + 1)*angle), 0,z -size*0.4*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4 - round)*cos((i + 1)*angle), 0,z- (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4 - round)*cos((i)*angle), 0,z- (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.6*cos(i*angle), 0,z- size*0.6*sin(i*angle));
		glVertex3f(x-size*0.6*cos((i + 1)*angle), 0,z- size*0.6*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4)*cos((i + 1)*angle), 0,z- (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4)*cos((i)*angle), 0,z- (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.6*cos(i*angle), 0, z-size*0.6*sin(i*angle));
		glVertex3f(x-size*0.6*cos((i + 1)*angle), 0,z- size*0.6*sin((i + 1)*angle));
		glVertex3f(x-(size*0.6 + round)*cos((i + 1)*angle), 0,z- (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.6 + round)*cos((i)*angle), 0,z- (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

}

void drawVienGach2(float size, float gachPosX, float gachPosZ) {
	float x = gachPosX +size;
	float z = gachPosZ;
	float ringWidth = size / 5;

	float round = ringWidth / 7;
	float angle = M_PI / (2 * nSegment);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.4*cos(i*angle), 0,z+ size*0.4*sin(i*angle));
		glVertex3f(x-size*0.4*cos((i + 1)*angle), 0,z+ size*0.4*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4 - round)*cos((i + 1)*angle), 0,z+ (size*0.4 - round)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4 - round)*cos((i)*angle), 0,z+ (size*0.4 - round)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0.6, 0.6, 0.6);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.6*cos(i*angle), 0,z+ size*0.6*sin(i*angle));
		glVertex3f(x-size*0.6*cos((i + 1)*angle), 0,z+ size*0.6*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4)*cos((i + 1)*angle), 0,z+ (size*0.4)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.4)*cos((i)*angle), 0,z+ (size*0.4)*sin((i)*angle));
		glEnd();
	}

	glColor3f(0, 0, 0);

	for (int i = 0; i < nSegment; i++) {
		glBegin(GL_POLYGON);
		glVertex3f(x-size*0.6*cos(i*angle), 0,z+ size*0.6*sin(i*angle));
		glVertex3f(x-size*0.6*cos((i + 1)*angle), 0,z+ size*0.6*sin((i + 1)*angle));
		glVertex3f(x-(size*0.6 + round)*cos((i + 1)*angle), 0,z+ (size*0.6 + round)*sin((i + 1)*angle));
		glVertex3f(x-(size*0.6 + round)*cos((i)*angle), 0,z+ (size*0.6 + round)*sin((i)*angle));
		glEnd();
	}

	x = gachPosX;
	z = gachPosZ+size;

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
		glVertex3f(x + size*0.6, 0, z );
		glVertex3f(x + size*0.6, 0, z + size);
		glVertex3f(x + size*0.4, 0, z + size);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(x , 0, z + size*0.4);
		glVertex3f(x , 0, z + size*0.6);
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

	x = gachPosX ;
	z = gachPosZ +size;
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

	x = gachPosX +size;
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
	float x = gachPosX+size/2;
	float z = gachPosZ+size/2;
	float ringWidth = size / 5;
	float midCircleRadius = size / 6;
	float largeCircleRadius = midCircleRadius + ringWidth;
	float anpha = atan((0.1*size) / largeCircleRadius);
	float round = ringWidth / 7;
	float templength = size / 2 - largeCircleRadius;
	int M = 4 * nSegment;
	float angle = 2* M_PI /  M;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0, 0, 0);
	for (int i = 0; i < M; i++) {
		if ((i*angle >= anpha && i*angle < M_PI / 2 - anpha) || (i*angle >= M_PI/2 + anpha && i*angle < M_PI - anpha) ||
			(i*angle >= M_PI+ anpha && i*angle < 3* M_PI / 2 - anpha) || (i*angle >= 3* M_PI / 2 + anpha && i*angle < 2*M_PI  - anpha))  {
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
	glVertex3f(x + (size*0.4 - round), 0, z );
	glVertex3f(x + size*0.4, 0, z );
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + templength, 0, z + size*0.4);
	glVertex3f(x + templength, 0, z + (size*0.4 - round));
	glVertex3f(x , 0, z + (size*0.4 - round));
	glVertex3f(x , 0, z + size*0.4);
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

	x = gachPosX +size;
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
	z = gachPosZ +size;
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
	x = gachPosX + size/2;
	z = gachPosZ + size/2;

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
	glVertex3f(x + size*0.4, 0, z + templength+ round);
	glVertex3f(x + size*0.6, 0, z + templength+ round);
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

void drawVienGach(float size,float gachPosX,float gachPosZ) {

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
		if (chot2Space < tayQuayRadius )
			chot2Space = tayQuayRadius;
		break;
	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'v':
	case 'V':
		view2D=!view2D;
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

	tayQuay.CreateShape2(tayQuayLength, tayQuayRadius, tayQuayHeight,nSegment);
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

