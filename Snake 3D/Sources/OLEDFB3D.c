/*
 * OLEDFB3D.c
 *
 *  Created on: Jun 3, 2015
 *      Author: tansinan
 */

#include "OLEDFB3D.h"
#include <math.h>

OLEDFB3D_Camera camera;

const float PI = 3.1415926;
const float focalLength = 120.0;

float degToRad(float deg)
{
	return deg / 180.0 * PI;
}

void Mat33_setToIdentity(Mat33 mat)
{
	for(int i =0;i<3;i++)
	{
		for(int j =0;j<3;j++)
		{
			mat[i][j] = i==j?1:0;
		}
	}
}

void Vec3D_add(Vec3D result, Vec3D vec1, Vec3D vec2)
{
	for (int i = 0; i < 3; i++)
	{
		result[i] = vec1[i] + vec2[i];
	}
}

void Vec3D_sub(Vec3D result, Vec3D vec1, Vec3D vec2)
{
	for (int i = 0; i < 3; i++)
	{
		result[i] = vec1[i] - vec2[i];
	}
}

void OLEDFB3D_drawTriangle2D(Triangle2D triangle2D)
{
	OLEDFB_drawLine(triangle2D[0][0],triangle2D[0][1],triangle2D[1][0],triangle2D[1][1]);
	OLEDFB_drawLine(triangle2D[1][0],triangle2D[1][1],triangle2D[2][0],triangle2D[2][1]);
	OLEDFB_drawLine(triangle2D[2][0],triangle2D[2][1],triangle2D[0][0],triangle2D[0][1]);
}

void OLEDFB3D_mat33Product(Mat33 result, Mat33 mat1, Mat33 mat2)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			result[i][j] = 0;
		}
	}
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				result[i][j] += mat1[i][k]*mat2[k][j];
			}
		}
	}
}

void OLEDFB3D_mat33vec3Product(Vec3D result, Mat33 mat, Vec3D vec)
{
	for(int i=0;i<3;i++)
	{
		result[i] = 0;
	}
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			result[i] += mat[i][j] * vec[j];
		}
	}
}

void OLEDFB3D_buildRotationMatrix(Mat33 rot, Vec3D angle)
{
	Mat33 rotX,rotY,rotZ,temp;
	Mat33_setToIdentity(rotX);
	Mat33_setToIdentity(rotY);
	Mat33_setToIdentity(rotZ);
	rotX[2][2] = rotX[1][1] = cos(degToRad(angle[0]));
	rotX[1][2] = sin(degToRad(angle[0]));
	rotX[2][1] = -rotX[1][2];

	rotY[0][0] = rotY[2][2] = cos(degToRad(angle[1]));
	rotY[2][0] = sin(degToRad(angle[1]));
	rotY[0][2] = -rotY[2][0];

	rotZ[0][0] = rotZ[1][1] = cos(degToRad(angle[2]));
	rotZ[0][1] = sin(degToRad(angle[2]));
	rotZ[1][0] = -rotZ[0][1];
	
	OLEDFB3D_mat33Product(temp,rotX,rotY);
	OLEDFB3D_mat33Product(rot,temp,rotZ);
}

void OLEDFB3D_createCamera(OLEDFB3D_Camera* camera, Vec3D position, Vec3D angle)
{
	for(int i=0;i<3;i++)
	{
		camera->position[i] = position[i];
		camera->angle[i] = angle[i];
	}
	OLEDFB3D_buildRotationMatrix(camera->rotationMatrix, angle);
}

void OLEDFB3D_setCamera(Vec3D position, Vec3D angle)
{
	OLEDFB3D_createCamera(&camera, position, angle);
}

void OLEDFB3D_projectPoint(Vec3D point3D, Vec2D point2D)
{
	Vec3D temp, relativePosition;
	Vec3D_sub(temp, point3D, camera.position);
	OLEDFB3D_mat33vec3Product(relativePosition, camera.rotationMatrix, temp);
	point2D[0] = -relativePosition[0] / relativePosition[2] * focalLength + 64;
	point2D[1] = 16 + relativePosition[1] / relativePosition[2] * 40;
}

void OLEDFB3D_prepareProjectPoint(Vec3D point3D, Vec3D relativePosition)
{
	Vec3D temp;
	Vec3D_sub(temp, point3D, camera.position);
	OLEDFB3D_mat33vec3Product(relativePosition, camera.rotationMatrix, temp);
}

void OLEDFB3D_drawLine3D(Vec3D point1, Vec3D point2)
{
	Vec3D rel1, rel2;
	OLEDFB3D_prepareProjectPoint(point1, rel1);
	OLEDFB3D_prepareProjectPoint(point2, rel2);
	Vec2D point2D1 = {
		-rel1[0] / rel1[2] * focalLength + 64,
		16 + rel1[1] / rel1[2] * focalLength
	};
	Vec2D point2D2 = {
		-rel2[0] / rel2[2] * focalLength + 64,
		16 + rel2[1] / rel2[2] * focalLength
	};
	OLEDFB_drawLine(round(point2D1[0]),round(point2D1[1]),round(point2D2[0]),round(point2D2[1]));
}

void OLEDFB3D_drawQuad2D(Quad2D quad2D)
{
	for(int i=0;i<3;i++)
	{
		OLEDFB_drawLine(quad2D[i][0],quad2D[i][1],quad2D[i+1][0],quad2D[i+1][1]);
	}
	OLEDFB_drawLine(quad2D[3][0],quad2D[3][1],quad2D[0][0],quad2D[0][1]);
}

void OLEDFB3D_drawQuad3D(Quad3D quad3D)
{
	for(int i=0;i<3;i++)
	{
		OLEDFB3D_drawLine3D(quad3D[i],quad3D[i+1]);
	}
	OLEDFB3D_drawLine3D(quad3D[3],quad3D[0]);
}
