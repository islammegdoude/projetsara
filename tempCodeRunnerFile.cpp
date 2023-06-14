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
    