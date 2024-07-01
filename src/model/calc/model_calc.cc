#include <cmath>
#include <locale>
#include <unordered_set>

#include "model_calc.hpp"

const std::unordered_map<char, CalcModel::Token> CalcModel::short_tokens_{
    {'^', Token{"Pow"}},
    {'(', Token{"OpenBr",  Type::kOpenBr,   Priority::kNo}},
    {')', Token{"CloseBr", Type::kCloseBr,  Priority::kNo}},
    {'+', Token{"Plus",    Type::kOperator, Priority::kLow}},
    {'-', Token{"Minus",   Type::kOperator, Priority::kLow}},
    {'%', Token{"Mod",     Type::kOperator, Priority::kHigh}},
    {'*', Token{"Mul",     Type::kOperator, Priority::kHigh}},
    {'/', Token{"Div",     Type::kOperator, Priority::kHigh}}
};

const std::unordered_map<std::string, CalcModel::Token> CalcModel::long_tokens_{
    {"ln",   Token{"Ln"}},   {"log",  Token{"Log"}},  {"abs",  Token{"Abs"}},
    {"cos",  Token{"Cos"}},  {"sin",  Token{"Sin"}},  {"tan",  Token{"Tan"}},
    {"acos", Token{"Acos"}}, {"asin", Token{"Asin"}}, {"atan", Token{"Atan"}},
    {"sqrt", Token{"Sqrt"}}, {"Pi", Token{"Pi", Type::kNumber, Priority::kNo, M_PI}}
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

CalcModel::CalcModel() {
    std::locale::global(std::locale("C"));
}

CalcModel::Coords CalcModel::CalculateGraph(std::string_view input, double x_start, double x_end, MeasurementType meas_type) {
    std::vector<double> x_coords;
    std::vector<double> y_coords;

    auto y_first{Calculate(input, x_start, meas_type)};

    if (y_first.has_value()) {
        x_coords.push_back(x_start);
        y_coords.push_back(*y_first);

        x_start += 0.1;

        while (x_start <= x_end) {
            ClearBuffer();

            x_coords.push_back(x_start);
            y_coords.push_back(*CalculateOperation(x_start));

            x_start += 0.1;
        }
    }

    return std::make_pair(x_coords, y_coords);
}

std::optional<double> CalcModel::Calculate(std::string_view input, double x, MeasurementType meas_type) {
    Clear();

    meas_type_ = meas_type;

    std::vector<Token> tokens{Tokenize(input)};

    for (const auto& token : tokens) {
        if (!HandleTokens(token)) {
            return std::nullopt;
        }
    }

    if (!HandleTail()) {
        return std::nullopt;
    }

    return CalculateOperation(x);
}

void CalcModel::ClearBuffer() {
    while (!buffer_.empty()) {
        buffer_.pop();
    }
}

void CalcModel::Clear() {
    while (!stack_.empty()) {
        stack_.pop();
    }

    ClearBuffer();
    output_.clear();
}

std::string CalcModel::Trim(std::string_view input) {
    std::string tmp;

    for (auto ch : input) {
        auto symbol{static_cast<unsigned char>(ch)};

        if (!std::isspace(symbol)) {
            tmp.push_back(ch);
        }
    }

    return tmp;
}

std::vector<CalcModel::Token> CalcModel::Tokenize(std::string_view input) {
    std::vector<Token> tokens;
    std::string tmp_str{Trim(input)};
    const std::size_t size{tmp_str.size()};

    for (std::size_t pos{}; pos < size; ) {
        auto symbol{static_cast<unsigned char>(tmp_str[pos])};
        auto next_symbol{static_cast<unsigned char>(tmp_str[pos + 1])};

        auto is_x{tmp_str[pos] == 'x'};
        auto is_digit{std::isdigit(symbol)};
        auto is_alpha{std::isalpha(symbol)};
        auto is_negative{symbol == '-' && tmp_str[pos - 1] == '('};
        is_negative &= (tmp_str[pos + 1] == '(' || std::isdigit(next_symbol));

        if (is_x) {
            tokens.emplace_back(Token{"", Type::kX});
            ++pos;
        } else if (is_digit) {
            tokens.emplace_back(ParseNumber(tmp_str, pos));
        } else if (is_alpha) {
            tokens.emplace_back(ParseName(tmp_str, pos));
        } else if (is_negative) {
            tokens.emplace_back(Token{"Neg", Type::kOperator});
            ++pos;
        } else if (auto it{short_tokens_.find(symbol)}; it != short_tokens_.end()) {
            tokens.emplace_back(it->second);
            ++pos;
        } else {
            tokens.emplace_back(Token{"", Type::kNo});
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
            return Token{"", Type::kNo};
        }
    }

    std::string num{input.substr(first, pos - first)};

    double res{std::stod(num)};

    return Token{"", Type::kNumber, Priority::kNo, res};
}

CalcModel::Token CalcModel::ParseName(std::string_view input, std::size_t& pos) {
    std::string name;
    auto symbol{static_cast<unsigned char>(input[pos])};

    while (std::isalpha(symbol)) {
        name.push_back(input[pos]);
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    if (long_tokens_.find(name) != long_tokens_.end()) {
        return long_tokens_.at(name);
    }

    return Token{"", Type::kNo};
}

void CalcModel::HandleOperator(const Token& data) {
    while (!stack_.empty()) {
        auto stack_top{stack_.top()};

        if (stack_top.type == Type::kOperator && stack_top.priority >= data.priority) {
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

        if (stack_top.type != Type::kOpenBr) {
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

        if (stack_top.type == Type::kFunction) {
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

    if (token.type == Type::kNo) {
        return false;
    } else if (token.type == Type::kNumber || token.type == Type::kX) {
        output_.push_back(token);
    } else if (token.type == Type::kFunction || token.type == Type::kOpenBr) {
        stack_.push(token);
    } else if (token.type == Type::kOperator) {
        HandleOperator(token);
    } else if (token.type == Type::kCloseBr) {
        is_correct = HandleClosingBracket();
    }

    return is_correct;
}

bool CalcModel::HandleTail() {
    while (!stack_.empty()) {
        auto stack_top{stack_.top()};

        if (stack_top.type == Type::kOpenBr || stack_top.type == Type::kCloseBr) {
            return false;
        } else if (stack_top.type == Type::kOperator || stack_top.type == Type::kFunction) {
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

bool CalcModel::IsBasicTrigFunction(const Token& token) {
    static const std::unordered_set<std::string> basic_trig{"Cos", "Sin", "Tan"};

    return basic_trig.find(token.name) != basic_trig.end();
}

bool CalcModel::IsInverseTrigFunction(const Token& token) {
    static const std::unordered_set<std::string> inverse_trig{"Acos", "Asin", "Atan"};

    return inverse_trig.find(token.name) != inverse_trig.end();
}

std::optional<double> CalcModel::CalculateOperation(double x) {
    for (const auto& token : output_) {
        if (token.type == Type::kNumber) {
            buffer_.push(token.value);
        } else if (token.type == Type::kX) {
            buffer_.push(x);
        }

        if (auto it{unary_op_.find(token.name)}; it != unary_op_.end()) {
            auto x{GetNum()};

            if (x.has_value()) {
                bool is_deg{meas_type_ == MeasurementType::kDeg};

                if (is_deg && IsBasicTrigFunction(token)) {
                    buffer_.push(it->second(*x * M_PI / 180));
                } else if (is_deg && IsInverseTrigFunction(token)) {
                    buffer_.push(it->second(*x) * 180 / M_PI);
                } else {
                    buffer_.push(it->second(*x));
                }
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
