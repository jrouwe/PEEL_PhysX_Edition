///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for collision hulls (i.e. convex hulls used for collision detection)
 *	\file		IceCollisionHull.h
 *	\author		Pierre Terdiman
 *	\date		January, 29, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef ICECOLLISIONHULL_H
#define ICECOLLISIONHULL_H

	// Forward declarations
	class Valencies;

	class MESHMERIZER_API CollisionHull : public ConvexHull
	{
		public:
											CollisionHull();
		virtual								~CollisionHull();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Computes the collision hull.
		 *	\param		create	[in] creation structure
		 *	\return		true if success.
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		override(ConvexHull)	bool		Compute(const CONVEXHULLCREATE& create);

		override(ConvexHull)	bool		Init(const SurfaceInterface& surface);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Computes hull's supporting vertex.
		 *	\param		dir		[in] separating vector
		 *	\param		id		[in] starting index
		 *	\return		supporting vertex's ID
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		inline_					udword		ComputeSupportingVertex(const Point& dir, udword id)	const
											{
												// "Hill climbing"
												if(LocalSearch(id, dir, GetVerts(), mValencies))	return id;
												else												return INVALID_ID;
											}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Computes hull's tight AABB.
		 *	\param		box		[out] tight AABB around the hull
		 *	\param		world	[in] current world matrix (or null for identity)
		 *	\param		time	[in] possible timestamp (or null)
		 *	\param		stamps	[in] possible array of timestamp (or null)
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								void		ComputeAABB(AABB& box, const Matrix4x4* world=null, udword* time=null, udword* stamps=null)	const;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Computes the number of bytes used by the collision hull.
		 *	\return		number of used bytes
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		override(ConvexHull)	udword		GetUsedRam()											const;

		// Data access
						const	Valencies*	GetValencies()	const	{ return mValencies;	}
		protected:
								Valencies*	mValencies;
		mutable					udword		mSupport[6];
		// Internal methods
								bool		ComputeValencies();
	};

#endif	// ICECOLLISIONHULL_H

