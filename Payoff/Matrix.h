#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <iostream>

///
/// Les matrices (de même que les vecteurs) sont néccesaires car interviennent 
/// naturellement dans la résolution de l'équation de Black Scholes
/// 
///
class Matrix 
{
    private:
    /// @warning Seules les matrices carrées sont implémentées, si bien que n_ 
    /// est le nombre de lignes mais aussi de colonnes
    int n_;
    double* data_;

    public:
    /// @brief le constructeur avec le paramètre "taille" d'une matrice
    Matrix(int n);
    /// @brief le constructeur de copie d'une matrice
    Matrix(const Matrix & m);
    /// @brief le destructeur d'une matrice
    ~Matrix();
    /// @return le nombre de lignes (ou bien colonnes) d'une matrice
    int get_n() const { return n_; }
    /// @brief l'opérateur permettant d'accéder à l'élément (i,j) dans la matrice (Version Getter) 
    double operator()(int i, int j) const;
    /// @brief l'opérateur permettant d'accéder à l'élément (i,j) dans la matrice (Version Setter)  
    double & operator()(int i, int j);
    /// @return true si l'objet courant (matrice) est inversible, false sinon
    bool is_invertible() const;
    /// @brief Fonction intermédiaire pour implémenter le déterminant d'une matrice
    Matrix sub(int l) const;
    /// @return le déterminant d'une matrice
    double det() const;
    /// @return true si l'objet courant (matrice) est triangulaire supérieure, false sinon
    bool is_triangular_sup() const;
    /// @return true si l'objet courant (matrice) est triangulaire inférieure, false sinon
    bool is_triangular_inf() const;
    /// @return true si l'objet courant (matrice) admet une décomposition LU, false sinon
    /// @warning la matrice doit impérativement être tridiagonale
    bool is_lu_decomp() const;
};

/// @brief Permet d'afficher le contenu d'une matrice
std::ostream & operator<<(std::ostream & os, const Matrix & m);

/// @param m une référence à une matrice
/// @param v une référence à un vecteur de flottants
/// @return le vecteur résultant du produit matriciel entre m et v
/// @warning le nombre de colonnes de m doit être égale au nombre de lignes de v
std::vector<double> operator*(const Matrix & m, const std::vector<double> & v);

/// @param A une matrice tridiagonale admettant une décomposition LU 
/// @param b un vecteur colonne
/// @return le vecteur solution de l'equation Ax=b en tirant profit de A=LU
/// @warning A doit impérativement être tridiagonale. Être LU-décomposable n'est pas suffisant
std::vector<double> solve(const Matrix & A, const std::vector<double> & b);

/// @param v1 un vecteur de flottants
/// @param v2 un autre vecteur de flottants
/// @param v le vecteur somme de v1 et v2, tel que: v[i]=v1[i]+v2[i]
/// @warning v1 et v2 doivent avoir le même nombre d'éléments
std::vector<double> operator+(const std::vector<double> & v1, const std::vector<double> & v2);

/// @brief Permet d'afficher le contenu d'un vecteur
std::ostream & operator<<(std::ostream & os, const std::vector<double> & v);

#endif /* _MATRIX_H_ */
