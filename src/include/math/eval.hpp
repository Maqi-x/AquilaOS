/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#pragma once
#include <string.hpp>
#include <types.hpp>

namespace math {

bool isDigit(char str);

class Parser {
  public:
    Parser(const char* expr);
    long eval();

    const char* expr;
    size_t pos;

    char peek();
    char get();
    long parseNumber();
    long parseFactor();
    long parseTerm();
    long parseExpression();
};

long Eval(const char* expr);
long Eval(String expr);

} // namespace math