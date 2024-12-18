/*
* Copyright (c) 2024 Diago Lima
* All rights reserved.
*
* This software is licensed under the BSD 3-Clause "New" or "Revised" license
* found in the LICENSE file in the root directory of this project's source tree.
*/

#include <Core/Stream.hpp>
BEGIN_NAMESPACE(n19);

auto OStream::from_stderr() -> OStream {
  auto the_stream = OStream();
  the_stream.fd_  = sys::IODevice::from_stderr();
  return the_stream;
}

auto OStream::from_stdout() -> OStream {
  auto the_stream = OStream();
  the_stream.fd_  = sys::IODevice::from_stdout();
  return the_stream;
}

auto OStream::from(const sys::IODevice& device) -> OStream {
  auto the_stream = OStream();
  the_stream.fd_  = device;
  return the_stream;
}

auto IStream::from_stdin() -> IStream {
  auto the_stream = IStream();
  the_stream.fd_  = sys::IODevice::from_stdin();
  return the_stream;
}

auto IStream::from(const sys::IODevice& device) -> IStream {
  auto the_stream = IStream();
  the_stream.fd_  = device;
  return the_stream;
}

END_NAMESPACE(n19);