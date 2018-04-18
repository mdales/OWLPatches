#ifndef __Test1_hpp__
#define __Test1_hpp__

#include "StompBox.h"

#define BUFSIZE (128 * 200)

class DougalTest : public Patch {

public:
    FloatArray delayBuffer;
    int bufferOffset;

  DougalTest() : bufferOffset(0) {
    registerParameter(PARAMETER_A, "Delay");
    registerParameter(PARAMETER_B, "Gain");
    registerParameter(PARAMETER_C, "HeadMix");
    registerParameter(PARAMETER_D, "Mix");

	delayBuffer = FloatArray::create(BUFSIZE);
  }

  void processAudio(AudioBuffer &buffer){

    FloatArray left = buffer.getSamples(LEFT_CHANNEL);

    float delay = getParameterValue(PARAMETER_A);
    float gain = getParameterValue(PARAMETER_B);
    float headmix = getParameterValue(PARAMETER_C);
    float mix = getParameterValue(PARAMETER_D);
    int size = buffer.getSize();

    int delaySize = (0.5 + (delay * 0.5)) * BUFSIZE;

    for (int i = 0; i < size; ++i) {
        float sample = left[i];

        left[i] = (sample * (1.0 - mix)) + (delayBuffer[bufferOffset] * mix);
        delayBuffer[bufferOffset] = ((sample * (1 - headmix)) + (left[i] * headmix)) * gain;
        bufferOffset = (bufferOffset + 1) % delaySize;
    }
  }
};


#endif // __Test1_hpp__
