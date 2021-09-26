#include <gtest/gtest.h>

#include "Bm.h"
#include "Kmp.h"

using BmSearch = string_alg::find<string_alg::Bm>;
using KmpSearch = string_alg::find<string_alg::Kmp>;

template<typename T>
void testSearchSubstr(T& search)
{
    EXPECT_EQ(search("KOLOLOKOLOKOLOKOL", "KOLOKOL"), 6);
    EXPECT_EQ(search("GCATCGCAGAGAGTATACAGTACG", "GCAGAGAG"), 5);
    EXPECT_EQ(search("abeccaabadbabbad", "abbad"), 11);
    EXPECT_EQ(search("qwteeqewqrwqwrqr", "qwrqr"), 11);
    EXPECT_EQ(search("...C.ABC.BC.C.ABC.......ABC......C.ABC.BC.C.ABC.ABC.BC.C.ABC.......", "BC.ABC.BC.C.ABC"), 45);
    EXPECT_EQ(search("qwteeqewqrwqwrqr", "qwrqrd"), string_alg::kNpos);
    EXPECT_EQ(search("aabaabaaaabaabaab", "aabaa"), 0);
}

TEST(StringSuit, BmTest)
{
    BmSearch search;
    testSearchSubstr(search);
}

TEST(StringSuit, KmpTest)
{
    KmpSearch search;
    testSearchSubstr(search);
}
