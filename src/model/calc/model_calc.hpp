#ifndef SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
#define SMARTCALC_MODEL_CALC_MODEL_CALC_HPP

#include <stack>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>

class CalcModel { 
public:
    struct Ln {};
    struct Log {};
    struct Abs {};
    struct Mod {};
    struct Pow {};
    struct Div {};
    struct Mul {};
    struct Sqrt {};
    struct Plus {};
    struct Minus {};
    struct BracketOpen {};
    struct BracketClose {};
    struct Trigonometry {};

    struct Number {
        double value{};
    };

public:
    using Token = std::variant<
        Ln,
        Log,
        Abs,
        Mod,
        Pow,
        Div,
        Mul,
        Sqrt,
        Plus,
        Minus,
        BracketOpen,
        BracketClose,
        Trigonometry
    >;

public:
    CalcModel() = default;
    ~CalcModel() = default;

public:
    std::optional<double> Calculate(const std::string& str);

private:
    std::vector<Token> Tokenize(const std::string& input);
    Number ParseNumber(const std::string& input, std::size_t& pos);

private:
    const std::unordered_map<std::string, Token> tokens_map_ {
        { "ln", Ln{} },
        { "*", Mul{} },
        { "/", Div{} },
        { "^", Pow{} },
        { "+", Plus{} },
        { "-", Minus{} },
        { "log", Log{} },
        { "mod", Mod{} },
        { "abs", Abs{} },
        { "sqrt", Sqrt{} },
        { "(", BracketOpen{} },
        { ")", BracketClose{} },
        { "cos", Trigonometry{} },
        { "sin", Trigonometry{} },
        { "tan", Trigonometry{} },
        { "acos", Trigonometry{} },
        { "asin", Trigonometry{} },
        { "atan", Trigonometry{} }
    };

    std::stack<std::string> stack_;
    std::vector<std::string> output_;

    bool is_rad_{false};
};

#endif  // SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
