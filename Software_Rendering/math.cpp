#include "math.h"

const float PI = 3.141592f;

Vector2::Vector2()
{
    x = 0;
    y = 0;
}
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector2 Vector2::operator+(const Vector2 &v)
{
    return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator-(const Vector2 &v)
{
    return Vector2(x - v.x, y - v.y);
}
float Vector2::Dot(Vector2& v)
{
    return (x * v.x + y * v.y);
}

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}
Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vector3 Vector3::operator+(const Vector3 &v)
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3 &v)
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}
Vector3 Vector3::operator+=(const Vector3 &v)
{
    *this = *this + v;
    return *this;
}
Vector3 Vector3::operator-=(const Vector3 &v)
{
    *this = *this - v;
    return *this;
}
Vector3 Vector3::operator*(float other)
{
    return Vector3(x * other,y * other,z * other);
}
Vector3 Vector3::operator*(const Vector3& v)
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}
Vector3 Vector3::Reverse()
{
    return Vector3(-x,-y,-z);
}
float Vector3::Dot(Vector3& v)
{
    return x * v.x + y * v.y + z * v.z;
}
Vector3 Vector3::Cross(Vector3& v)
{
    return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
Vector3 Vector3::Normalize()
{
    float length = sqrt((pow(x,2) + pow(y, 2) + pow(z,2)));
    return Vector3(x / length,y / length,z / length); 
}
Vector3 Vector3::Reflect(Vector3& v)
{
    return *this - (v * 2 * (this->Dot(v)));
}
Vector4::Vector4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
Vector4::Vector4(Vector3 v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = 1;
}
Vector4::Vector4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
Vector4 Vector4::operator+(const Vector4 &v)
{
    return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
Vector4 Vector4::operator-(const Vector4 &v)
{
    return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
float Vector4::Dot(Vector4& v)
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

Matrix4x4::Matrix4x4()
{
    this->M11 = 0, this->M12 = 0, this->M13 = 0, this->M14 = 0;
    this->M21 = 0, this->M22 = 0, this->M23 = 0, this->M24 = 0;
    this->M31 = 0, this->M32 = 0, this->M33 = 0, this->M34 = 0;
    this->M41 = 0, this->M42 = 0, this->M43 = 0, this->M44 = 0;
}
Matrix4x4::Matrix4x4(float M11, float M12, float M13, float M14,
	float M21, float M22, float M23, float M24,
	float M31, float M32, float M33, float M34,
	float M41, float M42, float M43, float M44)
{
	this->M11 = M11, this->M12 = M12, this->M13 = M13, this->M14 = M14;
	this->M21 = M21, this->M22 = M22, this->M23 = M23, this->M24 = M24;
	this->M31 = M31, this->M32 = M32, this->M33 = M33, this->M34 = M34;
    this->M41 = M41, this->M42 = M42, this->M43 = M43, this->M44 = M44;
}
Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &m)
{
	Matrix4x4 ret;
	ret.M11 = M11 + m.M11; ret.M12 = M12 + m.M12; ret.M13 = M13 + m.M13; ret.M14 = M14 + m.M14;
	ret.M21 = M21 + m.M21; ret.M22 = M22 + m.M22; ret.M23 = M23 + m.M23; ret.M24 = M24 + m.M24;
	ret.M31 = M31 + m.M31; ret.M32 = M32 + m.M32; ret.M33 = M33 + m.M33; ret.M34 = M34 + m.M34;
	ret.M41 = M41 + m.M41; ret.M42 = M42 + m.M42; ret.M43 = M43 + m.M43; ret.M44 = M44 + m.M44;
    return ret;
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &m)
{
	Matrix4x4 ret;
	ret.M11 = M11 - m.M11; ret.M12 = M12 - m.M12; ret.M13 = M13 - m.M13; ret.M14 = M14 - m.M14;
	ret.M21 = M21 - m.M21; ret.M22 = M22 - m.M22; ret.M23 = M23 - m.M23; ret.M24 = M24 - m.M24;
	ret.M31 = M31 - m.M31; ret.M32 = M32 - m.M32; ret.M33 = M33 - m.M33; ret.M34 = M34 - m.M34;
	ret.M41 = M41 - m.M41; ret.M42 = M42 - m.M42; ret.M43 = M43 - m.M43; ret.M44 = M44 - m.M44;
    return ret;
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4 m)
{
    return Multiply(m);
}
Matrix4x4 Matrix4x4::Multiply(Matrix4x4 m)
{
	//c ij = a i1 * b 1j + a i2 * b 2j...... 
    Matrix4x4 ret;
    ret.M11 = M11 * m.M11 + M12 * m.M21 + M13 * m.M31 + M14 * m.M41; ret.M12 = M11 * m.M12 + M12 * m.M22 + M13 * m.M32 + M14 * m.M42;
    ret.M13 = M11 * m.M13 + M12 * m.M23 + M13 * m.M33 + M14 * m.M43; ret.M14 = M11 * m.M14 + M12 * m.M24 + M13 * m.M34 + M14 * m.M44;


    ret.M21 = M21 * m.M11 + M22 * m.M21 + M23 * m.M31 + M24 * m.M41; ret.M22 = M21 * m.M12 + M22 * m.M22 + M23 * m.M32 + M24 * m.M42;
    ret.M23 = M21 * m.M13 + M22 * m.M23 + M23 * m.M33 + M24 * m.M43; ret.M24 = M21 * m.M14 + M22 * m.M24 + M23 * m.M34 + M24 * m.M44;

    ret.M31 = M31 * m.M11 + M32 * m.M21 + M33 * m.M31 + M34 * m.M41; ret.M32 = M31 * m.M12 + M32 * m.M22 + M33 * m.M32 + M34 * m.M42;
    ret.M33 = M31 * m.M13 + M32 * m.M23 + M33 * m.M33 + M34 * m.M43; ret.M34 = M31 * m.M14 + M32 * m.M24 + M33 * m.M34 + M34 * m.M44;

    ret.M41 = M41 * m.M11 + M42 * m.M21 + M43 * m.M31 + M44 * m.M41; ret.M42 = M41 * m.M12 + M42 * m.M22 + M43 * m.M32 + M44 * m.M42;
    ret.M43 = M41 * m.M13 + M42 * m.M23 + M43 * m.M33 + M44 * m.M43; ret.M44 = M41 * m.M14 + M42 * m.M24 + M43 * m.M34 + M44 * m.M44;
    return ret;
}
Vector4 Matrix4x4::operator*(const Vector4 &v)
{
    float x = M11 * v.x + M12 * v.y + M13 * v.z + M14 * v.w;
    float y = M21 * v.x + M22 * v.y + M23 * v.z + M24 * v.w;
    float z = M31 * v.x + M32 * v.y + M33 * v.z + M34 * v.w;
    float w = M41 * v.x + M42 * v.y + M43 * v.z + M44 * v.w;
    return Vector4(x, y, z, w);
}
Matrix4x4 Matrix4x4::Inverse()
{
    Matrix4x4 ret;
    float a =  M11, b =  M12, c =  M13, d =  M14;
    float e =  M21, f =  M22, g =  M23, h =  M24;
    float i =  M31, j =  M32, k =  M33, l =  M34;
    float m =  M41, n =  M42, o =  M43, p =  M44;

    float kp_lo = k * p - l * o;
    float jp_ln = j * p - l * n;
    float jo_kn = j * o - k * n;
    float ip_lm = i * p - l * m;
    float io_km = i * o - k * m;
    float in_jm = i * n - j * m;

    float a11 = +(f * kp_lo - g * jp_ln + h * jo_kn);
    float a12 = -(e * kp_lo - g * ip_lm + h * io_km);
    float a13 = +(e * jp_ln - f * ip_lm + h * in_jm);
    float a14 = -(e * jo_kn - f * io_km + g * in_jm);

    float det = a * a11 + b * a12 + c * a13 + d * a14;

    float invDet = 1.0f / det;

    ret.M11 = a11 * invDet;
    ret.M21 = a12 * invDet;
    ret.M31 = a13 * invDet;
    ret.M41 = a14 * invDet;

    ret.M12 = -(b * kp_lo - c * jp_ln + d * jo_kn) * invDet;
    ret.M22 = +(a * kp_lo - c * ip_lm + d * io_km) * invDet;
    ret.M32 = -(a * jp_ln - b * ip_lm + d * in_jm) * invDet;
    ret.M42 = +(a * jo_kn - b * io_km + c * in_jm) * invDet;

    float gp_ho = g * p - h * o;
    float fp_hn = f * p - h * n;
    float fo_gn = f * o - g * n;
    float ep_hm = e * p - h * m;
    float eo_gm = e * o - g * m;
    float en_fm = e * n - f * m;

    ret.M13 = +(b * gp_ho - c * fp_hn + d * fo_gn) * invDet;
    ret.M23 = -(a * gp_ho - c * ep_hm + d * eo_gm) * invDet;
    ret.M33 = +(a * fp_hn - b * ep_hm + d * en_fm) * invDet;
    ret.M43 = -(a * fo_gn - b * eo_gm + c * en_fm) * invDet;

    float gl_hk = g * l - h * k;
    float fl_hj = f * l - h * j;
    float fk_gj = f * k - g * j;
    float el_hi = e * l - h * i;
    float ek_gi = e * k - g * i;
    float ej_fi = e * j - f * i;

    ret.M14 = -(b * gl_hk - c * fl_hj + d * fk_gj) * invDet;
    ret.M24 = +(a * gl_hk - c * el_hi + d * ek_gi) * invDet;
    ret.M34 = -(a * fl_hj - b * el_hi + d * ej_fi) * invDet;
    ret.M44 = +(a * fk_gj - b * ek_gi + c * ej_fi) * invDet;
    return ret;
}
Matrix4x4 Matrix4x4::Translate(Vector3 position)
{
    Matrix4x4 ret;
    ret.M11 = 1; ret.M12 = 0; ret.M13 = 0; ret.M14 = position.x;
    ret.M21 = 0; ret.M22 = 1; ret.M23 = 0; ret.M24 = position.y;
    ret.M31 = 0; ret.M32 = 0; ret.M33 = 1; ret.M34 = position.z;
    ret.M41 = 0; ret.M42 = 0; ret.M43 = 0; ret.M44 = 1;
    return ret;
}
Matrix4x4 Matrix4x4::RotationX(float angle)
{
    float radian = angle / 180 * PI;
    float s = sinf(radian);
    float c = cosf(radian);
    Matrix4x4 ret;
    ret.M11 = 1; ret.M12 = 0; ret.M13 = 0;  ret.M14 = 0;
    ret.M21 = 0; ret.M22 = c; ret.M23 = -s; ret.M24 = 0;
    ret.M31 = 0; ret.M32 = s; ret.M33 = c;  ret.M34 = 0;
    ret.M41 = 0; ret.M42 = 0; ret.M43 = 0;  ret.M44 = 1;
    return ret;
}
Matrix4x4 Matrix4x4::RotationY(float angle)
{
    float radian = angle / 180 * PI;
    float s = sinf(radian);
    float c = cosf(radian);
    Matrix4x4 ret;
    ret.M11 = c; ret.M12 = 0; ret.M13 = s; ret.M14 = 0;
    ret.M21 = 0; ret.M22 = 1; ret.M23 = 0; ret.M24 = 0;
    ret.M31 = -s; ret.M32 = 0; ret.M33 = c; ret.M34 = 0;
    ret.M41 = 0; ret.M42 = 0; ret.M43 = 0; ret.M44 = 1;
    return ret;
}
Matrix4x4 Matrix4x4::RotationZ(float angle)
{
    float radian = angle / 180 * PI;
    float s = sinf(radian);
    float c = cosf(radian);
    Matrix4x4 ret;
    ret.M11 = c; ret.M12 = -s; ret.M13 = 0; ret.M14 = 0;
    ret.M21 = s; ret.M22 = c; ret.M23 = 0; ret.M24 = 0;
    ret.M31 = 0; ret.M32 = 0; ret.M33 = 1; ret.M34 = 0;
    ret.M41 = 0; ret.M42 = 0; ret.M43 = 0; ret.M44 = 1;
    return ret;
}
Matrix4x4 Matrix4x4::Rotation(Vector3 rotation)
{
    Matrix4x4 x = RotationX(rotation.x);
    Matrix4x4 y = RotationY(rotation.y);
    Matrix4x4 z = RotationZ(rotation.z);
    Matrix4x4 ret = x * y * z;
    return ret;
}
Matrix4x4 Matrix4x4::Scale(Vector3 scale)
{
    Matrix4x4 ret;
    ret.M11 = scale.x; ret.M12 = 0; ret.M13 = 0; ret.M14 = 0;
    ret.M21 = 0; ret.M22 = scale.y; ret.M23 = 0; ret.M24 = 0;
    ret.M31 = 0; ret.M32 = 0; ret.M33 = scale.z; ret.M34 = 0;
    ret.M41 = 0; ret.M42 = 0; ret.M43 = 0; ret.M44 = 1;
    return ret;
}
Matrix4x4 Matrix4x4::GetModelMatrix(Vector3 scale, Vector3 rotation, Vector3 position)
{
    Matrix4x4 ret;
    Matrix4x4 scaleMatrix = Matrix4x4::Scale(scale);
    Matrix4x4 rotationMatrix = Matrix4x4::Rotation(rotation);
    Matrix4x4 translateMatrix = Matrix4x4::Translate(position);
    ret = translateMatrix * rotationMatrix * scaleMatrix;
    return ret;
}

Index::Index()
{
    _1 = 0;
    _2 = 0;
    _3 = 0;
}
Index::Index(unsigned int _1, unsigned int _2, unsigned int _3)
{
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
}