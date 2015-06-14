/*
 * OLEDFB3D.h
 *
 *  Created on: Jun 3, 2015
 *      Author: tansinan
 */

#ifndef OLEDFB3D_H_
#define OLEDFB3D_H_

#include "Types.h"
#include "OLEDFB.h"

typedef float Vec2D[2];
typedef float Vec3D[3];
typedef float Mat33[3][3];
typedef float Triangle2D[3][2];
typedef float Triangle3D[3][3];
typedef float Quad2D[4][2];
typedef float Quad3D[4][3];

typedef struct OLEDFB3D_Camera
{
	Vec3D position;
	Vec3D angle;
	Mat33 rotationMatrix;
	float focalLength;
} OLEDFB3D_Camera;

void Vec3D_add(Vec3D result, Vec3D vec1, Vec3D vec2);

void Vec3D_sub(Vec3D result, Vec3D vec1, Vec3D vec2);

void Mat33_setToIdentity(Mat33 mat);

void OLEDFB3D_mat33Product(Mat33 result, Mat33 mat1, Mat33 mat2);

void OLEDFB3D_mat33vec3Product(Vec3D result, Mat33 mat, Vec3D vec);

void OLEDFB3D_buildRotationMatrix(Mat33 rot, Vec3D angle);

void OLEDFB3D_createCamera(OLEDFB3D_Camera* camera, Vec3D position, Vec3D angle);

void OLEDFB3D_setCamera(Vec3D position, Vec3D angle);

void OLEDFB3D_projectPoint(Vec3D point3D, Vec2D point2D);

void OLEDFB3D_drawLine3D(Vec3D point1, Vec3D point2);

void OLEDFB3D_drawTriangle2D(Triangle2D triangle2D);

void OLEDFB3D_drawQuad2D(Quad2D quad2D);
void OLEDFB3D_drawQuad3D(Quad3D quad3D);

void OLEDFB3D_projectPoint(Vec3D point3D, Vec2D point2D);

#endif /* OLEDFB3D_H_ */
