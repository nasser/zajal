Zajal 0.4 - Amsterdam
=====================
Amsterdam is the first major rewrite of Zajal since the start of the project. It uses a brand new, all-Ruby architechture built on Rubinius and aims to be easier to hack, maintain, and expand on. Specifically, Amsterdam is designed to incorporate more easily with RubyGems and ofxAddons.

A lot still needs to be done. All it does is open a window and draw circles. Live coding is absent, too. Amsterdam won't be usable by the general public for a few more months. In the meantime, you should check out the very capable [public release](http://zajal.cc/) if you want to make things in Zajal.

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
Provided under the MIT License
