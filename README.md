# A minimal C library for terminal manipulation
## About
### Why?
Well, I'm working on a VIM like hexadecimal editor for editing RAW files, and I haven't found any good options for creating a terminal-based UI that balances minimalism and simplicity. I just want a way to set characters on a terminal, And that is exactly what __libtermui__ does. No fancy colors by default, no buttons or anything like that.

## Building and Using
## Linux / Unix-like OSes
First of all, clone the source code `git clone https://github.com/ottav1o/libtermui.git` and run `Make`. This will build all the source files and create `SOURCE_DIR/build/libtermui.a`, a static linked library.

#### Header files
To install all the development headers, run `make install` with root privileges. This will create a new directory called `TERMUI` in your `/usr/share/include/` and copy all the `.h` files inside `SOURCE_DIR/source` into it.

#### Linking with your project
Copy and paste `SOURCE_DIR/build/libtermui.a` somewhere in your project and add `-Lpath_to_the_directory_where_is_located_libtermui.a` and `-ltermui` to your compile flags. Good luck!

## Windows / Not Unix-like OSes
### Not officially supported. libtermui uses `unistd.h` and others unix-like libraries to get the things done. If you really want to use libtermui, try WSL or something.

## Docs

---
sorry for my bad english :) it's not my main language :>
