#pragma once

#include <minwindef.h>

#pragma pack(push, 1)

struct T_VERTEX2F
{
	FLOAT fX;
	FLOAT fY;
};

struct T_VERTEX3F
{
	FLOAT fX;
	FLOAT fY;
	FLOAT fZ;
};

struct T_COLOR3F
{
	FLOAT fRed;
	FLOAT fGreen;
	FLOAT fBlue;
};

struct T_VERTEX3D
{
	DOUBLE dX;
	DOUBLE dY;
	DOUBLE dZ;
};

#pragma pack(pop)
	
class AFX_EXT_CLASS CSmsVector2f
{
public:
	CSmsVector2f();
	CSmsVector2f(FLOAT fX, FLOAT fY);
	CSmsVector2f(const FLOAT* pVector);
	CSmsVector2f(const CSmsVector2f& v);

public:
	void SetZero();
	void Set(FLOAT fX, FLOAT fY);
	void Get(FLOAT& fX, FLOAT& fY);
	FLOAT Length() const;

	CSmsVector2f& operator+=(const CSmsVector2f& v);
	CSmsVector2f& operator-=(const CSmsVector2f& v);
	CSmsVector2f& operator*=(const CSmsVector2f& v);

public:
	FLOAT x;
	FLOAT y;
};

class AFX_EXT_CLASS CSmsVector3f
{
public:
	CSmsVector3f();
	CSmsVector3f(FLOAT fX, FLOAT fY, FLOAT fZ);
	CSmsVector3f(const FLOAT* pVector);
	CSmsVector3f(const CSmsVector3f& v);

public:
	void SetZero();
	void Set(FLOAT fX, FLOAT fY, FLOAT fZ);
	void Get(FLOAT& fX, FLOAT& fY, FLOAT& fZ);
	FLOAT Dot(const CSmsVector3f& v) const;
	FLOAT Length() const;
	CSmsVector3f Cross(const CSmsVector3f& v) const;
	CSmsVector3f& Normalize();

	CSmsVector3f& operator+=(const CSmsVector3f& v);
	CSmsVector3f& operator-=(const CSmsVector3f& v);
	CSmsVector3f& operator*=(const CSmsVector3f& v);

public:
	FLOAT x;
	FLOAT y;
	FLOAT z;
};

class AFX_EXT_CLASS CSmsVector4f
{
public:
	CSmsVector4f();
	CSmsVector4f(FLOAT fX, FLOAT fY, FLOAT fZ, FLOAT fW);

public:
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT w;
};

inline CSmsVector2f operator+(const CSmsVector2f vVector, const FLOAT fValue);
inline CSmsVector2f operator-(const CSmsVector2f vVector, const FLOAT fValue);
inline CSmsVector2f operator*(const CSmsVector2f vVector, const FLOAT fValue);
inline CSmsVector2f operator/(const CSmsVector2f vVector, const FLOAT fValue);

inline CSmsVector3f operator+(const CSmsVector3f vVector, const FLOAT fValue);
inline CSmsVector3f operator-(const CSmsVector3f vVector, const FLOAT fValue);
inline CSmsVector3f operator*(const CSmsVector3f vVector, const FLOAT fValue);
inline CSmsVector3f operator/(const CSmsVector3f vVector, const FLOAT fValue);

inline CSmsVector4f operator+(const CSmsVector4f vVector, const FLOAT fValue);
inline CSmsVector4f operator-(const CSmsVector4f vVector, const FLOAT fValue);
inline CSmsVector4f operator*(const CSmsVector4f vVector, const FLOAT fValue);
inline CSmsVector4f operator/(const CSmsVector4f vVector, const FLOAT fValue);

class AFX_EXT_CLASS CSmsMatrix4f
{
public:
	CSmsMatrix4f();
	CSmsMatrix4f(FLOAT a00, FLOAT a01, FLOAT a02, FLOAT a03,
		FLOAT a10, FLOAT a11, FLOAT a12, FLOAT a13,
		FLOAT a20, FLOAT a21, FLOAT a22, FLOAT a23,
		FLOAT a30, FLOAT a31, FLOAT a32, FLOAT a33);

public:
	void SetZero();
	void Identity();

	void Scale(FLOAT fScaleX, FLOAT fScaleY, FLOAT ScaleZ);
	void RotationX(FLOAT fRotateX_Radian);
	void RotationY(FLOAT fRotateY_Radian);
	void RotationZ(FLOAT fRotateZ_Radian);

	void Translation(FLOAT fX, FLOAT fY, FLOAT fZ);

	float Determinant() const;

	CSmsMatrix4f Inverse() const;

	inline CSmsMatrix4f operator*(const CSmsMatrix4f& vMatrix) const;

public:
	FLOAT fMatrix[4][4];
};

