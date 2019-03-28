#ifndef warp_time_hpp
#define warp_time_hpp

#include <chrono>

// ============================================================================
// WARP the spacetime!
namespace warp {
  namespace time {

    // ============================================================================
    // simple structure to hold time values, make it separate for timer class
    // make float to be default
    template <typename T = float>
    struct TimeHolder_t {
      T curr;
      T prev;
      T delta;
      TimeHolder_t():
      curr(0.0f),
      prev(0.0f),
      delta(0.0f)
      {
      }
    };

    // ============================================================================
    // make float to be default
    template <class T = float>
    class Timer {

    public:
      Timer() : isStopped_(true) {
        timeStartSeconds_ = timeEndSeconds_ = -1;
      }

      Timer(bool startNow) : isStopped_(true) {
        timeEndSeconds_ = timeStartSeconds_ = -1;
        if( startNow ) {
          start();
        }
      }

      void start(T offsetSeconds = 0) {
        timeStartMilliseconds_ = ChronoGetEpochMilliseconds_();
        timeStartSeconds_ = ChronoGetEpochSeconds_() - offsetSeconds;
        isStopped_ = false;
      }

      T getSeconds() const {
        if( isStopped_ ) {
          return timeEndSeconds_ - timeStartSeconds_;
        } else {
          return ChronoGetEpochSeconds_() - timeStartSeconds_;
        }
      };

      void stop() {
        if( ! isStopped_ ) {
          timeEndSeconds_ = ChronoGetEpochSeconds_();
          isStopped_ = true;
        }
      }

      void resume() {
        start( getSeconds() );
      }

      bool isStopped() const {
        return isStopped_;
      }

    private:

      int64_t ChronoGetEpochMilliseconds_() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
      }

      int64_t ChronoGetStartMilliseconds_() const {
        return ChronoGetEpochMilliseconds_() - timeStartMilliseconds_;
      }

      T ChronoGetEpochSeconds_() const {
        return static_cast<T>(ChronoGetStartMilliseconds_()) / 1000.0f;
      }

      bool isStopped_;
      int64_t timeStartMilliseconds_;
      T timeStartSeconds_;
      T timeEndSeconds_;
    };

  } // namespace time
} // namespace warp

#endif // warp_time_hpp


