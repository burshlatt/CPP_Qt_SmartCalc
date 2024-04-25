#ifndef SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
#define SMARTCALC_MODEL_CALC_MODEL_CALC_HPP

#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <string_view>
#include <unordered_map>

#define LOW_PRIORITY 0
#define HIGH_PRIORITY 1
#define NO_PRIORITY 3

#define NO_TYPE 0
#define NUMBER 1
#define OPERATOR 2
#define FUNCTION 3
#define OPEN_BR 4
#define CLOSE_BR 5

class CalcModel {
private:
    using UOperation = std::function<double(double)>;
    using BOperation = std::function<double(double, double)>;

    struct Token {
        std::string name{};
        int type{FUNCTION};
        int priority{NO_PRIORITY};
        double value{};
    };

public:
    CalcModel() = default;
    ~CalcModel() = default;

public:
    std::optional<double> Calculate(std::string_view input);

private:
    void Clear();
    void HandleOperator(const Token& data);

    bool HandleTail();
    bool HandleClosingBracket();
    bool HandleTokens(const Token& token);

    std::optional<double> GetNum();
    std::optional<double> CalculateOperation();

    std::vector<Token> Tokenize(std::string_view input);
    Token ParseName(std::string_view input, std::size_t& pos);
    Token ParseNumber(std::string_view input, std::size_t& pos);

private:
    std::stack<Token> stack_;
    std::stack<double> buffer_;
    std::vector<Token> output_;

    static const std::unordered_map<char, Token> operators_;
    static const std::unordered_map<std::string, Token> functions_;
    static const std::unordered_map<std::string, UOperation> unary_op_;
    static const std::unordered_map<std::string, BOperation> binary_op_;
};

#endif  // SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
