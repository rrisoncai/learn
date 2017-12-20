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
if a class supports conversion, then it is good to define binary operators as nonmember functions. e.g. x + y; compiler look only at nonmember operator+ function and operator+ function that are members of x.  
**private** members are only accessible to the class and its friends.  
**protected** members are accessible to derived class.  
construction of derived object:  
- allocating space for the object  
- call base-class constructor to initialize base-calss members  
- initialize members of derived class directed by constructor initializer.  
- execute body of derived-class constructor  
**Virtual** function: run-time selection, when function is called through reference or pointer  
**Dynamic binding**: function bound at run-time;**Static binding**: function bound at compiling time  
**static member function** don't have this pointer, cannot access nonstatic class member.  