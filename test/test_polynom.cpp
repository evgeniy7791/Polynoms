//#include "gtest.h"
//#include "polynom.h"
//
//const int minDeg = -3;
//const int p = 10;
//
//
//TEST(polinom, p)
//{
//	Polinom l1, l2, l3;
//	//l1.add(5, 3);
//	//l1.add(2, 7);
//	//l1.add(68, 2);
//	//l2.add(5, 3);
//	//l2.add(6, 3);
//	//l2.add(4, 3);
//	//l3.add(6, 3);
//	//l3.add(4, 3);
//	ifstream in("poli.txt");
//	string s;
//	in >> l1;
//	in >> s;
//	switch (s[0])
//	{
//	case '+':
//	{
//		in >> l2;
//		l3 = l1 + l2;
//		break;
//	}
//	case '-':
//	{
//		in >> l2;
//		l3 = l1 - l2;
//		break;
//	}
//	case '*':
//	{
//		in >> l2;
//		l3 = l1 * l2;
//		break;
//	}
//	}
//	l3.calc(2, 3, 0.5);
//	ofstream out("resp.txt");
//	out << l3;
//	ASSERT_NO_THROW();
//}



