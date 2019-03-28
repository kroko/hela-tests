#include "MrBlinnNucleus.hpp"

// ----------------------------------------------------------------------------
int main(int argc, char const * const argv[]) {

  // --------------------------------
  // Set spdlog level
  // Hela talks mostly at trace level. Those few debugs and infos might be helpful also for you.
  // Anyways assume that trace level is "reserved" for Hela.
  // Thus in your code use higher levels, otherwise by setting trace you will not see through that sea of logs.

  // "trace", "debug", "info", "warning", "error", "critical", "off"
  // set level
  spdlog::set_level(spdlog::level::trace);
  // spdlog::set_level(spdlog::level::info);

  // set formatting https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
  spdlog::set_pattern("[%L] %v");

  // --------------------------------

  #if defined(HELA_MSW)
    spdlog::debug("Entering application in main() instead of WinMain() to get console going.");
  #endif

  // --------------------------------
  // Do not touch ^_^
#if defined(HELA_LINUX_ARM_FBDEV_MALI_ALLWINNER)
  return hela::nucleus::NucleusLinuxFbdevMaliAllwinner::main<MrBlinn>(argc, argv, &MrBlinn::prepareNucleus, &MrBlinn::prepareMotor);
#else
  return hela::nucleus::NucleusGenericOs::main<MrBlinn>(argc, argv, &MrBlinn::prepareNucleus, &MrBlinn::prepareMotor);
#endif

}
