///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for Loop subdivision surfaces
 *	\file		IceLoop.h
 *	\author		Pierre Terdiman
 *	\date		January, 29, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef ICELOOP_H
#define ICELOOP_H

	class MESHMERIZER_API LoopScheme : public PolyhedralScheme
	{
		public:
													LoopScheme();
		virtual										~LoopScheme();

		protected:
								bool*				mBoundary;
								Valencies*			mValencies;
								Adjacencies*		mAdj;
#ifndef MSH_ADJACENCIES_INCLUDE_TOPOLOGY
							const IndexedTriangle*	mFaces;
#endif
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 *	Initializes the subdivision scheme.
		 *	\param		surface		[in] the surface to subdivide
		 *	\return		true if success
		 */
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		override(SubdivScheme)	bool				Init(IndexedSurface& surface);
		override(SubdivScheme)	bool				Close(IndexedSurface& surface);
		override(SubdivScheme)	bool				ComputeNewVertex(udword face_id, udword vref0, udword vref1, Point& p, SubdivHistory* history);
	};

#endif // ICELOOP_H
