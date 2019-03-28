#ifndef warp_materials_hpp
#define warp_materials_hpp

namespace warp { namespace materials {

  struct TexturePackBlinn_t {
    int prefUnit;
    int base;
    int normal;
    int rough;
    int disp;
    int ao;
    TexturePackBlinn_t():
    base(-1),
    normal(-1),
    rough(-1),
    disp(-1),
    ao(-1)
    {
    }
  };

} }

#endif // warp_materials_hpp
