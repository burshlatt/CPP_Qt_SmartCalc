#include "model_calc.hpp"

const std::unordered_map<char, CalcModel::Token> CalcModel::operators_{
    {'%', Mod{}},   {'^', Pow{}},         {'*', Mul{}},
    {'/', Div{}},   {'+', Plus{}},        {'-', Minus{}},
    {',', Comma{}}, {'(', BracketOpen{}}, {')', BracketClose{}}
};

const std::unordered_map<std::string, CalcModel::Token> CalcModel::functions_{
    {"ln", Ln{}},     {"log", Log{}},   {"abs", Abs{}},   {"cos", Cos{}},
    {"sin", Sin{}},   {"tan", Tan{}},   {"max", Max{}},   {"min", Min{}},
    {"acos", Acos{}}, {"asin", Asin{}}, {"atan", Atan{}}, {"sqrt", Sqrt{}}
};

const std::unordered_map<std::string, std::function<double(double)>> CalcModel::func_operations_{
    {"Ln", [](double x) { return std::log(x); }},
    {"Cos", [](double x) { return std::cos(x); }},
    {"Sin", [](double x) { return std::sin(x); }},
    {"Tan", [](double x) { return std::tan(x); }},
    {"Abs", [](double x) { return std::fabs(x); }},
    {"Acos", [](double x) { return std::acos(x); }},
    {"Asin", [](double x) { return std::asin(x); }},
    {"Atan", [](double x) { return std::atan(x); }},
    {"Sqrt", [](double x) { return std::sqrt(x); }},
    {"Log", [](double x) { return std::log10(x); }}
};

const std::unordered_map<std::string, std::function<double(double, double)>> CalcModel::op_operations_{
    {"Plus", [](double x, double y) { return x + y; }},
    {"Minus", [](double x, double y) { return x - y; }},
    {"Mul", [](double x, double y) { return x * y; }},
    {"Div", [](double x, double y) { return x / y; }},
    {"Pow", [](double x, double y) { return std::pow(x, y); }},
    {"Mod", [](double x, double y) { return std::fmod(x, y); }},
    {"Max", [](double x, double y) { return std::max(x, y); }},
    {"Min", [](double x, double y) { return std::min(x, y); }}
};

std::optional<double> CalcModel::Calculate(std::string_view input) {
    Clear();

    std::vector<Token> tokens{Tokenize(input)};

    for (const auto& token : tokens) {
        if (std::holds_alternative<UnknownToken>(token)) {
            return std::nullopt;
        } else if (!DistributeTokens(token)) {
            return std::nullopt;
        }
    }

    if (!DistributeTail()) {
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
            tmp_str.push_back(symbol);
        }
    }

    std::vector<Token> tokens;
    std::size_t pos{};
    const std::size_t size{tmp_str.size()};

    while (pos < size) {
        auto symbol{static_cast<unsigned char>(tmp_str[pos])};

        if (std::isdigit(symbol)) {
            tokens.emplace_back(ParseNumber(tmp_str, pos));
        } else if (std::isalpha(symbol)) {
            tokens.emplace_back(ParseName(tmp_str, pos));
        } else if (symbol == '-' && tmp_str[pos - 1] == '(') {
            ++pos;
        } else if (auto it{operators_.find(symbol)}; it != operators_.end()) {
            tokens.emplace_back(it->second);
            ++pos;
        }
    }

    return tokens;
}

CalcModel::Number CalcModel::ParseNumber(std::string_view input, std::size_t& pos) {
    std::size_t first{pos};
    auto symbol{static_cast<unsigned char>(input[pos])};

    bool is_negative{false};

    if (input[pos - 1] == '-' && input[pos - 2] == '(') {
        is_negative = true;
    }

    while (std::isdigit(symbol) || symbol == '.') {
        symbol = static_cast<unsigned char>(input[++pos]);
    }

    std::string num{input.substr(first, pos - first)};

    double res{std::stod(num)};

    if (is_negative) {
        res = -res;
    }

    return Number{res};
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

    return UnknownToken{};
}

void CalcModel::ProcessOperator(const Token& data) {
    bool is_swap{true};

    while (!stack_.empty() && is_swap) {
        std::visit([this, &is_swap](auto&& stack_top, auto&& token_data) {
            if (stack_top.type == OPERATOR && stack_top.priority >= token_data.priority) {
                output_.push_back(stack_.top());
                stack_.pop();
            } else {
                stack_.push(token_data);
                is_swap = false;
            }
        }, stack_.top(), data);
    }

    if (stack_.empty()) {
        stack_.push(data);
    }
}

bool CalcModel::ProcessClosingBracket() {
    bool is_swap{true};

    while (!stack_.empty() && is_swap) {
        std::visit([this, &is_swap](auto&& stack_top) {
            if (stack_top.type != OPEN_BR) {
                output_.push_back(stack_.top());
            } else {
                is_swap = false;
            }
            stack_.pop();
        }, stack_.top());
    }

    if (stack_.empty() && is_swap) {
        return false;
    }

    is_swap = true;

    while (!stack_.empty() && is_swap) {
        std::visit([this, &is_swap](auto&& stack_top) {
            if (stack_top.type == FUNCTION) {
                output_.push_back(stack_.top());
                stack_.pop();
            } else {
                is_swap = false;
            }
        }, stack_.top());
    }

    return true;
}

bool CalcModel::ProcessComma() {
    bool is_swap{true};
    bool is_correct{true};

    while (!stack_.empty() && is_swap) {
        std::visit([this, &is_swap, &is_correct](auto&& stack_top) {
            if (stack_top.type == OPERATOR) {
                output_.push_back(stack_.top());
                stack_.pop();
            } else {
                if (stack_top.type != OPEN_BR) {
                    is_correct = false;
                }

                is_swap = false;
            }
        }, stack_.top());
    }

    return is_correct;
}

bool CalcModel::DistributeTokens(const Token& token) {
    bool is_correct{true};

    std::visit([this, &is_correct](auto&& data) {
        if (data.type == NUMBER) {
            output_.push_back(data);
        } else if (data.type == FUNCTION || data.type == OPEN_BR) {
            stack_.push(data);
        } else if (data.type == OPERATOR) {
            ProcessOperator(data);
        } else if (data.type == CLOSE_BR) {
            is_correct = ProcessClosingBracket();
        } else if (data.type == COMMA) {
            is_correct = ProcessComma();
        }
    }, token);

    return is_correct;
}

bool CalcModel::DistributeTail() {
    bool is_correct{true};

    while (!stack_.empty() && is_correct) {
        std::visit([this, &is_correct](auto&& stack_top) {
            if (stack_top.type == OPEN_BR || stack_top.type == CLOSE_BR) {
                is_correct = false;
                return;
            } else if (stack_top.type == OPERATOR || stack_top.type == FUNCTION) {
                output_.push_back(stack_.top());
                stack_.pop();
            }
        }, stack_.top());
    }

    return is_correct;
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
    bool is_correct{true};

    for (const auto& token : output_) {
        std::visit([this, &is_correct](auto&& data) {
            if (data.type == NUMBER) {
                buffer_.push(data.value);
            }

            if (auto it{func_operations_.find(data.name)}; it != func_operations_.end()) {
                auto x{GetNum()};

                if (x.has_value()) {
                    buffer_.push(it->second(*x));
                } else {
                    is_correct = false;
                    return;
                }
            } else if (auto it{op_operations_.find(data.name)}; it != op_operations_.end()) {
                auto x{GetNum()};
                auto y{GetNum()};

                if (x.has_value() && y.has_value()) {
                    buffer_.push(it->second(*y, *x));
                } else {
                    is_correct = false;
                    return;
                }
            }
        }, token);

        if (!is_correct) {
            return std::nullopt;
        }
    }

    if (buffer_.size() > 1) {
        return std::nullopt;
    }

    return *GetNum();
}
