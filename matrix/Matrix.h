#include <array>
#include <cassert>
#include <iostream>
#include <memory>

#pragma once
namespace JMat
{
#pragma region Matrix template struct declaration
template <class T, std::size_t R, std::size_t C> struct Matrix
{
  public:
    Matrix(const T[R][C]);
    Matrix(const T (&)[R][C]);
    Matrix(std::array<std::array<T, C>, R>);

    std::size_t row_count();
    std::size_t col_count();
    std::size_t entry_count();

    std::array<T, C> get_row_vec(const std::size_t);
    std::array<T, R> get_col_vec(const std::size_t);
    std::array<std::array<T, C>, R> get_matrix_copy();
    std::array<std::array<T, C>, R> get_matrix_transpose_copy();

    void print();
    void print_t();

    void set(const std::size_t, const std::size_t, const T);
    void replace_row(const std::size_t, const T[C]);
    void replace_col(const std::size_t, const T[R]);
    void replace_row(const std::size_t, const T (&)[C]);
    void replace_col(const std::size_t, const T (&)[R]);

  private:
    std::array<std::array<T, C>, R> _matrix;
    std::array<std::array<T, R>, C> _matrix_transpose;
};
#pragma endregion

#pragma region Matrix template struct methods
template <class T, std::size_t R, std::size_t C> Matrix<T, R, C>::Matrix(const T m[R][C])
{
    for (std::size_t i = 0; i < R; i++)
    {
        for (std::size_t j = 0; j < C; j++)
        {
            _matrix[i][j] = m[i][j];
            _matrix_transpose[j][i] = m[i][j];
        }
    }
}

template <class T, std::size_t R, std::size_t C> Matrix<T, R, C>::Matrix(const T (&m)[R][C])
{
    for (std::size_t i = 0; i < R; i++)
    {
        for (std::size_t j = 0; j < C; j++)
        {
            _matrix[i][j] = m[i][j];
            _matrix_transpose[j][i] = m[i][j];
        }
    }
}

template <class T, std::size_t R, std::size_t C> Matrix<T, R, C>::Matrix(std::array<std::array<T, C>, R> arr)
{
    _matrix = arr;

    for (std::size_t i = 0; i < R; i++)
    {
        for (std::size_t j = 0; j < C; j++)
        {
            _matrix_transpose[j][i] = _matrix[i][j];
        }
    }
}

template <class T, std::size_t R, std::size_t C> std::size_t Matrix<T, R, C>::row_count()
{
    return R;
}

template <class T, std::size_t R, std::size_t C> std::size_t Matrix<T, R, C>::col_count()
{
    return C;
}

template <class T, std::size_t R, std::size_t C> std::size_t Matrix<T, R, C>::entry_count()
{
    return R * C;
}

template <class T, std::size_t R, std::size_t C> std::array<T, C> Matrix<T, R, C>::get_row_vec(const std::size_t index)
{
    assert(index < R);
    return _matrix[index];
}

template <class T, std::size_t R, std::size_t C> std::array<T, R> Matrix<T, R, C>::get_col_vec(const std::size_t index)
{
    assert(index < C);
    return _matrix_transpose[index];
}

template <class T, std::size_t R, std::size_t C> std::array<std::array<T, C>, R> Matrix<T, R, C>::get_matrix_copy()
{
    return _matrix;
}

template <class T, std::size_t R, std::size_t C>
std::array<std::array<T, C>, R> Matrix<T, R, C>::get_matrix_transpose_copy()
{
    return _matrix_transpose;
}

template <class T, std::size_t R, std::size_t C> void Matrix<T, R, C>::print()
{
    for (std::array<T, C> rows : _matrix)
    {
        std::cout << "[";
        for (T v : rows)
        {
            std::cout << " " << v;
        }
        std::cout << " ]\n";
    }

    std::cout << std::endl;
}

template <class T, std::size_t R, std::size_t C> void Matrix<T, R, C>::print_t()
{
    for (std::array<T, R> rows : _matrix_transpose)
    {
        std::cout << "[";
        for (T v : rows)
        {
            std::cout << " " << v;
        }
        std::cout << " ]\n";
    }

    std::cout << std::endl;
}

template <class T, std::size_t R, std::size_t C>
void Matrix<T, R, C>::set(const std::size_t row, const std::size_t col, const T v)
{
    assert(row < R and col < C);
    _matrix[row][col] = v;
    _matrix_transpose[col][row] = v;
}

template <class T, std::size_t R, size_t C> void Matrix<T, R, C>::replace_row(const std::size_t row, const T v[C])
{
    for (std::size_t i = 0; i < C; i++)
    {
        set(row, i, v[i]);
    }
}

template <class T, std::size_t R, size_t C> void Matrix<T, R, C>::replace_col(const std::size_t col, const T v[R])
{
    for (std::size_t i = 0; i < R; i++)
    {
        set(i, i, v[i]);
    }
}

template <class T, std::size_t R, size_t C> void Matrix<T, R, C>::replace_row(const std::size_t row, const T (&v)[C])
{
    for (std::size_t i = 0; i < C; i++)
    {
        set(row, i, v[i]);
    }
}

template <class T, std::size_t R, size_t C> void Matrix<T, R, C>::replace_col(const std::size_t col, const T (&v)[R])
{
    for (std::size_t i = 0; i < R; i++)
    {
        set(i, col, v[i]);
    }
}
#pragma endregion

#pragma region Matrix functions
#pragma region Matrix Add functions
template <class T, std::size_t C> T *add(T (&v1)[C], const T v)
{
    T vec[C];

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] + v;
    }

    return vec;
}

template <class T, std::size_t C> T *add(T (&v1)[C], T (&v2)[C])
{
    T vec[C];

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] + v2[i];
    }

    return vec;
}

template <class T, std::size_t C> std::array<T, C> add(std::array<T, C> &v1, const T v)
{
    std::array<T, C> vec;

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] + v;
    }

    return vec;
}

template <class T, std::size_t C> std::array<T, C> add(std::array<T, C> &v1, std::array<T, C> &v2)
{
    std::array<T, C> vec;

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] + v2[i];
    }

    return vec;
}

template <class T, std::size_t C> std::array<T, C> add(std::array<T, C> v1, std::array<T, C> v2)
{
    std::array<T, C> vec;

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] + v2[i];
    }

    return vec;
}

template <class T, std::size_t R, std::size_t C> Matrix<T, R, C> add(Matrix<T, R, C> &m1, const T v)
{
    std::array<std::array<T, C>, R> arr;

    for (std::size_t i = 0; i < R; i++)
    {
        arr[i] = add(m1.get_row_vec(i), v);
    }

    return Matrix<T, R, C>(arr);
}

template <class T, std::size_t R, std::size_t C> Matrix<T, R, C> add(Matrix<T, R, C> &m1, Matrix<T, R, C> &m2)
{
    std::array<std::array<T, C>, R> arr;

    for (std::size_t i = 0; i < R; i++)
    {
        arr[i] = add(m1.get_row_vec(i), m2.get_row_vec(i));
    }

    return Matrix<T, R, C>(arr);
}
#pragma endregion

#pragma region Multiplication functions
template <class T, std::size_t C> T *scalar_mult(T (&v1)[C], const T v)
{
    T vec[C];

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] * v;
    }

    return vec;
}

template <class T, std::size_t C> T dot_prod(T (&v1)[C], T (&v2)[C])
{
    T v;

    for (std::size_t i = 0; i < C; i++)
    {
        v += v1[i] * v2[i];
    }

    return v;
}

template <class T, std::size_t C> std::array<T, C> scalar_mult(std::array<T, C> &v1, const T v)
{
    std::array<T, C> vec;

    for (std::size_t i = 0; i < C; i++)
    {
        vec[i] = v1[i] * v;
    }

    return vec;
}

template <class T, std::size_t C> std::array<T, C> dot_prod(std::array<T, C> &v1, std::array<T, C> &v2)
{
    T v;

    for (std::size_t i = 0; i < C; i++)
    {
        v += v1[i] * v2[i];
    }

    return v;
}

template <class T, std::size_t C> T dot_prod(std::array<T, C> v1, std::array<T, C> v2)
{
    T v;

    for (std::size_t i = 0; i < C; i++)
    {
        v += v1[i] * v2[i];
    }

    return v;
}

template <class T, std::size_t R, std::size_t C> Matrix<T, R, C> scalar_mult(Matrix<T, R, C> &m1, const T v)
{
    std::array<std::array<T, C>, R> arr;

    for (std::size_t i = 0; i < R; i++)
    {
        arr[i] = scalar_mult(m1.get_row_vec(i), v);
    }

    return Matrix<T, R, C>(arr);
}

template <class T, std::size_t R, std::size_t CC, std::size_t C>
Matrix<T, R, C> dot_prod(Matrix<T, R, CC> &m1, Matrix<T, CC, C> &m2)
{
    std::array<std::array<T, C>, R> arr;

    for (std::size_t i = 0; i < R; i++)
    {
        arr[i] = std::array<T, C>();
        std::array<T, CC> row = m1.get_row_vec(i);

        for (std::size_t j = 0; j < C; j++)
        {
            std::array<T, CC> col = m2.get_col_vec(j);
            for (std::size_t k = 0; k < CC; k++)
            {
                arr[i][j] += row[k] * col[k];
            }
        }
    }

    return Matrix<T, R, C>(arr);
}
#pragma endregion

#pragma endregion

} // namespace JMat
