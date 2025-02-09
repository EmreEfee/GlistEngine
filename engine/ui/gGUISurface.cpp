/*
 * gGUISurface.cpp
 *
 *  Created on: 27 Tem 2022
 *      Author: ezgil
 */

#include "gGUISurface.h"

#include "gBaseCanvas.h"
#include "gBaseApp.h"


gGUISurface::gGUISurface() {
	resetColorAndBorder();
}
gGUISurface::~gGUISurface() {

}
void gGUISurface::resetColorAndBorder() {
	/*With this function, unless the user calls the chooseColor() function,
		 * a fixed color will be assigned to the shape itself, so now it should
		 * call the chooseColor repeatedly after each drawRectangle/drawLine/drawCircle
		 *
		 * as an alternative, if you don't want to reset it every time:
		 * If the user calls resetColorAndBorder with his hand,
		 * the color entered in the previous way continues with the next shape.
		 *
		 **/
	isFilled = false;
	thickness = 0.0f;
	borderposition = 0.0f;
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

void gGUISurface::draw() {
	drawBackground();
	drawShapes();
}

void gGUISurface::drawShapes() {
	for(int i = 0; i < shapes.size(); i++) {
		//rectangle = 0
		if((int) shapes[i][0] == 0) {//for drawing RECTANGLE first index decides to the shape type
			if((int) shapes[i][5] == 0) {//isFilled = false
				if((int) shapes[i][6] == 0) {//no thickness
					renderer->setColor(gColor(shapes[i][7], shapes[i][8], shapes[i][9], shapes[i][10]));
					gDrawRectangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], shapes[i][4], false);
				}
				else
				{
					renderer->setColor(gColor(shapes[i][9], shapes[i][10], shapes[i][11], shapes[i][12]));
					gDrawRectangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], shapes[i][4], false, shapes[i][7], shapes[i][8]);
				}
			}
			else { //isFilled = true
				if((int) shapes[i][6] == 0) {//no thickness
					renderer->setColor(gColor(shapes[i][7], shapes[i][8], shapes[i][9], shapes[i][10]));
					gDrawRectangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], shapes[i][4], true);
				}
				else
				{
					renderer->setColor(gColor(shapes[i][9], shapes[i][10], shapes[i][11], shapes[i][12]));
					gDrawRectangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], shapes[i][4], true, shapes[i][7], shapes[i][8]);
				}
			}
		}
		//circle = 1
		else if((int) shapes[i][0] == 1) {//for drawing CIRCLE first index decides to the shape type
			if((int) shapes[i][4] == 0) {//isFilled = false
				renderer->setColor(gColor(shapes[i][6], shapes[i][7], shapes[i][8], shapes[i][9]));
				gDrawCircle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], false, shapes[i][5]);
			}
			else { //isFilled = true
				renderer->setColor(gColor(shapes[i][6], shapes[i][7], shapes[i][8], shapes[i][9]));
				gDrawCircle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], true, shapes[i][5]);
			}
		}
		//2d line = 2
		else if((int) shapes[i][0] == 2) {//for drawing 2D LINE first index decides to the shape type
			renderer->setColor(gColor(shapes[i][5], shapes[i][6], shapes[i][7], shapes[i][8]));
			gDrawLine(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3] + left, shapes[i][4] + top);
		}
		//arrow = 3
		else if((int) shapes[i][0] == 3) {//for drawing 3D LINE first index decides to the shape type
			renderer->setColor(gColor(shapes[i][7], shapes[i][8], shapes[i][9], shapes[i][10]));
			gDrawArrow(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3], shapes[i][4], shapes[i][5], shapes[i][6]);
		}
		//triangle = 4
		else if((int) shapes[i][0] == 4) {//for drawing 3D LINE first index decides to the shape type
			if((int) shapes[i][7] == 0) {//isFilled = false
				renderer->setColor(gColor(shapes[i][8], shapes[i][9], shapes[i][10], shapes[i][11]));
				gDrawTriangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3] + left, shapes[i][4] + top,shapes[i][5] + left, shapes[i][6] + top, false);
			}
			else { //isFilled = true
				renderer->setColor(gColor(shapes[i][8], shapes[i][9], shapes[i][10], shapes[i][11]));
				gDrawTriangle(shapes[i][1] + left, shapes[i][2] + top, shapes[i][3] + left, shapes[i][4] + top,shapes[i][5] + left, shapes[i][6] + top, true);
			}
		}
	}
}

void gGUISurface::drawBackground() {
	renderer->setColor(gColor(1.0f, 	1.0f, 	1.0f, 	1.0f));//white
	gDrawRectangle(left, top, right, bottom, true);
}
void gGUISurface::setColor(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
void gGUISurface::setBorder(float thickness, float borderposition) {
	this->thickness = thickness;
	this->borderposition = borderposition;
}
void gGUISurface::drawRectangle(float x, float y, float w, float h, bool isFilled) {
	std::vector<float> newShape;
	newShape.push_back(0); //for drawing rectangle //shapes[i][0]
	newShape.push_back(x); //shapes[i][x] 1
	newShape.push_back(y); //shapes[i][y] 2
	newShape.push_back(w); //shapes[i][w] 3
	newShape.push_back(h); //shapes[i][h] 4
	if(isFilled)
		newShape.push_back(1); //to get whether the rectagnle is filled //shapes[i][5] 0/1 = false/true
	else
		newShape.push_back(0); //to get whether the rectagnle is filled //shapes[i][5] 0/1 = false/true
	if(thickness != 0) {
		newShape.push_back(1); //shapes[i][1] 6 to understand that this rectangle has thickness and borderposition
		newShape.push_back(thickness); //shapes[i][thickness] 7
		newShape.push_back(borderposition); //shapes[i][borderposition] 8
	}
	else {
		newShape.push_back(0); //shapes[i][0] 6 to understand that this rectangle has thickness and borderposition
	}
	newShape.push_back(r); //shapes[i][r] 7 (thickness a girmiyorsa) or 9
	newShape.push_back(g); //shapes[i][g] 8 (thickness a girmiyorsa) or 10
	newShape.push_back(b); //shapes[i][b] 9 (thickness a girmiyorsa) or 11
	newShape.push_back(a); //shapes[i][a] 10 (thickness a girmiyorsa) or 12
	shapes.push_back(newShape);
	resetColorAndBorder();
}

void gGUISurface::drawCircle(float xCenter, float yCenter, float radius, bool isFilled, float numberOfSides) {
	std::vector<float> newShape;
	newShape.push_back(1); //for drawing CIRCLE //shapes[i][0]
	newShape.push_back(xCenter); //shapes[i][xCenter] 1
	newShape.push_back(yCenter); //shapes[i][yCenter] 2
	newShape.push_back(radius); //shapes[i][radius] 3

	if(isFilled)
		newShape.push_back(1); //to get whether the circle is filled //shapes[i][4] 0/1 = false/true
	else
		newShape.push_back(0); //to get whether the circle is filled //shapes[i][4] 0/1 = false/true
	newShape.push_back(numberOfSides); //shapes[i][numberOfSides] 5
	newShape.push_back(r); //shapes[i][r] 6
	newShape.push_back(g); //shapes[i][g] 7
	newShape.push_back(b); //shapes[i][b] 8
	newShape.push_back(a); //shapes[i][a] 9

	shapes.push_back(newShape);
	resetColorAndBorder();
}

void gGUISurface::drawLine(float x1, float y1, float x2, float y2) {
	std::vector<float> newShape;
	newShape.push_back(2); //for drawing 2D LINE //shapes[i][0]
	newShape.push_back(x1); //shapes[i][x1] 1
	newShape.push_back(y1); //shapes[i][y1] 2
	newShape.push_back(x2); //shapes[i][x2] 3
	newShape.push_back(y2); //shapes[i][y2] 4

	newShape.push_back(r); //shapes[i][r] 5
	newShape.push_back(g); //shapes[i][g] 6
	newShape.push_back(b); //shapes[i][b] 7
	newShape.push_back(a); //shapes[i][a] 8

	shapes.push_back(newShape);
	resetColorAndBorder();
}

//void gGUISurface::drawLine(float x1, float y1, float z1, float x2, float y2, float z2) {
//	std::vector<float> newShape;
//	newShape.push_back(3); //for drawing 3D LINE //shapes[i][0]
//	newShape.push_back(x1); //shapes[i][x1] 1
//	newShape.push_back(y1); //shapes[i][y1] 2
//	newShape.push_back(z1); //shapes[i][z1] 3
//	newShape.push_back(x2); //shapes[i][x2] 4
//	newShape.push_back(y2); //shapes[i][y2] 5
//	newShape.push_back(z2); //shapes[i][z2] 6
//
//	newShape.push_back(r); //shapes[i][r] 7
//	newShape.push_back(g); //shapes[i][g] 8
//	newShape.push_back(b); //shapes[i][b] 9
//	newShape.push_back(a); //shapes[i][a] 10
//
//	shapes.push_back(newShape);
//	resetColorAndBorder();
//}

void gGUISurface::drawArrow(float x1, float y1, float length, float angle, float tipLength, float tipAngle) {
	std::vector<float> newShape;
	newShape.push_back(3); //for drawing ARROW //shapes[i][0]
	newShape.push_back(x1); //shapes[i][x1] 1
	newShape.push_back(y1); //shapes[i][y1] 2
	newShape.push_back(length); //shapes[i][length] 3
	newShape.push_back(angle); //shapes[i][angle] 4
	newShape.push_back(tipLength); //shapes[i][tipLength] 5
	newShape.push_back(tipAngle); //shapes[i][tipAngle] 6

	newShape.push_back(r); //shapes[i][r] 7
	newShape.push_back(g); //shapes[i][g] 8
	newShape.push_back(b); //shapes[i][b] 9
	newShape.push_back(a); //shapes[i][a] 10

	shapes.push_back(newShape);
	resetColorAndBorder();
}

void gGUISurface::drawTriangle(float px, float py, float qx, float qy, float rx, float ry, bool isFilled) {
	std::vector<float> newShape;
	newShape.push_back(4); //for drawing TRIANGLE //shapes[i][0]
	newShape.push_back(px); //shapes[i][px] 1
	newShape.push_back(py); //shapes[i][py] 2
	newShape.push_back(qx); //shapes[i][qx] 3
	newShape.push_back(qy); //shapes[i][qy] 4
	newShape.push_back(rx); //shapes[i][rx] 5
	newShape.push_back(ry); //shapes[i][ry] 6

	if(isFilled)
		newShape.push_back(1); //to get whether the circle is filled //shapes[i][7] 0/1 = false/true
	else
		newShape.push_back(0); //to get whether the circle is filled //shapes[i][7] 0/1 = false/true

	newShape.push_back(r); //shapes[i][r] 8
	newShape.push_back(g); //shapes[i][g] 9
	newShape.push_back(b); //shapes[i][b] 10
	newShape.push_back(a); //shapes[i][a] 11

	shapes.push_back(newShape);
	resetColorAndBorder();
}

//void gGUISurface::drawBox(float x, float y, float z, float w, float h, float d, bool isFilled) {
//	this->x = x;
//	this->y = y;
//	this->z = z;
//	this->w = w;
//	this->h = h;
//	this->d = d;
//	this->isFilled = isFilled;
//	renderer->setColor(gColor(r, g, b, a));
//	gDrawBox(x + left, y + top, z, w, h, d, isFilled);
//}
////void gGUISurface::drawBox(glm::mat4 transformationMatrix, bool isFilled = true);
//void gGUISurface::drawSphere(float xPos, float yPos, float zPos, int xSegmentNum, int ySegmentNum, float scale, bool isFilled) {
//	this->xPos = xPos;
//	this->yPos = yPos;
//	this->zPos = zPos;
//	this->isFilled = isFilled;
//	renderer->setColor(gColor(r, g, b, a));
//	gDrawSphere(xPos + left, yPos + top, zPos, xSegmentNum, ySegmentNum, scale, isFilled);
//}

