/* 
 * File:   matrix.h
 * Author: mohd
 *
 * Created on November 30, 2012, 7:18 PM
 */

#ifndef MATRIX_H
#define	MATRIX_H

// 2D vector
class Vec2D
{
public:
    Vec2D(double x, double y)
    {
        set(x, y);
    }
    void set(double x, double y){
        this->x=x;this->y=y;
    }
    Vec2D add(Vec2D v){
        return Vec2D(v.x+x, v.y+y);
    }
public:
    double x, y;
};

// 2x2 matrix
class MAT22
{
public:
    MAT22(double a1, double a2, double b1, double b2){
        set(a1, a2, b1, b2);
    }
    void set(double a1, double a2, double b1, double b2){
        this->a1=a1;this->a2=a2;
        this->b1=b1;this->b2=b2;
    }
    Vec2D mulVector(Vec2D vector){
        //  [ a1   a2 ]
        //  [ b1   b2 ]
        return Vec2D(vector.x*a1+vector.y*a2, b1*vector.x+b2*vector.y);
    }
public:
    double a1, a2, b1, b2;
};

#endif	/* MATRIX_H */

