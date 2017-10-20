# Exercise Sheet 1 -- Infrastructure

*due on 20 October 2017*

In this exercise sheet you are asked to setup some infrastructure for developing C++ applications.
The time required for this exercise sheet varies depending on how much experience you have with installing software and setting up build environments.
If you run into problems consult your fellow students first and contact me if the problem persists.
Given you have a GitHub account, you can also open an *issue*.

Apart from doing the PS exercises you are recommended to spend some of your spare time on a C++ project to get more involved with the language.
Additionally, picking up a few books will help getting used to common C++ idioms and the standard library.

## Task 1

Install G++ or Clang and compile the provided file `hello.cc`.
Be sure to install a version that supports C++14.
When compiling specify the following flags:

    -std=c++14 -Wall -Wextra -O2

If you are a Windows user, you may instead want to use the compiler which comes along with Visual Studio.
Adjust the compile flags accordingly.

Next, setup [Boost] on your system and compile the provided file `hello_boost.cc`.
Boost is commonly used and provides you with a set of useful C++ libraries.
Some of its content is even promoted into the C++ standard library.

[Boost]: http://www.boost.org/

## Task 2

Install the Clang compiler and run it on the provided file `vec.cc` using the following command:

    $ clang -std=c++14 -Xclang -ast-dump -fsyntax-only -Wno-vexing-parse vec.cc

Clang will parse the input file and display its abstract syntax tree (AST).
In the bottom half of the output you can find the function declaration of `main` followed by its `CompoundStmt`.
Take a close look at its children and compare the resulting AST with the input code.
Notice any oddities, something that looks counter intuitive?

Sometimes looking at the AST of a C++ program helps one to understand what is really going on behind the scenes.
Clang is a useful tool for this purpose.
G++ also provides some mechanisms to dump internal representations, but I find Clang's AST more accessible.

## Task 3

Setup [Google Test] and write a basic set of unit tests for the provided stack implementation.
Your unit tests should go in a separate file `stack_test.cc`.

[Google Test]: (https://github.com/google/googletest)

Google Test gives you the possibility to compile your unit tests into an executable
To do this, compile both source files and also link with the `gtest_main` library.

Finally, take a look at the provided options by running the executable with `--help` as argument.

## Task 4

The directory `task4` hosts four subfolders, `libFoo`, `libBar`, `libBaz`, and `app`.
The three folders `libFoo`, `libBar`, and `libBaz` each contain a header and source file which should be compiled into a *shared* library.
Furthermore, the library in `libBaz` depends on the library in `libBar`.
`app` contains a single source file providing a `main` function and depends on all libraries.

Use a build system (ex [GNU Make], [Autotools], [CMake], [Ninja], [Meson], [Shake], ...) to build libraries and application.
Be sure to model all dependencies correctly in your setup.
The following criteria *should* be met:

[GNU Make]: https://www.gnu.org/software/make/
[Autotools]: https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html
[CMake]: https://cmake.org/
[Ninja]: https://ninja-build.org/
[Meson]: http://mesonbuild.com/
[Shake]: http://shakebuild.com/

- *Out of source build*, all generated files (`.o`, `.so`, ...) are placed in a separate folder outside the source directory.
- Automatically determine file dependencies.
  If a header file is touched, the build system should know which object files need to be rebuilt.
- Easily enable linking with rPath.
- Utilise multiple processor cores for the build process.
- Easily enable debugging + disable optimisation.

If you have the time, you are encouraged to try out different build systems.
Keep in mind that this example is very, very small and only covers an extremely basic use-case.

## Task 5 (Bonus)

Setup a development environment / text editor which supports the following features:

- syntax highlighting for C/C++
- support for snippets
- jump to line
- jump to symbol
- jump to file
- jump to definition / declaration
- find all references
- compile with one shortcut
- quickly switch between header / source file
- *semantic auto-completion*, provides (among others) auto-completion based on the type it is invoked on

Debugger integration can also be handy, but you instead want to look at GDB user interfaces (ex [voltron]).

[voltron]: https://github.com/snare/voltron

Generally speaking it is not *required* to have such an environment to develop C++ programs.
Yet it helps inexperienced programs to become productive more quickly.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

![Firelink Shrine](../gfx/firelink_shrine.jpg)

> A safe haven for the unkindled lies in reach.
