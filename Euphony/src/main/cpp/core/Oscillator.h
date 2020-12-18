//
// Created by designe on 20. 8. 25.
//

#ifndef EUPHONY_OSCILLATOR_H
#define EUPHONY_OSCILLATOR_H

#include <cstdint>
#include <atomic>
#include <math.h>
#include <memory>
#include <vector>
#include <IRenderableAudio.h>

constexpr int32_t kDefaultSampleRate = 48000;
constexpr double kPi = M_PI;
constexpr double kTwoPi = kPi * 2.0;

namespace Euphony {
    class Oscillator : public IRenderableAudio {
    public:
        ~Oscillator() = default;

        void setWaveOn(bool isWaveOn);

        void setSampleRate(int32_t sampleRate);

        void setFrequency(double frequency);

        inline void setAmplitude(float amplitude) {
            mAmplitude = amplitude;
        }

        // From IRenderableAudio
        void renderAudio(float *data, int32_t numFrames);

        static double getPhaseIncrement(double frequency){
            return ((kTwoPi * frequency) / static_cast<double> (kDefaultSampleRate));
        }

        static std::unique_ptr<float[]> makeStaticWave(int freq, int waveLength) {
            std::unique_ptr<float[]> source = std::make_unique<float[]>(waveLength);

            double phase = 0.0;
            double phaseIncrement = Euphony::Oscillator::getPhaseIncrement(freq);
            for(int i = 0; i < waveLength; i++) {
                source[i] = sin(phase);
                phase += phaseIncrement;
                if(phase > kTwoPi) phase -= kTwoPi;
            }

            return std::unique_ptr<float[]>();
        }


    private:
        std::atomic<bool> mIsFirstWave{false};
        std::atomic<bool> mIsLastWave{false};
        std::atomic<bool> mIsWaveOn{false};
        float mPhase = 0.0;
        std::atomic<float> mAmplitude{0};
        std::atomic<double> mPhaseIncrement{0.0};
        double mFrequency = 0.0;
        std::vector<double> mTimeArray;
        int32_t mSampleRate = kDefaultSampleRate;

        void updatePhaseIncrement() {
            mPhaseIncrement.store((kTwoPi * mFrequency) / static_cast<double>(mSampleRate));
        }
    };
}

#endif //EUPHONY_OSCILLATOR_H