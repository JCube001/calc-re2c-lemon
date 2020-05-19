#include "eval.hpp"

#include "calc.h"
#include <stdexcept>

double eval(const char* code)
{
    double result;
    auto rc = calc_eval(&result, code);
    if (rc != 0) throw std::runtime_error{"invalid expression"};
    return result;
}
