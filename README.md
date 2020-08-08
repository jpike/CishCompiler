# CishCompiler
A sort-of-compiler for a sort-of-C-ish programming language.  Not yet done and not robust.  And probably never intended to be a real "production quality" compiler.

Basically, this is intended to be a compiler for C or a custom but similar programming language.  It's somewhat being done as a learning experiment but there are some other reasons.  Namely, while I still rate C or C++ as my favorite programming language, they still have a lot of problems.  They're either showing their age (moreso C) or starting to get into the realm of complexity where I have concerns about their future (moreso C++).  I still want the low-level capabilities of these languages, but I want to be able to write better high-level code without being encumbered by a lot of the cruft in these languages.  To do that somewhat requires "metaprogramming" capabilities that effectively come down to being able to parse and manipulate C/C++ code and generate new code.

I say this is a compiler for a "C-ish" language for the following reasons:
* While C is effectively the base language, I'm not going to feel pressured to implement any features of C that I don't really care for.  So it may not actually be able to handle all "valid" C code according to the spec.
* I'm likely to add custom stuff that isn't in the C language.
* I may add some C++ features (or stuff from other languages), but I'm certainly not going to tackle all of C++.

I also say this is "sort-of" a compiler because it technically doesn't fully compile anything yet (only some parsing, and that's even incomplete)...and I'm not sure if/when I'll get to that.  If I do, the target instructions would be x64 or 64-bit ARM.

License is the "unlicense" - I'm putting this code in the public domain.  You can do whatever you want with it - I don't really care one way or the other.
