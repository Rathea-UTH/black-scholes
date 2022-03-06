#include "Payoff.h"
#include <math.h>

Payoff::Payoff(double K, double r, double sigma, double T, double L, int N, int M)
{
    r_ = r;
    K_ = K;
    sigma_= sigma;
    L_ = L;
    T_ = T;
    N_ = N;
    M_ = M;
}

Payoff::Payoff(const Payoff & P)
{
    r_ = P.r_;
    K_ = P.K_;
    sigma_= P.sigma_;
    L_ = P.L_;
    T_ = P.T_;
    N_ = P.N_;
    M_ = P.M_;
}

Matrix Payoff::get_A() const
{
    int N = get_N();
    Matrix A(N-1);
    // Update of the lower elements of A
    for(int i=0; i<N-2; i++){
        A(i+1,i) = (-get_r()*(i+2) + pow(get_sigma()*(i+2),2))/4;
    }
    // Update of the upper elements of A
    for(int i=0; i<N-2; i++){
        A(i,i+1) = (get_r()*(i+1) + pow(get_sigma()*(i+1),2))/4;
    }
    // Update of the diagonal of A
    for(int i=0; i<N-1; i++){
        A(i,i) = -get_M()/get_T() - get_r()/2 - pow(get_sigma()*(i+1),2)/2;
    }
    return A;
}

Matrix Payoff::get_B() const
{
    int N = get_N();
    Matrix B(N-1);
    // Update of the lower elements of B
    for(int i=0; i<N-2; i++){
        B(i+1,i) = -(-get_r()*(i+2) + pow(get_sigma()*(i+2),2))/4;
    }
    // Update of the upper elements of B
    for(int i=0; i<N-2; i++){
        B(i,i+1) = -(get_r()*(i+1) + pow(get_sigma()*(i+1),2))/4;
    }
    // Update of the diagonal of B
    for(int i=0; i<N-1; i++){
        B(i,i) = -get_M()/get_T() + get_r()/2 + pow(get_sigma()*(i+1),2)/2;
    }
    return B;
}

Matrix Payoff::get_C() const
{
    int N = get_N();
    Matrix C(N-1);
    // Update of the lower elements of C
    for(int i=0; i<N-2; i++){
        C(i+1,i) = -(pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2));
    }
    // Update of the upper elements of C
    for(int i=0; i<N-2; i++){
        C(i,i+1) = -(pow(get_sigma(),2)*delta_T())/(2*pow(delta_stilde(),2));
    }
    // Update of the diagonal of C
    for(int i=0; i<N-1; i++){
        C(i,i) = 1 + ((pow(get_sigma(),2)*delta_T())/pow(delta_stilde(),2));
    }
    return C;
}

std::vector<double> Payoff::s_regular_values() const 
{
    std::vector<double> v(N_-1,0);
    for(int i=0; i<N_-1; i++){
        v.at(i) = (i+1)*L_/N_;
    }
    return v;
}

std::vector<double> Payoff::s_not_regular_values() const 
{
    std::vector<double> v(N_-1,0);
    for(int i=0; i<N_-1; i++){
        // À t=0: s_i = K*e^{stilde_i + (r-sigma^2/2)}
        v.at(i) = K_*exp(log(L_/(K_*N_)) + i*delta_stilde());
    }
    return v;
}

