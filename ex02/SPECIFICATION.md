# Version Control System Specification

## Intro

You should already be familiar with tools like Git, Mercurial, Subversion, Bazaar and so on.
If not, go ahead and do some research before continuing.
Your VCS should be able to track changes across files, line by line.
Supporting binary file formats is optional, for now we will stick to simple text files.

## Setup

It is up to you how you are going to store the data required for this system.
Typically, data is stored in a hidden subdirectory inside the version controlled folder.
Your *init* command should therefore do the initialisation.

## Commit

A commit typically consist, among others, of a message, author information, a date, and some changes.
Furthermore a commit usually features one (or multiple in-case of a merge) *parent* (prior commit).

Creating a new commit with your implementation should take *all* changes (with respect to the previous commit) into account.
You do not need to implement a selection mechanism (ie which changes go into a commit) like Git's staging.
Simply take all of them.

Let us do a quick example.
`vcs` is here assumed to be the executable containing your implementation.

    $ mkdir MyAwesomeProject
    $ cd MyAwesomeProject
    $ vcs init                      # setup this folder for version control
    $ vim README                    # create a new file with some content
    $ vim main.c                    # create another file
    $ vcs commit -m "First Commit"  # create your first commit with a nice message

Now you should have your first commit.
Continue working.

    $ vim main.c                    # doing some changes to this awesome program
    $ vcs commit -m "Add coin operated self destruct feature"

The second commit should now only contain the changes done to `main.c`.

## Viewing a Commit

Viewing should be one of the first things to implement as it makes debugging your application easier.
Each commit should have a unique identifier which can be used as a handle.
Let us assume the first commit is identified by the string `r0` and the second by `r1`.
Your *show* command could output something like this.

    $ vcs show r1
    Add coin operated self destruct feature

    By:      Sheldon J. Plankton
    Date:    Tue 15 Aug 12:38:52 CEST 2017
    Parents: r0

    === Changes Follow ===

    --- a/main.c
    +++ b/main.c
    @@ -1,7 +1,18 @@
     #include <stdio.h>
     #include <stdlib.h>

    +#include <ship_systems/propulsion/shaw_fujikawa.h>
    +
    +#include <utils/coin_operator.h>
    +
     int main(void) {
         puts("Hello World");
    +
    +    if (coin_operator_triggered()) {
    +        puts("Have a nice day (> . =)");
    +        prop_engine_t *t = prop_ftl_get_shaw_fujikawa();
    +        prop_detonate(t);
    +    }
    +
         return EXIT_SUCCESS;
     }

## Checking out past Commits

Your VCS should provide a way to go back to a different commit simply by specifying its id.

    $ vcs checkout r0
    $ cat main.c
    #include <stdio.h>
    #include <stdlib.h>

    int main(void) {
        puts("Hello World");
        return EXIT_SUCCESS;
    }

For simplicity you can drop all un-commited changes upon doing a checkout.

## Create a Branch

If one would now change `main.c` and create a new commit another branch has been created.

    $ vim main.c
    $ vcs commit -m "Add chocolate egg dispenser"  # this would be r2

## Merging

Now that you have two different branches in your repository you should also provide a way to merge them.
You are not required to do any sort of auto-merging if a file has been changed in both branches.
Simply provide a way for the user to merge the file in conflict by hand.

Typical VCS open a tool (like `vimdiff`) which shows three different versions of the file side by side.

    +---------------------------------------------------+
    |               |                    |              |
    |               |                    |              |
    |   main.c      |    main.c          |   main.c     |
    |               |                    |              |
    |     r1        |    merge result    |     r2       |
    |<              |<                   |<             |
    |>              |>                   |<             |
    |>              |>                   |>             |
    |<              |>                   |>             |
    |               |                    |              |
    +---------------------------------------------------+

Upon exiting the tool, the *merge result* is used.
A merge is done by issuing:

    $ vcs merge r1   # while r2 has been checked out, result has id r3

## Graph

Similar to viewing a single commit, a command should be provided to view the relationship between commits as a graph.
For the running example the graph could look like this.

    $ vcs graph

      o   r3 "Merge r1 with r2"
     /|
    | o   r2 "Add chocolate egg dispenser"
    | |
    o |   r1 "Add coin operated self destruct feature"
    |/
    o     r0 "First Commit"

## Note

This specification is just a rough outline of what your system should look like.
View it as guidelines, nothing is set in stone, use your brain.
If you encounter a problem where the specification is ambiguous or unclear, make a justifiable decision on what to do.
