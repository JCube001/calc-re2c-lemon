#include "catch.hpp"
#include "eval.hpp"

SCENARIO("The evaluator shall produce correct subtraction results", "[calc][op][sub]") {
    CHECK(eval("0 - 0") == 0);
    CHECK(eval("0 - 1") == -1);
    CHECK(eval("1 - 0") == 1);
    CHECK(eval("1 - 1") == 0);
    CHECK(eval("1 - 2") == -1);
    CHECK(eval("2 - 1") == 1);
    CHECK(eval("4 - 2 - 1") == 1);
    CHECK(eval("(4 - 2) - 1") == 1);
    CHECK(eval("4 - (2 - 1)") == 3);
    CHECK(eval("-1 - 1") == -2);
    CHECK(eval("1 - -1") == 2);
    CHECK(eval("-1 - -1") == 0);
}
