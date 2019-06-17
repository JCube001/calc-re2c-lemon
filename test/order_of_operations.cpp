#include "calc.h"
#include "catch.hpp"
#include "utility.hpp"

SCENARIO("The evaluator shall adhere to the order of operations for arithmetic", "[calc][op]") {
    CHECK(CALC_EVAL("1 + 2 * 3") == 7);
    CHECK(CALC_EVAL("(1 + 2) * 3") == 9);
    CHECK(CALC_EVAL("(1 + 3 * 5) / 2 - 1") == 7);
    CHECK(CALC_EVAL("20 - 4 - 6") == 10);
}
