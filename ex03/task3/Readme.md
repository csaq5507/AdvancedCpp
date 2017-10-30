# Expected behaviour

Either add the elements 0-9 to the vector or loop till infinity. (meaning till stack or allocation overflow)

# Behaviour

As expected infinity loop.
The function xs.end() is called in the outer for loop to check if the iteratior reaches the end
of the container(i.r. xs.end() points at the address after the last element of the container),
but each time the body of the loop is executed the container expandes.

# Preventing such errors

Read the documentation of the function you use.

# Warnings


Clang-5.0 with flags -Wall -Wextra -std=c++17 -O2
	did not print any warnings.

Same goes for g++-7.2