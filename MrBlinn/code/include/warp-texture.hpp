#ifndef warp_texture_hpp
#define warp_texture_hpp

#include <random>


#define stb_lib // make fake namespace-like marker for stb to differentiate global stuff easier

// #define STBI_HEADER_FILE_ONLY
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// #define STB_IMAGE_RESIZE_IMPLEMENTATION
// #include <stb/stb_image_resize.h>

// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include <stb/stb_image_write.h>

#define WARP_TEXTURE_STBI_FLIP 1

//#if !defined(GL_SRGB)
//  #define GL_SRGB GL_RGB
//#endif
//
//#if !defined(GL_SRGB_ALPHA)
//  #define GL_SRGB_ALPHA GL_RGBA
//#endif

#if !defined(GL_SRGB)
  #define WARP_TEXTURE_MANUAL_GL_SRGB // assume that no GL_SRGB also means no GL_SRGB_ALPHA
#endif

namespace warp {
  namespace texture {

    // ----------------------------------------------------------------------------
    GLuint textureLoadFromDisk(const std::string& path, bool convertToLinear = false, unsigned bindToUnit = 0, bool applyFallback = true) {

      constexpr bool genMipMaps = true;

      GLuint textureId;
      glGenTextures(1, &textureId);
      glActiveTexture(GL_TEXTURE0 + bindToUnit);
      glBindTexture(GL_TEXTURE_2D, textureId);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      if (genMipMaps) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      }
      else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      }

#if defined(GL_TEXTURE_MAX_ANISOTROPY_EXT) && defined(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT)
      GLfloat largestSupportedAnisotropy;
      glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largestSupportedAnisotropy);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largestSupportedAnisotropy);
      spdlog::trace("textureLoadFromDisk: Setting anisotropic texture filtering to: {}", largestSupportedAnisotropy);
#endif

      // apply user parameters here
      // border stuff
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      // float borderColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
      // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

      int stbiWidth, stbiHeight, stbiChannelsCount;
      unsigned char *stbiDataLdr;
      stb_lib::stbi_set_flip_vertically_on_load(WARP_TEXTURE_STBI_FLIP);

      if (!stbi_is_hdr(path.c_str())) {
        stbiDataLdr = stb_lib::stbi_load(path.c_str(), &stbiWidth, &stbiHeight, &stbiChannelsCount, 0);
      }
      else {
        throw std::runtime_error(std::string("textureLoadFromDisk does not implement HDR textures, sorry. Aborting because of " + path));
      }

      // data from disk not loaded
      if (stbiDataLdr == nullptr) {
        if (applyFallback) {
          spdlog::error("textureLoadFromDisk: Unable to load image at path {}, applying fallback (random data)", path);
          std::vector<GLubyte> texCheckerData4x4(4*4*3);
          std::independent_bits_engine<std::default_random_engine, CHAR_BIT, GLubyte> texCheckerRandomizer;
          std::generate(begin(texCheckerData4x4), end(texCheckerData4x4), std::ref(texCheckerRandomizer));
          // pixelate
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexImage2D(
                       GL_TEXTURE_2D,
                       0,
                       (convertToLinear) ? GL_SRGB : GL_RGB,
                       4,
                       4,
                       0,
                       GL_RGB,
                       GL_UNSIGNED_BYTE,
                       (GLvoid *)texCheckerData4x4.data()
                       );
        }
        else {
          glActiveTexture(GL_TEXTURE0 + 0);
          glBindTexture(GL_TEXTURE_2D, 0);
          glDeleteTextures(1, &textureId);
          throw std::runtime_error(std::string("ERROR: textureLoadFromDisk: texture file not read, some error for: " + path));
        }
      }
      // data from disk loaded
      else {
        spdlog::trace("textureLoadFromDisk: Image loaded from path: {}, has {} channels", path, stbiChannelsCount);


        if(!((stbiWidth & (stbiWidth - 1)) == 0) || !((stbiHeight & (stbiHeight - 1)) == 0)) {
          if (!hela::motor::isExtensionSupported("OES_texture_npot")) {
            spdlog::warn("textureLoadFromDisk: Loaded texture is not n^2 and you don't have OES_texture_npot support {}", path);
          }
          else {
            spdlog::trace("textureLoadFromDisk: Loaded texture is not n^2, but no worries as you have OES_texture_npot support {}", path);
          }
        }

        GLenum format;
        GLint internalFormat;

        switch (stbiChannelsCount) {
          case 1:
            format = GL_RED;
            break;
          case 3:
            format = GL_RGB;
            break;
          case 4:
            format = GL_RGBA;
            break;
          default:
            throw std::runtime_error(std::string("textureLoadFromDisk: channel count " + std::to_string(stbiChannelsCount) + " not implemented. look at: " + path));
            break;
        }

        internalFormat = format;

        // if convert to linear
        if (convertToLinear) {

#if defined(WARP_TEXTURE_MANUAL_GL_SRGB)
          // convert to linear before offloading to GPU

          // GL_FRAMEBUFFER_SRGB on devbench should be off (and is by default) to reflect Mali not having it
          // The bad news is that there is no GL_SRGB(_ALPHA) internal format on Mali
          // Either pass textures "as is" and in fragment shaders do conversation to linear color space on every lookup
          // Or before passing data to GPU and on do conversation ourselves on CPU for raw data

          spdlog::debug("textureLoadFromDisk: you requested conversation for texure internal format to linear. this OpenGL implementation has no SRGB internal formats, but will fix that by manually crunching it before offloadinfg data to GPU! expect linear for {}", path);

          std::vector<float> stbiDataLdrF;

          unsigned int stbiCount = stbiWidth * stbiHeight * stbiChannelsCount;
          for (unsigned int pIdx = 0; pIdx < stbiCount; pIdx += stbiChannelsCount) {
            for (unsigned int cIdx = pIdx; (cIdx < pIdx + stbiChannelsCount); ++cIdx) {
              stbiDataLdrF.push_back(warp::lut::lut_srgb_to_linear_f[stbiDataLdr[cIdx]]);
              stbiDataLdr[cIdx] = warp::lut::lut_srgb_to_linear_8[stbiDataLdr[cIdx]];
            }
          }

          if (hela::motor::isExtensionSupported("OES_texture_float") && hela::motor::isExtensionSupported("OES_texture_float_linear")) {
            switch (stbiChannelsCount) {
              case 1:
                internalFormat = GL_R32F;
                break;
              case 3:
                internalFormat = GL_RGB32F;
                break;
              case 4:
                internalFormat = GL_RGBA32F;
                break;
              default:
                // should not reach this
                break;
            }
            std::cout << "textureLoadFromDisk: loaded linear from LUT GL_FLOAT" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_FLOAT, stbiDataLdrF.data());
          } else {
            std::cout << "textureLoadFromDisk: loaded linear from LUT GL_UNSIGNED_BYTE" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiDataLdr);
          }
          stbiDataLdrF.clear();

#else
          // convert to linear on GPU
          spdlog::debug("textureLoadFromDisk: you requested conversation for texure internal format to linear and implementation supports it. expect linear for {}", path);
          switch (format) {
            case GL_RED:
              // keep at GL_RED
              break;
            case GL_RGB:
              internalFormat = GL_SRGB;
              break;
            case GL_RGBA:
              internalFormat = GL_SRGB_ALPHA;
              break;
            default:
              break;
          }
          glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiDataLdr);
#endif
        }
        // if keep as is (no linear conversion because texture file already is linear or maybe linear not needed)
        else {
          spdlog::trace("textureLoadFromDisk: texture color space will be left untouched for: {}", path);
          glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiDataLdr);
        }
      }
      // generate mipmaps after loading data
      if (genMipMaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
      }
      glActiveTexture(GL_TEXTURE0 + 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      if (stbiDataLdr != nullptr) {
        stbi_image_free(stbiDataLdr); // if it throws earlier, whateva
      }
      return textureId;

    }


  }
}

#endif // warp_texture_hpp
