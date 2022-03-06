#include "Matrix.h"

Matrix::Matrix(int n)
{
    n_ = n;
    data_ = new double[n*n];
    if(!data_)
    {
        throw "Not enough memory";
    }
}

Matrix::Matrix(const Matrix & m)
{
    n_ = m.get_n();
    data_ = new double[n_*n_];
    if(!data_)
    {
        throw "Not enough memory";
    }
    for(size_t i=0; i<n_; i++)
    {
        for(size_t j=0; j<n_; j++)
        {
            operator()(i,j) = m(i,j);
        }
    }
}

Matrix::~Matrix()
{
    delete[] data_;
}

double Matrix::operator()(int i, int j) const
{
    if(i < 0 || i>= n_ || j<0 || j>=n_)
    {
        throw "wrong index";
    }
    return data_[i*n_ + j];
}

double & Matrix::operator()(int i, int j)
{
    if(i < 0 || i>= n_ || j<0 || j>=n_)
    {
        throw "wrong index";
    }
    return data_[i*n_ + j];
}

bool Matrix::is_invertible() const
{
    return det() == 0;
}

bool Matrix::is_triangular_inf() const
{
    bool res = true;
    for(size_t i=0; i<n_-1; i++)
    {
        for(size_t j=i+1; j<n_; j++)
        {
            if(operator()(i,j) != 0)
            {
                res = false;
                break;
            }
        }
    }
    return res;
}

Matrix Matrix::sub(int l) const
{
    Matrix m(get_n() - 1);

    int idx = 0;
    for (int i = 0; i < get_n(); i++)
    {
        if (i != l)
        {
            for (int j = 1; j < get_n(); j++)
            {
                m(idx, j - 1) = operator()(i, j);
            }
            idx++;
        }
    }
    return m;
}

double Matrix::det() const
{
    if (get_n() == 1)
        return operator()(0, 0);

    double d = 0;
    int eps = 1;
    for (int i = 0; i < get_n(); i++, eps = -eps)
        d += eps * operator()(i, 0) * sub(i).det();

    return d;
}


bool Matrix::is_triangular_sup() const
{
    bool res = true;
    for(size_t i=1; i<n_; i++)
    {
        for(size_t j=0; j<i; j++)
        {
            if(operator()(i,j) != 0)
            {
                res = false;
                break;
            }
        }
    }
    return res;
}

std::ostream & operator<<(std::ostream & os, const Matrix & m)
{
    int n = m.get_n();
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            os << m(i,j) << " ";
        }
        os << "\n";
    }
    return os;
}

std::vector<double> operator*(const Matrix & m, const std::vector<double> & v)
{
    int n = m.get_n();
    if(n != v.size())
    {
        throw "Not compatible dimensions";
    }
    std::vector<double> v_(n,0);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            v_.at(i) += m(i,j)*v.at(j);
        }
    }
    return v_;
}

// Seems pretty costly (storage of 2 vectors) for nothing
bool Matrix::is_lu_decomp() const
{
    if(operator()(0,0) == 0)
    {
        return false;
    }
    int n = get_n();
    std::vector<double> b_star(n,0);
    std::vector<double> c_star(n,0);
    // Initialization
    b_star.at(0) = operator()(0,0);
    c_star.at(0) = operator()(0,1)/operator()(0,0);
    for(int k=1; k<n-1; k++)
    {
        b_star.at(k) = operator()(k,k) - operator()(k,k-1)*c_star.at(k-1);
        if(b_star.at(k) ==0)
        {
            return false;
        }
        c_star.at(k) = operator()(k,k+1)/b_star.at(k);
    }
    return true;
}

std::vector<double> solve(const Matrix & A, const std::vector<double> & b)
{
    int n = A.get_n();
    if(n != b.size())
    {
        throw "Not compatible dimensions";
    }
    // cf https://www.ljll.math.upmc.fr/hecht/ftp/InfoSci/doc-pdf/Master_book_LU.pdf
    std::vector<double> b_star(n,0);
    std::vector<double> c_star(n,0);
    // Initialization
    b_star.at(0) = A(0,0);
    c_star.at(0) = A(0,1)/A(0,0);
    for(int k=1; k<n-1; k++)
    {
        b_star.at(k) = A(k,k) - A(k,k-1)*c_star.at(k-1);
        if(b_star.at(k) == 0)
        {
            throw "The matrix can't be LU decomposable";
        }
        c_star.at(k) = A(k,k+1)/b_star.at(k);
    }
    b_star.at(n-1) = A(n-1,n-1) - A(n-1,n-2)*c_star.at(n-2);

    // Solution of the intermediate equation LY=b
    std::vector<double> Y(n,0);
    Y.at(0) = b.at(0)/b_star.at(0);
    for(int i=1; i<n; i++)
    {
        Y.at(i) = (b.at(i) - A(i,i-1)*Y.at(i-1))/b_star.at(i);
    }

    // Solution of the equation UX=b
    std::vector<double> X(n,0);
    X.at(n-1) = Y.at(n-1);
    for(int i=n-2; i>=0; i--)
    {
        X.at(i) = Y.at(i) - c_star.at(i)*X.at(i+1);
    }
    return X;
}

std::vector<double> operator+(const std::vector<double> & v1, const std::vector<double> & v2)
{
    if(v1.size() != v2.size())
    {
        throw "Can't sum the vectors since they don't have the same size";
    }
    int n = v1.size();
    std::vector<double> v(n,0);
    for(int i=0; i<n; i++)
    {
        v.at(i) = v1.at(i) + v2.at(i);
    }
    return v;
}

std::ostream & operator<<(std::ostream & os, const std::vector<double> & v)
{
    std::vector<double>::const_iterator iter = v.begin();
    while(iter != v.end())
    {
        os << *iter << " ";
        iter++;
    }
    os << "\n";
    return os;
}