Entry function: int main()  
"::":scope operator  
{} is scope operator  
char and wchar_t  

it is a good habit to use the type that the library defines as being appropriate for that specific purpose.  
Asymmetric ranges are usually easier to use than symmetric ones because of an important property: A range of the form [m, n) has n - m elements, and a range of the form [m, n] has n - m + 1 elements.  
cout set precision:
```cpp
float a = 1.23456;
streamsize prec = cout.precision(2);
cout << a << endl;
cout.precision(prec)
```
**Loop invariance** is a property of a loop that is true before and after each iteration.  
reference:
```cpp
vector<int> homework;
vector<int>& hw = homework; // hw is a synonym for homework
```
**lvalue** denotes nontemporary object.  
it is a good idea for the #ifndef to be the first line of file, some C++ implementation will skip the file if already defined.  
**vector** fast random access.  
**list** for fast insertion and deletion.  
It's not easy to pass an overloaded function directly as an argument to a template function.  

