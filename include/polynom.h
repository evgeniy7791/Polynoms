#include "monom.h"

using namespace std;

//const int minDeg = -1;
//const int p = 25;

class Polinom
{
protected:
    Node* head;
    Node* end;
    void addlast(Monom _v)
    {
        Node* n = new Node(_v, head);
        end->next = n;
        end = n;
    }

    void clear()
    {
        while (head->next != head)
        {
            Node* d = head->next;
            head->next = head->next->next;
            delete d;
        }
        end = head;
    }

public:
    Polinom()
    {
        head = new Node();
        head->next = head;
        end = head;
    }

    Polinom(const Polinom& l)
    {
        head = new Node();
        head->next = head;
        end = head;
        Node* tmp = l.head->next;
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
        Node* tmp = l.head->next;
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
            Node* d = head->next;
            head->next = head->next->next;
            delete d;
        }
    }

    void add(Monom m)
    {
        Node* tmp = head;
        while (tmp->next != head)
        {
            if (tmp->next->val.pow == m.pow)
            {
                tmp->next->val.mult += m.mult;
                return;
            }
            if (tmp->next->val.pow > m.pow)
            {
                Node* n = new Node(m, tmp->next);
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
        Node* t = head->next;
        Node* p = poly.head->next;
        while (t != head && p != poly.head)
        {
            if (t->val.pow == p->val.pow)
            {
                if (t->val.mult + p->val.mult != 0)
                    res.addlast(t->val + p->val);
                t = t->next;
                p = p->next;
            }
            else if (t->val.pow < p->val.pow)
            {
                res.addlast(t->val);
                t = t->next;
            }
            else
            {
                res.addlast(p->val);
                p = p->next;
            }
        }
        while (t != head)
        {
            res.addlast(t->val);
            t = t->next;
        }
        while (p != poly.head)
        {
            res.addlast(p->val);
            p = p->next;
        }
        return res;
    }

    Polinom operator-(const Polinom& poly)
    {
        Polinom res;
        Node* t = head->next;
        Node* p = poly.head->next;
        while (t != head && p != poly.head)
        {
            if (t->val.pow == p->val.pow)
            {
                if (t->val.mult - p->val.mult != 0)
                    res.addlast(t->val - p->val);
                t = t->next;
                p = p->next;
            }
            else if (t->val.pow < p->val.pow)
            {
                res.addlast(t->val);
                t = t->next;
            }
            else
            {
                res.addlast(-(p->val));
                p = p->next;
            }
        }
        while (t != head)
        {
            res.addlast(t->val);
            t = t->next;
        }
        while (p != poly.head)
        {
            res.addlast(-(p->val));
            p = p->next;
        }
        return res;
    }

    Polinom operator*(const Polinom& poly)
    {
        Polinom res;
        Node* t = head->next;
        Node* p = poly.head->next;
        while (t != head)
        {
            while (p != poly.head)
            {
                res.add(t->val * p->val);
                p = p->next;
            }
            t = t->next;
            p = poly.head->next;
        }
        return res;
    }

    Polinom operator/(const Polinom& poly)
    {
        Polinom res;
        Node* t = head->next;
        Node* p = poly.head->next;
        while (t != head)
        {
            while (p != poly.head)
            {
                res.add(t->val / p->val);
                p = p->next;
            }
            t = t->next;
            p = poly.head->next;
        }
        return res;
    }

    double calc(double x = 1.0, double y = 1.0, double z = 1.0)
    {
        double res = 0;
        Node* tmp = head->next;
        while (tmp != head)
        {
            res += tmp->val.calc(x, y, z);
            tmp = tmp->next;
        }
        return res;
    }

    friend ostream& operator<<(ostream& out, Polinom& poli)
    {
        Node* tmp = poli.head->next;
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