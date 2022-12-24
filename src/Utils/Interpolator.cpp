#include "Interpolator.hpp"

float Interpolator::powerInOut(float t, float a) {
    float tt = max(0.f, min(t, 1.f));
    if (tt < 0.5) {
      return pow(tt * 2, a) * 0.5;
    } else {
      return 1.0 - pow((1 - tt) * 2, a) * 0.5;
    }
}
