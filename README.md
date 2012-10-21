Zajal 0.4 - Amsterdam
=====================
Amsterdam is the first major rewrite of Zajal since the start of the project. It uses a brand new, all-Ruby architechture built on Rubinius and aims to be easier to hack, maintain, and expand on. Specifically, Amsterdam is designed to incorporate more easily with RubyGems and ofxAddons.

A lot still needs to be done. All it does is open a window and draw basic shapes. Live coding is very basic. Amsterdam won't be usable by the general public for a few more months. In the meantime, you should check out the very capable [public release](http://zajal.cc/) if you want to make things in Zajal.

Using
-----
Install Rubinius in 1.9 mode

    rvm install rbx --1.9
    rvm use rbx

Get Zajal

    git clone https://github.com/nasser/zajal.git
    cd zajal
    git co amsterdam
    ./bin/zajal examples/hello-world.zj

Legal
-----
Zajal is a labor of love by [Ramsey Nasser](http://nas.sr/). Use it for good, not evil.

Provided under the MIT License

Support
-------
This project has been generously supported by the following institutions. They believed in it, challenged it, and pushed it forward beyond my wildest dreams. Zajal would be no where near where it is without them, and I thank them all deeply.

- [Parsons The New School for Design](http://amt.parsons.edu/), where Zajal was my thesis project towards an MFA in Design and Technology
- [Karaj Beirut](http://www.karajbeirut.org/), where Zajal was the focus of my residency
- [Eyebeam Art and Technology Center](http://eyebeam.org/), where Zajal was the primary project of my fellowship exploring code as self expression
