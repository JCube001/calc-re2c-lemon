#include "catch.hpp"
#include "eval.hpp"

SCENARIO("The evaluator shall produce correct multiplication results", "[calc][op][mul]") {
    CHECK(eval("0 * 0") == 0);
    CHECK(eval("0 * 1") == 0);
    CHECK(eval("1 * 0") == 0);
    CHECK(eval("1 * 1") == 1);
    CHECK(eval("1 * 2") == 2);
    CHECK(eval("2 * 1") == 2);
    CHECK(eval("2 * 3 * 4") == 24);
    CHECK(eval("(2 * 3) * 4") == 24);
    CHECK(eval("2 * (3 * 4)") == 24);
    CHECK(eval("-1 * 1") == -1);
    CHECK(eval("1 * -1") == -1);
    CHECK(eval("-1 * -1") == 1);
}
