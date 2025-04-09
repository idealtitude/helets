# helets

The helets programming language

![Helets Logo](./helets_logo-512x512.png)

**helets** (1) is a hebrew word meaning “extract” (חלץ). I've chosen that name after the quote from [Bjarne Stroustrup](https://www.stroustrup.com/ "Bjarne Stroustrup Website") creator of the C++ language:

> **Within C++, there is a much smaller and cleaner language struggling to get out.**
>
> Src: Bjarne Stroustrup (1994) The Design and Evolution of C++. Addison-Wesley, p. 207

That's what **helets** would like to be, ideally, that smaller and cleaner language; but it's giganormous and very difficult goal to reach.
So as a step forward the vision of what I'd want `helets` to be, I'm starting very simple, with the bases for the specifications, etc..
Basically, from C/C++, and some features from others of my favourite languages, like Python (etc.), I try to "extract" that smaller and cleaner language, at least partially.

For now, I've implement simply the very first logical step (I assume it is): variables declaration and assignment, and also basic arithmetic operators (with precedence).

**Note:** if you want to try it, you'll need Flex, Bison, and later LLVM, and clang (or you can use g++ if you prfer, you'll just have to adapt the `Makefile`).

**helets** is a statically and weak typed language; it's indentation sensitive exactly as Python, to make it easy, sympy, and relatively fast to write.
Also a notable feature: in **helets* the colon `:` is the assignment operator.

In summary:

* exactly as in C/C++ the type comes first, then the identifier of the variable, typically on the pattern `^[a-zA-Z][a-zA-Z0-9_]+$`
* single line comments start with two forward slashes
* no need for trailing `;` at the end of the declarations
* very important: in Helets, the assignment operator is the colon character `:`
* also very important: Helets is indentation sensitive language, exactly as in Python; but we'll handle that later, for the moment let's stay focused on the minimal base as I've explained

I have more to say about the design, syntax, and features of the language; for the moment I'm still struggling to define a comprehensive specifications list.

But, right now you can compile and try the **helets** files in the [./examples](examples directory), their extension is `hlt`, they are just simple plain text files.

To give a quick overview of what helets** looks like, here are some examples:

#### Variables, declaration and assignment
```hlt
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
int[] int_array: {10, 20, 30}

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

#### Loops, control structures

```hlt
// if elif else
if x >= 5:
    x: 15
elif x < 5:
    x: 1
else:
    x: 10

// match case
match x:
    x >= 5
        x: 15
    _
        x: 10

// for loop
x: 10
y: 0
for i in 0..x:
    y:+ i // equivalent to y: y + i
```

#### Functions

```hlt
int my_func(int a, int b = 5):
    // Parameters can be accessed by names or by `$n`
    // `$0` is the function, or `this` object; params follow: `$1, $2, ...`
```

#### Classes

```hlt
// Basic class declaration
class MyClass:
    public
    int x
    MyClass(int x): // implicit `this` parameter
        this.x: x

    private
    int get_x():
```

-----------------

**helets** (חלץ) pronounciation in the [IPA](https://en.wikipedia.org/wiki/International_Phonetic_Alphabet "Wikipedia Article"): [χe̞le̞ts] (2)

----

(1) [helets translation](https://translate.google.fr/?sl=iw&tl=en&text=%D7%97%D7%9C%D7%A5&op=translate "On Google Translate")

(2):

+ [χ](https://en.wikipedia.org/wiki/Voiceless_uvular_fricative), IPA Number 142 (Entity `&#967;` Unicode `U+03C7`)
+ [l](https://en.wikipedia.org/wiki/Voiced_dental,_alveolar_and_postalveolar_lateral_approximants), IPA Number 155 (Entity `&#108;` Unicode `U+006C`)
+ [ts](https://en.wikipedia.org/wiki/Voiceless_alveolar_affricate), IPA Number 103 132 (Entity `&#678;` Unicode `U+02A6`)
+ [e̞](https://en.wikipedia.org/wiki/Mid_front_unrounded_vowel), IPA Number 302 430 (Entity `&#101;​&#798;` Unicode `U+0065 U+031E`)
