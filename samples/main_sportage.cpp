#include <iostream>

#include "../containers/unordered_table.h"

#include "../containers/ordered_table.h"

#include "../containers/method_chain.h"

#include "../containers/open_adress.h"

#include "../containers/avl_trees.h"

#include "../containers/red_black_trees.h"

#include "polynom.h"

using namespace std;









int menu1()

{

    cout<< "Select date structure to store polinoms:" << "\n";

    cout<< "1.Unordered Table" << "\n";

    cout<< "2.Ordered Table" << "\n";

    cout<< "3.Avl Tree" << "\n";

    cout<< "4.Red and black tree" << "\n";

    cout<< "5.Hash table with open adress" << "\n";

    cout << "6.Hash table with chains" << "\n";

    int a;

    cin >> a;

    return a;

}

TABLE<int, Polinom>* CreateTable(int a)

{

    switch (a) {

    case 1:

        return new UnorderedTable<int, Polinom>();

    case 2:

        return new OrderedTable<int, Polinom>();

    case 3:

        return new AVLTree<int, Polinom>();

    case 4:

        return new RedBlackTree<int, Polinom>();

    case 5:

        return new HashTable2<int, Polinom>();

    case 6:

        return new HashTable<int, Polinom>();





    default:

        std::cout << "Incorrect table type" << "\n";

        return nullptr;

    }

}



void menu2(TABLE<int, Polinom>* tab)

{

    Monom m1;

    Polinom p;

    while (true)

    {

        cout << "1.Add monom to polinom:" << "\n";

        cout << "2.Add polinom to table:" << "\n";

        cout << "3.Exit create polinoms:" << "\n";

        int ex;

        cin >> ex;

        if (ex == 3)

        {

            cout << "Completed add polinoms to table" << "\n";

            break;

        }

        switch (ex) {

        case 1:

            cout << "Input monom coefficients:" << "\n";

            double m;

            int x, y, z;

            cin >> m >> x >> y >> z;

            m1 = Monom(m, x, y, z);

            p.add(m1);

            break;

        case 2:

            int K;

            cout << "Input key to add polinom into table:" << "\n";

            cin >> K;

            tab->insert(K, p);

            p.clear();

            break;

        default:

            cout << "Incorrect command number" << "\n";

        }



    }
    
}



void menu3(TABLE<int, Polinom>* tab)

{

    int k1, k2, K;

    double res;

    int x, y, z;

    Polinom p1, p2, p3;



    while (true)

    {

        cout << "1.Add(+) polinoms:" << "\n";

        cout << "2.Minus(-) polinoms:" << "\n";

        cout << "3.Mult(*) polinoms:" << "\n";

        cout << "4.Div(/) polinoms:" << "\n";

        cout << "5.Calculate polinom value:" << "\n";

        cout << "6.Exit polinoms operations:" << "\n";



        int ex;

        cin >> ex;

        if (ex == 6)

        {

            cout << "Completed polinoms operations" << "\n";

            break;

        }

        switch (ex) {

        case 1:



            cout << "Input key for polinom1:" << "\n";

            cin >> k1;

            cout << "Input key for polinom2:" << "\n";

            cin >> k2;

            p1 = tab->operator[](k1);

            p2 = tab->operator[](k2);

            p3 = p1 + p2;



            cout << "Input key to add sum of polinoms into table:" << "\n";

            cin >> K;

            tab->insert(K, p3);

            break;

        case 2:



            cout << "Input key for polinom1:" << "\n";

            cin >> k1;

            cout << "Input key for polinom2:" << "\n";

            cin >> k2;

            p1 = tab->operator[](k1);

            p2 = tab->operator[](k2);

            p3 = p1 - p2;



            cout << "Input key to add differense of polinoms into table:" << "\n";

            cin >> K;

            tab->insert(K, p3);

            break;

        case 3:



            cout << "Input key for polinom1:" << "\n";

            cin >> k1;

            cout << "Input key for polinom2:" << "\n";

            cin >> k2;

            p1 = tab->operator[](k1);

            p2 = tab->operator[](k2);

            p3 = p1 * p2;



            cout << "Input key to add product of polinoms into table:" << "\n";

            cin >> K;

            tab->insert(K, p3);

            break;

        case 4:



            cout << "Input key for polinom1:" << "\n";

            cin >> k1;

            cout << "Input key for polinom2:" << "\n";

            cin >> k2;

            p1 = tab->operator[](k1);

            p2 = tab->operator[](k2);

            p3 = p1 / p2;



            cout << "Input key to add quotient of division of polinoms into table:" << "\n";

            cin >> K;

            tab->insert(K, p3);

            break;

        case 5:



            cout << "Input key to calculate polinpm value:" << "\n";

            cin >> K;

            p1 = tab->operator[](K);



            cout << "Input values to X, Y, Z:" << "\n";

            cin >> x >> y >> z;

            res = p1.calc(x, y, z);

            cout << "RESULT CALC: " << res << "\n";



        default:

            cout << "Incorrect command number" << "\n";



        }

    }

}



int main() {



    int a = menu1();

    TABLE<int, Polinom>* tab = CreateTable(a);

    menu2(tab);

    tab->print();



    menu3(tab);

    tab->print();

    return 0;

}