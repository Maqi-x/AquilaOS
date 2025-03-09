/******************************************************************************
 *                                   AquilaOS
 * (c) 2025 Maqix
 *
 * You should receive AquilaOS license with this source code. If not - check:
 *  https://github.com/Maqi-x/AquilaOS/blob/main/LICENSE.md
 ******************************************************************************/

#include <math/eval.hpp>
#include <string.hpp>

namespace math {

bool isDigit(char str) { return str >= '0' && str <= '9'; }

Parser::Parser(const char* expr) : expr(expr), pos(0) {}

long Parser::eval() { return parseExpression(); }
char Parser::peek() { return expr[pos]; }
char Parser::get() { return expr[pos++]; }

long Parser::parseNumber() {
    long result = 0;
    while (isDigit(peek())) {
        result = result * 10 + (get() - '0');
    }
    return result;
}

long Parser::parseFactor() {
    while (peek() == ' ') get();
    if (peek() == '(') {
        get();
        long result = parseExpression();
        get();
        return result;
    } else {
        return parseNumber();
    }
}

long Parser::parseTerm() {
    long result = parseFactor();
    while (true) {
        while (peek() == ' ') get();
        if (peek() == '*') {
            get();
            result *= parseFactor();
        } else if (peek() == '/') {
            get();
            result /= parseFactor();
        } else {
            break;
        }
    }
    return result;
}

long Parser::parseExpression() {
    long result = parseTerm();
    while (true) {
        while (peek() == ' ') get();
        if (peek() == '+') {
            get();
            result += parseTerm();
        } else if (peek() == '-') {
            get();
            result -= parseTerm();
        } else {
            break;
        }
    }
    return result;
}

long Eval(const char* expr) { return Parser(expr).eval(); }

long Eval(String expr) { return Parser(expr.c_str()).eval(); }

} // namespace math