#include "catch.hpp"
#include "eval.hpp"

SCENARIO("The evaluator shall adhere to the order of operations for arithmetic", "[calc][op]") {
    CHECK(eval("1 + 2 * 3") == 7);
    CHECK(eval("(1 + 2) * 3") == 9);
    CHECK(eval("(1 + 3 * 5) / 2 - 1") == 7);
    CHECK(eval("20 - 4 - 6") == 10);
    CHECK(eval("-(4 + 2 ^ 3 ^ 0 * 5 ^ 2) + 7") == -47);
}
