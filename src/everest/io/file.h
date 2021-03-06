#pragma once

#include <sys/fcntl.h>
#include <everest/strings/string.h>
#include <everest/containers/option.h>
#include <everest/containers/checked.h>
#include <cerrno>

namespace everest {

template<class E, class S>
class Checked;

class File final {

  int _descriptor;

  int _flags;

  File(int descriptor, int flags) noexcept : _descriptor(descriptor), _flags(flags) { }

public:

  File(const File& other) = delete;

  File(File&& other) noexcept : _descriptor(other._descriptor), _flags(other._flags) {
    other._descriptor = -1;
    other._flags      = -1;
  }

  File& operator=(File&& other) {
    _descriptor       = other._descriptor;
    _flags            = other._flags;
    other._descriptor = -1;
    other._flags      = -1;
  }

  ~File() noexcept {
    if (_descriptor != -1) {
      close(_descriptor);
    }
  }

  int Descriptor() const noexcept {
    return _descriptor;
  }

  int Flags() const noexcept {
    return _flags;
  }

  static Checked<int, File> Open(const char* filePath, int flags) noexcept {
    int fd = open(filePath, flags);
    if (fd != -1) {
      return Checked<int, File>::Ok(File(fd, flags));
    } else {
      return Checked<int, File>::Error(errno);
    }
  }

  static Checked<int, File> OpenWithMode(const char* filePath, int flags, int mode) noexcept {
    int fd = open(filePath, flags, mode);
    if (fd != -1) {
      return Checked<int, File>::Ok(File(fd, flags));
    } else {
      return Checked<int, File>::Error(errno);
    }
  }

  static Checked<int, File> Open(String filePath, int flags) noexcept {
    return Open(filePath.Pointer(), flags);
  }

  static Checked<int, File> Open(const char* filePath) noexcept {
    return Open(filePath, O_RDWR);
  }

  static Checked<int, File> Open(const String& filePath) noexcept {
    return Open(filePath.Pointer(), O_RDWR);
  }

  static Checked<int, File> OpenForRead(const char* filePath) noexcept {
    return Open(filePath, O_RDONLY);
  }

  static Checked<int, File> OpenForRead(const String& filePath) noexcept {
    return Open(filePath.Pointer(), O_RDONLY);
  }

  static Checked<int, File> OpenForWrite(const char* filePath) noexcept {
    return Open(filePath, O_WRONLY);
  }

  static Checked<int, File> OpenForWrite(const String& filePath) noexcept {
    return Open(filePath.Pointer(), O_WRONLY);
  }

  static bool Touch(const char* filePath) noexcept {
    return OpenWithMode(filePath, O_CREAT | O_WRONLY, 420).IsOk();
  }

  static bool Touch(const String& filePath) noexcept {
    return Touch(filePath.Pointer());
  }

  static bool Unlink(const char* filePath) noexcept {
    return unlink(filePath) == 0;
  }

  static bool Unlink(const String& filePath) noexcept {
    return Unlink(filePath.Pointer());
  }

};

}
