class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> operand;
        
        int ret = 0;
        for(int i = 0; i < tokens.size(); ++i) {
            string str = tokens[i];
            if(str == "+" || str == "-" || str == "*" || str == "/") {
                int op2 = operand.top();
                operand.pop();
                int op1 = operand.top();
                operand.pop();
                int res = 0;
                switch(str[0]) {
                    case '+': res = op1 + op2; break;
                    case '-': res = op1 - op2; break;
                    case '*': res = op1 * op2; break;
                    case '/': res = op1 / op2; break;
                    default: break;
                }
                operand.push(res);
            }
            else {
                int op = atoi(str.c_str());
                operand.push(op);
            }
        }
        return operand.top();
    }
};