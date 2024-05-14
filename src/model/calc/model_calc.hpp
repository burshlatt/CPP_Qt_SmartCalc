#ifndef SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
#define SMARTCALC_MODEL_CALC_MODEL_CALC_HPP

#include <stack>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <string_view>
#include <unordered_map>

class CalcModel {
private:
    using UOperation = std::function<double(double)>;
    using BOperation = std::function<double(double, double)>;

public:
    using Coords = std::pair<std::vector<double>, std::vector<double>>;

private:
    enum class Priority : int {
        kLow,
        kHigh,
        kNo
    };

    enum class Type {
        kNo,
        kX,
        kNumber,
        kOperator,
        kFunction,
        kOpenBr,
        kCloseBr
    };

    struct Token {
        std::string name{};
        Type type{Type::kFunction};
        Priority priority{Priority::kNo};
        double value{};
    };

public:
    std::optional<double> Calculate(std::string_view input, double x = 0.0);
    Coords CalculateGraph(std::string_view input, double x_start, double x_end);

private:
    void Clear();
    void ClearBuffer();
    void HandleOperator(const Token& data);

    bool HandleTail();
    bool HandleClosingBracket();
    bool HandleTokens(const Token& token);

    std::string Trim(std::string_view input);

    std::optional<double> GetNum();
    std::optional<double> CalculateOperation(double x);

    std::vector<Token> Tokenize(std::string_view input);
    Token ParseName(std::string_view input, std::size_t& pos);
    Token ParseNumber(std::string_view input, std::size_t& pos);

private:
    std::stack<Token> stack_;
    std::stack<double> buffer_;
    std::vector<Token> output_;

    static const std::unordered_map<char, Token> short_tokens_;
    static const std::unordered_map<std::string, Token> long_tokens_;
    static const std::unordered_map<std::string, UOperation> unary_op_;
    static const std::unordered_map<std::string, BOperation> binary_op_;
};

#endif  // SMARTCALC_MODEL_CALC_MODEL_CALC_HPP
