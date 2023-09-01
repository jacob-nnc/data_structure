#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
#include<string>
#include<initializer_list>
using namespace std;
template <typename Type = double>
class matix
{
private:
    size_t rows;
    size_t clos;
    vector<vector<Type> > mat;
    //计算行列式的值
    Type det(const matix& item) const
    {
        if (item.Clos() == 1)
            return item[0][0];
        else if (item.Clos() == 2)
            return item[0][0] * item[1][1] - item[0][1] * item[1][0];
        Type sum = 0;
        for (size_t i = 0; i < item.Clos(); i++)
        {
        	if(item[0][i]!=0)
        	{
        		sum += A(0, i) * item[0][i];
			}
        }
        return sum;
    }
public:
    //构造方法
    matix(size_t n) :rows(n), clos(n), mat(n)
    {
        vector<Type> _t(n);
        for (size_t i = 0; i < n; i++)
        {
            mat[i] = _t;
        }
    }
    matix(size_t m, size_t n) :rows(m), clos(n), mat(m)
    {
        vector<Type> _t(n);
        for (size_t i = 0; i < m; i++)
        {
            mat[i] = _t;
        }
    }
    matix(const matix& item) :rows(item.Rows()), clos(item.Clos())
    {
        mat = item.get();
    }

    //操作符
    matix operator=(const matix& item)
    {
        rows = item.Rows();
        clos = item.Clos();
        mat = item.get();
        return *this;
    }
    matix operator=(initializer_list<Type> a)
    {
        auto be = a.begin();
        auto en = a.end();
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < clos; j++)
            {
                (*this)[i][j] = *be;
                be++;
                if (be == en)
                    return *this;
            }
        }
        return *this;
    }

    //方法
    size_t Rows() const
    {
        return rows;
    }
    size_t Rows()
    {
        return rows;
    }
    size_t Clos()
    {
        return clos;
    }
    size_t Clos() const
    {
        return clos;
    }
    vector<vector<Type> >& get()
    {
        return mat;
    }
    const vector<vector<Type> >& get()const
    {
        return mat;
    }
    matix remove(size_t _i, size_t _j)const
    {
        if (_i >= rows || _j >= clos)
            throw("out of index");
        matix ret(rows - 1);
        int m = 0, n = 0;
        for (int i = 0; i < rows; i++)
        {
            if (i == _i)
                continue;
            n = 0;
            for (int j = 0; j < clos; j++)
            {
                if (j == _j)
                    continue;
                ret[m][n] = (*this)[i][j];
                n++;
            }
            m++;
        }
        return ret;
    }
    matix remove(size_t i, size_t j)
    {
        return static_cast<const matix>(*this).remove(i, j);
    }
    Type M(size_t i, size_t j)
    {
        assert(clos == rows);
        return remove(i, j).det();
    }
    Type A(size_t i, size_t j)
    {
        assert(clos == rows);
        return i % 2 == j % 2 ? M(i, j) : -M(i, j);
    }
    Type M(size_t i, size_t j)const
    {
        assert(clos == rows);
        return remove(i, j).det();
    }
    Type A(size_t i, size_t j)const
    {
        assert(clos == rows);
        return (i+j)%2==0? M(i, j) : -M(i, j);
    }
    Type det()
    {
        assert(clos == rows);
        return det(*this);
    }
    Type det() const
    {
        assert(clos == rows);
        return det(*const_cast<matix<>*>(this));
    }
    matix T() const
    {
        matix ret(clos, rows);
        for (int i = 0; i < clos; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                ret[i][j] = (*this)[j][i];
            }
        }
        return ret;
    }
    matix T()
    {
        return const_cast<const matix<Type>&>(*this).T();
    }
    matix inv()
    {
        Type a = this->det();
        assert(a != 0);
        return this->ad() / a;
    }
    matix ad()
    {
        assert(rows == clos);
        matix ret(rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < clos; j++)
            {
                ret[j][i] = (*this).A(i, j);
            }
        }
        return ret;
    }
    matix inv()const
    {
        Type a = this->det();
        assert(a != 0);
        return this->ad() / a;
    }
    matix ad()const
    {
        assert(rows == clos);
        matix ret(rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < clos; j++)
            {
                ret[i][j] = (*this).A(i, j);
            }
        }
        return ret;
    }
    void clear()
    {
        mat.clear();
        clos = 0;
        rows = 0;
    }
    void resize(size_t _i, size_t _j)
    {
        mat.clear();
        mat.resize(_i);
        for (int i = 0; i < _i; i++)
        {
            mat[i].resize(_j);
        }
        rows = _i;
        clos = _j;
    }

    //克莱默法则
    vector<Type> gramm()
    {
        matix<> a(rows), b(rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                a[i][j] = (*this)[i][j];
            }
        }
        int mu = a.det();
        if (mu == 0)
        {
            return vector<Type>();
        }
        b = a;
        vector<Type> ret(rows);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < rows; j++)
            {
                a[j][i] = (*this)[j][clos - 1];
            }
            ret[i] = a.det() / mu;
            a = b;
        }
        return ret;
    }

    //重载索引
    const vector<Type>& operator[](size_t n)const
    {
        assert(n < rows);
        return mat[n];
    }
    vector<Type>& operator[](size_t n)
    {
        return mat[n];
    }
};
template<typename T = double> ostream& operator<<(ostream& os, const matix<T>& item)
{
    for (size_t i = 0; i < item.Rows(); i++)
    {
        for (size_t j = 0; j < item.Clos(); j++)
        {
            os << item[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}
template<typename T> const matix<T> operator+(const matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Clos() && x.Rows() == y.Rows());
    matix<T> ret(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < x.Clos(); j++)
        {
            ret[i][j] = x[i][j] + y[i][j];
        }
    }
    return ret;
}
template<typename T>const matix<T> operator-(const matix<T>& x)
{
    matix<T>ret(x.Rows(), x.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < x.Clos(); j++)
        {
            ret[i][j] = -x[i][j];
        }
    }
    return x;
}
template<typename T>const matix<T> operator-(const matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Clos() && x.Rows() == y.Rows());
    return x + -y;
}
template<typename T, typename C> const matix<T> operator*(const matix<T>& x, const C& y)
{
    matix<T> ret(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            ret[i][j] = y * x[i][j];
        }
    }
    return ret;
}
template<typename T, typename C> const matix<T> operator/(const matix<T>& x, const C& y)
{
    matix<T> ret(x.Rows(), x.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < x.Clos(); j++)
        {
            ret[i][j] = x[i][j] / y;
        }
    }
    return ret;
}
template<typename T, typename C> const matix<T> operator*(const C& y, const matix<T>& x)
{
    matix<T> ret(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            ret[i][j] = y * x[i][j];
        }
    }
    return ret;
}
template<typename T, typename C> const matix<T> operator*=(matix<T>& x, const C& y)
{
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            x[i][j] *= y;
        }
    }
    return x;
}
template<typename T> const matix<T> operator*(const matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Rows());
    matix<T> ret(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            for (size_t k = 0; k < x.Clos(); k++)
            {
                ret[i][j] += (x[i][k] * y[k][j]);
                cout << i << ' ' << j << ' ' << ret[i][j] << endl;
            }
        }
    }
    return ret;
}
template<typename T> const matix<T> operator*=(matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Rows());
    x.resize(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            for (size_t k = 0; k < x.Clos(); k++)
            {
                x[i][j] += (x[i][k] * y[k][j]);
            }
        }
    }
    return x;

}
template<typename T, typename C> const matix<T> operator/=(const matix<T>& x, const C& y)
{
    matix<T> ret(x.Rows(), y.Clos());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            x[i][j] /= y;
        }
    }
    return x;
}
template<typename T>const matix<T> operator+=(matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Clos() && x.Rows() == y.Rows());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < x.Clos(); j++)
        {
            x[i][j] += y[i][j];
        }
    }
    return x;
}
template<typename T>const matix<T> operator-=(matix<T>& x, const matix<T>& y)
{
    assert(x.Clos() == y.Clos() && x.Rows() == y.Rows());
    for (size_t i = 0; i < x.Rows(); i++)
    {
        for (size_t j = 0; j < x.Clos(); j++)
        {
            x[i][j] -= y[i][j];
        }
    }
    return x;
}
template<typename T>const matix<T> operator/(const matix<T>& x, const matix<T>& y)
{
    return x * y.inv();
}
template<typename T>const matix<T> operator/(matix<T>& x, const matix<T>& y)
{
    return x *= y.inv();
}
template<typename T>istream& operator>>(istream& is, matix<T>& y)
{
    size_t a;
    cout << "the num of x" << endl;
    is >> a;
    y.resize(a, a+1);
    cout << "matix" << endl;
    for (size_t i = 0; i < y.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
                is >> y[i][j];

        }
    }
    return is;
}
template<typename T>ostream& operator<<(ostream& os, matix<T>& y)
{
    for (size_t i = 0; i < y.Rows(); i++)
    {
        for (size_t j = 0; j < y.Clos(); j++)
        {
            os << y[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}

int main()
{
    matix<> a;
}