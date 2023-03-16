#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
class Tache
{
public:
    int travail; // nombre de la gamme
    int t;       // numero de la tache
    int p;
    int r;
    int d;
    int machine; // numero de la machine de cette tache
    int prec;
    int Lmin;
    int Smin;
    int Fmin;
    int Lmax;
    int Smax;
    int Fmax;
};

class Gamme
{
public:
    int n;         // nombre des taches dans une gamme
    Tache lis[40]; // 40 tache dans cette gamme
    void initialiser()
    {
        int i;
        i = 0;
        while (lis[i].t != 0)
        {
            i++;
        }
        n = i;
    }
    int r(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].r);
                break;
            }
        }
        return test;
    }
    int d(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].d);
                break;
            }
        }
        return test;
    }
    int p(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].p);
                break;
            }
        }
        return test;
    }
    int machine(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].machine);
            }
        }
        return test;
    }
    int Smin(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].Smin);
                break;
            }
        }
        return test;
    }
    int Fmin(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].Fmin);
                break;
            }
        }
        return test;
    }
    int Smax(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].Smax);
                break;
            }
        }
        return test;
    }
    int Fmax(int x)
    {
        int test;
        for (int i = 0; i < n; i++)
        {
            if (lis[i].t == x)
            {
                test = (lis[i].Fmax);
                break;
            }
        }
        return test;
    }
};

class Machine
{
public:
    int num;
    int nbrt;
    int nbrs;
    Tache tab[40];        // 40
    int tabsom[40];       // 40
    int tabpyr[40][40];   // 40 sommet * 40 tache appartien a un sommet//40*40
    int tabpyr_r[40][40]; // 40*40
    int tabpyr_d[40][40]; // 40*40
    // ********* les fonctions ************
    void initialiser_machine(int j)
    {
        num = j;
        int i;
        i = 0;
        while (tab[i].t != 0)
        {
            i++;
        }
        nbrt = i;
    }
    void sommet_pyramide()
    {
        int i, j, n, m, k, o;

        for (k = 0; k < 40; k++)
            for (o = 0; o < 40; o++)
                tabpyr[k][o] = -1;

        k = 0;
        o = 0;
        for (i = 0; i < 40; i++)
        {
            tabsom[i] = 0;
        }

        for (i = 0; i < nbrt; i++)
        {
            n = 0;
            m = 0;
            for (j = 0; j < nbrt; j++)
            {
                if ((tab[j].r < tab[i].r) && (tab[j].d > tab[i].d))
                {
                    n++;
                }
                else if ((tab[j].r > tab[i].r) && (tab[j].d < tab[i].d))
                {
                    m++;
                }
            }
            if ((n != 0) && (m == 0))
            {
                tabsom[k] = tab[i].t;
                k++;
            }
            else if ((n == 0) && (m == 0))
            {
                tabsom[k] = tab[i].t;

                k++;
            }
        }

        int l, min, min_r;
        o = 0;
        // يرتب لي سومي مللي عندها أصغر r
        for (l = 0; (l < k); l++)
        {
            min = info_r(tabsom[l]);
            min_r = l;

            for (o = l + 1; (o < k); o++)
            {
                if (min > info_r(tabsom[o]))
                {
                    min_r = o;
                    min = info_r(tabsom[o]);
                }
            }

            {
                int c;
                c = tabsom[min_r];
                tabsom[min_r] = tabsom[l];
                tabsom[l] = c;
            }
        }

        nbrs = k;

        int b;
        // remplire tabpyr
        for (n = 0; n < k; n++)
        {
            for (j = 0; j < nbrt; j++)
            {
                if (tabsom[n] == tab[j].t)
                {
                    o = 0;
                    b = 0;
                    for (int l = 0; l < nbrt; l++)
                    {
                        if ((tab[l].r < tab[j].r) && (tab[l].d > tab[j].d))
                        {
                            tabpyr[n][o] = tab[l].t;

                            o++;
                            b++;
                        }
                    }
                    if (b == 0)
                        tabpyr[n][o] = 0;
                }
            }
        }
    }

    void ordre_r()
    {
        for (int i = 0; i < 40; i++)
        {

            int t[40], j, o, l, k, n;
            k = 0;
            o = 0;

            for (j = 0; j < 40; j++)
            {
                if (tabpyr[i][j] != -1)
                {
                    t[k] = tabpyr[i][j];

                    k++;
                }
            }
            // ترتيب ال t[] حساب ال r
            if (k != 0)
            {
                n = 0;
                int min, min_r;
                for (l = 0; (l < k) && (t[l] != 0) && (t[l] != -1); l++)
                {
                    min = info_r(t[l]);
                    min_r = l;

                    for (o = l + 1; (o < k) && (t[o] != 0); o++)
                    {
                        if (min > info_r(t[o]))
                        {
                            min_r = o;
                            min = info_r(t[o]);
                        }
                    }

                    {
                        int c;
                        c = t[min_r];
                        t[min_r] = t[l];
                        t[l] = c;
                    }
                }
            }
            n = 0;
            for (int j = 0; j < 40; j++)
            {
                if (n < k)
                {
                    tabpyr_r[i][j] = t[n];
                    n++;
                }
                else
                    tabpyr_r[i][j] = -1;
            }
            for (j = 0; j < k; j++)
            {
                t[j] = 0;
            }
        }
    }
    void ordre_d()
    {
        for (int i = 0; i < 40; i++)
        {

            int t[40], j, o, l, k, n;
            k = 0;
            o = 0;

            for (j = 0; j < 40; j++)
            {
                if (tabpyr[i][j] != -1)
                {
                    t[k] = tabpyr[i][j];

                    k++;
                }
            }

            if (k != 0)
            {
                n = 0;
                int min, min_r;
                for (l = 0; (l < k) && (t[l] != 0) && (t[l] != -1); l++)
                {
                    min = info_d(t[l]);
                    min_r = l;

                    for (o = l + 1; (o < k) && (t[o] != 0); o++)
                    {
                        if (min > info_d(t[o]))
                        {
                            min_r = o;
                            min = info_d(t[o]);
                        }
                    }

                    {
                        int c;
                        c = t[min_r];
                        t[min_r] = t[l];
                        t[l] = c;
                    }
                }
            }
            n = 0;
            for (int j = 0; j < 40; j++)
            {
                if (n < k)
                {
                    tabpyr_d[i][j] = t[n];
                    n++;
                }
                else
                    tabpyr_d[i][j] = -1;
            }
            for (j = 0; j < k; j++)
            {
                t[j] = 0;
            }
        }
    }
    /* void sequence();*/
    int info_r(int a)
    {
        int test;
        for (int j = 0; j < nbrt; j++)
        {
            if (tab[j].t == a)
            {
                test = tab[j].r;
                break;
            }
        }
        return test;
    }
    int info_d(int a)
    {
        int test;
        for (int j = 0; j < nbrt; j++)
        {
            if (tab[j].t == a)
            {
                test = tab[j].d;
                break;
            }
        }
        return test;
    }
    int info_p(int a)
    {
        int test;
        for (int j = 0; j < nbrt; j++)
        {
            if (tab[j].t == a)
            {
                test = tab[j].p;
                break;
            }
        }
        return test;
    }
    int U(int x)
    {
        int i, j = 0, t = 0;
        int k = 0; // crated by islam
        int resultat = 0;
        // *****
        for (i = 0; i <= nbrs; i++)
        {
            if (i != nbrs)
            {
                if (x == tabsom[i])
                {
                    resultat = i + 1;
                    break;
                }
            }
            else
            {
                while ((k < 40) && (t == 0) && (tabpyr[k][j] != -1))
                {
                    while ((j < 40) && (t == 0) && (tabpyr[k][j] != -1) && (tabpyr[k][j] != 0))
                    {
                        if (x == tabpyr[k][j])
                        {
                            t = 1;
                        }
                        j++;
                    }
                    k++;
                }
                resultat = i;
                break;
            }
        }
        return resultat;
    }
    int V(int x)
    {
        int i, j, t, m, resultat;
        for (i = 0; i <= nbrs; i++)
        {
            if (i != nbrs)
            {
                if (x == tabsom[i])
                {
                    resultat = i + 1;
                    break;
                }
            }
            else
            {
                for (i = 0; i < 40; i++)
                {
                    j = 0;
                    t = 0;
                    while ((j < 40) && (tabpyr[i][j] != -1) && (t == 0))
                    {
                        if (tabpyr[i][j] == x)
                        {
                            m = i;
                            t = 1;
                        }
                        j++;
                    }
                }
                resultat = m + 1;
                break;
            }
        }
        return resultat;
    }
    int L_min(int m)
    {
        int i, j, k, l, x, t;
        int tabseq[40];
        k = U(m);

        j = 0;
        for (i = 0; i < nbrt; i++)
        {
            if (V(tab[i].t) < k)
            {
                tabseq[j] = tab[i].t;
                j++;
            }
        }

        for (i = j; i < 40; i++)
            tabseq[i] = -1;

        /*cout<<"********debu**************"<<endl;
        for(i=0;(i<40)&&(tabseq[i]!=-1);i++)
                cout<<"h"<<tabseq[i]<<endl;
        cout<<"**********fin************"<<endl;*/
        //*************ordonner*******************
        int min, min_r, c;
        for (i = 0; (i < 40) && (tabseq[i] != -1); i++)
        {
            min = info_r(tabseq[i]);
            min_r = i;
            for (j = i + 1; (j < 40) && (tabseq[j] != -1); j++)
            {
                if (min > info_r(tabseq[j]))
                {
                    min = info_r(tabseq[j]);
                    min_r = j;
                }
            }
            c = tabseq[i];
            tabseq[i] = tabseq[min_r];
            tabseq[min_r] = c;
        }

        //*************calculer*******************

        if (tabseq[0] != -1)
        {
            x = info_r(tabseq[0]) + info_p(tabseq[0]);
            for (i = 1; (i < 40) && (tabseq[i] != -1); i++)
            {
                if (info_r(tabseq[i]) >= x)
                    x = info_r(tabseq[i]) + info_p(tabseq[i]);
                else
                    x = x + info_p(tabseq[i]);
            }
            if (x > info_r(m))
                return x + info_p(m) - info_d(m);
            else
                return info_r(m) + info_p(m) - info_d(m);
        }
        else
        {
            return info_r(m) + info_p(m) - info_d(m);
        }
    }
    int L_max(int m)
    {
        int i, j, k, l, x, p, h, seq1[40], seq2[40];

        x = V(m);
        j = 0;
        k = 0;

        for (i = 0; i < nbrt; i++)
        {
            if (V(tab[i].t) < x)
            {
                seq1[j] = tab[i].t;
                j++;
            }
            if ((U(tab[i].t) <= x) && (x <= V(tab[i].t)))
            {
                seq2[k] = tab[i].t;
                k++;
            }
        }
        for (i = j; i < 40; i++)
            seq1[i] = -1;

        for (i = k; i < 40; i++)
            seq2[i] = -1;

        //*************ordonner_seq1*******************
        int min, min_d, c;
        for (i = 0; (i < 40) && (seq1[i] != -1); i++)
        {
            min = info_d(seq1[i]);
            min_d = i;
            for (j = i + 1; (j < 40) && (seq1[j] != -1); j++)
            {
                if (min > info_d(seq1[j]))
                {
                    min = info_d(seq1[j]);
                    min_d = j;
                }
            }
            c = seq1[i];
            seq1[i] = seq1[min_d];
            seq1[min_d] = c;
        }
        //*************ordonner_seq2*******************
        //******************P-{s}********************
        int t, indice, som;
        t = 0;
        for (i = 0; (i < 40) && (seq2[i] != -1) && (t == 0); i++)
        {
            j = 0;
            while ((j < nbrs) && (t == 0))
            {
                if (seq2[i] == tabsom[j])
                {
                    t = 1;
                    indice = i;
                    som = seq2[i];
                }
                else
                    j++;
            }
        }
        for (i = indice; i < 40; i++)
            seq2[i] = seq2[i + 1];
        // ttm7a 1
        /*
        cout<<"********seq25*********"<<endl;
        for(i=0;(i<40)&&(seq2[i]!=-1);i++)
                cout<<seq2[i]<<endl;
        */
        // ttm7a 1
        //*******************A_et_B****************************

        int a[40], b[40];
        k = 0;
        l = 0;
        for (i = 0; (i < 40) && (seq2[i] != -1); i++)
        {
            if (info_d(seq2[i]) > info_d(m))
            {
                a[k] = seq2[i];
                k++;
            }
            else
            {
                if (seq2[i] != m)
                {
                    b[l] = seq2[i];
                    l++;
                }
            }
        }
        for (i = k; i < 40; i++)
            a[i] = -1;

        for (i = l; i < 40; i++)
            b[i] = -1;
        /*cout<<"********A1*********"<<endl;
        for(i=0;(i<40)&&(a[i]!=-1);i++)
                cout<<a[i]<<endl;*/

        //*************ordonner_A*******************
        int min_r;
        for (i = 0; (i < 40) && (a[i] != -1); i++)
        {
            min = info_r(a[i]);
            min_r = i;
            for (j = i + 1; (j < 40) && (a[j] != -1); j++)
            {
                if (min > info_r(a[j]))
                {
                    min = info_r(a[j]);
                    min_r = j;
                }
            }
            c = a[i];
            a[i] = a[min_r];
            a[min_r] = c;
        }
        //*************ordonner_B*******************

        for (i = 0; (i < 40) && (b[i] != -1); i++)
        {
            min = info_d(b[i]);
            min_d = i;
            for (j = i + 1; (j < 40) && (b[j] != -1); j++)
            {
                if (min > info_d(b[j]))
                {
                    min = info_d(b[j]);
                    min_d = j;
                }
            }
            c = b[i];
            b[i] = b[min_d];
            b[min_d] = c;
        }

        //***************Seq22(A<s<B)**********************
        int seq22[40];
        j = 0;
        i = 0;
        k = 0;
        while ((i < 40) && (a[i] != -1))
        {
            seq22[j] = a[i];
            i++;
            j++;
        }
        seq22[j] = som;
        j++;
        while ((k < 40) && (b[k] != -1))
        {
            seq22[j] = b[k];
            k++;
            j++;
        }

        for (i = j; i < 40; i++)
            seq22[i] = -1;

        //***************Seq3(Seq1<Seq22)**********************
        int seq3[40];
        j = 0;
        i = 0;
        k = 0;
        while ((i < 40) && (seq1[i] != -1))
        {
            seq3[j] = seq1[i];
            i++;
            j++;
        }

        while ((k < 40) && (seq22[k] != -1))
        {
            seq3[j] = seq22[k];
            k++;
            j++;
        }

        for (i = j; i < 40; i++)
            seq3[i] = -1;

        /*cout<<"********seq1*********"<<endl;
                for(i=0;(i<40)&&(seq1[i]!=-1);i++)
                        cout<<seq1[i]<<endl;
        cout<<"********seq2*********"<<endl;
                for(i=0;(i<40)&&(seq2[i]!=-1);i++)
                        cout<<seq2[i]<<endl;
        cout<<"********A*********"<<endl;
                for(i=0;(i<40)&&(a[i]!=-1);i++)
                        cout<<a[i]<<endl;
        cout<<"********B*********"<<endl;
                for(i=0;(i<40)&&(b[i]!=-1);i++)
                        cout<<b[i]<<endl;
        cout<<"********Seq22*********"<<endl;
                for(i=0;(i<40)&&(seq22[i]!=-1);i++)
                        cout<<seq22[i]<<endl;
        cout<<"********finale*********"<<endl;
                for(i=0;(i<40)&&(seq3[i]!=-1);i++)
                        cout<<seq3[i]<<endl;*/
        //*******************calculer*********************
        if (seq3[0] != m)
        {
            x = info_r(seq3[0]) + info_p(seq3[0]);
            for (i = 1; (i < 40) && (seq3[i] != -1) && (seq3[i] != m); i++)
            {
                if (info_r(seq3[i]) >= x)
                    x = info_r(seq3[i]) + info_p(seq3[i]);
                else
                    x = x + info_p(seq3[i]);
            }

            if (x > info_r(m))
                return x + info_p(m) - info_d(m);
            else
                return info_r(m) + info_p(m) - info_d(m);
        }
        else
        {
            return info_r(m) + info_p(m) - info_d(m);
        }
    }
    void machine_calculer()
    {
        for (int i = 0; i < nbrt; i++)
        {
            tab[i].Lmin = L_min(tab[i].t);
            tab[i].Smin = tab[i].Lmin + info_d(tab[i].t) - info_p(tab[i].t);
            tab[i].Fmin = tab[i].Smin + info_p(tab[i].t);
            tab[i].Lmax = L_max(tab[i].t);
            tab[i].Smax = tab[i].Lmax + info_d(tab[i].t) - info_p(tab[i].t);
            tab[i].Fmax = tab[i].Smax + info_p(tab[i].t);
        }
    }
    int dernier_sommet(int x)
    {
        int i = 0, j, m = 0;
        for (i = 0; i < nbrs; i++)
        {
            if (tabsom[i] == x)
                return tabsom[i];
        }
        if (i == nbrs)
        {
            i = 0;
            while (i < nbrt)
            {
                j = 0;
                while (j < nbrt)
                {
                    if (tabpyr[i][j] == x)
                        m = i;
                    j++;
                }
                i++;
            }
            return tabsom[m];
        }
    }
    int premier_sommet(int x)
    {
        int i = 0, j;
        for (i = 0; i < nbrs; i++)
        {
            if (tabsom[i] == x)
                return tabsom[i];
        }
        if (i == nbrs)
        {
            i = 0;
            bool trouve = false;
            while (i < nbrt && !trouve)
            {
                j = 0;
                while (j < nbrt && !trouve)
                {
                    if (tabpyr[i][j] == x)
                        trouve = true;
                    j++;
                }
                i++;
            }
            return tabsom[i - 1];
        }
    }
    /*
    void seq()
    {
        foreach (int x, tab_seq)
            cout << x << "<";
        cout << endl;
    }
    */
    int S_dom()
    {
        int i, j, m, o, l, p, k, s, t;
        int tab1[40][2];
        bool test;
        m = 0;
        s = 1;
        //************************************
        for (i = 0; i < 40; i++)
        {
            for (j = 0; j < 2; j++)
            {
                tab1[i][j] = -1;
            }
        }

        //*************************************
        for (i = 0; i < 40; i++)
        {
            for (j = 0; (j < 40) && (tabpyr[i][j] != -1); j++)
            {
                test = false;
                for (p = 0; (p < 40); p++)
                {
                    if (tabpyr[i][j] == tab1[p][0])
                        test = true;
                }
                if (!test)
                {
                    k = 0;
                    for (o = 0; o < 40; o++)
                    {
                        for (l = 0; (l < 40) && (tabpyr[o][l] != -1); l++)
                        {
                            if (tabpyr[i][j] == tabpyr[o][l])
                                k++;
                        }
                    }
                    if (tabpyr[i][j] != 0)
                    {
                        tab1[m][0] = tabpyr[i][j];
                        tab1[m][1] = k;
                        m++;
                    }
                }
            }
        }
        //****************************calculer*********
        // return 1;

        for (i = 0; i < nbrs; i++)
        {
            k = 0;
            for (j = 0; (j < 40) && (tab1[j][1] != -1); j++)
            {
                if (tab1[j][1] == i + 1)
                    k++;
            }
            t = pow((1 + i + 1), k);
            s = s * t;
        }

        /* for(i=0;i<40;i++)
         {
             if(tab1[i][0]!=-1)
            cout<<tab1[i][0]<<"--"<<tab1[i][1]<<endl;
         }
         */

        if (s != 1)
            cout << "la machine " << num << " est flexible" << endl;
        else
            cout << "la machine " << num << " n'est pas flexible" << endl;
        cout << "la valeur du S_dom est: ";

        return s;
    }
    /* void SeqToChaine(); */
};

class Mainview
{
public:
    int nombreGammes;   // nombre des gammes
    int nombreMachines; // nombre des machines
    Gamme gammes[40];
    Machine machines[40];
    int numero = 0;
    int nember_of_incoher_enitial;
    int nember_of_incoher_final;
    int incoher_min[30][3];
    int incoher_max[30][3];
    int Fin_min;
    int Fin_max;
    int num_page;
    // ******** les fonctions **********
    void initialiser_atelier()
    {
        char numero_To_String[2];
        sprintf(numero_To_String, "%d", this->numero);

        char fileName[20] = "ex01.txt";

        for (int i = 1; i <= 69; i++)
        {
            if (numero == i)
            {
                if (i < 10)
                {
                    fileName[2] = '0';
                    fileName[3] = numero_To_String[0];
                    cout << fileName << endl;
                    break;
                }
                else
                {
                    fileName[2] = numero_To_String[0];
                    fileName[3] = numero_To_String[1];
                    cout << fileName << endl;
                    break;
                }
            }
        }
        ifstream entree(fileName, ios::in);

        entree >> nombreGammes;
        // cout<<"nbr de gammes: "<<g<<endl;
        entree >> nombreMachines;
        // cout<<"nbr de machines: "<<z<<endl;

        for (int j = 0; j < nombreGammes; j++)
        {
            for (int u = 0; u < nombreMachines; u++)
            {
                gammes[j].lis[u].t = 0;
            }
        }

        int i = 0, c, j = 0, test, k;
        // int a,b;
        entree >> c;
        while (i < nombreGammes)
        {
            k = 0;
            gammes[i].lis[k].travail = c;
            test = c;
            entree >> gammes[i].lis[k].machine;
            // gammes[i].lis[k].m=gammes[i].lis[k].m+1;
            entree >> gammes[i].lis[k].p; //
            // entree >> gammes[i].lis[k].m;//
            j++;
            gammes[i].lis[k].t = j;
            gammes[i].lis[k].prec = 0;

            entree >> c;

            while ((c == test) && (j < 600) && (!entree.eof()))
            {
                k++;
                gammes[i].lis[k].travail = c;
                entree >> gammes[i].lis[k].machine;
                // gammes[i].lis[k].m=gammes[i].lis[k].m+1;
                entree >> gammes[i].lis[k].p; //
                // entree >> gammes[i].lis[k].m;//
                j++;
                gammes[i].lis[k].t = j;
                gammes[i].lis[k].prec = j - 1;
                entree >> c;
            }
            i++;
        }

        for (int i = 0; i < nombreGammes; i++)
        {
            gammes[i].initialiser();
        }
    }
    void calculer_ford()
    {
        int i;
        for (i = 0; i < nombreGammes; i++)
        {
            gammes[i].lis[0].r = 0;
        }

        int max = 0, j;
        // remplire de R
        for (i = 0; i < nombreGammes; i++)
        {
            // remplire R
            for (j = 1; j < gammes[i].n; j++)
            {
                gammes[i].lis[j].r = (gammes[i].lis[j - 1].r) + (gammes[i].lis[j - 1].p);
            }
            // max[ (R[n-1]) + (P[n-1])]
            if (max < gammes[i].lis[(gammes[i].n) - 1].r + gammes[i].lis[(gammes[i].n) - 1].p)
            {
                max = gammes[i].lis[(gammes[i].n) - 1].r + gammes[i].lis[(gammes[i].n) - 1].p;
            }
        }
        // remplire d[n-1] = max[ (R[n-1]) + (P[n-1])] ;
        for (i = 0; i < nombreGammes; i++)
        {
            gammes[i].lis[(gammes[i].n) - 1].d = max;
        }
        // remplire D
        for (i = 0; i < nombreGammes; i++)
        {
            for (j = (gammes[i].n) - 2; j >= 0; j--)
            {
                gammes[i].lis[j].d = (gammes[i].lis[j + 1].d) - (gammes[i].lis[j + 1].p);
            }
        }
    }
    void calculer_debut_fin()
    {
        for (int i = 0; i < nombreMachines; i++)
        {
            machines[i].sommet_pyramide();
            machines[i].ordre_r();
            machines[i].ordre_d();
            machines[i].machine_calculer();
        }
        for (int i = 0; i < nombreMachines; i++)
        {
            for (int j = 0; j < machines[i].nbrt; j++)
            {
                for (int k = 0; k < nombreGammes; k++)
                {
                    for (int l = 0; l < gammes[k].n; l++)
                    {
                        if ((machines[i].tab[j].t) == (gammes[k].lis[l].t))
                            gammes[k].lis[l] = machines[i].tab[j];
                    }
                }
            }
        }
    }
    void initialiser_atelier_machines()
    {
        for (int j = 0; j < nombreMachines; j++)
        {
            for (int u = 0; u < 100; u++)
                // machines[j].tab[u].t=0;
                machines[j].tab[u].t = 0;
        }
        int k;
        for (int i = 0; i < nombreGammes; i++)
        {
            for (int j = 0; j < gammes[i].n; j++)
            {
                k = 0;
                while (machines[(gammes[i].lis[j].machine) - 1].tab[k].t != 0)
                {
                    k++;
                }

                machines[(gammes[i].lis[j].machine) - 1].tab[k] = gammes[i].lis[j];
            }
        }

        for (int i = 0; i < nombreMachines; i++)
        {
            machines[i].initialiser_machine(i + 1);
        }
    }
    void taches_incoherentes()
    {

        int i, j, l, k, m, n;
        k = 0;
        m = 0;

        for (i = 0; i < 30; i++)
        {
            for (j = 0; j < 3; j++)
            {
                incoher_max[i][j] = -1;
                incoher_min[i][j] = -1;
            }
        }

        for (i = 0; i < nombreGammes; i++)
        {
            for (j = 0; j < (gammes[i].n) - 1; j++)
            {
                l = 0;
                n = 0;
                if (gammes[i].lis[j].Fmin > gammes[i].lis[j + 1].Smin)
                {
                    incoher_min[k][l] = gammes[i].lis[j].t;
                    incoher_min[k][l + 1] = gammes[i].lis[j + 1].t;
                    incoher_min[k][l + 2] = (gammes[i].lis[j].Fmin) - (gammes[i].lis[j + 1].Smin);
                    k++;
                }
                if (gammes[i].lis[j].Fmax > gammes[i].lis[j + 1].Smax)
                {
                    incoher_max[m][n] = gammes[i].lis[j].t;
                    incoher_max[m][n + 1] = gammes[i].lis[j + 1].t;
                    incoher_max[m][n + 2] = (gammes[i].lis[j].Fmax) - (gammes[i].lis[j + 1].Smax);
                    m++;
                }
            }
        }
        //***********ordonner les 2 tableaux*****************
        int max, o, a, b, c, max_ind;
        //*********incoher_min****************
        for (l = 0; l < 30; l++)
        {
            max = incoher_min[l][2];
            max_ind = l;
            for (o = l + 1; o < 30; o++)
            {
                if (max < incoher_min[o][2])
                {
                    max = incoher_min[o][2];
                    max_ind = o;
                }
            }
            //*********
            c = incoher_min[max_ind][2];
            incoher_min[max_ind][2] = incoher_min[l][2];
            incoher_min[l][2] = c;
            //*********
            a = incoher_min[max_ind][0];
            incoher_min[max_ind][0] = incoher_min[l][0];
            incoher_min[l][0] = a;
            //*********
            b = incoher_min[max_ind][1];
            incoher_min[max_ind][1] = incoher_min[l][1];
            incoher_min[l][1] = b;
        }

        //*********incoher_max****************
        for (l = 0; l < 30; l++)
        {
            max = incoher_max[l][2];
            max_ind = l;
            for (o = l + 1; o < 30; o++)
            {
                if (max < incoher_max[o][2])
                {
                    max = incoher_max[o][2];
                    max_ind = o;
                }
            }
            //*********
            c = incoher_max[max_ind][2];
            incoher_max[max_ind][2] = incoher_max[l][2];
            incoher_max[l][2] = c;
            //*********
            a = incoher_max[max_ind][0];
            incoher_max[max_ind][0] = incoher_max[l][0];
            incoher_max[l][0] = a;
            //*********
            b = incoher_max[max_ind][1];
            incoher_max[max_ind][1] = incoher_max[l][1];
            incoher_max[l][1] = b;
        }
    }
    // la reordonnoncement
    int travail(int x)
    {
        for (int i = 0; i < nombreGammes; i++)
        {
            for (int j = 0; j < gammes[i].n; j++)
            {
                if (gammes[i].lis[j].t == x)
                    return ((gammes[i].lis[j].travail) - 1);
            }
        }
    }
    int pos(int x)
    {
        for (int i = 0; i < nombreGammes; i++)
        {
            for (int j = 0; j < gammes[i].n; j++)
            {
                if (gammes[i].lis[j].t == x)
                    return (j);
            }
        }
    }
    void calculer_debut_fin_machine(int x)
    {
        // gamme to machine
        /* for(int i=0;i<g;i++)
          {
              for(int j=0;j<gammes[i].n;j++)
              {
                  for(int l=0;l<z;l++)
                  {
                      for(int k=0;k<machines[l].nbrt;k++)
                      {
                          if((machines[l].tab[k].t)==(gammes[i].lis[j].t))
                          {
                              machines[l].tab[k]=gammes[i].lis[j];
                          }
                      }


                  }
              }
          }*/

        for (int i = 0; i < nombreGammes; i++)
        {
            for (int j = 0; j < gammes[i].n; j++)
            {
                for (int k = 0; k < machines[x - 1].nbrt; k++)
                {
                    if ((machines[x - 1].tab[k].t) == (gammes[i].lis[j].t))
                    {
                        machines[x - 1].tab[k] = gammes[i].lis[j];
                    }
                }
            }
        }

        /*  Machine t;
          t=machines[x-1];*/

        // calculer
        // cout<<"machine"<<x<<endl;
        machines[x - 1].sommet_pyramide();
        machines[x - 1].ordre_r();
        machines[x - 1].ordre_d();
        machines[x - 1].machine_calculer();
        /* t.sommet_pyramide();
         t.ordre_r();
         t.ordre_d();
         t.machine_calculer();
         machines[x-1]=t;*/

        // machine to gamme
        // for(int i=0;i<z;i++)
        //{
        for (int j = 0; j < machines[x - 1].nbrt; j++)
        {
            for (int k = 0; k < nombreGammes; k++)
            {
                for (int l = 0; l < gammes[k].n; l++)
                {
                    if ((machines[x - 1].tab[j].t) == (gammes[k].lis[l].t))
                        gammes[k].lis[l] = machines[x - 1].tab[j];
                }
            }
        }
        //}
    }
    bool diminuer_Fmin(int i, int x)
    {

        int p;
        p = x;
        bool test;
        test = false;
        int d1, m;
        // m=gammes[travail(i)].m(i);
        // cout<<m<<"avant"<<endl;
        // m=gammes[travail(i)].m(i)-1;
        // cout<<m<<"apres"<<endl;
        d1 = gammes[travail(i)].lis[pos(i)].d;
        // p=gammes[travail(i)].d(machines[m].premier_sommet(i));
        while ((((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i))) <= ((gammes[travail(i)].d(i)) - p)) && (!test))
        {
            gammes[travail(i)].lis[pos(i)].d = (gammes[travail(i)].lis[pos(i)].d) - p;
            // gammes[travail(i)].lis[pos(i)].d=p;
            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
            if ((gammes[travail(i)].Fmin(i)) <= (gammes[travail(i)].Smin(i + 1)))
            {
                test = true;
                taches_incoherentes();
                return true; // cout<<"ffff"<<endl;
            }
            p = (gammes[travail(i)].Fmin(i)) - (gammes[travail(i)].Smin(i + 1));
            // p--;
        }
        /* if(test==false)
             return false;*/
        if (test == false || ((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) > (gammes[travail(i)].d(i)) - p))
        {
            gammes[travail(i)].lis[pos(i)].d = d1;
            // cout<<"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"<<endl;
            int m; // cout<<x<<"jj"<<machines[x].nbrt<<endl;

            m = gammes[travail(i)].machine(i);
            // cout<<m<<"avant"<<endl;
            m = gammes[travail(i)].machine(i) - 1;
            // cout<<m<<"apres"<<endl;

            // cout<<"yyy"<<m<<endl;
            int t[40], t1[40][2], t2[40], k = 0, l = 0, n = 0, a, b, max, max_ind, min, min_ind;

            for (int j = 0; j < 40; j++)
                t[j] = -1;

            for (int j = 0; j < 40; j++)
                for (int o = 0; o < 2; o++)
                    t1[j][o] = -1;

            //*******************u(k)<u(i)et v(k)>=u(k)****************************************
            for (int j = 0; j < machines[m].nbrt; j++)
            {
                // cout<<machines[x].U(i)<<"ee"<<machines[x].U(machines[x].tab[j].t)<<"hh"<<machines[x].tab[j].t<<endl;
                if ((machines[m].U(machines[m].tab[j].t) < machines[m].U(i)) && (machines[m].V(machines[m].tab[j].t) >= machines[m].U(i)))
                {
                    t[k] = machines[m].tab[j].t; // cout<<t[k]<<endl;
                    k++;
                }
            }
            //*******************recherche dans incoher_min u(k)<u(i)etv(k)>=u(k)****************************************
            for (k = 0; k < 40; k++)
            {
                for (int j = 0; j < 40; j++)
                {
                    if ((t[k] == incoher_min[j][l + 1]) && (t[k] != -1))
                    {
                        t1[n][0] = t[k];
                        t1[n][1] = incoher_min[j][l + 2];
                        // cout<<t1[n]<<"oo"<<incoher_min[j][l+1]<<"pp"<<t[k]<<"ll"<<incoher_min[j][l+2]<<endl;
                        n++;
                    }
                }
            }
            //*******************ordonner u(k)<u(i) et v(k)>=u(k)****************************************
            for (l = 0; l < 40; l++)
            {
                max = t1[l][1];
                max_ind = l;
                for (int o = l + 1; o < 40; o++)
                {
                    if (max < t1[o][1])
                    {
                        max = t1[o][1];
                        max_ind = o;
                    }
                }
                //*********
                a = t1[max_ind][0];
                t1[max_ind][0] = t1[l][0];
                t1[l][0] = a;
                //*********
                b = t1[max_ind][1];
                t1[max_ind][1] = t1[l][1];
                t1[l][1] = b;
            }
            //******************************--2cas--*************************************
            //*******************recherche dans les gammes  u(k)<u(i)etv(k)>=u(k)****************************************
            // cout<<"raouf"<<endl;
            for (int j = 0; j < 40; j++)
                t2[j] = t[j];

            for (l = 0; (l < 40) && t2[l] != -1; l++)
            {
                min = gammes[travail(t2[l])].lis[(gammes[travail(t2[l])].n) - 1].Fmin; // cout<<"uu"<<min<<endl;
                min_ind = l;
                for (int o = l + 1; (o < 40) && t2[o] != -1; o++)
                {
                    // cout<<gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n)-1].Fmin;
                    if (min > gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmin)
                    {
                        min = gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmin;
                        min_ind = o;
                    }
                }
                a = t2[min_ind];
                t2[min_ind] = t2[l];
                t2[l] = a;
            }

            //*********************************les 2m�thodes***********************
            bool verif, test1;
            int r1, test_r;
            k = 0;
            verif = false;
                if (verif == false || k == 0)
                {
                    
                    while ((t2[k] != -1) && !verif)
                    {
                        test1 = false;
                        r1 = gammes[travail(t2[k])].r(t2[k]);
                        test_r = (gammes[travail(i)].r(i /*machines[m].premier_sommet(i)*/)) + 1;

                        while (((test_r + (gammes[travail(t2[k])].p(t2[k]))) < (gammes[travail(t2[k])].d(t2[k]))) && !test1)
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].r = test_r;
                            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                            if ((gammes[travail(i)].Fmin(i)) <= (gammes[travail(i)].Smin(i + 1)))
                            {
                                test1 = true;
                                taches_incoherentes();
                            }
                            else
                                test_r = test_r + 1;
                        }
                        if (test1 == true)
                        {
                            verif = true;
                        }
                        else
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].r = r1;
                            k++;
                        }
                    }
                    //**
                    test = verif ;
                }
                //******fin_2cas**************
            //**fin sinon
            
        }
        return test ; 
        //******fin********************
    }
    void augmenter_Smin(int i, int x)
    {

        int p;
        p = x;
        bool test1, test2;
        test1 = false;
        test2 = false;
        int s = gammes[travail(i)].lis[pos(i)].r;
        int m = gammes[travail(i)].machine(i) - 1;
        // p=gammes[travail(i)].d(machines[m].premier_sommet(i))+1;
        while (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + p <= (gammes[travail(i)].d(i))) && (!test1))
        {
            gammes[travail(i)].lis[pos(i)].r = (gammes[travail(i)].lis[pos(i)].r) + p;
            // gammes[travail(i)].lis[pos(i)].r=p;
            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
            if ((gammes[travail(i)].Fmin(i - 1)) <= (gammes[travail(i)].Smin(i)))
            {
                test1 = true;
                taches_incoherentes();
            }
            else
                p = (gammes[travail(i)].Fmin(i - 1)) - (gammes[travail(i)].Smin(i));
            // p++;
        }
        bool trouve = false; // gammes[travail(i)].lis[pos(i)].r=s;
        if (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + p > (gammes[travail(i)].d(i))) && (test1 == false))
        {

            int m = gammes[travail(i)].machine(i) - 1; // cout<<x<<"jj"<<machines[x].nbrt<<endl;
            int t[40], t1[40][2], t2[40], k = 0, l = 0, n = 0, a, b, max, max_ind, min, min_ind;

            for (int j = 0; j < 40; j++)
                t[j] = -1;

            for (int j = 0; j < 40; j++)
                for (int o = 0; o < 2; o++)
                    t1[j][o] = -1;

            //*******************u(k)<u(i)etv(k)>=u(k)****************************************
            for (int j = 0; j < machines[m].nbrt; j++)
            {
                // cout<<machines[x].U(i)<<"ee"<<machines[x].U(machines[x].tab[j].t)<<"hh"<<machines[x].tab[j].t<<endl;
                if ((machines[m].U(machines[m].tab[j].t) < machines[m].U(i)) && (machines[m].V(machines[m].tab[j].t) >= machines[m].U(i)))
                {
                    t[k] = machines[m].tab[j].t; // cout<<t[k]<<endl;
                    k++;
                }
            }
            //*******************recherche dans incoher_min u(k)<u(i)etv(k)>=u(k)****************************************
            for (k = 0; k < 40; k++)
            {
                for (int j = 0; j < 40; j++)
                {
                    if ((t[k] == incoher_min[j][0]) && (t[k] != -1))
                    {
                        t1[n][0] = t[k];
                        t1[n][1] = incoher_min[j][l + 2];
                        // cout<<t1[n]<<"oo"<<incoher_min[j][l+1]<<"pp"<<t[k]<<"ll"<<incoher_min[j][l+2]<<endl;
                        n++;
                    }
                }
            }
            //*******************ordonner u(k)<u(i)etv(k)>=u(k)****************************************
            for (l = 0; l < 40; l++)
            {
                max = t1[l][1];
                max_ind = l;
                for (int o = l + 1; o < 40; o++)
                {
                    if (max < t1[o][1])
                    {
                        max = t1[o][1];
                        max_ind = o;
                    }
                }
                //*********
                a = t1[max_ind][0];
                t1[max_ind][0] = t1[l][0];
                t1[l][0] = a;
                //*********
                b = t1[max_ind][1];
                t1[max_ind][1] = t1[l][1];
                t1[l][1] = b;
            }

            //******************************--2cas--*************************************
            //*******************recherche dans les gammes  u(k)<u(i)etv(k)>=u(k)****************************************
            // cout<<"raouf"<<endl;
            for (int j = 0; j < 40; j++)
                t2[j] = t[j];

            for (l = 0; (l < 40) && t2[l] != -1; l++)
            {
                max = gammes[travail(t2[l])].lis[(gammes[travail(t2[l])].n) - 1].Fmin; // cout<<"uu"<<min<<endl;
                max_ind = l;
                for (int o = l + 1; (o < 40) && t2[o] != -1; o++)
                {
                    // cout<<gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n)-1].Fmin;
                    if (max < gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmin)
                    {
                        max = gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmin;
                        max_ind = o;
                    }
                }
                a = t2[max_ind];
                t2[max_ind] = t2[l];
                t2[l] = a;
            }

            //*********************************les 2m�thodes***********************

            bool verif, test3;
            int d1, test_d;
            k = 0;
            verif = false;
            if (verif == true)
                trouve = true;
            else
            {
                // trouve=false;
                if (verif == false || k == 0)
                {
                    verif = false;
                    k = 0;

                    while ((t2[k] != -1) && !verif)
                    {

                        test3 = false;
                        d1 = gammes[travail(t2[k])].d(t2[k]);
                        test_d = (gammes[travail(i)].d(machines[m].premier_sommet(i))) - 1;
                        // cout<<test_r<<endl;

                        while ((((gammes[travail(t2[k])].r(t2[k])) + (gammes[travail(t2[k])].p(t2[k]))) < test_d) && !test3)
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].d = test_d;
                            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                            if ((gammes[travail(i)].Fmin(i - 1)) <= (gammes[travail(i)].Smin(i)))
                            {
                                test3 = true;
                                taches_incoherentes();
                            }
                            else
                            {
                                test_d = test_d - 1;
                            }
                        }
                        if (test3 == true)
                        {
                            verif = true;
                        }
                        else
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].d = d1;
                            k++;
                        }
                    }

                    if (verif == true)
                        trouve = true;
                    else
                        trouve = false;

                    //****************************************
                }
            }
        }
        if (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + p > (gammes[travail(i)].d(i))) && (test1 == false) && (trouve == false))
        {
            int m = gammes[travail(i)].machine(i) - 1;
            gammes[travail(i)].lis[pos(i)].r = s;
            // gammes[travail(i)].lis[pos(i)].r=gammes[travail(i)].r(machines[m].premier_sommet(i));
            while (((gammes[travail(i)].Fmin(i - 1)) > (gammes[travail(i)].Smin(i))) && (!test2))
            {
                gammes[travail(i)].lis[pos(i)].r = (gammes[travail(i)].lis[pos(i)].r) + p; // cout<<gammes[travail(i)].lis[pos(i)].r<<endlp;
                gammes[travail(i)].lis[pos(i)].d = (gammes[travail(i)].lis[pos(i)].r) + (gammes[travail(i)].lis[pos(i)].p);
                calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                if ((gammes[travail(i)].Fmin(i - 1)) <= (gammes[travail(i)].Smin(i)))
                {
                    test2 = true;
                    taches_incoherentes();
                }
                else
                    p = (gammes[travail(i)].Fmin(i - 1)) - (gammes[travail(i)].Smin(i));
            }
        }
    }
    bool diminuer_Fmax(int i, int x)
    {

        int t;
        t = x;
        bool test;
        test = false;
        int d1 = gammes[travail(i)].lis[pos(i)].d;
        while (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) <= (gammes[travail(i)].d(i)) - t) && (!test))
        {
            gammes[travail(i)].lis[pos(i)].d = (gammes[travail(i)].lis[pos(i)].d) - t;
            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
            if ((gammes[travail(i)].Fmax(i)) <= (gammes[travail(i)].Smax(i + 1)))
            {
                test = true;
                taches_incoherentes();
                return true; // cout<<"ffff"<<endl;
            }
            t = (gammes[travail(i)].Fmax(i)) - (gammes[travail(i)].Smax(i + 1));
        }
        if (test == false)
        // return false;
        {
            gammes[travail(i)].lis[pos(i)].d = d1;
            // cout<<"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"<<endl;
            int m = gammes[travail(i)].machine(i) - 1; // cout<<x<<"jj"<<machines[x].nbrt<<endl;
            int t[40], t1[40][2], t2[40], k = 0, l = 0, n = 0, a, b, max, max_ind, min, min_ind;

            for (int j = 0; j < 40; j++)
                t[j] = -1;

            for (int j = 0; j < 40; j++)
                for (int o = 0; o < 2; o++)
                    t1[j][o] = -1;
            //*******************u(k)<=v(i)<=v(k)et Dk>Di****************************************
            for (int j = 0; j < machines[m].nbrt; j++)
            {

                if ((machines[m].U(machines[m].tab[j].t) <= machines[m].V(i)) && (machines[m].V(machines[m].tab[j].t) >= machines[m].V(i)) && ((machines[m].info_d(machines[m].tab[j].t) > (machines[m].info_d(i)))))
                {
                    t[k] = machines[m].tab[j].t; // cout<<t[k]<<endl;
                    k++;
                }
            }
            //*******************recherche dans incoher_max u(k)<=v(i)<=v(k)et Dk>Di ****************************************
            for (k = 0; k < 40; k++)
            {
                for (int j = 0; j < 40; j++)
                {
                    if ((t[k] == incoher_max[j][l + 1]) && (t[k] != -1))
                    {
                        t1[n][0] = t[k];
                        t1[n][1] = incoher_max[j][l + 2];
                        // cout<<t1[n]<<"oo"<<incoher_max[j][l+1]<<"pp"<<t[k]<<"ll"<<incoher_max[j][l+2]<<endl;
                        n++;
                    }
                }
            }
            //*******************ordonner u(k)<u(i)etv(k)>=u(k)****************************************
            for (l = 0; l < 40; l++)
            {
                max = t1[l][1];
                max_ind = l;
                for (int o = l + 1; o < 40; o++)
                {
                    if (max < t1[o][1])
                    {
                        max = t1[o][1];
                        max_ind = o;
                    }
                }
                //*********
                a = t1[max_ind][0];
                t1[max_ind][0] = t1[l][0];
                t1[l][0] = a;
                //*********
                b = t1[max_ind][1];
                t1[max_ind][1] = t1[l][1];
                t1[l][1] = b;
            }

            //******************************--2cas--*************************************
            //*******************recherche dans les gammes  u(k)<=v(i)<=v(k)et Dk>Di****************************************
            // cout<<"raouf"<<endl;
            for (int j = 0; j < 40; j++)
                t2[j] = t[j];

            for (l = 0; (l < 40) && t2[l] != -1; l++)
            {
                min = gammes[travail(t2[l])].lis[(gammes[travail(t2[l])].n) - 1].Fmax; // cout<<"uu"<<min<<endl;
                min_ind = l;
                for (int o = l + 1; (o < 40) && t2[o] != -1; o++)
                {
                    // cout<<gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n)-1].Fmin;
                    if (min > gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmax)
                    {
                        min = gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmax;
                        min_ind = o;
                    }
                }
                a = t2[min_ind];
                t2[min_ind] = t2[l];
                t2[l] = a;
            }

            bool verif, test1;
            int r1, test_r;
            k = 0;
            verif = false;
            /* while((t1[k][0]!=-1)&&!verif)
              {

                  test1=false;
                  r1=gammes[travail(t1[k][0])].r(t1[k][0]);
                  test_r=(gammes[travail(i)].r(machines[m].dernier_sommet(i)))+1;
                  //cout<<test_r<<endl;

                  while(((test_r+(gammes[travail(t1[k][0])].p(t1[k][0])))<(gammes[travail(t1[k][0])].d(t1[k][0])))&&!test1 )
                  {
                      gammes[travail(t1[k][0])].lis[pos(t1[k][0])].r=test_r;
                      calculer_debut_fin_machine(gammes[travail(i)].m(i));
                      if((gammes[travail(i)].Fmax(i))<=(gammes[travail(i)].Smax(i+1)))
                      {
                          test1=true;
                          taches_incoherentes();
                      }
                      else
                      { test_r=test_r+((gammes[travail(i)].Fmax(i))-(gammes[travail(i)].Smax(i+1)));}
                  }
                  if(test1==true)
                  {
                      verif=true;
                  }
                  else
                  {
                      gammes[travail(t1[k][0])].lis[pos(t1[k][0])].r=r1;
                      k++;
                  }

              }*/
            //*****fin_1cas************
            if (verif == true)
            {
                return true;
            }
            else
            {
                return false;
                if (verif == false || k == 0)
                {
                    //**
                    verif = false;
                    k = 0;
                    while ((t2[k] != -1) && !verif)
                    {
                        test1 = false;
                        r1 = gammes[travail(t2[k])].r(t2[k]);
                        test_r = (gammes[travail(i)].r(machines[m].dernier_sommet(i))) + 1;

                        while (((test_r + (gammes[travail(t2[k])].p(t2[k]))) < (gammes[travail(t2[k])].d(t2[k]))) && !test1)
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].r = test_r;
                            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                            if ((gammes[travail(i)].Fmax(i)) <= (gammes[travail(i)].Smax(i + 1)))
                            {
                                test1 = true;
                                taches_incoherentes();
                            }
                            else
                                test_r = test_r + 1;
                        }
                        if (test1 == true)
                        {
                            verif = true;
                        }
                        else
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].r = r1;
                            k++;
                        }
                    }
                    //**
                    if (verif == true)
                        return true;
                    else
                        return false;
                }

            } //***
        }
        //}
    }
    void augmenter_Smax(int i, int x)
    {

        int t;
        t = x;
        bool test1, test2, test3;
        test1 = false;
        test2 = false;
        test3 = false;
        int r1 = gammes[travail(i)].lis[pos(i)].r;
        while (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + t <= (gammes[travail(i)].d(i))) && (!test1))
        {
            gammes[travail(i)].lis[pos(i)].r = (gammes[travail(i)].lis[pos(i)].r) + t;
            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
            if ((gammes[travail(i)].Fmax(i - 1)) <= (gammes[travail(i)].Smax(i)))
            {
                test1 = true;
                taches_incoherentes();
            }
            else
                t = (gammes[travail(i)].Fmax(i - 1)) - (gammes[travail(i)].Smax(i));
        }
        if (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + t > (gammes[travail(i)].d(i))) && (test1 == false))
        {

            // cout<<"yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy"<<endl;
            int m = gammes[travail(i)].machine(i) - 1; // cout<<x<<"jj"<<machines[x].nbrt<<endl;
            int t[40], t1[40][2], t2[40], k = 0, l = 0, n = 0, a, b, max, max_ind, min, min_ind;

            for (int j = 0; j < 40; j++)
                t[j] = -1;

            for (int j = 0; j < 40; j++)
                for (int o = 0; o < 2; o++)
                    t1[j][o] = -1;
            //*******************u(k)<=v(i)<=v(k)et Dk>Di****************************************
            for (int j = 0; j < machines[m].nbrt; j++)
            {

                if ((machines[m].U(machines[m].tab[j].t) <= machines[m].V(i)) && (machines[m].V(machines[m].tab[j].t) >= machines[m].V(i)) && ((machines[m].info_d(machines[m].tab[j].t) > (machines[m].info_d(i)))))
                {
                    t[k] = machines[m].tab[j].t; // cout<<t[k]<<endl;
                    k++;
                }
            }
            //*******************recherche dans incoher_max u(k)<=v(i)<=v(k)et Dk>Di ****************************************
            for (k = 0; k < 40; k++)
            {
                for (int j = 0; j < 40; j++)
                {
                    if ((t[k] == incoher_max[j][0]) && (t[k] != -1))
                    {
                        t1[n][0] = t[k];
                        t1[n][1] = incoher_max[j][l + 2];
                        // cout<<t1[n]<<"oo"<<incoher_max[j][l+1]<<"pp"<<t[k]<<"ll"<<incoher_max[j][l+2]<<endl;
                        n++;
                    }
                }
            }
            //*******************ordonner u(k)<u(i)etv(k)>=u(k)****************************************
            for (l = 0; l < 40; l++)
            {
                max = t1[l][1];
                max_ind = l;
                for (int o = l + 1; o < 40; o++)
                {
                    if (max < t1[o][1])
                    {
                        max = t1[o][1];
                        max_ind = o;
                    }
                }
                //*********
                a = t1[max_ind][0];
                t1[max_ind][0] = t1[l][0];
                t1[l][0] = a;
                //*********
                b = t1[max_ind][1];
                t1[max_ind][1] = t1[l][1];
                t1[l][1] = b;
            }

            //******************************--2cas--*************************************
            //*******************recherche dans les gammes  u(k)<=v(i)<=v(k)et Dk>Di****************************************
            // cout<<"raouf"<<endl;
            for (int j = 0; j < 40; j++)
                t2[j] = t[j];

            for (l = 0; (l < 40) && t2[l] != -1; l++)
            {
                max = gammes[travail(t2[l])].lis[(gammes[travail(t2[l])].n) - 1].Fmax; // cout<<"uu"<<min<<endl;
                max_ind = l;
                for (int o = l + 1; (o < 40) && t2[o] != -1; o++)
                {
                    // cout<<gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n)-1].Fmin;
                    if (max < gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmax)
                    {
                        max = gammes[travail(t2[o])].lis[(gammes[travail(t2[o])].n) - 1].Fmax;
                        max_ind = o;
                    }
                }
                a = t2[max_ind];
                t2[max_ind] = t2[l];
                t2[l] = a;
            }
            //************************rani hena************************************

            bool verif, test4;
            int d1, test_d;
            k = 0;
            verif = false;
            /*while((t1[k][0]!=-1)&&!verif)
            {

                test4=false;
                d1=gammes[travail(t1[k][0])].d(t1[k][0]);
                test_d=(gammes[travail(i)].d(i))-1;
                //cout<<test_r<<endl;

                while((((gammes[travail(t1[k][0])].r(t1[k][0]))+(gammes[travail(t1[k][0])].p(t1[k][0])))<test_d)&&(test_d>gammes[travail(i)].d(machines[m].dernier_sommet(i)))&&!test4 )
                {
                    gammes[travail(t1[k][0])].lis[pos(t1[k][0])].d=test_d;
                    calculer_debut_fin_machine(gammes[travail(i)].m(i));
                    if((gammes[travail(i)].Fmax(i-1))<=(gammes[travail(i)].Smax(i)))
                    {
                        test4=true;
                        taches_incoherentes();
                    }
                    else
                    { test_d=test_d-1;}
                }
                if(test4==true)
                {
                    verif=true;
                }
                else
                {
                    gammes[travail(t1[k][0])].lis[pos(t1[k][0])].d=d1;
                    k++;
                }

            }*/
            if (verif == true)
                test3 = true;
            else
            {
                // test3=false;
                if (verif == false || k == 0)
                {
                    verif = false;
                    k = 0;

                    while ((t2[k] != -1) && !verif)
                    {

                        test4 = false;
                        d1 = gammes[travail(t2[k])].d(t2[k]);
                        test_d = (gammes[travail(i)].d(i)) - 1;
                        // cout<<test_r<<endl;

                        while ((((gammes[travail(t2[k])].r(t2[k])) + (gammes[travail(t2[k])].p(t2[k]))) < test_d) && (test_d > gammes[travail(i)].d(machines[m].dernier_sommet(i))) && !test4)
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].d = test_d;
                            calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                            if ((gammes[travail(i)].Fmax(i - 1)) <= (gammes[travail(i)].Smax(i)))
                            {
                                test4 = true;
                                taches_incoherentes();
                            }
                            else
                            {
                                test_d = test_d - 1;
                            }
                        }
                        if (test4 == true)
                        {
                            verif = true;
                        }
                        else
                        {
                            gammes[travail(t2[k])].lis[pos(t2[k])].d = d1;
                            k++;
                        }
                    }
                    if (verif == true)
                        test3 = true;
                    else
                        test3 = false;
                }

                //****************************************

            } ////89
        }

        if (((gammes[travail(i)].r(i)) + (gammes[travail(i)].p(i)) + t > (gammes[travail(i)].d(i))) && (test1 == false) && (test3 == false))
        {
            t = x;
            gammes[travail(i)].lis[pos(i)].r = r1;
            while (((gammes[travail(i)].Fmax(i - 1)) > (gammes[travail(i)].Smax(i))) && (!test2))
            {
                gammes[travail(i)].lis[pos(i)].r = (gammes[travail(i)].lis[pos(i)].r) + t; // cout<<gammes[travail(i)].lis[pos(i)].r<<endl;
                gammes[travail(i)].lis[pos(i)].d = (gammes[travail(i)].lis[pos(i)].r) + (gammes[travail(i)].lis[pos(i)].p);
                calculer_debut_fin_machine(gammes[travail(i)].machine(i));
                if ((gammes[travail(i)].Fmax(i - 1)) <= (gammes[travail(i)].Smax(i)))
                {
                    test2 = true;
                    taches_incoherentes();
                }
                else
                    t = (gammes[travail(i)].Fmax(i - 1)) - (gammes[travail(i)].Smax(i));
            }
        }
    }
    void reordonner()
    {
        int i = 0, j = 0, l = 0, k = 0;
        bool test, test2;
        // cout<<endl<<endl<<"les test: "<<endl<<endl;
        // test 
        /*
        for (l = 0 ; l < 30 ; l++)
        {
            // incoher_max[l][k] != -1
            test2 = diminuer_Fmax(incoher_max[l][k], incoher_max[l][k + 2]);

            if (!test2)
            {
                cout << "\n islam max \n";
                augmenter_Smax(incoher_max[l][k + 1], incoher_max[l][k + 2]);
            }
        }
        while (incoher_min[i][j] != -1)
        {
            test = diminuer_Fmin(incoher_min[i][j], incoher_min[i][j + 2]);

            if (!test)
            {
                cout << "\n islam min \n";
                augmenter_Smin(incoher_min[i][j + 1], incoher_min[i][j + 2]);
            }
        }
        */
        
        int counter_min = 0 ;
        int counter_max = 0 ;
        while (incoher_min[i][j] != -1 || incoher_max[l][k] != -1)
        {
            if(counter_max == 30 || counter_max == 30){
                break;
            }
            if (incoher_min[i][j] != -1)
            {
                counter_min++;
                test = diminuer_Fmin(incoher_min[i][j], incoher_min[i][j + 2]);

                if (!test)
                {
                    //cout << "\n islam min \n";
                    augmenter_Smin(incoher_min[i][j + 1], incoher_min[i][j + 2]);
                }
            }
            if (incoher_max[l][k] != -1)
            {

                // if(incoher_max[l][k]!=-1)
                counter_max++;
                test2 = diminuer_Fmax(incoher_max[l][k], incoher_max[l][k + 2]);

                if (!test2)
                {
                    //cout << "\n islam max \n";
                    augmenter_Smax(incoher_max[l][k + 1], incoher_max[l][k + 2]);
                }
            }
        }
        
        
        /*
        for (int p = 0; p < nombreMachines; p++)
        {
            machines[p].sequence();
        }
        */

        // calculer_makespan();
        // testu(10);
    }
    // ******** les fonction de l'affichage *********
    void affichage_dans_le_console_bellman_debutFin()
    {

        cout << "*** Gamme "
             << "**** Machine "
             << "**** P "
             << "******** R "
             << "******** D ";
        cout << "******* Smin "
             << "***** Smax "
             << "***** Fmin "
             << "****** Fmax ****" << endl;
        for (int i = 0; i < nombreGammes; i++)
        {
            for (int j = 0; j < gammes[i].n; j++)
            {
                cout << "**** " << gammes[i].lis[j].travail << " ****";
                cout << "**** " << gammes[i].lis[j].machine << " ****";
                cout << "**** " << gammes[i].lis[j].p << " ****";
                cout << "**** " << gammes[i].lis[j].r << " ****";
                cout << "**** " << gammes[i].lis[j].d << " ****";
                cout << "**** " << gammes[i].lis[j].Smin << " ****";
                cout << "**** " << gammes[i].lis[j].Smax << " ****";
                cout << "**** " << gammes[i].lis[j].Fmin << " ****";
                cout << "**** " << gammes[i].lis[j].Fmax << " ****" << endl;
            }
        }
        cout << "\n";
    }
    void affichage_dans_le_console_incoherentes_enitial()
    {

        cout << "******** Incoherence au Min ********" << endl;
        cout << "**** Tache i **** Tache i+1 **** Ecart au min ****" << endl;
        nember_of_incoher_enitial = 0;
        for (int i = 0; (i < 30) && (incoher_min[i][0] != -1); i++)
        {
            nember_of_incoher_enitial++;
            cout << "******* " << incoher_min[i][0];
            cout << "*********** " << incoher_min[i][1];
            cout << "************ " << incoher_min[i][2] << "******\n"
                 << endl;
        }
        cout << "\n \n******** Incoherence au Max ********" << endl;
        cout << "**** Tache i **** Tache i+1 **** Ecart au max ****" << endl;

        for (int i = 0; (i < 30) && (incoher_max[i][0] != -1); i++)
        {
            nember_of_incoher_enitial++;
            cout << "******* " << incoher_max[i][0];
            cout << "*********** " << incoher_max[i][1];
            cout << "************ " << incoher_max[i][2] << "******\n"
                 << endl;
        }
    }
    void affichage_dans_le_console_reordonner()
    {
        cout << "\n \n ************  la reordonnoncement  ************\n"
             << endl;
        cout << "****** Machine "
             << "****** Nbr de Seq "
             << "****** Sequence Maitre Pyramide" << endl;
        for (int i = 0; (i < nombreMachines); i++)
        {
            // machines[i].SeqToChaine();
            cout << "********* " << machines[i].num;
            cout << "************* " << machines[i].S_dom();
            cout << "*************** ";
            // machines[i].seq();
            cout << endl;
        }
    }
    void affichage_dans_le_console()
    {

        // la demande de nombre datelier
        cout << "donner le nombre d'atelier : ";
        cin >> numero;
        cout << endl;
        // Etap 1
        cout << " \n \n ********* Etape 1 ********* \n \n ";
        // lappele des fonction de ford-Bellman et le debut-fin
        // pour calcule le temps
        // clock_t start, end;
        // start = clock();
        initialiser_atelier();
        calculer_ford();
        initialiser_atelier_machines();
        calculer_debut_fin();

        // l affichage du resultat de Bellman et debut-fin
        affichage_dans_le_console_bellman_debutFin();

        // le calcule du lincoherentes
        taches_incoherentes();

        // laffichage du resultat de lincoherentes enitiale
        cout << "\n ************ l'affichage du resultat de l'incoherence initiale ************ \n " << endl;
        affichage_dans_le_console_incoherentes_enitial();

        // le calcule de reordonnencement
        reordonner();

        // laffichage du resultat de reordonnencement
        affichage_dans_le_console_reordonner();

        // laffichage la corriger apret la reordonnoncement
        affichage_dans_le_console_bellman_debutFin();
        // laffichage de resultat de lincoherentes final
        cout<<"\n ************ l'affichage du resultat de l'incoherence final ************ \n "<<endl;
        affichage_dans_le_console_incoherentes_enitial();
        /*

                // Etape 2

                // laffichage la corriger apret la reordonnoncement
                cout<<" \n \n ********* Etape 2 ********* \n \n ";
                initialiser_atelier_machines();
                calculer_debut_fin();
                affichage_dans_le_console_bellman_debutFin();

                // laffichage de resultat de lincoherentes final
                cout<<"\n ************ l'affichage du resultat de l'incoh�rence final ************ \n "<<endl;
                affichage_dans_le_console_incoherentes_final();

                // l'appel et l'affichage de la fonction Makespan
                calculer_makespan();
                cout<<" \n \n \n ******** l'affichage du resultat de Makespane ********* "<<endl;
                cout<<"\n ******** Makespan *******"<<endl;
                cout<<"******  "<<Fin_min<<" <= Cmax <= "<<Fin_max<<" *******"<<endl;
                end = clock();
                double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
                // laffichage de la table final
                affichage_dans_le_console_le_tableux_final(time_taken);
                */
    }
};

int main(int argc, char const *argv[])
{
    Mainview w;
    w.affichage_dans_le_console();
    return 0;
}
