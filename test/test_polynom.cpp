#include "polynom.h"
#include <gtest.h>

TEST(Polinom, can_create_empty_polinom)
{
    EXPECT_NO_THROW(Polinom p1);
}

TEST(Polinom, can_add_monom_to_polinom)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    EXPECT_NO_THROW(p.add(m));
}

TEST(Polinom, can_calc_polinom_with_single_monom)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.calc());
}

TEST(Polinom, can_calc_polinom_with_single_monom_correctly)
{
    Monom m(2, 1, 1, 1);
    Polinom p;
    p.add(m);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(4, res);
}

TEST(Polinom, can_add_second_monom_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.add(m1));
}

TEST(Polinom, can_add_second_monom_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    p.add(m);
    p.add(m1);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(16, res);
}

TEST(Polinom, can_add_second_monom_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    p.add(m);
    EXPECT_NO_THROW(p.add(m1));
}

TEST(Polinom, can_add_second_monom_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    p.add(m);
    p.add(m1);
    int res = p.calc(2, 1, 1);
    EXPECT_EQ(10, res);
}

TEST(Polinom, can_plus_empty_polinoms)
{
    Polinom p;
    Polinom p1;
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p + p1).calc(2, 1, 1), p.calc(2, 1, 1) + p1.calc(2, 1, 1));
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p + p1);
}

TEST(Polinom, can_plus_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p + p1).calc(2, 1, 1), p.calc(2, 1, 1) + p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p * p1);
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(24, p.calc(2, 1, 1) * p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p * p1);
}

TEST(Polinom, can_mult_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(48, p.calc(2, 1, 1) * p1.calc(2, 1, 1));
}

TEST(Polinom, can_mult_polinoms_in_different_points_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(384, p.calc(2, 1, 1) * p1.calc(2, 2, 2));
}

TEST(Polinom, can_mult_polinoms_in_same_points_correctly_2)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_LE(abs(((p * p1).calc(2, 2, 2)) - 1536), 1e-7);
}

TEST(Polinom, can_mult_polinoms_in_different_points)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW((p * p1).calc(2, 2, 2));
}

TEST(Polinom, can_minus_empty_polinoms)
{
    Polinom p;
    Polinom p1;
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p - p1).calc(2, 1, 1), p.calc(2, 1, 1) - p1.calc(2, 1, 1));
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p - p1);
}

TEST(Polinom, can_minus_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ((p - p1).calc(2, 1, 1), p.calc(2, 1, 1) - p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_with_monoms_with_same_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p / p1);
}

TEST(Polinom, can_div_polinoms_with_monoms_with_same_power_correctly)
{
    Monom m(6, 1, 1, 1);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(2, p.calc(2, 1, 1) / p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_with_monoms_with_different_power)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW(p / p1);
}

TEST(Polinom, can_div_polinoms_with_monoms_with_different_power_correctly)
{
    Monom m(6, 2, 2, 2);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(4, p.calc(2, 1, 1) / p1.calc(2, 1, 1));
}

TEST(Polinom, can_div_polinoms_in_different_points_correctly)
{
    Monom m(9, 2, 2, 2);
    Monom m1(3, 1, 1, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_EQ(1.5, p.calc(2, 1, 1) / p1.calc(2, 2, 2));
}


TEST(Polinom, can_div_polinoms_in_same_points_correctly)
{
    Monom m(6, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_LE(abs(((p / p1).calc(2, 2, 2)) - 16), 1e-7);
}

TEST(Polinom, can_div_polinoms_in_different_points)
{
    Monom m(2, 1, 1, 1);
    Monom m1(3, 2, 2, 1);
    Polinom p;
    Polinom p1;
    p.add(m);
    p1.add(m1);
    EXPECT_NO_THROW((p / p1).calc(2, 2, 2));
}

TEST(Polinom, div_polinoms_1)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Monom m2(10, 3, 3, 3);
    Monom k(4, 1, 1, 1);
    Polinom p;
    Polinom p1;
    Polinom p2;
    p.add(m);
    p1.add(m1);
    p.add(m2);
    p2.add(k);
    EXPECT_EQ((p / p1).calc(1, 1, 1), p2.calc(1, 1, 1));
}

TEST(Polinom, div_polinoms_2)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 2, 2);
    Monom m2(10, 3, 3, 3);
    Monom k(4, 1, 1, 1);
    Polinom p;
    Polinom p1;
    Polinom p2;
    p.add(m);
    p1.add(m1);
    p.add(m2);
    p2.add(k);
    EXPECT_EQ((p / p1).calc(1, 1, 1), p2.calc(1, 1, 1));
}

TEST(Monom, monoms_pow1)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 3, 2);
    int res = m.getX();
    int res1 = m1.getY();
    //EXPECT_EQ(3, m.getX());
    EXPECT_EQ(res, res1);
}

TEST(Monom, monoms_pow)
{
    Monom m(2, 3, 3, 3);
    Monom m1(3, 2, 3, 2);
    //int res = m.getX();
    //auto res1 = m1.getY();
      //EXPECT_EQ(3, m.getX());
    EXPECT_NO_THROW(m.getX());
}