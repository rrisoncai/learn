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