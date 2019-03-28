#ifndef warp_texture_hpp
#define warp_texture_hpp

#include <random>

#define stb_lib // make fake namespace-like marker for stb to differentiate global stuff easier
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
      std::cout << "textureLoadFromDisk: Setting anisotropic texture filtering to: " << largestSupportedAnisotropy  << std::endl;
#endif

      // apply user parameters here

      // border stuff
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      // float borderColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
      // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

      int stbiWidth, stbiHeight, stbiNoChannels;
      unsigned char *stbiData;
      stb_lib::stbi_set_flip_vertically_on_load(WARP_TEXTURE_STBI_FLIP);
      stbiData = stb_lib::stbi_load(path.c_str(), &stbiWidth, &stbiHeight, &stbiNoChannels, 0);
      std::vector<float> stbiDataF;

      if (stbiData == nullptr) {
        if (applyFallback) {
          std::cerr << "textureLoadFromDisk: Unable to load image at path " << path << ", apply fallback by feeding in random data." << std::endl;
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
          if (genMipMaps) glGenerateMipmap(GL_TEXTURE_2D);
        } else {
          glActiveTexture(GL_TEXTURE0 + 0);
          glBindTexture(GL_TEXTURE_2D, 0);
          glDeleteTextures(1, &textureId);
          throw std::runtime_error(std::string("ERROR: textureLoadFromDisk: texture file not read, some error for: " + path));
        }
      } else {
        std::cout << "textureLoadFromDisk: Image loaded from path: " << path << ", has " << stbiNoChannels << " channels." << std::endl;

//        if (!isGlExtensionSupported("OES_texture_npot")) {
//          if(!((stbiWidth & (stbiWidth - 1)) == 0) || !((stbiHeight & (stbiHeight - 1)) == 0)) {
//            std::cout << "WARNING: textureLoadFromDisk: Loaded texture is not n^2 and you don't have OES_texture_npot support, expect bad things for image at path: " << path << std::endl;
//          }
//        }

        GLint internalFormat;
        GLenum format;

        switch (stbiNoChannels) {
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
            format = GL_RGB;
            break;
        }

        internalFormat = format;

        if (convertToLinear) {

#if USER_GL_SRGB_ON_CPU == 1

          std::cout << "textureLoadFromDisk: you requested conversation for texure internal format to linear. USER_GL_SRGB_ON_CPU specified and will use CPU to crunch it before offloadinfg data to GPU! expect linear for: " << path << std::endl;
          std::cout << "textureLoadFromDisk: manually changing sRGB to linear color space... " << std::endl;
          unsigned int stbiCount = stbiWidth * stbiHeight * stbiNoChannels;
          for (unsigned int pIdx = 0; pIdx < stbiCount; pIdx += stbiNoChannels) {
            for (unsigned int cIdx = pIdx; (cIdx < pIdx + stbiNoChannels && cIdx < pIdx + 3); cIdx++) {
              stbiDataF.push_back(warp::lut::lut_srgb_to_linear_f[stbiData[cIdx]]);
              stbiData[cIdx] = warp::lut::lut_srgb_to_linear_8[stbiData[cIdx]];
            }
          }

          // this mali does not have OES_texture_float
          if (isGlExtensionSupported("OES_texture_float")) {
            switch (stbiNoChannels) {
              case 1:
                internalFormat = GL_R16F;
                break;
              case 3:
                internalFormat = GL_RGB16F;
                break;
              case 4:
                internalFormat = GL_RGBA16F;
                break;
              default:
                internalFormat = GL_RGB16F;
                break;
            }
            // GL_HALF_FLOAT, GL_HALF_FLOAT_OES
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_FLOAT, stbiDataF.data());
          } else {
            std::cout << "textureLoadFromDisk: no OES_texture_float, will use unsigned byte linear LUT" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiData);
          }

#else
          std::cout << "textureLoadFromDisk: you requested conversation for texure internal format to linear and implementation supports it: " << path << std::endl;
          switch (format) {
            case GL_RGB:
              internalFormat = GL_SRGB;
              break;
            case GL_RGBA:
              internalFormat = GL_SRGB_ALPHA;
              break;
            default:
              break;
          }
          glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiData);
#endif
        } else {
          std::cout << "textureLoadFromDisk: texture color space will be left untouched for: " << path << std::endl;
          glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, stbiWidth, stbiHeight, 0, format, GL_UNSIGNED_BYTE, stbiData);
        }
        if (genMipMaps) glGenerateMipmap(GL_TEXTURE_2D);
      }

      glActiveTexture(GL_TEXTURE0 + 0);
      glBindTexture(GL_TEXTURE_2D, UNBIND);
      stbi_image_free(stbiData);
      stbiDataF.clear();
      return textureId;

    }



  }
}

#endif // warp_texture_hpp
