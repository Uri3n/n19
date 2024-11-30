/*
* Copyright (c) 2024 Diago Lima
* All rights reserved.
*
* This software is licensed under the BSD 3-Clause "New" or "Revised" license
* found in the LICENSE file in the root directory of this project's source tree.
*/

#ifndef FILEREF_HPP
#define FILEREF_HPP
#include <Core/Result.hpp>
#include <Core/Bytes.hpp>
#include <Native/String.hpp>
#include <filesystem>
#include <cstdint>

namespace fs = std::filesystem;
namespace n19 {
  class FileRef;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// n19::FileRef is very similar to n19::IODevice, except
// that it specifically deals with files, and uses higher level
// STL features to accomplish its tasks rather than native
// API functions.

class n19::FileRef {
public:
  auto operator->() -> fs::path*;
  auto operator*()  -> fs::path&;
  auto operator->() const -> const fs::path*;
  auto operator*()  const -> const fs::path&;

  // Attempts to convert the type T to a
  // n19::ByteView (AKA std::span<std::byte).
  template<typename T> auto operator<<(const T& val) -> FileRef&;
  template<typename T> auto operator>>(T& val)       -> FileRef&;

  // Used for reading to/writing to the file, called by
  // operator<< and operator>> as well.
  auto write(const Bytes& bytes, bool app = false) const -> Result<None>;
  auto read_into(const WritableBytes& bytes) const -> Result<None>;

  [[nodiscard]] auto nstr() const -> native::String;
  [[nodiscard]] auto size() const -> Result<uintmax_t>;
  [[nodiscard]] auto path() -> fs::path&;
  [[nodiscard]] auto path() const -> const fs::path&;

  // Creates a new file, ONLY if the specified file did not
  // exist beforehand. If the file already exists, the
  // call fails and an error value is returned.
  static auto create(const std::string& fname)  -> Result<FileRef>;
  static auto create(const std::wstring& fname) -> Result<FileRef>;

  // Creates or opens the specified file, as long as
  // the file path is lexically valid. If the file does not exist,
  // one will be created.
  static auto create_or_open(const std::wstring& fname) -> Result<FileRef>;
  static auto create_or_open(const std::string& fname)  -> Result<FileRef>;

  // Opens the specified file, ONLY if the file
  // already exists. If it does not exist, the call fails
  // and an error value is returned.
  static auto open(const std::wstring& fname) -> Result<FileRef>;
  static auto open(const std::string& fname)  -> Result<FileRef>;

  FileRef() = default;
  explicit FileRef(const fs::path& path) : path_(path) {}
private:
  fs::path path_;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
auto n19::FileRef::operator<<(const T& val) -> FileRef& {
  if constexpr(std::ranges::contiguous_range<T>) {
    auto bytes = n19::as_bytes(val);
    write(bytes);
  } else if constexpr (std::is_trivially_constructible_v<T>){
    auto bytes = n19::as_scalar_bytecopy(val);
    write(bytes);
  } else {
    static_assert(
    "FileRef::operator<< must be called with "
    "a type easily convertible to n19::ByteView.");
  }

  return *this;
}

template<typename T>
auto n19::FileRef::operator>>(T& val) -> FileRef& {
  static_assert(std::ranges::contiguous_range<T>);
  auto bytes = n19::as_writable_bytes(val);
  read_into(bytes);
  return *this;
}

inline auto n19::FileRef::nstr() const -> native::String {
#if defined(N19_WIN32)
  return path_.wstring();
#else
  return path_.string();
#endif
}

inline auto n19::FileRef::operator*() -> fs::path& {
  return path_;
}

inline auto n19::FileRef::operator->() -> fs::path* {
  return &path_;
}

inline auto n19::FileRef::operator*() const -> const fs::path& {
  return path_;
}

inline auto n19::FileRef::operator->() const -> const fs::path* {
  return &path_;
}

inline auto n19::FileRef::path() -> fs::path& {
  return path_;
}

inline auto n19::FileRef::path() const -> const fs::path & {
  return path_;
}

#endif //FILEREF_HPP
