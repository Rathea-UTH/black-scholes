#ifndef _PAYOFF_H_
#define _PAYOFF_H_

#include "Matrix.h"
#include <math.h>

class Matrix;

///
/// L'objectif principal est d'implémenter la fonction
/// C_t0(s), qui retourne le vecteur contenant les valeurs
/// du payoff à l'instant initial pour chaque point s de "l'espace"
///
class Payoff
{
    protected:
    double K_, r_, sigma_, T_, L_;
    int N_, M_;

    public:
    /// @brief le constructeur d'une classe Payoff
    Payoff(double K, double r, double sigma, double T, double L, int N, int M);
    /// @brief le constructeur de copie d'une classe Payoff
    Payoff(const Payoff & P);

    public:
    /// @return la valeur de N
    int get_N() const { return N_;}
    /// @return la valeur de M
    int get_M() const { return M_;}
    /// @return la valeur de K
    double get_K() const { return K_;}
    /// @return la valeur de r
    double get_r() const { return r_;}
    /// @return la valeur de sigma
    double get_sigma() const { return sigma_;}
    /// @return la valeur de T
    double get_T() const { return T_;}
    /// @return la valeur de L
    double get_L() const { return L_;}
    /// @return le pas temporel résultant du découpage de [0,T] en M segments 
    double delta_T() const {return T_/M_;}

    /// @return le pas temporel résultant du découpage des stilde en N segments lorsque s varie 
    /// dans [0,L]
    double delta_stilde() const {return log(N_)/(N_ - 1);}

    /// @return un vecteur contenant les valeurs des s_i (pas régulier)
    std::vector<double> s_regular_values() const;

    /// @return un vecteur contenant les valeurs des points s
    /// résultant d'une discrétisation des stilde à pas régulier
    /// @attention le pas entre chaque s n'est alors pas régulier
    std::vector<double> s_not_regular_values() const;

    /// @brief Fonction virtuelle pure que les classes Put et Call devront implémenter
    /// @return le vecteur contenant les valeurs
    /// du payoff à l'instant initial pour chaque point s de "l'espace"
    virtual std::vector<double> C_t0() const=0;

    /// @note Voir le pdf pour plus de détails
    /// @return A la matrice qui multiplie les C_{m} dans la formule de 
    /// récurrence tirée de l'équation de Black Scholes (1)
    Matrix get_A() const;

    /// @note Voir le pdf pour plus de détails
    /// @return B la matrice qui multiplie les C_{m+1} dans la formule de 
    /// récurrence tirée de l'équation de Black Scholes (1)
    Matrix get_B() const;

    /// @note Voir le pdf pour plus de détails
    /// @return C la matrice qui multiplie les C_{m+1} dans la formule de 
    /// récurrence tirée de l'équation de Black Scholes réduite (5)
    Matrix get_C() const;
};

#endif /* _PAYOFF_H_ */
