#pragma once
#include "GraphicsPCH.h"

// Add, Subtract, Multiply, Divide
#pragma region ADD
inline XMFLOAT2 operator+(XMFLOAT2 _lv, XMFLOAT2 _rv)
{
	return XMFLOAT2(_lv.x + _rv.x, _lv.y + _rv.y);
}
inline XMFLOAT3 operator+(XMFLOAT3 _lv, XMFLOAT3 _rv)
{
	return XMFLOAT3(_lv.x + _rv.x, _lv.y + _rv.y, _lv.z + _rv.z);
}
inline XMFLOAT4 operator+(XMFLOAT4 _lv, XMFLOAT4 _rv)
{
	return XMFLOAT4(_lv.x + _rv.x, _lv.y + _rv.y, _lv.z + _rv.z, _lv.w + _rv.w);
}
#pragma endregion

#pragma region Subtract
inline XMFLOAT2 operator-(XMFLOAT2 _lv, XMFLOAT2 _rv)
{
	return XMFLOAT2(_lv.x - _rv.x, _lv.y - _rv.y);
}
inline XMFLOAT3 operator-(XMFLOAT3 _lv, XMFLOAT3 _rv)
{
	return XMFLOAT3(_lv.x - _rv.x, _lv.y - _rv.y, _lv.z - _rv.z);
}
inline XMFLOAT4 operator-(XMFLOAT4 _lv, XMFLOAT4 _rv)
{
	return XMFLOAT4(_lv.x - _rv.x, _lv.y - _rv.y, _lv.z - _rv.z, _lv.w - _rv.w);
}
#pragma endregion

#pragma region Multiply
inline XMFLOAT2 operator*(XMFLOAT2 _lv, float _rv)
{
	return XMFLOAT2(_lv.x * _rv, _lv.y * _rv);
}
inline XMFLOAT3 operator*(XMFLOAT3 _lv, float _rv)
{
	return XMFLOAT3(_lv.x * _rv, _lv.y * _rv, _lv.z * _rv);
}
inline XMFLOAT4 operator*(XMFLOAT4 _lv, float _rv)
{
	return XMFLOAT4(_lv.x * _rv, _lv.y * _rv, _lv.z * _rv, _lv.w * _rv);
}
#pragma endregion

#pragma region Divide
inline XMFLOAT2 operator/(XMFLOAT2 _lv, float _rv)
{
	return XMFLOAT2(_lv.x / _rv, _lv.y / _rv);
}
inline XMFLOAT3 operator/(XMFLOAT3 _lv, float _rv)
{
	return XMFLOAT3(_lv.x / _rv, _lv.y / _rv, _lv.z / _rv);
}
inline XMFLOAT4 operator/(XMFLOAT4 _lv, float _rv)
{
	return XMFLOAT4(_lv.x / _rv, _lv.y / _rv, _lv.z / _rv, _lv.w / _rv);
}
#pragma endregion

// Clamp, Magnitude, Normalize, Lerp
#pragma region Clamp
inline float Clamp(float _val, float _min, float _max)
{
	return _val < _min
		? _min
		: _val > _max
		? _max
		: _val;
}
inline XMFLOAT2 Clamp(XMFLOAT2 _val, XMFLOAT2 _min, XMFLOAT2 _max)
{
	return XMFLOAT2(Clamp(_val.x, _min.x, _max.x),
		Clamp(_val.y, _min.y, _max.y));
}
inline XMFLOAT3 Clamp(XMFLOAT3 _val, XMFLOAT3 _min, XMFLOAT3 _max)
{
	return XMFLOAT3(Clamp(_val.x, _min.x, _max.x),
		Clamp(_val.y, _min.y, _max.y),
		Clamp(_val.z, _min.z, _max.z));
}
inline XMFLOAT4 Clamp(XMFLOAT4 _val, XMFLOAT4 _min, XMFLOAT4 _max)
{
	return XMFLOAT4(Clamp(_val.x, _min.x, _max.x),
		Clamp(_val.y, _min.y, _max.y),
		Clamp(_val.z, _min.z, _max.z),
		Clamp(_val.w, _min.w, _max.w));
}
#pragma endregion

#pragma region Magnitude
inline float Magnitude(XMFLOAT2 _val)
{
	return sqrt(_val.x * _val.x + _val.y * _val.y);
}
inline float Magnitude(XMFLOAT3 _val)
{
	return sqrt(_val.x * _val.x + _val.y * _val.y + _val.z * _val.z);
}
inline float Magnitude(XMFLOAT4 _val)
{
	return sqrt(_val.x * _val.x + _val.y * _val.y + _val.z * _val.z + _val.w * _val.w);
}
#pragma endregion

#pragma region Normalize
inline XMFLOAT2 Normalize(XMFLOAT2 _val)
{
	return _val / Magnitude(_val);
}
inline XMFLOAT3 Normalize(XMFLOAT3 _val)
{
	return _val / Magnitude(_val);
}
inline XMFLOAT4 Normalize(XMFLOAT4 _val)
{
	return _val / Magnitude(_val);
}
#pragma endregion

#pragma region Lerp
inline XMFLOAT2 Lerp(XMFLOAT2 _a, XMFLOAT2 _b, float _t)
{
	return _a + (_b - _a) * _t;
}
inline XMFLOAT3 Lerp(XMFLOAT3 _a, XMFLOAT3 _b, float _t)
{
	return _a + (_b - _a) * _t;
}
inline XMFLOAT4 Lerp(XMFLOAT4 _a, XMFLOAT4 _b, float _t)
{
	return _a + (_b - _a) * _t;
}
#pragma endregion

inline bool PointInRect(XMFLOAT2 _pos, XMFLOAT2 _extends, XMFLOAT2 _point) 
{
	return (_point.x >= _pos.x && _point.x <= _pos.x + _extends.x)
		&& (_point.y >= _pos.y && _point.y <= _pos.y + _extends.y);
}

inline bool PointInRect(RECT _rect, XMFLOAT2 _point)
{
	return (_point.x >= _rect.left && _point.x <= _rect.right)
		&& (_point.y >= _rect.top && _point.y <= _rect.bottom);
}