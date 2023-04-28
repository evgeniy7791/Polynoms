#ifndef POLYNOM_H
#define POLYNOM_H
#include "monom.h"

using namespace std;

//const int minDeg = -1;
//const int poni = 25;

class Polinom
{
protected:
    Unit* head;
    Unit* end;
    void addlast(Monom _v)
    {
        Unit* n = new Unit(_v, head);
        end->next = n;
        end = n;
    }

    void clear()
    {
        while (head->next != head)
        {
            Unit* d = head->next;
            head->next = head->next->next;
            delete d;
        }
        end = head;
    }

public:
    Polinom()
    {
        head = new Unit();
        head->next = head;
        end = head;
    }

    Polinom(const Polinom& l)
    {
        head = new Unit();
        head->next = head;
        end = head;
        Unit* tmp = l.head->next;
        while (tmp != l.head)
        {
            addlast(tmp->val);
            tmp = tmp->next;
        }
    }

    Polinom operator=(const Polinom& l)
    {
        if (this == &l)
            return *this;
        clear();
        Unit* tmp = l.head->next;
        while (tmp != l.head)
        {
            addlast(tmp->val);
            tmp = tmp->next;
        }
        return *this;
    }



    ~Polinom()
    {
        while (head->next != head)
        {
            Unit* d = head->next;
            head->next = head->next->next;
            delete d;
        }
    }

    void add(Monom m)
    {
        Unit* tmp = head;
        while (tmp->next != head)
        {
            if (tmp->next->val.pow == m.pow)
            {
                tmp->next->val.mult += m.mult;
                return;
            }
            if (tmp->next->val.pow > m.pow)
            {
                Unit* n = new Unit(m, tmp->next);
                tmp->next = n;
                return;
            }
            tmp = tmp->next;
        }
        addlast(m);
    }

    Polinom operator+(const Polinom& poly)
    {
        Polinom res;
        Unit* t = head->next;
        Unit* poni = poly.head->next;
        while (t != head && poni != poly.head)
        {
            if (t->val.pow == poni->val.pow)
            {
                if (t->val.mult + poni->val.mult != 0)
                    res.addlast(t->val + poni->val);
                t = t->next;
                poni = poni->next;
            }
            else if (t->val.pow < poni->val.pow)
            {
                res.addlast(t->val);
                t = t->next;
            }
            else
            {
                res.addlast(poni->val);
                poni = poni->next;
            }
        }
        while (t != head)
        {
            res.addlast(t->val);
            t = t->next;
        }
        while (poni != poly.head)
        {
            res.addlast(poni->val);
            poni = poni->next;
        }
        return res;
    }

    Polinom operator-(const Polinom& poly)
    {
        Polinom res;
        Unit* t = head->next;
        Unit* poni = poly.head->next;
        while (t != head && poni != poly.head)
        {
            if (t->val.pow == poni->val.pow)
            {
                if (t->val.mult - poni->val.mult != 0)
                    res.addlast(t->val - poni->val);
                t = t->next;
                poni = poni->next;
            }
            else if (t->val.pow < poni->val.pow)
            {
                res.addlast(t->val);
                t = t->next;
            }
            else
            {
                res.addlast(-(poni->val));
                poni = poni->next;
            }
        }
        while (t != head)
        {
            res.addlast(t->val);
            t = t->next;
        }
        while (poni != poly.head)
        {
            res.addlast(-(poni->val));
            poni = poni->next;
        }
        return res;
    }

    Polinom operator*(const Polinom& poly)
    {
        Polinom res;
        Unit* t = head->next;
        Unit* poni = poly.head->next;
        while (t != head)
        {
            while (poni != poly.head)
            {
                res.add(t->val * poni->val);
                poni = poni->next;
            }
            t = t->next;
            poni = poly.head->next;
        }
        return res;
    }

    Polinom operator/(const Polinom& poly)
    {
        Polinom res;
        Unit* t = head->next;
        Unit* poni = poly.head->next;
        while (t != head)
        {
            while (poni != poly.head)
            {
                res.add(t->val / poni->val);
                poni = poni->next;
            }
            t = t->next;
            poni = poly.head->next;
        }
        return res;
    }

    double calc(double x = 1.0, double y = 1.0, double z = 1.0)
    {
        double res = 0;
        Unit* tmp = head->next;
        while (tmp != head)
        {
            res += tmp->val.calc(x, y, z);
            tmp = tmp->next;
        }
        return res;
    }

    friend ostream& operator<<(ostream& out, Polinom& poli)
    {
        Unit* tmp = poli.head->next;
        while (tmp->next != poli.head)
        {
            out << tmp->val << " + ";
            tmp = tmp->next;
        }
        out << tmp->val << " & " << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Polinom& poli)
    {
        string s, sep = "&";
        bool minus = false;
        Monom tmp;
        in >> s;
        while (s != sep && s != "")
        {
            if (s == "-")
                minus = true;
            else if (s != "+")
            {
                stringstream ss;
                ss << s;
                ss >> tmp;
                if (minus)
                {
                    minus = false;
                    tmp.mult = -tmp.mult;
                }
                poli.add(tmp);
            }

            in >> s;
        }
        return in;
    }
};

#endif