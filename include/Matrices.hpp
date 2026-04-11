#ifndef __MATRICES_HPP__
#define __MATRICES_HPP__

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Vectors.hpp"

template <typename T>
class Mat44
{
    public:
        Mat44() {}
        Mat44(const Mat44<T> &inputMat) {}
        Mat44(T a, T b, T c, T d, T e, T f, T g, T h, T i, T j, T k, T l, T m, T n, T o, T p)
        {
            m[0][0] = a;
            m[0][1] = b;
            m[0][2] = c;
            m[0][3] = d;
            m[1][0] = e;
            m[1][1] = f;
            m[1][2] = g;
            m[1][3] = h;
            m[2][0] = i;
            m[2][1] = j;
            m[2][2] = k;
            m[2][3] = l;
            m[3][0] = m;
            m[3][1] = n;
            m[3][2] = o;
            m[3][3] = p;
        }

        const T* operator [] (uint8_t i) const
        {
            return m[i];
        }
        T* operator [] (uint8_t i)
        {
            return m[i];
        }
        Mat44<T> operator + (const Mat44<T> &rhs)
        {
            Mat44<T> result;
            for(unsigned int i=0; i<4; i++)
            {
                for(unsigned int j=0; j<4; j++)
                    result[i][j] = m[i][j] + rhs[i][j];
            }
            return result;
        }
        Mat44<T> operator * (const Mat44<T> &rhs)
        {
            Mat44<T> result;
            for(unsigned int i=0; i<4; i++)
            {
                for(unsigned int j=0; j<4; j++)
                    result[i][j] = m[i][0]*rhs[0][j] + m[i][1]*rhs[1][j] + m[i][2]*rhs[2][j] + m[i][3]*rhs[3][j];
            }
            return result;
        }
        Vec4<T> operator * (const Vec4<T> &rhs)
        {
            T x,y,z,w;
            x = m[0][0]*rhs[0] + m[0][1]*rhs[1] + m[0][2]*rhs[2] + m[0][3]*rhs[3];
            y = m[1][0]*rhs[0] + m[1][1]*rhs[1] + m[1][2]*rhs[2] + m[1][3]*rhs[3];
            z = m[2][0]*rhs[0] + m[2][1]*rhs[1] + m[2][2]*rhs[2] + m[2][3]*rhs[3];
            w = m[3][0]*rhs[0] + m[3][1]*rhs[1] + m[3][2]*rhs[2] + m[3][3]*rhs[3];
            return Vec4<T>(x,y,z,w);
        }
        Mat44<T> operator = (const Mat44<T> &rhs)
        {
            if(this != &rhs)
            {
                for(unsigned int i=0; i<4; i++)
                {
                    for(unsigned int j=0; j<4; j++)
                        this->m[i][j] = rhs[i][j];
                }
            }
            return *this;
        }
        Mat44<T> transposed() const
        {
            return Mat44<T> (m[0][0], m[1][0], m[2][0], m[3][0], 
                             m[0][1], m[1][1], m[2][1], m[3][1],
                             m[0][2], m[1][2], m[2][2], m[3][2],
                             m[0][3], m[1][3], m[2][3], m[3][3]);
        }
        Mat44<T>& transpose()
        {
            T temp;
            for(unsigned int i=0; i<4; i++)
            {
                for(unsigned int j=i+1; j<4; j++)
                {
                    temp = m[i][j];
                    m[i][j] = m[j][i];
                    m[j][i] = temp;
                }
            }
            return *this;
        }
        Mat44<T> inverse() const
        {
            Mat44<T> s;
            
            double s0,s1,s2,s3,s4,s5;
            double c0,c1,c2,c3,c4,c5;
            double inverseDet;
            s0 = m[0][0]*m[1][1] - m[1][0]*m[0][1];
            s1 = m[0][0]*m[1][2] - m[1][0]*m[0][2];
            s2 = m[0][0]*m[1][3] - m[1][0]*m[0][3];
            s3 = m[0][1]*m[1][2] - m[1][1]*m[0][2];
            s4 = m[0][1]*m[1][3] - m[1][1]*m[0][3];
            s5 = m[0][2]*m[1][3] - m[1][2]*m[0][3];

            c0 = m[2][0]*m[3][1] - m[3][0]*m[2][1];
            c1 = m[2][0]*m[3][2] - m[3][0]*m[2][2];
            c2 = m[2][0]*m[3][3] - m[3][0]*m[2][3];
            c3 = m[2][1]*m[3][2] - m[3][1]*m[2][2];
            c4 = m[2][1]*m[3][3] - m[3][1]*m[2][3];
            c5 = m[2][2]*m[3][3] - m[3][2]*m[2][3];

            inverseDet = 1.0/(s0*c5 - s1*c4 + s2*c3 + s3*c2 - s4*c1 + s5*c0);

            s[0][0] = ( m[1][1]*c5 - m[1][2]*c4 + m[1][3]*c3)*inverseDet;
            s[0][1] = (-m[0][1]*c5 + m[0][2]*c4 - m[0][3]*c3)*inverseDet;
            s[0][2] = ( m[3][1]*s5 - m[3][2]*s4 + m[3][3]*s3)*inverseDet;
            s[0][3] = (-m[2][1]*s5 + m[2][2]*s4 - m[2][3]*s3)*inverseDet;

            s[1][0] = (-m[1][0]*c5 + m[1][2]*c2 - m[1][3]*c1)*inverseDet;
            s[1][1] = ( m[0][0]*c5 - m[0][2]*c2 + m[0][3]*c1)*inverseDet;
            s[1][2] = (-m[3][0]*s5 + m[3][2]*s2 - m[3][3]*s1)*inverseDet;
            s[1][3] = ( m[2][0]*s5 - m[2][2]*s2 + m[2][3]*s1)*inverseDet;

            s[2][0] = ( m[1][0]*c4 - m[1][1]*c2 + m[1][3]*c0)*inverseDet;
            s[2][1] = (-m[0][0]*c4 + m[0][1]*c2 - m[0][3]*c0)*inverseDet;
            s[2][2] = ( m[3][0]*s4 - m[3][1]*s2 + m[3][3]*s0)*inverseDet;
            s[2][3] = (-m[2][0]*s4 + m[2][1]*s2 - m[2][3]*s0)*inverseDet;

            s[3][0] = (-m[1][0]*c3 + m[1][1]*c1 - m[1][2]*c0)*inverseDet;
            s[3][1] = ( m[0][0]*c3 - m[0][1]*c1 + m[0][2]*c0)*inverseDet;
            s[3][2] = (-m[3][0]*s3 + m[3][1]*s1 - m[3][2]*s0)*inverseDet;
            s[3][3] = ( m[2][0]*s3 - m[2][1]*s1 + m[2][2]*s0)*inverseDet;
            
            return s;
        }
        const Mat44<T>& invert()
        {
            *this = this->inverse();
            return *this;
        }
        friend std::ostream& operator << (std::ostream &s, const Mat44<T> &mat)
        {
            std::ios_base::fmtflags oldFlags = s.flags();
            int width = 12; // total width of the displayed number
            s.precision(5); // control the number of displayed decimals
            s.setf (std::ios_base::fixed);
            
            s << "[" << std::setw (width) << mat[0][0] <<
                " " << std::setw (width) << mat[0][1] <<
                " " << std::setw (width) << mat[0][2] <<
                " " << std::setw (width) << mat[0][3] << "\n" <<
                
                " " << std::setw (width) << mat[1][0] <<
                " " << std::setw (width) << mat[1][1] <<
                " " << std::setw (width) << mat[1][2] <<
                " " << std::setw (width) << mat[1][3] << "\n" <<
                
                " " << std::setw (width) << mat[2][0] <<
                " " << std::setw (width) << mat[2][1] <<
                " " << std::setw (width) << mat[2][2] <<
                " " << std::setw (width) << mat[2][3] << "\n" <<
                
                " " << std::setw (width) << mat[3][0] <<
                " " << std::setw (width) << mat[3][1] <<
                " " << std::setw (width) << mat[3][2] <<
                " " << std::setw (width) << mat[3][3] << "]";
            
            s.flags (oldFlags);
            return s;
        }
    
    public:
        T m[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
};

typedef Mat44<float> Mat44f;

#endif