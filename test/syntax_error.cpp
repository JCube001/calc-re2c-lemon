#include "calc.h"
#include "catch.hpp"
#include "utility.hpp"
#include <cmath>

SCENARIO("The evaluator shall return NaN for invalid expressions", "[calc][syntax][error]") {
    CHECK(isnan(CALC_EVAL("")));
    CHECK(isnan(CALC_EVAL("1 // 2")));
    CHECK(isnan(CALC_EVAL("1 + 2 3")));
    CHECK(isnan(CALC_EVAL("(1 + 2")));
    CHECK(isnan(CALC_EVAL("+1")));
    CHECK(isnan(CALC_EVAL("1 ++ 2")));
}
