#include "calc.h"
#include "catch.hpp"
#include "utility.hpp"

SCENARIO("The evaluator shall produce correct multiplication results", "[calc][op][mul]") {
    CHECK(CALC_EVAL("0 * 0") == 0);
    CHECK(CALC_EVAL("0 * 1") == 0);
    CHECK(CALC_EVAL("1 * 0") == 0);
    CHECK(CALC_EVAL("1 * 1") == 1);
    CHECK(CALC_EVAL("1 * 2") == 2);
    CHECK(CALC_EVAL("2 * 1") == 2);
    CHECK(CALC_EVAL("2 * 3 * 4") == 24);
    CHECK(CALC_EVAL("(2 * 3) * 4") == 24);
    CHECK(CALC_EVAL("2 * (3 * 4)") == 24);
    CHECK(CALC_EVAL("-1 * 1") == -1);
    CHECK(CALC_EVAL("1 * -1") == -1);
    CHECK(CALC_EVAL("-1 * -1") == 1);
}
