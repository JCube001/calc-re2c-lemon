#ifndef EVAL_HPP
#define EVAL_HPP

#define EVAL(input, expected) \
    calc_eval(input, stderr, &result); \
    CHECK(result == Approx(expected));

#endif // EVAL_HPP
