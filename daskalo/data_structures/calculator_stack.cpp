#include <iostream>
#include "stack_array.cpp"

using namespace std;

class calculator {
    public:

    static double eval_sum(const double &a, const double &b) {
        return a + b;
    }

    static double eval_sub(const double &a, const double &b) {
        return a - b;
    }

    static double eval_mul(const double &a, const double &b) {
        return a * b;
    }

    static double eval_div(const double &a, const double &b) {
        return a / b;
    }

    static constexpr double ( * evaluators[])(const double &, const double &) = {eval_sum, eval_sub, eval_mul, eval_div};
    
    static constexpr int ops_count = 8;
    static constexpr const char op_char_by_id[ops_count] = {'+', '-', '*', '/', '(', ')', '[', ']'};

    static constexpr const int precedence[] = {1, 1, 2, 2, 0, 0, 0, 0};

    static int get_operator_id(const char &a) {
        for(int i = 0; i < ops_count; ++ i) {
            if(a == op_char_by_id[i])
                return i;
        } 
        return -1;
    }

    static bool is_digit(const char &a) {
        return (a >= '0' && a <= '9');
    }

    static bool is_bracket(const int &op_id) {
        return op_id >= 4;
    }

    static bool is_open_bracket(const int &op_id) {
        return is_bracket(op_id) && op_id % 2 == 0;
    }

    static bool is_close_bracket(const int &op_id) {
        return is_bracket(op_id) && op_id % 2 == 1;
    }

    static int reverse_bracket(const int &op_id) {
        return op_id ^ 1;
    }

    static double eval(const double &a, const double &b, const char &operator_ch) {
        return eval(a, b, get_operator_id(operator_ch));
    }

    static double eval(const double &a, const double &b, const int &operator_id) {
        return evaluators[operator_id](a, b);
    }

    static double evaluate(const string &expression) {
        stack<double> vals; // the values
        stack<int> ops; // the operator id-s


        double value = 0;
        
        char prev = -1;
        
        for(int i = 0; i < (int)expression.size(); i ++) {
            const char& curr = expression[i];

            int operator_id = get_operator_id(curr);

            bool is_op = operator_id != -1;
            bool is_dig = is_digit(curr);
            bool is_last = i == (int) expression.size() - 1;
            bool bracket = is_bracket(operator_id);
            //cout << is_op << " " << is_dig << " " << is_last << endl;

            if(is_dig) {
                value *= 10;
                value += (int)(curr - '0');
            }

            if(is_last || is_op) {
                if(value != 0) {
                    vals.push(value);
                    cout << "pushing " << value << endl;
                    value = 0;
                }

                if(!bracket && is_op && (vals.empty() || is_open_bracket(get_operator_id(prev)))) {
                    vals.push(0);
                    cout << "pushing0" << endl;
                }

                if(!is_open_bracket(operator_id) && !ops.empty() && vals.size() >= 2 && (is_last || precedence[ops.top()] >= precedence[operator_id])) {
                    do {
                        int id = ops.top();
                        ops.pop();
                        double b = vals.top();
                        vals.pop();
                        double a = vals.top();
                        vals.pop();

                        cout << "evaluating: " << a << " " << b << " " << id << endl;

                        vals.push(eval(a, b, id));

                        if(!ops.empty() && is_open_bracket(ops.top()) && is_last) ops.pop();

                    } while((is_last || is_close_bracket(operator_id)) && !ops.empty() && !is_open_bracket(ops.top()));
                    if(!ops.empty() && is_open_bracket(ops.top())) ops.pop();
                }

                if(is_op && !is_close_bracket(operator_id)) {
                    ops.push(operator_id);
                    cout << "pushing: " << operator_id << endl;
                }
                continue;
            }
            if(is_dig || is_op)
                prev = curr;
        }

        return vals.top();
    }
};

constexpr double (*calculator::evaluators[])(const double&, const double&);

constexpr int calculator::precedence[];

constexpr char calculator::op_char_by_id[];

int main() {
    string expr;
    getline(cin, expr);

    //cout << calculator::eval(2, 3, '+') << endl;

    cout << calculator::evaluate(expr);
    cout << endl;
}
