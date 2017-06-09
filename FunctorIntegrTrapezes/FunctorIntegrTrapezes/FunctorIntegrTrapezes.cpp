/**
 *
 * @file    IntegrTrapezes.cpp
 *
 * @authors D. Mathieu
 *
 * @date    06/11/2007
 *
 * @version V1.0
 *
 * @brief   Integration par la methodes des trapezes au moyen de
 *             pointeurs de fonctions

 *
 **/
#include <iostream>
#include <cmath>               // cos(), sin(), M_PI_2

using namespace std;

namespace
{
    typedef double (*FdeX) (double);


    template <typename T, typename TRes>
    class IUnaryFunction{

      public :

        virtual ~IUnaryFunction (void) {}
        virtual TRes operator () (const T &) const throw () = 0;

    }; // IUnaryFunction


    class CFctor_sin : public IUnaryFunction <double,double>{
    public:
        virtual ~CFctor_sin (void) {}
        virtual double operator () (const double & T) const throw () {
            return sin(T);
        }

    };

    class CFctor_cos : public IUnaryFunction <double,double>{
    public:
        virtual ~CFctor_cos (void) {}
        virtual double operator () (const double & T) const throw () {
            return cos(T);
        }

    };

    double IntegrTrapezes (const IUnaryFunction <double,double>  & f, double a, double b, unsigned n)
    {
        double S     = (f (a) + f (b)) / 2.0; 
        double Delta = (b - a) / double (n);

        for ( ; --n; ) S += f (a += Delta);

        return S * Delta;

    } // IntegrTrapezes

    void TestIntegrTrapezes (void)
    {
        cout << "IntegrTrapezes : \n\n";

        cout << "Methode des trapezes : \n";

        cout << "S (cos (x)) entre 0 et +Pi/2  avec   5 intervalles = " 
             << IntegrTrapezes (CFctor_cos(), 0, M_PI_2,   5) << '\n';

        cout << "S (cos (x)) entre 0 et +Pi/2  avec  10 intervalles = " 
             << IntegrTrapezes (CFctor_cos(), 0, M_PI_2,  10) << '\n';

        cout << "S (cos (x)) entre 0 et +Pi/2  avec  50 intervalles = " 
             << IntegrTrapezes (CFctor_cos(), 0, M_PI_2,  50) << '\n';

        cout << "S (cos (x)) entre 0 et +Pi/2  avec 100 intervalles = " 
             << IntegrTrapezes (CFctor_cos(), 0, M_PI_2, 100) << '\n';

        cout << '\n';

        cout << "S (sin (x)) entre -Pi/2 et 0  avec   5 intervalles = " 
             << IntegrTrapezes (CFctor_sin(), -M_PI_2, 0,   5) << '\n';

        cout << "S (sin (x)) entre -Pi/2 et 0  avec  10 intervalles = " 
             << IntegrTrapezes (CFctor_sin(), -M_PI_2, 0,  10) << '\n';

        cout << "S (sin (x)) entre -Pi/2 et 0  avec  50 intervalles = " 
             << IntegrTrapezes (CFctor_sin(), -M_PI_2, 0,  50) << '\n';

        cout << "S (sin (x)) entre -Pi/2 et 0  avec 100 intervalles = " 
             << IntegrTrapezes (CFctor_sin(), -M_PI_2, 0, 100) << '\n';

    } // TestIntegrTrapezes()


} // namespace anonyme

int main (void)
{
    TestIntegrTrapezes ();

    return 0;

} // main()
