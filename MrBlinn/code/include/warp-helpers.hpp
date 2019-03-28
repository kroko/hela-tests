#ifndef warp_helpers_hpp
#define warp_helpers_hpp

#include <vector>

namespace warp { namespace helpers {

  template <typename oT = float, typename iT>
  oT normalizeFromRange(iT v, iT rangeMin, iT rangeMax) {
    return static_cast<oT>(v - rangeMin) / static_cast<oT>(rangeMax - rangeMin);
  }

  template <typename T>
  std::size_t sizeofVector(std::vector<T>& v) {
    if (v.empty()) return 0;
    return v.size() * sizeof(decltype(v.back())); // sizeof(decltype(v)::value_type);
  }

} }

#endif // warp_helpers_hpp

