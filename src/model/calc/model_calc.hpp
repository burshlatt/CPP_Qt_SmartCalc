#ifndef SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
#define SMARTCALC_MODEL_CALC_MODEL_CALC_HPP

#include <algorithm>
#include <cmath>
#include <functional>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <string_view>
#include <variant>
#include <vector>

#define NO_PRIORITY 0
#define LOW_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define HIGH_PRIORITY 3

#define NO_TYPE 0
#define NUMBER 1
#define OPERATOR 2
#define FUNCTION 3
#define OPEN_BR 4
#define CLOSE_BR 5
#define COMMA 6

class CalcModel {
private:
    struct Ln {
        double value{};
        std::string name{"Ln"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Log {
        double value{};
        std::string name{"Log"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Abs {
        double value{};
        std::string name{"Abs"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Mod {
        double value{};
        std::string name{"Mod"};
        int type{OPERATOR};
        int priority{MEDIUM_PRIORITY};
    };

    struct Pow {
        double value{};
        std::string name{"Pow"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Div {
        double value{};
        std::string name{"Div"};
        int type{OPERATOR};
        int priority{MEDIUM_PRIORITY};
    };

    struct Mul {
        double value{};
        std::string name{"Mul"};
        int type{OPERATOR};
        int priority{MEDIUM_PRIORITY};
    };

    struct Cos {
        double value{};
        std::string name{"Cos"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Sin {
        double value{};
        std::string name{"Sin"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Tan {
        double value{};
        std::string name{"Tan"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Acos {
        double value{};
        std::string name{"Acos"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Asin {
        double value{};
        std::string name{"Asin"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Atan {
        double value{};
        std::string name{"Atan"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Sqrt {
        double value{};
        std::string name{"Sqrt"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Plus {
        double value{};
        std::string name{"Plus"};
        int type{OPERATOR};
        int priority{LOW_PRIORITY};
    };

    struct Minus {
        double value{};
        std::string name{"Minus"};
        int type{OPERATOR};
        int priority{LOW_PRIORITY};
    };

    struct Max {
        double value{};
        std::string name{"Max"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Min {
        double value{};
        std::string name{"Min"};
        int type{FUNCTION};
        int priority{HIGH_PRIORITY};
    };

    struct Comma {
        double value{};
        std::string name{"Comma"};
        int type{COMMA};
        int priority{NO_PRIORITY};
    };

    struct BracketOpen {
        double value{};
        std::string name{};
        int type{OPEN_BR};
        int priority{NO_PRIORITY};
    };

    struct BracketClose {
        double value{};
        std::string name{};
        int type{CLOSE_BR};
        int priority{NO_PRIORITY};
    };

    struct UnknownToken {
        double value{};
        std::string name{};
        int type{NO_TYPE};
        int priority{NO_PRIORITY};
    };

    struct Number {
        double value{};
        std::string name{};
        int type{NUMBER};
        int priority{NO_PRIORITY};
    };

public:
    using Token = std::variant<
        Ln, Log, Abs, Mod, Pow,
        Div, Mul, Cos, Sin, Tan,
        Acos, Asin, Atan, Sqrt,
        Plus, Minus, Min, Max,
        BracketOpen, BracketClose,
        UnknownToken, Number, Comma
    >;

public:
    CalcModel() = default;
    ~CalcModel() = default;

public:
    std::optional<double> Calculate(std::string_view input);

private:
    void Clear();
    void ProcessOperator(const Token& data);

    bool ProcessComma();
    bool DistributeTail();
    bool ProcessClosingBracket();
    bool DistributeTokens(const Token& token);

    std::optional<double> GetNum();
    std::optional<double> CalculateOperation();

    std::vector<Token> Tokenize(std::string_view input);
    Token ParseName(std::string_view input, std::size_t& pos);
    Number ParseNumber(std::string_view input, std::size_t& pos);

private:
    std::stack<Token> stack_;
    std::stack<double> buffer_;
    std::vector<Token> output_;

    static const std::unordered_map<char, Token> operators_;
    static const std::unordered_map<std::string, Token> functions_;
    static const std::unordered_map<std::string, std::function<double(double)>> func_operations_;
    static const std::unordered_map<std::string, std::function<double(double, double)>> op_operations_;
};

#endif  // SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
