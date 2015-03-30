Zajal 0.5 - Nostrand
====================
Nostrand is the next major rewrite of the Zajal creative coding framework. It is built on [Clojure CLR](https://github.com/clojure/clojure-clr), [OpenTK](http://www.opentk.com/), and the ongoing progress of the [Arcadia project](https://github.com/arcadia-unity/arcadia). The goal is to create a highly expressive, completely live creative coding experience suitable for beginners and advanced programmers alike.

This rewrite, the third, is a significant deviation from past prototypes in that it abandons Ruby in favor of Clojure, and abandons the openFrameworks toolkit in favor of the OpenTK. Much like Arcadia, this incarnation of Zajal is experimenting with the effects of functional programming on high performance interactive graphics programming.

Status
------
The code is currently very bare bones and does next to nothing beyond start an Arcadia-style main thread REPL and include the OpenTK assemblies. I am currently experimenting with different abstractions, trying to find the right ones to default to, and the right mechanisms to allow users to define their own.

Using
-----
The only dependency is the [Mono MDK](http://www.mono-project.com/download/)

    git clone https://github.com/nasser/zajal.git
    cd zajal
    git checkout nostrand
    xbuild Zajal/Zajal.csproj
    mono Zajal/bin/Debug/Zajal.exe

The current REPL is lifted directly from Arcadia, so [the same setup instructions](https://github.com/arcadia-unity/arcadia/wiki/Editor-support) apply. Evaluate the contents of the `Examples/brownian.clj` file to see a functional port of the [standard Brownian motion sketch](https://processing.org/examples/brownian.html).

Legal
-----
Zajal is a labor of love by [Ramsey Nasser](http://nas.sr/). Use it for good, not evil.

Provided under the MIT License.

Support
-------
This project has been generously supported by the following institutions. They believed in it, challenged it, and pushed it forward. Zajal would be nowhere without them, and I thank them all deeply.

- [Parsons The New School for Design](http://amt.parsons.edu/), where Zajal was my thesis project towards an MFA in Design and Technology
- [Karaj Beirut](http://www.karajbeirut.org/), where Zajal was the focus of my residency
- [Eyebeam Art and Technology Center](http://eyebeam.org/), where Zajal was part of my fellowship exploring code as self expression