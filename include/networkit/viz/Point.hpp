/*
 * Point.h
 *
 *  Created on: Apr 11, 2013
 *      Author: Henning
 */

#ifndef NETWORKIT_VIZ_POINT_HPP_
#define NETWORKIT_VIZ_POINT_HPP_

#include <vector>
#include <cassert>
#include <cmath>
#include <string>

#include <networkit/Globals.hpp>

namespace NetworKit {

/**
 * @ingroup viz
 *
 * Formerly marked as deprecated:
 * To take advantage of automatic mapping between C++ and Python data structures, use
 * standard library containers (std::pair, std::tuple..) instead.
 *
 * DEPRECATION removed since suggested solution does not work when dimension is not known
 * at compile time.
 *
 * Points in any dimension of templated type.
 */
template<class T>
class Point {
protected:
    std::vector<T> data;

public:
    Point() { data = {0.0, 0.0}; }
    Point(T x, T y) { data = {x, y}; }
    Point(count dimension) : data(std::vector<T>(dimension, 0.0)) {}
    Point(std::vector<T>& values): data(values) {}
    virtual ~Point() {}

    count getDimensions() const { return data.size(); }

    T distance(const Point<T>& p) const;
    T squaredDistance(const Point<T>& p) const;

    Point& operator+=(const Point<T>& p);
    Point& operator-=(const Point<T>& p);
    Point& scale(const T factor);

    Point operator-(const Point<T>& other);
    Point operator+(const Point<T>& other);

    Point operator*(const double scalar) const;

    bool operator==(const Point<T>& other) const;
    bool operator!=(const Point<T>& other) const;

    Point<T>& operator=(const Point<T>& other) = default;

    T length() const;
    T squaredLength() const;

    T& operator[](const index i);
    T& at(const index i);

    T operator[](const index i) const;
    T at(const index i) const;

    /**
     * Default point to string conversion.
     */
    std::string toString();

    /**
     * Point to comma separated string.
     */
    std::string toCsvString();

    /**
     * Point to space separated string.
     */
    std::string toSsvString();

    std::string genericToString(const std::string& start, const std::string& sep, const std::string& end);

};

template<class T>
T Point<T>::length() const {
    T length = (T) 0;
    for (index i = 0; i < data.size(); ++i) {
        T diff = this->data[i];
        length += diff * diff;
    }
    return sqrt(length);
}

template<class T>
T Point<T>::squaredLength() const {
    T length = (T) 0;
    for (index i = 0; i < data.size(); ++i) {
        T diff = this->data[i];
        length += diff * diff;
    }
    return length;
}

template<class T>
T Point<T>::squaredDistance(const Point<T>& p) const {
    assert(this->data.size() == p.data.size());
    T dist = (T) 0;
    for (index i = 0; i < data.size(); ++i) {
        T diff = this->data[i] - p.data[i];
        dist += diff * diff;
    }
    return dist;
}

template<class T>
T Point<T>::distance(const Point<T>& p) const {
    return sqrt(squaredDistance(p));
}

template<class T>
Point<T>& Point<T>::operator+=(const Point<T>& p) {
    assert(this->data.size() == p.data.size());
    for (index i = 0; i < data.size(); ++i) {
        this->data[i] += p.data[i];
    }
    return *this;
}

template<class T>
Point<T>& Point<T>::operator-=(const Point<T>& p) {
    assert(this->data.size() == p.data.size());
    for (index i = 0; i < data.size(); ++i) {
        this->data[i] -= p.data[i];
    }
    return *this;
}

template<class T>
Point<T> Point<T>::operator-(const Point<T>& other) {
    Point<T> result(*this);
    assert(result.data.size() == other.data.size());
    for (index i = 0; i < result.data.size(); ++i) {
        result.data[i] -= other.data[i];
    }
    return result;
}

template<class T>
Point<T> Point<T>::operator+(const Point<T>& other) {
    Point<T> result(*this);
    assert(result.data.size() == other.data.size());
    for (index i = 0; i < result.data.size(); ++i) {
        result.data[i] += other.data[i];
    }
    return result;
}

template<typename T>
Point<T> Point<T>::operator*(const double scalar) const {
    Point<T> result(*this);
    for (index i = 0; i < getDimensions(); ++i) {
        result.data[i] = data[i] * scalar;
    }

    return result;
}

template<typename T>
bool Point<T>::operator==(const Point<T>& other) const {
    if (getDimensions() != other.getDimensions()) return false;
    for (index i = 0; i < data.size(); ++i) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

template<typename T>
bool Point<T>::operator!=(const Point<T>& other) const {
    return !(*this == other);
}

template<class T>
Point<T>& Point<T>::scale(const T factor) {
    for (index i = 0; i < data.size(); ++i) {
        this->data[i] *= factor;
    }
    return *this;
}

template<class T>
inline T& Point<T>::operator [](index i) {
    assert(i >= 0 && i < data.size());
    return data[i];
}

template<class T>
inline T& Point<T>::at(index i) {
    assert(i >= 0 && i < data.size());
    return data[i];
}

template<class T>
inline T Point<T>::operator [](index i) const {
    assert(i >= 0 && i < data.size());
    return data[i];
}

template<class T>
inline T Point<T>::at(index i) const {
    assert(i >= 0 && i < data.size());
    return data[i];
}

template<class T>
std::string Point<T>::toString() {
    return genericToString("", ", ", "");
}

template<class T>
inline std::string Point<T>::toCsvString() {
    return genericToString("(", ", ", ")");
}

template<class T>
inline std::string Point<T>::toSsvString() {
    return genericToString("", " ", "");
}

template<class T>
inline std::string Point<T>::genericToString(
        const std::string& start, const std::string& sep,
        const std::string& end)
{
    assert(this->data.size() > 0);

    std::string res = start;

    res += std::to_string((*this)[0]);
    for (index i = 1; i < this->data.size(); ++i) {
        res += sep;
        res += std::to_string(this->data[i]);
    }

    res += end;
    return res;
}

} /* namespace NetworKit */

#endif // NETWORKIT_VIZ_POINT_HPP_
