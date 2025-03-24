#include "wyrazenia.hpp"
#include "operatory1.hpp"
#include "operatory2.hpp"
#include "stale.hpp"

int main()
{
    Zmienna *x = new Zmienna("x");
    Zmienna *y = new Zmienna("y");
    x->dodaj_zmienna(0);
    y->dodaj_zmienna(0);


    Wyrazenie *a = new dziel(
        new mnoz(
            new odejmij(
                x,
                new Liczba(1)
            ),
            x
        ),
        new Liczba(2)
    );

    Wyrazenie *b = new dziel(
        new dodaj(
            new Liczba(3),
            new Liczba(5)
        ),
        new dodaj(
            new Liczba(2),
            new mnoz(
                x,
                new Liczba(7)
            )
        )
    );

    Wyrazenie *c = new odejmij(
        new dodaj(
            new Liczba(2),
            new mnoz(
                x,
                new Liczba(7)
            )
        ),
        new dodaj(
            new mnoz(
                y,
                new Liczba(3)
            ),
            new Liczba(5)
        )
    );

    Wyrazenie *d = new dziel(
        new Cos(
            new mnoz(
                new dodaj(
                    x,
                    new Liczba(1)
                ),
                new pi()
            )
        ),
        new potega(
            new e(),
            new potega(
                x,
                new Liczba(2)
            )
        )
    );

    Wyrazenie *e = new odejmij(
        new pi(),
        new dodaj(
            new Liczba(2),
            new mnoz(
                new Zmienna("x"),
                new Liczba(7)
            )
        )
    );


    // cout << a->zapis() << endl;
    // cout << b->zapis() << endl;
    // cout << c->zapis() << endl;
    // cout << d->zapis() << endl;

    // for(double i=0; i <=100; i++)
    // {
    //     x->zmien_wartosc(i/100);
    //     y->zmien_wartosc(i/100);
    //     cout<<endl;
    //     cout<<"x=y="<<i/100<<": "<<a->zapis()<<" = "<<a->oblicz()<<endl;
    //     cout<<"x=y="<<i/100<<": "<<b->zapis()<<" = "<<b->oblicz()<<endl;
    //     cout<<"x=y="<<i/100<<": "<<c->zapis()<<" = "<<c->oblicz()<<endl;
    //     cout<<"x=y="<<i/100<<": "<<d->zapis()<<" = "<<d->oblicz()<<endl;
    // }

    // // testy innnych wyrazeń
    // cout << endl;
    // Wyrazenie *q = new logarytm(new Liczba(2), new Liczba(8));
    // Wyrazenie *w = new Ln(new e());
    // cout << q->zapis() << "= " << q->oblicz() << endl;
    // cout << w->zapis() << "= " << w->oblicz() << endl;

    // Wyrazenie *e = new Bezwzgl(new Przeciw(q));
    // cout << e->zapis() << "= " << e->oblicz() << endl;

    // Wyrazenie *r = new Exp(new Przeciw(new dodaj(q,w)));
    // cout << r->zapis() << "= " << r->oblicz() << endl;
    double i = 0;
    double j = 0;
    cout << "\n x = " << i << " ";
    x->zmien_wartosc(i);
    cout << "\n y = " << j << "\n";
    y->zmien_wartosc(j);
    cout << a->zapis() << " = " << a->oblicz() << endl;
    cout << b->zapis() << " = " << b->oblicz() << endl;
    cout << c->zapis() << " = " << c->oblicz() << endl;
    cout << d->zapis() << " = " << d->oblicz() << endl;
    cout << e->zapis() << " = " << e->oblicz() << endl;

    i = 0;
    j = 0.5;
    cout << "\n x = " << i << " ";
    x->zmien_wartosc(i);
    cout << "\n y = " << j << "\n";
    y->zmien_wartosc(j);
    cout << a->zapis() << " = " << a->oblicz() << endl;
    cout << b->zapis() << " = " << b->oblicz() << endl;
    cout << c->zapis() << " = " << c->oblicz() << endl;
    cout << d->zapis() << " = " << d->oblicz() << endl;
    cout << e->zapis() << " = " << e->oblicz() << endl;

    i = 0.5;
    j = 0;
    cout << "\n x = " << i << " ";
    x->zmien_wartosc(i);
    cout << "\n y = " << j << "\n";
    y->zmien_wartosc(j);
    cout << a->zapis() << " = " << a->oblicz() << endl;
    cout << b->zapis() << " = " << b->oblicz() << endl;
    cout << c->zapis() << " = " << c->oblicz() << endl;
    cout << d->zapis() << " = " << d->oblicz() << endl;
    cout << e->zapis() << " = " << e->oblicz() << endl;

    i = 0.5;
    j = 0.5;
    cout << "\n x = " << i << " ";
    x->zmien_wartosc(i);
    cout << "\n y = " << j << "\n";
    y->zmien_wartosc(j);
    cout << a->zapis() << " = " << a->oblicz() << endl;
    cout << b->zapis() << " = " << b->oblicz() << endl;
    cout << c->zapis() << " = " << c->oblicz() << endl;
    cout << d->zapis() << " = " << d->oblicz() << endl;
    cout << e->zapis() << " = " << e->oblicz() << endl;

    i = 1;
    j = 1;
    cout << "\n x = " << i << " ";
    x->zmien_wartosc(i);
    cout << "\n y = " << j << "\n";
    y->zmien_wartosc(j);
    cout << a->zapis() << " = " << a->oblicz() << endl;
    cout << b->zapis() << " = " << b->oblicz() << endl;
    cout << c->zapis() << " = " << c->oblicz() << endl;
    cout << d->zapis() << " = " << d->oblicz() << endl;
    cout << e->zapis() << " = " << e->oblicz() << endl;

    return 0;
}

