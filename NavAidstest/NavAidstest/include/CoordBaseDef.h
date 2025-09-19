#pragma once

namespace NS_SALUS_MS_APP
{
	static const DOUBLE g_dPOLE_LIMITED = 85.051129;

#pragma pack(push, 1)

	// ******************************************************************************
	//  Data Structure Definition
	// ******************************************************************************

	// Position in Geodetic Coordinate
	struct T_GEO_POS2D
	{
		DOUBLE m_dLat;
		DOUBLE m_dLon;
	};

	struct T_GEO_POS3D
	{
		DOUBLE m_dLat;
		DOUBLE m_dLon;
		DOUBLE m_dAltitude;
	};

	struct T_GEO_RECT
	{
		T_GEO_POS2D m_tLT;		// Left-Top
		T_GEO_POS2D m_tRB;		// Right-Bottom
	};

	// Position in Cartesian Coordinate
	struct T_CART_POS2D
	{
		DOUBLE m_dX;		// Position on X-axis (meter)
		DOUBLE m_dY;		// Position on Y-axis (meter)
	};

	struct T_CART_POS3D
	{
		DOUBLE m_dX;
		DOUBLE m_dY;
		DOUBLE m_dZ;
	};

	struct T_CART_RECT
	{
		T_CART_POS2D m_tLT;
		T_CART_POS2D m_tRB;
	};

	struct T_CART_RECT4P
	{
		T_CART_POS2D m_tLT;		// Left - Top
		T_CART_POS2D m_tRT;		// Right - Top
		T_CART_POS2D m_tRB;		// Rigth - Bottom
		T_CART_POS2D m_tLB;		// Left - Bottom
	};

#pragma pack(pop)

}	// namespace NS_SALUS_MS_APP
