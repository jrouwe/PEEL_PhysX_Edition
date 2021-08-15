///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Fracture code.
 *	\file		IceDelaunay3d.h
 *	\author		Pierre Terdiman
 *	\date		October, 31, 2018
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef ICEFRACTUREPATTERN_H
#define ICEFRACTUREPATTERN_H

#include "IceDelaunay3d.h"

	class FractureConvex;

	class MESHMERIZER_API FracturePattern : public Allocateable
	{
	public:
							FracturePattern();
							~FracturePattern();

				void		clear();

				void		create3dVoronoi(const Point dims, int numCells, float biasExp=1.0f, udword seed=42);
				void		getConvexIntersection(const FractureConvex* convex, const Point& center, float scale, PtrContainer& convexes) const;
	private:
				AABB		mBounds;
				Delaunay3d	mDelaunay3d;
	};

#endif	// ICEFRACTUREPATTERN_H