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
Local variable declared to be **static** is preserved across invocation of the function.  
**remove_if** move elements to new position in the container.  
**map** will initialize value.  
template instantiate at link time.  
input iterator, output iterator, forward iterator, bidirectional iterator, random access  
Why range is [,): 1. treat last element; 2.treat empty range. 3. only != is needed.  
**const member function**: int grade() const; will not change the state of object.  
**class** private member by default; **struct** public member by default.  
function pointer as return type:
```cpp
typedef double (*fp)(int);
fp get_fp();
```
C++ differs from C in requiring a zero request to return a non-null pointer.  
constructor control initialization; operator= control assignment.  
**new** is expensive: allocate memory and initialize memory.  

