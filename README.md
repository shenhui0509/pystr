# PyStr is a C++ str class that Support the methods in Python

## Methods of PyStr that original string from C++ standard lib does not hold
1. PyStr.capitialize()
    return the copy of the string with its first letters captialized

2. PyStr.casefold()

3. PyStr.center(width, fillchar = ' ')

4. PyStr.count(substr, start = begin(self), end = end(self))

    - Iterator based range : start = self.begin(), end = self.end()
    - Position based range : start = start_position : size_t, end = end_position : size_t

