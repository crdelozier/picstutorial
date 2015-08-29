Compilation
-----------

* C and C++ programs are compiled.  This means that once an executable has 
been created, it will run as native machine code.  Other languages, like python,
are interpreted.  Interpreted languages are not executed as native machine code
but rather rely on an interpreter to execute the code, either from an intermediate
form or from the source code.

* Compilation broadly requires a front-end and a back-end.  The front-end parses
the code and analyzes the syntax to determine if the code matches the language
specification and prepare for code generation.  The back-end generates an intermediate
representation, optimizes the code, and finally generates assembly code.

* A pre-processor runs before the compiler to replace macros in the code
and include required files.  The "#include" directive is an example of a 
preprocessor directive.  This indicates that the preprocessor should include 
some file.  Other preprocessor directives include "#define" and "#ifdef".

* The C++ compiler checks the syntax of the program to ensure that all of the
expressions (code statements) used in the program are legal with regard to 
the C++ syntax specification.  

Separate Compilation
-----------

* So far, we've compiled programs on the Unix command-line as follows, e.g.,
  with test.cpp)

```
$ g++ test.cpp -o test
```

* This command compiles the `test.cpp` file and creates a program called `test`.
  We can think of the current pipeline as follows:

```
**********  g++   ********
* test.c * -----> * test *
**********        ********
  C++ src         Program
```

* However, g++ is doing more behind the scenes which we can reveal with the `-c`
  flag.

```
$ g++ test.cpp -c
```

* By specifying the `-c` flag, we tell gcc to compile each source file to an
  *object file* rather than a final program.  An object file contains compiled
  code (i.e., machine code) coupled with *holes* that we will explain shortly.

* From here, we can compile all the object files (here just `test.o`) into the
  final executable by invoking `gcc` again.

```
$ g++ test.o -o test
```
* Now the compilation pipeline looks like this:

```
************  g++ -c   **********   g++   ********
* test.cpp * --------> * test.o * ------> * test *
************           **********         ********
  C src               Obj. file         Program
        (Compilation)          (Linking)
```

* We'll call the process of going from a C++ source file to its corresponding
  object file *compilation*.  The final step of taking object files into a final
  program is called *linking*.  During linking, we analyzes the holes in the
  object files and patch them with code from object files.

* In the in class example, we'll use separate compilation with a Makefile 
  to compile the files for our C++ class and driver program.

gdb
-----------

* gdb is a debugger for C and C++ programs that can be used on most UNIX based
operating systems.

* For the following examples, we will be using this simple code found in debugging.cpp.

``` c
int f(int x){
  int y = 5;
  return x + y;
}

int main(){
  int x = 1;
  int y = 2;
  int z = 3;

  z = z + x;
  y = 2 * z;
  x = y + 1;

  return 0;
}
```

* To compile a program for use with gdb, the "-g" flag must be added to the 
compilation commands.  This flag instructs the compiler to add user-readable
symbols to the executable for function and variable names.

```
g++ -o debugging debugging.cpp -g
```

* Once the program has been compiled with the "-g" flag, it can be run 
using gdb.

```
gdb ./test
```

* Once the gdb prompt has loaded, the program can be started using the "run"
command.  The command-line output when gdb starts will look something like this.

```
GNU gdb (GDB; openSUSE 13.1) 7.6.50.20130731-cvs
Copyright (C) 2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-suse-linux".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://bugs.opensuse.org/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
..
Reading symbols from /mnt/eclipse/acg/users/delozier/git/cis190/CIS190/lecture2/debugging...done.
(gdb) run
```

* Simply running the program using a debugger is often not very useful.  Instead, 
we would like to be able to stop the program's execution at certain points 
to examine the program's state (the values of its variables).  We can do this by 
setting "breakpoints" for the debugger to use.  At each breakpoint, gdb will 
halt the execution of the program and return control to the user.

```
(gdb) break main
Breakpoint 1 at 0x4005e4: file debugging.cpp, line 2.
(gdb) break debugging.cpp:4
Breakpoint 2 at 0x4005f2: file debugging.cpp, line 4.
```

* First, we set a breakpoint at the start of the main function.  Next, we set a breakpoint
at line 4 in debugging.cpp.  gdb allows us to set breakpoints at specific line numbers or
at specific functions.  When we run the program, gdb will halt its execution at lines 2 and 
4.

* Once we've encountered a breakpoint in the program, we might want to know what the 
current state of the program is.  We can use the where (or backtrace), list, and 
print commands to print the current state of the program.

```
Breakpoint 1, main () at debugging.cpp:2
2         int x = 1;
(gdb) where
#0  main () at debugging.cpp:2
(gdb) list
1       int main(){
2         int x = 1;
3         int y = 2;
4         int z = 3;
5
6         z = z + x;
7         y = 2 * z;
8         x = y + 1;
9
10        return 0;
(gdb) print x
$1 = 0
```

* We can also advance the program's execution using the next, step, and continue 
commands.  "next" moves to the next line of code and avoids tracing into any function 
calls that are made.  On the other hand, "step" moves to the next line of code and will 
enter any functions that are called.  Finally, "continue" starts execution from the 
current line of code and continues until the next breakpoint or the end of the program.

```
Breakpoint 1, main () at debugging.cpp:7
7         int x = 1;
(gdb) next
8         int y = 2;
(gdb) next
9         int z = 3;
(gdb) next
11        z = z + x;
(gdb) next
12        y = 2 * z;
(gdb) next
13        x = y + 1;
(gdb) next
15        z = f(x);
(gdb) step
f (x=9) at debugging.cpp:2
2         int y = 5;
(gdb) continue
Continuing.
[Inferior 1 (process 32491) exited normally]
```

* The "quit" command exits the debugger and returns the user to the UNIX
command line.

