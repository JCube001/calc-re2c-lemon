#include "calc.h"
#include "catch.hpp"
#include "utility.hpp"

SCENARIO("The evaluator shall produce correct addition results", "[calc][op][add]") {
    CHECK(CALC_EVAL("0 + 0") == 0);
    CHECK(CALC_EVAL("0 + 1") == 1);
    CHECK(CALC_EVAL("1 + 0") == 1);
    CHECK(CALC_EVAL("1 + 1") == 2);
    CHECK(CALC_EVAL("1 + 2") == 3);
    CHECK(CALC_EVAL("2 + 1") == 3);
    CHECK(CALC_EVAL("1 + 2 + 3") == 6);
    CHECK(CALC_EVAL("(1 + 2) + 3") == 6);
    CHECK(CALC_EVAL("1 + (2 + 3)") == 6);
    CHECK(CALC_EVAL("-1 + 1") == 0);
    CHECK(CALC_EVAL("1 + -1") == 0);
    CHECK(CALC_EVAL("-1 + -1") == -2);
}
