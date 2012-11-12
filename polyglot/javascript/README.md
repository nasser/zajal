Javascript on Zajal
===================

This is a polyglot Zajal experiment, an attempt to expose Zajal's creative coding and live updating facilities to other languages targeting the Rubinius VM.

Usage
-----
First, install Zajal as a gem (from the root of the zajal folder)
```bash
gem build zajal.gemspec
gem install zajal-0.4.0.gem
```

Next, install [Capuchin](https://github.com/matthewd/capuchin), @matthewd's JavaScript implementation that targets the Rubinius VM.
```bash
cd polyglot/capuchin/
bundle install
```

Finally, run the example!
```bash
./jszj example.js
```

Live coding should work as expected, and all Zajal methods are exposed as global functions to Capuchin.