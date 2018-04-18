#ifndef __Test1_hpp__
#define __Test1_hpp__

#include "StompBox.h"

#define BUFSIZE (128 * 100)

class DougalTest : public Patch {

public:
    FloatArray delayBuffer;
    int bufferOffset;

  DougalTest() : bufferOffset(0) {
    registerParameter(PARAMETER_A, "Gain");
    registerParameter(PARAMETER_D, "Mix");

	delayBuffer = FloatArray::create(BUFSIZE);
  }

  void processAudio(AudioBuffer &buffer){

    FloatArray left = buffer.getSamples(LEFT_CHANNEL);

    float gain = getParameterValue(PARAMETER_A);
    float mix = getParameterValue(PARAMETER_D);
    int size = buffer.getSize();

    for (int i = 0; i < size; ++i) {
        float sample = left[i];

        left[i] = (sample * (1.0 - mix)) + (delayBuffer[bufferOffset % BUFSIZE] * mix);
        delayBuffer[bufferOffset % BUFSIZE] = left[i] * gain;
        bufferOffset = (bufferOffset + 1) % BUFSIZE;
    }
  }
};


#endif // __Test1_hpp__
