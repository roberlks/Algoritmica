#include <cmath>
#include <vector>
#include "City.h"

typedef long long ll;
typedef long double ld;

struct Edge
{
    City A, B;
    Edge() {}
    Edge(City _A, City _B) : A(_A), B(_B) {}

    friend bool operator<(const Edge &e1, const Edge &e2) {
	return ((e1.A - e1.B)<(e2.A - e2.B));
    }
};

