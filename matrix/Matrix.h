#include <array>
#include <iostream>
#include <memory>

#pragma once
namespace JMat
{
#pragma region Matrix template struct declaration
template <class T, size_t R, size_t C> struct Matrix
{
  public:
    std::array<std::array<T, C>, R> _matrix;

  private:
    const size_t _rows = R;
    const size_t _cols = C;
};
#pragma endregion

} // namespace JMat
