//
// Created by Daniel Ariaz-Avalos on 6/2/26.
//

#include <iostream>
#include <cmath>
#include <vector>

constexpr double PI{3.14159265358979323846};

constexpr double SAMPLE_RATE{44100.0};
constexpr double FREQUENCY{440.0};
constexpr double AMPLITUDE{0.5};
constexpr double DURATION{1.0};

int main() {
    constexpr int NUM_SAMPLES {static_cast<int>(SAMPLE_RATE * DURATION)};
    std::vector<double> samples(NUM_SAMPLES);

    constexpr double PHASE_INCREMENT{(2.0 * PI * FREQUENCY) / SAMPLE_RATE};
    double phase{0.0};

    for (int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = AMPLITUDE * std::sin(phase);

        phase += PHASE_INCREMENT;

        if (phase >= 2.0 * PI) {
            phase -= 2.0 * PI;
        }
    }

    std::cout << "Sample Rate : " << SAMPLE_RATE << " Hz\n";
    std::cout << "Frequency   : " << FREQUENCY << " Hz\n";
    std::cout << "Amplitude   : " << AMPLITUDE << "\n";
    std::cout << "Total samples: " << NUM_SAMPLES << "\n\n";

    for (int i = 0; i < 100; i++) {
        std::cout << "sample[" << i << "] = " << samples[i] << "\n";
    }

    return 0;
}