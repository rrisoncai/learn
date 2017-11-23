#include <iostream>
#include <string>

using namespace std;

void printName(string name)
{
    string greetings = "hello, " + name + "!";
    int pad = 1;
    int num_row = pad * 2 + 3;
    const string::size_type cols = greetings.size() + pad * 2 + 2;
    int r = 0;
    int c = 0;
    while(r != num_row)
    {
        c = 0;
        while(c != cols)
        {
            if(r == pad + 1 && c == pad + 1)
            {
                cout << greetings;
                c += greetings.size();
            }
            else
            {
                if(r == 0 || r == num_row - 1 || c == 0 || c == cols - 1)
                    cout << "*";
                else
                    cout << " ";
                c++;
            }
        }
        cout << endl;
        r++;
    }
}
int main()
{
    cout << "input your name:";
    string name;
    cin >> name;
    printName(name);
    return 0;
}
