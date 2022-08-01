#ifdef TEST

TEST(Mabius, 10377)
{
    std::istringstream iss(R"(2

20 21
*********************
*       * ** *  * * *
* ***  *     *   *  *
**  *   * **  *     *
****    *          **
* **  ***        ****
* *   *        * ** *
**    *       *   * *
*     ** *  ** * *  *
* *      *          *
**** ** *       * ***
***    *    *   *   *
*  *   *   *  *** ***
**    *   *   *   * *
*    *    *         *
*       *    * * *  *
*     *    **    ** *
*           * * * * *
*  *    *  **   *   *
*********************
8 11
LFF FFRRF R F   F RL LRRLFRLRF F LR LF RFL  FL LRLR FL FL FRLFRRLLRR RFRLLQ

15 11
***********
**     *  *
**   *    *
* * * **  *
* *  * *  *
*    *    *
* *   * * *
***   * * *
*   * * * *
** **   * *
*   *     *
*    ** * *
*        **
**   ** * *
***********
5 10
FRF RLL  FLLRRRLRFL FFFQ
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(11 5 E

2 10 N
)", oss.str());
}
TEST(orig, uva10377)
{
    std::istringstream iss(R"(1

7 8
********
* * * **
* *    *
* * ** *
* * *  *
*   * **
********
2 4
RRFLFF FFR
FF
RFFQ
)");
    std::ostringstream oss;
    solve(iss, oss);
    EXPECT_EQ(R"(5 6 W
)", oss.str());
}
#endif
