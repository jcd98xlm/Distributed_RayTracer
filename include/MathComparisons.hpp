#ifndef __MATH_COMPARISONS_HPP__
#define __MATH_COMPARISONS_HPP__

#include <cmath>
#include <limits>
#include <float.h>

template <typename T>
bool almostEqual(T a, T b, T maxDiff, T maxRelDiff = std::numeric_limits<T>::epsilon())
{
    // Baseado em https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    // Verifica se os numeros sao bem proximos, necessario para comparacoes com numeros proximos a zero
    T diff = fabs(a - b);
    if(diff <= maxDiff)
        return true;
    
    a = fabs(a);
    b = fabs(b);
    T largest = (b > a) ? b : a;
    if( diff <= largest*maxRelDiff)
        return true;
    return false;
}

#endif