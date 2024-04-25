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

private:
    enum class Priority : int {
        kLow,
        kHigh,
        kNo
    };

    enum class Type {
        kNo,
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

    std::string Trim(std::string_view input);

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
