//
// Created by Daniel Ariaz-Avalos on 5/25/26.
// A single biquad filter using Direct Form II Transposed (DF2T).
// Implementation of a peak (bell) filter using the RBJ Audio EQ Cookbook formulas.
//

#ifndef BIQUAD_H
#define BIQUAD_H

#include <cmath>

static constexpr double PI{3.14159265358979323846};

struct BiquadCoefficients {
    double b0{}, b1{}, b2{}; // feedforward coefficients
    double a1{}, a2{}; // feedback coefficients (in this implementation we will normalize a0 to be 1)
};

// Compute RBJ peak (bell) coefficients
// samplingFrequency - sample rate in Hz
// centerFrequency - center frequency in Hz
// dbGain - boost or cut in decibels (positive = boost, negative = cut)
// Q - bandwidth / resonance (typical range: 0.1 to 18.0)
inline BiquadCoefficients computePeakCoefficients(double samplingFrequency, double centerFrequency, double dbGain,
                                                  double Q) {
    const double A{std::pow(10.0, (dbGain / 40.0))};
    const double w0{2 * PI * (centerFrequency / samplingFrequency)};
    const double alpha{(std::sin(w0) / (2.0 * Q))};

    const double a0_inv{1.0 / (1.0 + (alpha / A))};

    return BiquadCoefficients{
        .b0 = (1.0 + (alpha * A)) * a0_inv,
        .b1 = (-2.0 * std::cos(w0)) * a0_inv,
        .b2 = (1.0 - (alpha * A)) * a0_inv,
        .a1 = (-2.0 * std::cos(w0)) * a0_inv,
        .a2 = (1.0 - (alpha / A)) * a0_inv
    };
}

struct BiquadFilter {
    BiquadCoefficients coefficients{};
    double z1{};
    double z2{};

    void setCoefficients(const BiquadCoefficients &newCoefficients) {
        coefficients = newCoefficients;
    }

    void reset() {
        z1 = 0.0;
        z2 = 0.0;
    }

    double processSample(double x) {
        const double y{coefficients.b0 * x +z1};
        z1 = coefficients.b1 * x - coefficients.a1* y + z2;
        z2 = coefficients.b2 * x - coefficients.a2 * y;
        return y;
    }
};

#endif //BIQUAD_H
