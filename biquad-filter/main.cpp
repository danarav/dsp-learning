//
// Created by Daniel Ariaz-Avalos on 5/25/26.
//
#include <iostream>
#include "biquad.h"
#include <cmath>

double measureRMS(BiquadFilter& filter, double testFreq, double sampleRate, int numSamples)
{
    filter.reset();
    double sum = 0.0;
    for (int i = 0; i < numSamples; i++)
    {
        const double x = std::sin(2.0 * PI * testFreq / sampleRate * i);
        const double y = filter.processSample(x);
        sum += y * y;
    }
    return std::sqrt(sum / numSamples);
}

int main() {
    constexpr double sampleRate = 44100.0;
    constexpr int    numSamples = 4096;

    // --- Test 1: +12 dB boost at 1kHz, Q=1.0 ---
    {
        double freq = 1000.0, Q = 1.0, gain = 12.0;
        BiquadFilter filter;
        filter.setCoefficients(computePeakCoefficients(sampleRate, freq, gain, Q));

        double rms_at_1k   = measureRMS(filter, 1000.0, sampleRate, numSamples);
        double rms_at_100  = measureRMS(filter, 100.0,  sampleRate, numSamples);

        std::cout << "Test 1 — Peak +12 dB @ 1kHz, Q=1.0\n";
        std::cout << "  RMS at 1kHz  (should be boosted ~x4 (~2.828) ): " << rms_at_1k  << "\n";
        std::cout << "  RMS at 100Hz (should be ~0.707):       " << rms_at_100 << "\n\n";
    }

    // --- Test 2: -12 dB cut at 1kHz, Q=1.0 ---
    {
        double freq = 1000.0, Q = 1.0, gain = -12.0;
        BiquadFilter filter;
        filter.setCoefficients(computePeakCoefficients(sampleRate, freq, gain, Q));

        double rms_at_1k  = measureRMS(filter, 1000.0, sampleRate, numSamples);
        double rms_at_100 = measureRMS(filter, 100.0,  sampleRate, numSamples);

        std::cout << "Test 2 — Peak -12 dB @ 1kHz, Q=1.0\n";
        std::cout << "  RMS at 1kHz  (should be cut ~x0.25 (~0.177) ):  " << rms_at_1k  << "\n";
        std::cout << "  RMS at 100Hz (should be ~0.707):       " << rms_at_100 << "\n\n";
    }

    // --- Test 3: 0 dB gain (unity) — output should equal input ---
    {
        double freq = 1000.0, Q = 1.0, gain = 0.0;
        BiquadFilter filter;
        filter.setCoefficients(computePeakCoefficients(sampleRate, freq, gain, Q));

        double rms = measureRMS(filter, 1000.0, sampleRate, numSamples);
        std::cout << "Test 3 — Unity gain (0 dB)\n";
        std::cout << "  RMS at 1kHz  (should be ~0.707):       " << rms << "\n\n";
    }
    return 0;
}