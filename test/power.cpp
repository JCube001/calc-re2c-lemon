#include "eval.hpp"
#include "catch.hpp"

SCENARIO("The evaluator shall produce correct power results", "[calc][op][pow]") {
    CHECK(eval("1 ^ 0") == 1);
    CHECK(eval("1 ^ 1") == 1);
    CHECK(eval("1 ^ 2") == 1);
    CHECK(eval("2 ^ 0") == 1);
    CHECK(eval("2 ^ 1") == 2);
    CHECK(eval("2 ^ 2") == 4);
    CHECK(eval("2 ^ 3") == 8);
    CHECK(eval("3 ^ 2") == 9);
    CHECK(eval("2 ^ 3 ^ 2") == 512);
    CHECK(eval("(2 ^ 3) ^ 2") == 64);
    CHECK(eval("2 ^ (3 ^ 2)") == 512);
    CHECK(eval("2 ^ -1") == 0.5);
    CHECK(eval("-2 ^ 1") == -2);
}
