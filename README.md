Zajal
=====

A blend of [ruby][ruby], [openFrameworks][of] and a clean consistent syntax, 
Zajal is a staggeringly awesome creative coding tool.

How do I use it?
----------------
The easiest way to get started is to head over to [the main site][main] and 
hit the giant download button (Only Mac OS 10.6 or later is supported at the 
moment). This will download the latest build of the interpreter. From there, 
check out the [documentation][docs] and the built in examples in Help>Examples 
to learn how to use the language. The [sketch book][sketch] is also a great resource.

If anything looks a little spotty, that's because Zajal is still brand new and
under active development! Report anything amiss on the [forums][forum].

To get the bleeding edge, try this

    $ git clone http://github.com/nasser/zajal.git
    $ cd zajal
    $ make
    $ ./bin/zajal examples/complete-sketches/ballerina.rb

To build the Cocoa app, open `frontends/cocoa/Zajal.xcodeproj` in XCode 4 and
build that baby out!

How do I contribute?
--------------------
Just using Zajal and providing feedback on the [forums][forums] is plenty. If
you happen to be awesome and want to do more, [bug reports][bugs],
[improved documentation][docs], [better examples][examples], 
[sketch book submissions][sketch] and [code submissions][fork] are all welcome.

![usage](http://zajal.cc/zajal.png)

Legal
-----
Provided under the MIT License. Check [LICENSE][license] for more on that.

[ruby]: http://ruby-lang.org
[of]: http://openframeworks.cc/
[main]: http://zajal.cc/
[docs]: http://docs.zajal.cc/
[sketch]: http://sketch.zajal.cc/
[forum]: http://forum.zajal.cc
[bugs]: https://github.com/nasser/zajal/issues
[examples]: https://github.com/nasser/zajal/tree/master/examples
[fork]: https://github.com/nasser/zajal/fork
[license]: http://github.com/nasser/zajal/blob/master/LICENSE