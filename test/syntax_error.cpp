#include "calc.h"
#include "catch.hpp"

SCENARIO("The evaluator shall return -1 for invalid expressions", "[calc][syntax][error]") {
    double result;
    CHECK(calc_eval(&result, "") == -1);
    CHECK(calc_eval(&result, "1 // 2") == -1);
    CHECK(calc_eval(&result, "1 + 2 3") == -1);
    CHECK(calc_eval(&result, "(1 + 2") == -1);
}
