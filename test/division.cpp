#include "calc.h"
#include "catch.hpp"
#include "utility.hpp"

SCENARIO("The evaluator shall produce correct division results", "[calc][op][div]") {
    CHECK(CALC_EVAL("0 / 1") == 0);
    CHECK(CALC_EVAL("1 / 1") == 1);
    CHECK(CALC_EVAL("1 / 2") == Approx(0.5));
    CHECK(CALC_EVAL("2 / 1") == 2);
    CHECK(CALC_EVAL("2 / 3 / 4") == Approx(0.16666666666666666));
    CHECK(CALC_EVAL("(2 / 3) / 4") == Approx(0.16666666666666666));
    CHECK(CALC_EVAL("2 / (3 / 4)") == Approx(2.6666666666666665));
    CHECK(CALC_EVAL("-1 / 1") == -1);
    CHECK(CALC_EVAL("1 / -1") == -1);
    CHECK(CALC_EVAL("-1 / -1") == 1);
}
