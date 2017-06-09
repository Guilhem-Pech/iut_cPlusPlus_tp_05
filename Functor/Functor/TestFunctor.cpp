/**
 *
 * @file   TestFunctor.cpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    27/04/2010
 *
 * @version V1.0
 *
 * @brief   Premier functor 
 *
 **/
#include <iostream>
#include <string>
#include <cctype>               // tolower(), toupper()
#include <cassert>

using namespace std;

namespace 
{
    class CToLower
    {
    public:
        virtual ~CToLower(){}
        virtual int operator () (int x) noexcept {
            return tolower (x);
        }

        // ToDo

    }; // CToLower

    typedef int (* FctInt2Int_t) (int);
    string & Moulinette (string & Str, CToLower Transf)
    {
        for (string::size_type i (Str.size ()); i--; )
            Str [i] = Transf (Str [i]);

        return Str;

    } // Moulinette()

    void TestFunctor (void)
    {
        cout << "Functor : ";

        string Ligne  ("AZECv qrgWSg wrV  wfdgWFDHG  wdfGWXCV");
        string Minusc ("azecv qrgwsg wrv  wfdgwfdhg  wdfgwxcv");

        // ToDo 
        assert (Minusc == Moulinette (Ligne, CToLower() ));

        cout << "OK\n";

    } // TestFunctor()

} // namespace anonyme

int main (void)
{
    /*      */    TestFunctor ();     /*           */

    return 0;

} // main()
