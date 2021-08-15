///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Contains code for a planes container.
 *	\file		IcePlanes.h
 *	\author		Pierre Terdiman
 *	\date		February, 19, 2003
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef ICEPLANES_H
#define ICEPLANES_H

	class ICEMATHS_API Planes : public Container
	{
		public:
								Planes()								{}
								Planes(udword nb, const Plane* p)		{ Add(&p->n.x, nb*(sizeof(Plane)/sizeof(float)));				}
								~Planes()								{}

		inline_	udword			GetNbPlanes()					const	{ return GetNbEntries()>>2;										}
		inline_	const Plane*	GetPlanes()						const	{ return (const Plane*)GetEntries();							}

		inline_	void			ResetPlanes()							{ Reset();														}

				Planes&			AddPlane(const Plane& p)				{ Add(p.n.x).Add(p.n.y).Add(p.n.z).Add(p.d);	return *this;	}
	};

	CHECK_CONTAINER_ITEM(Plane)

#endif // ICEPLANES_H
