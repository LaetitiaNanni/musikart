#pragma once
#include <iostream>

struct Point3D {
    float x, y, z;

    Point3D(); // constructeur par défaut
    Point3D(float x, float y, float z); // constructeur

    Point3D(const Point3D& other); // constructeur par copie
    Point3D& operator=(const Point3D& other);

    Point3D& operator*=(const float alpha);
    Point3D& operator+=(const Point3D& other);

    Point3D operator+(const Point3D& other) const;
    Point3D operator-(const Point3D& other) const;
    Point3D operator*(const float alpha) const;

    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
};


// Surcharge de l'opérateur << pour afficher le point
std::ostream& operator<<(std::ostream& out, const Point3D& point);

