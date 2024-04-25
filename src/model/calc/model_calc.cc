#include "model_calc.hpp"

const std::unordered_map<char, CalcModel::Token> CalcModel::operators_{
    {'^', Token{"Pow"}},
    {'(', Token{"", OPEN_BR, NO_PRIORITY}},
    {')', Token{"", CLOSE_BR, NO_PRIORITY}},
    {'%', Token{"Mod", OPERATOR, HIGH_PRIORITY}},
    {'*', Token{"Mul", OPERATOR, HIGH_PRIORITY}},
    {'/', Token{"Div", OPERATOR, HIGH_PRIORITY}},
    {'+', Token{"Plus", OPERATOR, LOW_PRIORITY,}},
    {'-', Token{"Minus", OPERATOR, LOW_PRIORITY}}
};

const std::unordered_map<std::string, CalcModel::Token> CalcModel::functions_{
    {"ln",   Token{"Ln"}},   {"log",  Token{"Log"}},  {"abs",  Token{"Abs"}},
    {"cos",  Token{"Cos"}},  {"sin",  Token{"Sin"}},  {"tan",  Token{"Tan"}},
    {"acos", Token{"Acos"}}, {"asin", Token{"Asin"}}, {"atan", Token{"Atan"}},
    {"sqrt", Token{"Sqrt"}}
};

const std::unordered_map<std::string, CalcModel::UOperation> CalcModel::unary_op_{
    {"Neg",  [](double x) { return -x; }},
    {"Ln",   [](double x) { return std::log(x); }},
    {"Cos",  [](double x) { return std::cos(x); }},
    {"Sin",  [](double x) { return std::sin(x); }},
    {"Tan",  [](double x) { return std::tan(x); }},
    {"Abs",  [](double x) { return std::fabs(x); }},
    {"Acos", [](double x) { return std::acos(x); }},
    {"Asin", [](double x) { return std::asin(x); }},
    {"Atan", [](double x) { return std::atan(x); }},
    {"Sqrt", [](double x) { return std::sqrt(x); }},
    {"Log",  [](double x) { return std::log10(x); }}
};

const std::unordered_map<std::string, CalcModel::BOperation> CalcModel::binary_op_{
    {"Mul",   [](double x, double y) { return x * y; }},
    {"Div",   [](double x, double y) { return x / y; }},
    {"Plus",  [](double x, double y) { return x + y; }},
    {"Minus", [](double x, double y) { return x - y; }},
    {"Pow",   [](double x, double y) { return std::pow(x, y); }},
    {"Mod",   [](double x, double y) { return std::fmod(x, y); }}
};

std::optional<double> CalcModel::Calculate(std::string_view input) {
    Clear();

    std::vector<Token> tokens{Tokenize(input)};

    for (const auto& token : tokens) {
        if (token.type == NO_TYPE) {
            return std::nullopt;
        } else if (!HandleTokens(token)) {
            return std::nullopt;
        }
    }

    if (!HandleTail()) {
        return std::nullopt;
    }

    return CalculateOperation();
}

void CalcModel::Clear() {
    while (!stack_.empty()) {
        stack_.pop();
    }

    while (!buffer_.empty()) {
        buffer_.pop();
    }

    output_.clear();
}

std::vector<CalcModel::Token> CalcModel::Tokenize(std::string_view input) {
    std::string tmp_str;

    for (auto ch : input) {
        auto symbol{static_cast<unsigned char>(ch)};

        if (!std::isspace(symbol)) {
            tmp_str.push_back(ch);
        }
    }

    std::vector<Token> tokens;
    const std::size_t size{tmp_str.size()};

    for (std::size_t pos{}; pos < size; ) {
        auto symbol{static_cast<unsigned char>(tmp_str[pos])};
        auto next_symbol{static_cast<unsigned char>(tmp_str[pos + 1])};

        auto is_digit{std::isdigit(symbol)};
        auto is_alpha{std::isalpha(symbol)};
        auto is_negative{symbol == '-' && tmp_str[pos - 1] == '('};
        is_negative &= (tmp_str[pos + 1] == '(' || std::isdigit(next_symbol));

        if (is_digit) {
            tokens.emplace_back(ParseNumber(tmp_str, pos));
        } else if (is_alpha) {
            tokens.emplace_back(ParseName(tmp_str, pos));
        } else if (is_negative) {
            tokens.emplace_back(Token{"Neg", OPERATOR});
            ++pos;
        } else if (auto it{operators_.find(symbol)}; it != operators_.end()) {
            tokens.emplace_back(it->second);
            ++pos;
        } else {
            tokens.emplace_back(Token{"", NO_TYPE});
            return tokens;
        }
    }

    return tokens;
}

CalcModel::Token CalcModel::ParseNumber(std::string_view input, std::size_t& pos) {
    std::size_t first{pos};
    auto symbol{static_cast<unsigned char>(input[pos])};
    bool is_dot{false};

    while (std::isdigit(symbol) || symbol == '.') {
        symbol = static_cast<unsigned char>(input[++pos]);

        if (!is_dot && symbol == '.') {
            is_dot = true;
        } else if (is_dot && symbol == '.') {
            ++pos;
            return Token{"", NO_TYPE};
        }
    }

    std::string num{input.substr(first, pos - first)};

    double res{std::stod(num)};

    return Token{"", NUMBER, NO_PRIORITY, res};
}

CalcModel::Token CalcModel::ParseName(std::string_view input, std::size_t& pos) {
    std::string name;
    auto symbol{static_cast<unsigned char>(input[pos])};

    while (std::isalpha(symbol)) {
        name.push_back(input[pos]);
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (functions_.find(name) != functions_.end()) {
        return functions_.at(name);
    }

    return Token{"", NO_TYPE};
}

void CalcModel::HandleOperator(const Token& data) {
    while (!stack_.empty()) {
        auto stack_top{stack_.top()};

        if (stack_top.type == OPERATOR && stack_top.priority >= data.priority) {
            output_.push_back(stack_.top());
            stack_.pop();
        } else {
            stack_.push(data);
            break;
        }
    }

    if (stack_.empty()) {
        stack_.push(data);
    }
}

bool CalcModel::HandleClosingBracket() {
    bool is_open_br{false};

    while (!stack_.empty() && !is_open_br) {
        auto stack_top{stack_.top()};

        if (stack_top.type != OPEN_BR) {
            output_.push_back(stack_.top());
        } else {
            is_open_br = true;
        }

        stack_.pop();
    }

    if (stack_.empty() && !is_open_br) {
        return false;
    }

    while (!stack_.empty()) {
        auto stack_top{stack_.top()};

        if (stack_top.type == FUNCTION) {
            output_.push_back(stack_.top());
            stack_.pop();
        } else {
            break;
        }
    }

    return true;
}

bool CalcModel::HandleTokens(const Token& token) {
    bool is_correct{true};

    if (token.type == NUMBER) {
        output_.push_back(token);
    } else if (token.type == FUNCTION || token.type == OPEN_BR) {
        stack_.push(token);
    } else if (token.type == OPERATOR) {
        HandleOperator(token);
    } else if (token.type == CLOSE_BR) {
        is_correct = HandleClosingBracket();
    }

    return is_correct;
}

bool CalcModel::HandleTail() {
    while (!stack_.empty()) {
        auto stack_top{stack_.top()};

        if (stack_top.type == OPEN_BR || stack_top.type == CLOSE_BR) {
            return false;
        } else if (stack_top.type == OPERATOR || stack_top.type == FUNCTION) {
            output_.push_back(stack_.top());
            stack_.pop();
        }
    }

    return true;
}

std::optional<double> CalcModel::GetNum() {
    if (!buffer_.empty()) {
        double num{buffer_.top()};
        buffer_.pop();
        return num;
    }

    return std::nullopt;
}

std::optional<double> CalcModel::CalculateOperation() {
    for (const auto& token : output_) {
        if (token.type == NUMBER) {
            buffer_.push(token.value);
        }

        if (auto it{unary_op_.find(token.name)}; it != unary_op_.end()) {
            auto x{GetNum()};

            if (x.has_value()) {
                buffer_.push(it->second(*x));
            } else {
                return std::nullopt;
            }
        } else if (auto it{binary_op_.find(token.name)}; it != binary_op_.end()) {
            auto x{GetNum()};
            auto y{GetNum()};

            if (x.has_value() && y.has_value()) {
                buffer_.push(it->second(*y, *x));
            } else {
                return std::nullopt;
            }
        }
    }

    if (buffer_.size() > 1) {
        return std::nullopt;
    }

    return *GetNum();
}
