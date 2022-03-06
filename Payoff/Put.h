#ifndef _PUT_H_
#define _PUT_H_

#include "Payoff.h"
#include <math.h>

///
/// Le namespace "Complete" correspond à la résolution 
/// de l'EDP (1) (version complète de l'équation de Black Scholes)
///

namespace Complete
{
///
/// Il s'agit d'un type particulier d'option, ce qui se traduit par un héritage:
/// Put est une classe fille de Payoff.
///
class Put : public Payoff{
    public:
    // Constructeurs
    /// @brief Constructeur par défaut d'une classe Put. Les valeurs des paramètres sont initialisées avec
    /// celles fournies dans l'énoncé.
    Put(): Payoff(100, 0.1, 0.1, 1, 300, 1000, 1000){;}
    /// @brief le constructeur avec paramètres d'une classe Put
    Put(double K, double r, double sigma, double T, double L, int N, int M): Payoff(K, r, sigma, T, L, N, M){;}
    
    /// @param s un flottant indiquant le "point de l'espace"
    /// en lequel le payoff est évalué à l'instant T 
    /// @return La valeur du payoff associée au couple (s,T)
    double C_T(double s) const {
        if(K_ - s > 0){
            return K_ - s;
        }
        return 0;
    }

    /// @param t un flottant indiquant l'instant en lequel est évalué le payoff 
    /// lorsque s=L
    /// @return la valeur du payoff en s=L (=0 pour un call)
    double C_L(double t) const {return 0;}

    /// @param t un flottant 
    /// @return La valeur du payoff à l'instant t, en s=0
    double C_s0(double t) const {return K_*exp(-r_*(T_-t));}
    
    /// @return Un vecteur de taille N-1 contenant les valeurs
    /// du payoff à l'instant 0 en chaque point de l'espace: C(0,s_1),...,C(0,s_{N-1}) 
    /// @warning Les conditions aux bords C(0,s_0) et C(0,L) sont déjà connues,
    /// donc ne sont pas incluses dans le vecteur retourné
    std::vector<double> C_t0() const;
};
} // namespace Complete


///
/// Le namespace "Reduced" correspond à la résolution 
/// de l'EDP (5) (version réduite de l'équation de Black Scholes)
///

namespace Reduced
{
///
/// Il s'agit d'un type particulier d'option, ce qui se traduit par un héritage:
/// Put est une classe fille de Payoff.
///
class Put : public Payoff{
    public:
    // Constructeurs
    /// @brief Constructeur par défaut d'une classe Put. Les valeurs des paramètres sont initialisées avec
    /// celles fournies dans l'énoncé.
    Put() : Payoff(100, 0.1, 0.1, 1, 300, 1000, 1000){;}
    /// @brief le constructeur d'une classe Put
    Put(double K, double r, double sigma, double T, double L, int N, int M): Payoff(K, r, sigma, T, L, N, M){;}

    /// @param s un flottant indiquant le "point de l'espace"
    /// en lequel le payoff est évalué à l'instant T
    /// @param t un flottant indiquant l'instant en lequel est évalué le payoff 
    /// @return La valeur de stilde correspondant au couple (s,t)
    /// @warning s doit être supérieur strictement à 0. Pour s=0, stilde=-infini
    double stilde(double s, double t) const
    {
        if(s <= 0){
            throw "stilde is not defined";
        }
        return log(s/get_K()) + (get_r() - pow(get_sigma(),2)/2)*(get_T()-t);
    }

    /// @brief Discrétisation des t_tildes avec un pas régulier
    /// @param m un integer indiquant le numéro du point temporel 
    /// @return le m ième point de l'intervalle [0,T] discrétisé avec un
    /// pas constant en M segments 
    double ttilde(int m) const { return m*T_/M_;}

    /// @brief Discrétisation des s_tildes avec un pas régulier
    /// @param i un integer indiquant le numéro du point désiré 
    /// @return le i ième point de l'intervalle des stildes discrétisé avec un
    /// pas constant en N segments
    double stilde(int i) const { return (log(L_/(K_*N_)) + (r_ - pow(sigma_,2)/2) + i*delta_stilde());}


    /// @param ttilde un flottant indiquant l'instant en lequel est évalué le payoff 
    /// lorsque s_tilde atteint la borne supérieure de son intervalle (s_tilde = log(L/K)+(r-sigma^2/2)ttilde)
    /// @return La valeur associée du payoff à l'instant ttilde (vaut toujours 0 pour un call)
    double C_stildeN(double ttilde) const { return 0;}

    /// @param ttilde un flottant 
    /// @return La valeur du payoff associée à ttilde lorsque stilde=-infini 
    double C_stilde0(double ttilde) const {return get_K();}

    /// @param stilde un flottant 
    /// @return La valeur du payoff associé à stilde lorsque ttilde = 0
    double C_ttilde0(double stilde) const{
        if(stilde < 0){
            return get_K()*(1 - exp(stilde));
        }
        return 0;
    }
    
    /// @return Un vecteur de taille N-1 contenant les valeurs
    /// du payoff à l'instant 0 en chaque point de l'espace: C(0,s_1),...,C(0,s_{N-1}) 
    /// @warning Les conditions aux bords C(0,s_0) et C(0,L) sont déjà connues,
    /// donc ne sont pas incluses dans le vecteur retourné
    std::vector<double> C_t0() const;
};
} // namespace Reduced

#endif /* _PUT_H_ */






