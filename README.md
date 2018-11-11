# Polynomial as a data container
Project which I've done on the second semester of studying computer science at Warsaw University of Technology. My first task was to implement a class to store a polynomial and be able to do simple mathematical operations on it. My second task was to extend the first project and make this Polynomial class a data container.

## Parser
To improve UI, I created a parser which could translate a single string to a polynomial. The parser works with all data types which could get a value from stream (with few restrictions).

## Rules of creating a string to represent a polynomial

- single string could contain any number of monomials
- few monomials of the same degree are allowed; they will be summed
- monomials are separated by character '+' (one exception -> read the next point)
- if the next monomial is negative, user should type a single '-' (without '+' before the minus)
- given factor [TEMP] could not contain '+' and '-' characters (they are used for separating monomials)
- spaces are allowed (but not required) to use between monomials but they cannot be used within a monomial



## Correct syntax of the monomial:

	[TEMP]x[INTEGER]    	- degree = INTEGER; factor = TEMP
	[TEMP]x^[INTEGER]   	- degree = INTEGER; factor = TEMP
	[TEMP]x			        - degree = 1; factor = TEMP
	x			            - degree = 1; factor = 1
	-x			            - degree = 1; factor = -1
	[TEMP]			        - a constant; in this case [TEMP] could not contain 'x' character

where:

[TEMP]		- value of the factor next to x; its type depends on the type used when created an object of Polynomial<TEMP_TYPE> class
[INTEGER]	- exponent of the x (values greater or equal 0]

## Example string polynomials for parser
    "x^5 + 3x^4 - 5x^2 + 1"
    "2x3 + 3x3 + 4x5 + x2"
    "12x88 + 15x70 + 10x5 + 2x15 - x70 + 3x"

NOTE: You can use spaces between monomials in the string but don't use them when using build-in UI. This UI bases on std iostream and it loads all text until the first white character appears.

## Copyright
Copyright (C) Robert Dudzinski 2018
