#include "catch.hpp"
#include "eval.hpp"

SCENARIO("The evaluator shall produce correct division results", "[calc][op][div]") {
    CHECK(eval("0 / 1") == 0);
    CHECK(eval("1 / 1") == 1);
    CHECK(eval("1 / 2") == Approx(0.5));
    CHECK(eval("2 / 1") == 2);
    CHECK(eval("2 / 3 / 4") == Approx(0.16666666666666666));
    CHECK(eval("(2 / 3) / 4") == Approx(0.16666666666666666));
    CHECK(eval("2 / (3 / 4)") == Approx(2.6666666666666665));
    CHECK(eval("-1 / 1") == -1);
    CHECK(eval("1 / -1") == -1);
    CHECK(eval("-1 / -1") == 1);
}
