/*
* Copyright (c) 2024 Diago Lima
* All rights reserved.
*
* This software is licensed under the BSD 3-Clause "New" or "Revised" license
* found in the LICENSE file in the root directory of this project's source tree.
*/

#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP
#include <Core/TypeTraits.hpp>
#include <Core/Forward.hpp>
BEGIN_NAMESPACE(n19);

template<class T, class ...Us>
concept AreAll = (IsSame<T, Us> && ...);

template<class T, class ...Us>
concept AnyOf = (IsSame<T, Us> || ...);

template<class T, class ...Us>
concept CallableWith = requires(T&& t, Us&&... us){
  { t(forward<Us>(us)...) };
};

template<class T>
concept Character = IsCharacter<T>;

template<class T>
concept Integer = IsIntegral<T>;

template<class T>
concept Pointer = IsPointer<T>;

template<class T>
concept Reference = IsReference<T>;

template<class T>
concept FloatingPoint = IsFloatingPoint<T>;

template<class T>
concept IntOrFloat = IsIntegral<T> || IsFloatingPoint<T>;

END_NAMESPACE(n19);
#endif //CONCEPTS_HPP
