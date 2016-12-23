#ifndef ESSENTIA_ATTACKTIME_H
#define ESSENTIA_ATTACKTIME_H

#include "algorithm.h"

namespace essentia {
namespace standard {

class AttackTime : public Algorithm {

 private:
  Real _startThreshold, _stopThreshold;
  Real _sampleRate;

  Input<std::vector<Real> > _signal;
  Output<Real> _attackTime;
  Output<Real> _attackStart;
  Output<Real> _attackStop;

 public:
  AttackTime() {
    declareInput(_signal, "signal", "the input signal envelope (must be non-empty)");
    declareOutput(_attackTime, "attackTime", "the log (base 10) of the attack time [log10(s)]");
    declareOutput(_attackStart, "attackStart", "the attack start time [s]");
    declareOutput(_attackStop, "attackStop", "the attack end time [s]");    
  }

  void declareParameters() {
    declareParameter("sampleRate", "the audio sampling rate [Hz]", "(0,inf)", 44100.);
    declareParameter("startAttackThreshold", "the percentage of the input signal envelope at which the starting point of the attack is considered", "[0,1]", 0.2);
    declareParameter("stopAttackThreshold", "the percentage of the input signal envelope at which the ending point of the attack is considered", "[0,1]", 0.9);
  }

  void configure();
  void compute();

  static const char* name;
  static const char* category;
  static const char* description;

};

} // namespace standard
} // namespace essentia

#include "streamingalgorithmwrapper.h"

namespace essentia {
namespace streaming {

class AttackTime : public StreamingAlgorithmWrapper {

 protected:
  Sink<std::vector<Real> > _signal;
  Source<Real> _attackTime;
  Source<Real> _attackStart;
  Source<Real> _attackStop;

 public:
  AttackTime() {
    declareAlgorithm("AttackTime");
    declareInput(_signal, TOKEN, "signal");
    declareOutput(_attackTime, TOKEN, "attackTime");
    declareOutput(_attackStart, TOKEN, "attackStart");
    declareOutput(_attackStop, TOKEN, "attackStop"); 
  }

};

} // namespace streaming
} // namespace essentia

#endif // ESSENTIA_LOGATTACKTIME_H
