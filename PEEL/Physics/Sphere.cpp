///////////////////////////////////////////////////////////////////////////////
/*
 *	PEEL - Physics Engine Evaluation Lab
 *	Copyright (C) 2012 Pierre Terdiman
 *	Homepage: http://www.codercorner.com/blog.htm
 */
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sphere.h"

SphereMesh::SphereMesh() : mRadius(0.0f), mNbVerts(0), mVerts(null), mNbTris(0), mTris(null)
{
}

SphereMesh::SphereMesh(udword nb_circle_pts, udword nb_rotations, float radius, bool half_sphere) : mRadius(0.0f), mNbVerts(0), mVerts(null), mNbTris(0), mTris(null)
{
	Generate(nb_circle_pts, nb_rotations, radius, half_sphere);
}

SphereMesh::~SphereMesh()
{
	Reset();
}

void SphereMesh::Reset()
{
	mRadius = 0.0f;
	mNbVerts = 0;
	mNbTris = 0;
	DELETEARRAY(mTris);
	DELETEARRAY(mVerts);
}

void SphereMesh::Generate(udword nb_circle_pts, udword nb_rotations, float radius, bool half_sphere)
{
	const udword NbCirclePts = nb_circle_pts;
	const udword NbRotations = nb_rotations;

	const udword NbCirclePts1 = (NbCirclePts/2)+1;
	const udword NbVerts = NbCirclePts1*NbRotations;
	mNbVerts = NbVerts;
	mVerts = ICE_NEW(Point)[NbVerts];

	{
		Point* Pts = ICE_NEW(Point)[NbCirclePts];
		GeneratePolygon(NbCirclePts, Pts, sizeof(Point), ORIENTATION_XY, radius, 0.0f);

		udword k=0;
		const float Range = half_sphere ? PI : TWOPI;
		for(udword j=0;j<NbRotations;j++)
		{
			const float Coeff = float(j)/float(NbRotations-1);
			Matrix3x3 Rot;
			Rot.RotY(Range*Coeff);

			for(udword i=0;i<NbCirclePts1;i++)
				mVerts[k++] = Pts[i] * Rot;
		}
		DELETEARRAY(Pts);
	}

	mNbTris = (NbRotations-1)*(NbCirclePts/2)*2;
	mTris = ICE_NEW(IndexedTriangle)[mNbTris];
	udword k=0;
	for(udword j=0;j<NbRotations-1;j++)
	{
		const udword j1 = (j+1)%NbRotations;

		const Point* CircleBase = mVerts + j*NbCirclePts1;
		const Point* NextCircle = mVerts + j1*NbCirclePts1;
		for(udword i=0;i<NbCirclePts/2;i++)
		{
			const Point* p0 = &CircleBase[i];
			const Point* p1 = &CircleBase[i+1];
			const Point* p2 = &NextCircle[i+1];
			const Point* p3 = &NextCircle[i];

			mTris[k].mRef[0] = udword(p0 - mVerts);
			mTris[k].mRef[1] = udword(p1 - mVerts);
			mTris[k].mRef[2] = udword(p2 - mVerts);

			mTris[k+1].mRef[0] = udword(p0 - mVerts);
			mTris[k+1].mRef[1] = udword(p2 - mVerts);
			mTris[k+1].mRef[2] = udword(p3 - mVerts);

			k+=2;
		}
	}
}




static const udword gIndices[] = {85, 149, 138, 138, 151, 145, 138, 149, 151, 149, 150, 151, 145, 158, 144, 145, 151, 158, 151, 154, 158, 151, 150, 154, 150, 152, 154, 144, 160, 141, 144, 158, 160, 158, 159, 160, 158, 154, 159, 154, 161, 159, 154, 152, 161, 152, 148, 161, 85, 96, 149, 149, 97, 150, 149, 96, 97, 96, 92, 97, 150, 98, 152, 150, 97, 98, 97, 93, 98, 97, 92, 93, 92, 89, 93, 152, 153, 148, 152, 98, 153, 98, 94, 153, 98, 93, 94, 93, 90, 94, 93, 89, 90, 89, 86, 90, 85, 84, 96, 96, 82, 92, 96, 84, 82, 84, 81, 82, 92, 88, 89, 92, 82, 88, 82, 77, 88, 82, 81, 77, 81, 78, 77, 89, 20, 86, 89, 88, 20, 88, 18, 20, 88, 77, 18, 77, 17, 18, 77, 78, 17, 78, 75, 17, 85, 135, 84, 84, 83, 81, 84, 135, 83, 135, 136, 83, 81, 79, 78, 81, 83, 79, 83, 80, 79, 83, 136, 80, 136, 130, 80, 78, 76, 75, 78, 79, 76, 79, 44, 76, 79, 80, 44, 80, 53, 44, 80, 130, 53, 130, 52, 53, 
85, 138, 135, 135, 137, 136, 135, 138, 137, 138, 145, 137, 136, 131, 130, 136, 137, 131, 137, 142, 131, 137, 145, 142, 145, 144, 142, 130, 133, 52, 130, 131, 133, 131, 134, 133, 131, 142, 134, 142, 143, 134, 142, 144, 143, 144, 141, 143, 141, 155, 140, 140, 112, 111, 140, 155, 112, 155, 126, 112, 111, 109, 110, 111, 112, 109, 112, 123, 109, 112, 126, 123, 126, 125, 123, 110, 104, 106, 110, 109, 104, 109, 105, 104, 109, 123, 105, 123, 118, 105, 123, 125, 118, 125, 124, 118, 148, 146, 147, 147, 122, 128, 147, 146, 122, 146, 73, 122, 128, 121, 127, 128, 122, 121, 122, 120, 121, 122, 73, 120, 73, 72, 120, 127, 119, 124, 127, 121, 119, 121, 115, 119, 121, 120, 115, 120, 68, 115, 120, 72, 68, 72, 69, 68, 86, 19, 87, 87, 15, 65, 87, 19, 15, 19, 6, 15, 65, 64, 70, 65, 15, 64, 15, 14, 64, 15, 6, 14, 6, 5, 14, 70, 63, 69, 70, 64, 63, 64, 61, 63, 64, 14, 61, 14, 13, 61, 14, 5, 13, 5, 9, 13, 
75, 74, 16, 16, 11, 4, 16, 74, 11, 74, 38, 11, 4, 12, 3, 4, 11, 12, 11, 58, 12, 11, 38, 58, 38, 41, 58, 3, 10, 9, 3, 12, 10, 12, 54, 10, 12, 58, 54, 58, 55, 54, 58, 41, 55, 41, 40, 55, 52, 51, 50, 50, 46, 2, 50, 51, 46, 51, 49, 46, 2, 45, 37, 2, 46, 45, 46, 48, 45, 46, 49, 48, 49, 107, 48, 37, 39, 40, 37, 45, 39, 45, 47, 39, 45, 48, 47, 48, 101, 47, 48, 107, 101, 107, 106, 101, 124, 125, 127, 127, 129, 128, 127, 125, 129, 125, 126, 129, 128, 157, 147, 128, 129, 157, 129, 156, 157, 129, 126, 156, 126, 155, 156, 147, 161, 148, 147, 157, 161, 157, 159, 161, 157, 156, 159, 156, 160, 159, 156, 155, 160, 155, 141, 160, 69, 72, 70, 70, 71, 65, 70, 72, 71, 72, 73, 71, 65, 91, 87, 65, 71, 91, 71, 95, 91, 71, 73, 95, 73, 146, 95, 87, 90, 86, 87, 91, 90, 91, 94, 90, 91, 95, 94, 95, 153, 94, 95, 146, 153, 146, 148, 153, 
9, 5, 3, 3, 0, 4, 3, 5, 0, 5, 6, 0, 4, 7, 16, 4, 0, 7, 0, 8, 7, 0, 6, 8, 6, 19, 8, 16, 17, 75, 16, 7, 17, 7, 18, 17, 7, 8, 18, 8, 20, 18, 8, 19, 20, 19, 86, 20, 40, 41, 37, 37, 36, 2, 37, 41, 36, 41, 38, 36, 2, 42, 50, 2, 36, 42, 36, 43, 42, 36, 38, 43, 38, 74, 43, 50, 53, 52, 50, 42, 53, 42, 44, 53, 42, 43, 44, 43, 76, 44, 43, 74, 76, 74, 75, 76, 106, 107, 110, 110, 108, 111, 110, 107, 108, 107, 49, 108, 111, 139, 140, 111, 108, 139, 108, 132, 139, 108, 49, 132, 49, 51, 132, 140, 143, 141, 140, 139, 143, 139, 134, 143, 139, 132, 134, 132, 133, 134, 132, 51, 133, 51, 52, 133, 1, 30, 23, 23, 34, 28, 23, 30, 34, 30, 35, 34, 28, 113, 67, 28, 34, 113, 34, 114, 113, 34, 35, 114, 35, 117, 114, 67, 68, 69, 67, 113, 68, 113, 115, 68, 113, 114, 115, 114, 119, 115, 114, 117, 119, 117, 124, 119, 
1, 23, 21, 21, 27, 24, 21, 23, 27, 23, 28, 27, 24, 62, 56, 24, 27, 62, 27, 66, 62, 27, 28, 66, 28, 67, 66, 56, 13, 9, 56, 62, 13, 62, 61, 13, 62, 66, 61, 66, 63, 61, 66, 67, 63, 67, 69, 63, 1, 21, 22, 22, 25, 26, 22, 21, 25, 21, 24, 25, 26, 59, 60, 26, 25, 59, 25, 57, 59, 25, 24, 57, 24, 56, 57, 60, 55, 40, 60, 59, 55, 59, 54, 55, 59, 57, 54, 57, 10, 54, 57, 56, 10, 56, 9, 10, 1, 22, 29, 29, 31, 33, 29, 22, 31, 22, 26, 31, 33, 100, 102, 33, 31, 100, 31, 99, 100, 31, 26, 99, 26, 60, 99, 102, 101, 106, 102, 100, 101, 100, 47, 101, 100, 99, 47, 99, 39, 47, 99, 60, 39, 60, 40, 39, 1, 29, 30, 30, 32, 35, 30, 29, 32, 29, 33, 32, 35, 116, 117, 35, 32, 116, 32, 103, 116, 32, 33, 103, 33, 102, 103, 117, 118, 124, 117, 116, 118, 116, 105, 118, 116, 103, 105, 103, 104, 105, 103, 102, 104, 102, 106, 104};

static const Point gPoints[] = {Point(-3.096383f, 0.000001f, -0.000002f), Point(-0.000002f, 0.000000f, 3.096378f), Point(-0.000002f, -3.096378f, -0.000003f), Point(-2.970213f, -0.497345f, 0.719765f), Point(-2.944835f, -0.956832f, -0.000002f), Point(-2.970213f, 0.497347f, 0.719766f), Point(-2.944836f, 0.956835f, -0.000001f), Point(-2.958136f, -0.461495f, -0.789962f), Point(-2.958136f, 0.461498f, -0.789961f), Point(-2.769489f, 0.000000f, 1.384741f), Point(-2.547145f, -0.804723f, 1.565902f), Point(-2.505027f, -1.820004f, -0.000002f), Point(-2.664443f, -1.365386f, 0.789958f), Point(-2.547145f, 0.804724f, 1.565903f), Point(-2.664444f, 1.365389f, 0.789959f), Point(-2.505027f, 1.820007f, -0.000001f), Point(-2.695287f, -1.343482f, -0.719769f), Point(-2.533689f, -0.846135f, -1.565906f), Point(-2.633941f, 0.000002f, -1.627864f), Point(-2.695287f, 1.343485f, -0.719768f), Point(-2.533689f, 0.846138f, -1.565905f), Point(-0.846140f, 0.000000f, 2.978524f), Point(-0.261474f, -0.804724f, 2.978524f), Point(-0.261474f, 0.804724f, 2.978525f), Point(-1.627866f, 0.000000f, 2.633935f), Point(-1.120284f, -0.813931f, 2.769483f), Point(-0.503040f, -1.548189f, 2.633935f), Point(-1.120284f, 0.813931f, 2.769484f), Point(-0.503040f, 1.548190f, 2.633936f), Point(0.684536f, -0.497346f, 2.978524f), Point(0.684536f, 0.497347f, 2.978525f), Point(0.427906f, -1.316968f, 2.769483f), Point(1.384741f, 0.000000f, 2.769484f), Point(1.316966f, -0.956833f, 2.633935f), Point(0.427906f, 1.316969f, 2.769484f), Point(1.316966f, 0.956834f, 2.633936f), Point(-0.956837f, -2.944829f, -0.000003f), Point(-0.444843f, -2.978524f, 0.719764f), Point(-1.820008f, -2.505021f, -0.000002f), Point(-0.021774f, -2.671148f, 1.565901f), Point(-0.855822f, -2.633936f, 1.384740f), Point(-1.390853f, -2.671147f, 0.719765f), Point(-0.475206f, -2.955959f, -0.789963f), Point(-1.353025f, -2.670738f, -0.789963f), Point(-0.813933f, -2.505021f, -1.627865f), Point(0.475201f, -2.955960f, 0.789957f), Point(0.956831f, -2.944829f, -0.000003f), Point(0.813930f, -2.505022f, 1.627860f), Point(1.353021f, -2.670739f, 0.789957f), Point(1.820004f, -2.505021f, -0.000002f), Point(0.444838f, -2.978524f, -0.719770f), Point(1.390849f, -2.671147f, -0.719770f), Point(0.855816f, -2.633935f, -1.384746f), Point(0.021770f, -2.671146f, -1.565907f), Point(-2.130903f, -1.548189f, 1.627860f), Point(-1.552451f, -2.173801f, 1.565901f), Point(-2.285674f, 0.000000f, 2.088843f), Point(-1.913147f, -0.819539f, 2.292551f), Point(-2.121922f, -2.112103f, 0.789958f), Point(-1.370625f, -1.566256f, 2.292550f), Point(-0.706314f, -2.173801f, 2.088842f), Point(-2.130903f, 1.548190f, 1.627861f), Point(-1.913147f, 0.819539f, 2.292551f), Point(-1.552451f, 2.173802f, 1.565903f), 
Point(-2.121922f, 2.112106f, 0.789959f), Point(-1.820009f, 2.505024f, -0.000000f), Point(-1.370625f, 1.566257f, 2.292552f), Point(-0.706314f, 2.173802f, 2.088844f), Point(-0.021774f, 2.671150f, 1.565903f), Point(-0.855822f, 2.633937f, 1.384742f), Point(-1.390853f, 2.671150f, 0.719767f), Point(-0.956837f, 2.944832f, 0.000000f), Point(-0.444843f, 2.978527f, 0.719767f), Point(-0.000004f, 3.096381f, 0.000000f), Point(-2.110620f, -2.148205f, -0.719769f), Point(-2.240563f, -1.627861f, -1.384745f), Point(-1.587678f, -2.148205f, -1.565907f), Point(-2.029481f, -0.461494f, -2.292554f), Point(-1.849149f, -1.343482f, -2.088847f), Point(-1.066055f, -1.787535f, -2.292555f), Point(-0.188236f, -2.072756f, -2.292555f), Point(-1.316971f, -0.956831f, -2.633939f), Point(-1.384746f, 0.000002f, -2.769487f), Point(-0.427912f, -1.316966f, -2.769488f), Point(-0.684542f, -0.497344f, -2.978528f), Point(-0.000002f, 0.000003f, -3.096381f), Point(-2.240564f, 1.627864f, -1.384744f), Point(-2.110620f, 2.148209f, -0.719768f), Point(-2.029481f, 0.461499f, -2.292554f), Point(-1.849150f, 1.343485f, -2.088846f), Point(-1.587679f, 2.148210f, -1.565905f), Point(-1.353025f, 2.670742f, -0.789960f), Point(-1.316971f, 0.956836f, -2.633938f), Point(-1.066055f, 1.787540f, -2.292553f), Point(-0.813934f, 2.505024f, -1.627863f), Point(-0.475206f, 2.955963f, -0.789960f), Point(-0.684542f, 0.497349f, -2.978527f), Point(-0.427912f, 1.316971f, -2.769486f), Point(-0.188237f, 2.072761f, -2.292553f), Point(0.188231f, -2.072758f, 2.292550f), Point(1.066051f, -1.787538f, 2.292550f), Point(1.587673f, -2.148206f, 1.565901f), Point(1.849144f, -1.343483f, 2.088843f), Point(2.029475f, -0.461496f, 2.292551f), Point(2.533683f, -0.846136f, 1.565902f), Point(2.633935f, 0.000000f, 1.627861f), Point(2.240558f, -1.627862f, 1.384741f), Point(2.110614f, -2.148206f, 0.719765f), Point(2.505021f, -1.820004f, -0.000002f), Point(2.958131f, -0.461495f, 0.789958f), Point(2.695281f, -1.343482f, 0.719765f), Point(2.944829f, -0.956832f, -0.000002f), Point(3.096377f, 0.000001f, -0.000002f), Point(0.188231f, 2.072760f, 2.292552f), Point(1.066051f, 1.787539f, 2.292552f), Point(0.813930f, 2.505023f, 1.627862f), Point(2.029475f, 0.461497f, 2.292551f), Point(1.849144f, 1.343484f, 2.088844f), Point(2.533683f, 0.846138f, 1.565902f), Point(1.587673f, 2.148208f, 1.565903f), Point(0.475201f, 2.955962f, 0.789959f), Point(1.353021f, 2.670742f, 0.789959f), Point(0.956831f, 2.944832f, 0.000000f), Point(2.958131f, 0.461498f, 0.789959f), Point(2.240558f, 1.627863f, 1.384742f), Point(2.695281f, 1.343485f, 0.719766f), Point(2.944829f, 0.956835f, -0.000001f), Point(2.110614f, 2.148208f, 0.719767f), 
Point(1.820004f, 2.505024f, -0.000000f), Point(2.505021f, 1.820007f, -0.000001f), Point(0.706309f, -2.173799f, -2.088847f), Point(1.370621f, -1.566254f, -2.292555f), Point(2.121917f, -2.112103f, -0.789963f), Point(1.552445f, -2.173799f, -1.565907f), Point(2.130898f, -1.548187f, -1.627865f), Point(0.261468f, -0.804721f, -2.978528f), Point(0.503035f, -1.548187f, -2.633939f), Point(1.120278f, -0.813929f, -2.769487f), Point(0.846134f, 0.000003f, -2.978527f), Point(2.664439f, -1.365386f, -0.789962f), Point(2.970208f, -0.497345f, -0.719769f), Point(2.769485f, 0.000002f, -1.384745f), Point(1.913142f, -0.819536f, -2.292554f), Point(2.547139f, -0.804721f, -1.565906f), Point(2.285668f, 0.000002f, -2.088847f), Point(1.627861f, 0.000002f, -2.633938f), Point(0.444838f, 2.978527f, -0.719767f), Point(1.390847f, 2.671150f, -0.719767f), Point(0.855816f, 2.633939f, -1.384743f), Point(0.261468f, 0.804727f, -2.978527f), Point(0.503035f, 1.548192f, -2.633938f), Point(1.120278f, 0.813934f, -2.769486f), Point(0.706309f, 2.173804f, -2.088846f), Point(0.021770f, 2.671150f, -1.565904f), Point(1.370621f, 1.566258f, -2.292553f), Point(2.970208f, 0.497348f, -0.719769f), Point(2.664439f, 1.365389f, -0.789961f), Point(2.121915f, 2.112106f, -0.789961f), Point(1.913142f, 0.819541f, -2.292554f), Point(2.130898f, 1.548192f, -1.627863f), Point(2.547139f, 0.804726f, -1.565905f), Point(1.552445f, 2.173804f, -1.565904f)};

GeoSphereMesh::GeoSphereMesh(float radius) : mRadius(radius), mNbVerts(0), mVerts(null), mNbTris(0), mTris(null)
{
	mNbTris = sizeof(gIndices)/(sizeof(udword)*3);
	mTris = reinterpret_cast<const IndexedTriangle*>(gIndices);

	const float DefaultRadius = 3.096f;
	const float Coeff = radius/DefaultRadius;

	mNbVerts = sizeof(gPoints)/sizeof(Point);
	mVerts = ICE_NEW(Point)[mNbVerts];
	for(udword i=0;i<mNbVerts;i++)
		mVerts[i] = gPoints[i] * Coeff;
}

GeoSphereMesh::~GeoSphereMesh()
{
	mRadius = 0.0f;
	mNbVerts = 0;
	mNbTris = 0;
	mTris = null;
	DELETEARRAY(mVerts);
}

