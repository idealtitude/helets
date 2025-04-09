# helets

The helets programming language

![Helets Logo](./helets_logo-512x512.png)

**helets** (1) is a hebrew word meaning “extract” (חלץ). I did chosse that name after the quote from [Bjarne Stroustrup](https://www.stroustrup.com/ "Bjarne Stroustrup Website") creator of the C++ language:

> **Within C++, there is a much smaller and cleaner language struggling to get out.**
>
> Src: Bjarne Stroustrup (1994) The Design and Evolution of C++. Addison-Wesley, p. 207

That's what **helets** would like to be, ideally, that smaller and cleaner language; but it's a giganormous and very difficult goal to reach.
So as a step forward the vision of what I'd want `helets` to be, I'm starting very simple, with the bases for the specifications, etc..
Basically, from C/C++, and some features from other of my favourite languages, like Python (etc.), I try to "extract" that smaller and cleaner language, at least partially.

For the implementation, I want it to be a compiled language, that's why I plan to use LLVM later on.

For now, I've implemented simply the very first logical step (I assume it is): variables declaration and assignment, and also basic arithmetic operators (with precedence).

**Note:** if you want to try it, you'll need Flex, Bison, and later LLVM, and clang (or you can use g++ if you prefer, you'll just have to adapt the `Makefile`).

**helets** is a statically and weak typed language; it's indentation sensitive exactly as Python, to make it easy, symple, and relatively fast to write.
Also a notable feature: in **helets** the colon `:` is the assignment operator.

In summary:

* exactly as in C/C++ the type comes first, then the identifier of the variable, typically on the pattern `^[a-zA-Z][a-zA-Z0-9_]+$`
* single line comments start with two forward slashes (I have not defined multiline comments for the moment)
* no need for trailing `;` at the end of the declarations
* very important: in Helets, the assignment operator is the colon character `:`
* also very important: Helets is indentation sensitive language, exactly as in Python

I have more to say about the design, syntax, and features of the language; for the moment I'm still struggling to define a comprehensive specifications list.

But, right now you can compile and try the **helets** files in the [examples dolder](https://github.com/idealtitude/helets/tree/main/examples), their extension is `hlts`, they are just simple plain text files.

To give a quick overview of what **helets** looks like, here are some examples:

#### Basic types

```
* `int`       integer numbers
* `float`     decimal numbers
* `bool`      boolean values, true or false
* `str`       strings
* `int[]`     arrays, here an integer array
* `int[str]`  associative array, here with integer keys and string values
```

#### Variables, declaration and assignment
```hlts
// Integer
int my_int: 105

// Float/Double
float my_float: 0.514
double my_double: 115.0011547856

// Boolean
bool my_bool: true

// String
str my_string: "Hello, world!\n"

// Arrays
int[] int_array: {10, 20, 30} // accessed withe subscript operator: int_array[0]
str[int] asso_array: {"item0": 0, "item1": 1, "item2": 2} // access: asso_array["item2"] or asso_array[0] works as well; more sophisticated array types will have `array.key(0) or array.key("item"), and also array.items() for iteration by key, value

// Constants
const int const_int: 50

// Pointers, the `@` operator returns the adress of a variable
int x: 10
int# x_ptr: @x

// Indirection operator, returns the value pointed by the pointer
print(#x_ptr)

// References
float y: 3.14
float& y_ref: y
print(y_ref) // outputs 3.14
```

#### Operators

The logical, comparison, bitwise, etc, are the classical set of operators, common to many languages, with the following notable differences:

```hlts
// equal
=  // comparison operator, by value
== // Comparison by value and by type
=: // Comparison by type only

// not equal
!=  // same, by value
!== // by value and by type
!=: // by type only

:  // assignment operator, as previously explained above
+: // equivalent to ` x: x + y
-: // idem
&: // idem
^: // idem
// etc.
```

#### Loops, control structures

```hlts
// if elif else
if x >= 5:
    x: 15
elif x < 5:
    x: 1
else:
    x: 10

// match case
match x:
    x >= 5:
        x: 15
    x <= 5:
        x: 1
    _
        x: 10 // default case

// for loop
x: 10
y: 0
for i in 0..x:
    y +: i // equivalent to y: y + i
```

#### Functions

Functions are objects! So they have a `this` accessor.

```hlts
int my_func(int a, int b = 5):
    // Parameters can be accessed by names or by `$n`
    // `$0` is the function, or `this` object; params follow: `$1, $2, ...`
    return $0 // return `this`
```

#### Classes

I plan to create an `import` system, to make the declaration and implementation of classes.

```hlts
// ./mylib/my_class.hlts (see next example for import)
import <iostream>
export MyClass

// Basic class declaration and implementation (no separation!)
// use of namespaces, templates, are part of the language (not shown here)
class MyClass:
    public
    // Constructors
    MyClass(): delete
    MyClass(int x, int y):
        this.x: x
        this.y: y
        this.z: x + y

    // Destructor
    ~MyClass(): default

    int x // public attribute

    // public method
    void print_x():
         std::print(f"Value of x: {x}") // Python-like "f string"

    private
    int y
    int z
    int get_x() const:
        return this.x
```

### Basic program

```hlts
import <iostream>
from mylib.my_class import MyClass as MCls

template<typename T>
T add_numbers(const T& x, const T& y):
    return x + y

int main(int argc, char## argv):
    MCls mcls(86)
    mcls.print_x()

    int my_int: add_numbers<int>(100, 200)

    if my_int != mcls.get_x():
        return std::exit_failure

    return std::exit_success
```


Of course in its time it will need a standard libray as shown in the example above. So, the list of TODO's is slowly going to become more and more rich. And speaking of that, if you like the **helets** project, and if you're interested in contributing, just let me known!

-----------------

**helets** (חלץ) pronounciation in the [IPA](https://en.wikipedia.org/wiki/International_Phonetic_Alphabet "Wikipedia Article"): [χe̞le̞ts] (2)

----

(1) [helets translation](https://translate.google.fr/?sl=iw&tl=en&text=%D7%97%D7%9C%D7%A5&op=translate "On Google Translate")

(2):

+ [χ](https://en.wikipedia.org/wiki/Voiceless_uvular_fricative), IPA Number 142 (Entity `&#967;` Unicode `U+03C7`)
+ [l](https://en.wikipedia.org/wiki/Voiced_dental,_alveolar_and_postalveolar_lateral_approximants), IPA Number 155 (Entity `&#108;` Unicode `U+006C`)
+ [ts](https://en.wikipedia.org/wiki/Voiceless_alveolar_affricate), IPA Number 103 132 (Entity `&#678;` Unicode `U+02A6`)
+ [e̞](https://en.wikipedia.org/wiki/Mid_front_unrounded_vowel), IPA Number 302 430 (Entity `&#101;​&#798;` Unicode `U+0065 U+031E`)
