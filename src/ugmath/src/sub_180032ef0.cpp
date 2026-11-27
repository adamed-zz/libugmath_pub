






struct Blk16 { unsigned long long a, b; };
typedef unsigned char (*Cmp)(const Blk16*, const Blk16*);
struct Pair16 { Blk16* first; Blk16* second; };


extern "C" bool sub_180032E70(Blk16* a1, Blk16* a2, Blk16* a3, Cmp cmp);

static void Med3(Blk16* a, Blk16* b, Blk16* c, Cmp pred)
{
    sub_180032E70(a, b, c, pred);
}

static void GuessMedian(Blk16* First, Blk16* Mid, Blk16* Last, Cmp Pred)
{
    const __int64 Count = Last - First;
    if (40 < Count)
    {
        const __int64 Step = (Count + 1) >> 3;
        const __int64 TwoStep = Step << 1;
        Med3(First, First + Step, First + TwoStep, Pred);
        Med3(Mid - Step, Mid, Mid + Step, Pred);
        Med3(Last - TwoStep, Last - Step, Last, Pred);
        Med3(First + Step, Mid, Last - Step, Pred);
    }
    else
    {
        Med3(First, Mid, Last, Pred);
    }
}

extern "C" Pair16* sub_180032EF0(Pair16* a1, Blk16* a2, Blk16* a3, Cmp a4)
{
    Blk16* First = a2;
    Blk16* Last = a3;
    Cmp Pred = a4;

    Blk16* Mid = First + ((Last - First) >> 1);
    GuessMedian(First, Mid, Last - 1, Pred);
    Blk16* Pfirst = Mid;
    Blk16* Plast = Pfirst + 1;

    while (First < Pfirst && !Pred(Pfirst - 1, Pfirst) && !Pred(Pfirst, Pfirst - 1))
        --Pfirst;

    while (Plast < Last && !Pred(Plast, Pfirst) && !Pred(Pfirst, Plast))
        ++Plast;

    Blk16* Gfirst = Plast;
    Blk16* Glast = Pfirst;

    for (;;)
    {
        for (; Gfirst < Last; ++Gfirst)
        {
            if (Pred(Pfirst, Gfirst))
            {
                continue;
            }
            else if (Pred(Gfirst, Pfirst))
            {
                break;
            }
            else if (Plast != Gfirst)
            {
                Blk16 t = *Plast;
                *Plast = *Gfirst;
                *Gfirst = t;
                ++Plast;
            }
            else
            {
                ++Plast;
            }
        }

        for (; First < Glast; --Glast)
        {
            if (Pred(Glast - 1, Pfirst))
            {
                continue;
            }
            else if (Pred(Pfirst, Glast - 1))
            {
                break;
            }
            else if (--Pfirst != Glast - 1)
            {
                Blk16 t = *Pfirst;
                *Pfirst = *(Glast - 1);
                *(Glast - 1) = t;
            }
        }

        if (Glast == First && Gfirst == Last)
        {
            a1->first = Pfirst;
            a1->second = Plast;
            return a1;
        }

        if (Glast == First)
        {
            if (Plast != Gfirst)
            {
                Blk16 t = *Pfirst;
                *Pfirst = *Plast;
                *Plast = t;
            }
            ++Plast;
            Blk16 u = *Pfirst;
            *Pfirst = *Gfirst;
            *Gfirst = u;
            ++Pfirst;
            ++Gfirst;
        }
        else if (Gfirst == Last)
        {
            if (--Glast != --Pfirst)
            {
                Blk16 t = *Glast;
                *Glast = *Pfirst;
                *Pfirst = t;
            }
            Blk16* p = --Plast;
            Blk16 u = *Pfirst;
            *Pfirst = *p;
            *p = u;
        }
        else
        {
            Blk16* g = --Glast;
            Blk16 t = *Gfirst;
            *Gfirst = *g;
            *g = t;
            ++Gfirst;
        }
    }
}
