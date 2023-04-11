#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

const int minDeg = -1;
const int p = 25;

//x - 0
//y - 1
//z - 2

int control(int a)
{
    if (a < minDeg)
        return minDeg;
    if (a > minDeg + p - 1)
        return minDeg + p - 1;
    return a;
}

class Monom
{
public:
    double mult;
    int pow;
    Monom(double m = 1.0, int x = 0, int y = 0, int z = 0)
    {
        mult = m;
        pow = (x - minDeg) + (y - minDeg) * p + (z - minDeg) * p * p;
    }

    int getX() { return pow % p + minDeg; }
    int getY() { return (pow / p) % p + minDeg; }
    int getZ() { return pow / p / p + minDeg; }

    void clear()
    {
        mult = 1.0; pow = -minDeg + -minDeg * p + -minDeg * p * p;
    }

    Monom operator-()
    {
        return Monom(-mult, getX(), getY(), getZ());
    }

    Monom operator+ (const Monom& m)
    {
        if (pow == m.pow)
            return Monom(mult + m.mult, getX(), getY(), getZ());
        return Monom();
    }

    Monom operator- (const Monom& m)
    {
        if (pow == m.pow)
            return Monom(mult - m.mult, getX(), getY(), getZ());
        return Monom();
    }

    Monom operator* (Monom& m)
    {
        return Monom(mult * m.mult, control(getX() + m.getX()), control(getY() + m.getY()), control(getZ() + m.getZ()));
    }

    Monom operator/ (Monom& m)
    {
        return Monom(mult / m.mult, control(getX() - m.getX()), control(getY() - m.getY()), control(getZ() - m.getZ()));
    }

    double calc(double x, double y, double z)
    {
        double res = 0;
        res += mult * exp(getX() * log(x)) * exp(getY() * log(y)) * exp(getZ() * log(z));
        return res;
    }

    string toString()
    {
        std::string s = std::to_string(mult);
        if (mult == 0) return s;
        if (getX()) s += "*X^" + std::to_string(getX());
        if (getY()) s += "*Y^" + std::to_string(getY());
        if (getZ()) s += "*Z^" + std::to_string(getZ());
        return s;
    }

    friend ostream& operator<<(ostream& out, Monom& m)
    {
        out << m.mult;
        if (m.mult == 0) return out;
        if (m.getX()) out << "*X^" << m.getX();
        if (m.getY()) out << "*Y^" << m.getY();
        if (m.getZ()) out << "*Z^" << m.getZ();
        out << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Monom& m)
    {
        m.clear();
        string s, tmp = "";
        int st = 0, i = 0, t;
        char c;
        in >> s;
        while (i < s.length())
        {
            c = s[i];
            if (c <= '9' && c >= '0' || c == '.' || c == '-')
            {
                tmp += c;
            }
            else if (c == 'X' || c == 'Y' || c == 'Z')
            {
                if (tmp == "")
                    tmp += "1";
                if (!st)
                    m.mult = stod(tmp, 0);
                else
                {
                    t = stoi(tmp, 0, 10);
                    while (st - 1)
                    {
                        t *= p;
                        st--;
                    }
                    m.pow += t;
                }
                switch (c)
                {
                case 'X': {st = 1; break; }

                case 'Y': {st = 2; break; }

                case 'Z': {st = 3; break; }
                }
                tmp = "";
                i++;
            }
            i++;
        }
        if (!st)
            m.mult = stod(tmp, 0);
        else
        {
            t = stoi(tmp, 0, 10);
            while (st - 1 > 0)
            {
                t *= p;
                st--;
            }
            m.pow += t;
        }
        return in;
    }
};


struct Node
{
    Monom val;
    Node* next;
    Node(Monom _v = Monom(), Node* l = nullptr)
    {
        val = _v;
        next = l;
    }
};