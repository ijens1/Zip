#ifndef ZIP_EXCEPTION_H
#define ZIP_EXCEPTION_H

#include <string>

namespace zip {

  class ZipException {
      std::string reason;

    public:
      ZipException() : reason{"unknown error occured"} {}
      ZipException(std::string reason) : reason{reason} {}
      ZipException(const ZipException& other) : reason{other.reason} {}
      ZipException(ZipException&& other) : reason{std::move(other.reason)} {}
      ZipException& operator=(const ZipException& other) {
        reason = other.reason;
        return *this;
      }
      ZipException& operator=(ZipException&& other) {
        reason = std::move(other.reason);
        return *this;
      }
      virtual ~ZipException() {}

      std::string getReason() { return reason; }
  };

}

#endif
