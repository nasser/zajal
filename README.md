Zajal 0.6 - Atlantic
====================
Atlantic is the next major rewrite of the Zajal creative coding framework. It is built on [ClojureScript](http://clojurescript.org), [Pixi.js](http://www.pixijs.com/), [ThreeJS](https://threejs.org/) and the ongoing progress of the [Arcadia project](https://github.com/arcadia-unity/arcadia). The goal, as always, is to create a highly expressive, completely live creative coding experience suitable for beginners and advanced programmers alike.

This fourth rewrite, continues the exploration of Clojure and Lisp in the service of creative coding, but builds on a web-based stack of functional reactive tools that have become practical in recent years. This incarnation of Zajal, like the previous one and the Arcadia project, experiments with the effects of functional programming on high performance interactive graphics programming. The hope is to provide a real semantic alternative to the imperative painters-algorithm style tools available today.

Status
------
Extremely early, nothing beyond the basic concept has been demonstrated to work. 

```clojure
(defn step [x] (inc x))

(defn draw [t]
  (renderer
    {:width 400
     :height 400}
    [(graphics {:shape (circle 20)
                :line-width 4 
                :line-color 0xffffff
                :x 100
                :y 100})
     (graphics {:shape (polygon [0 -15 -10 10 0 5 10 10 0 -15])
                :fill 0
                :line-width 1
                :line-color 0xffffff
                :x 100
                :y 75
                :rotation (* 0.05 t)})
     (text {:text "Zajal!"
            :fill "white"
            :x 50})
     (graphics {:shape (polygon [0 -15 -10 10 0 5 10 10 0 -15])
                :fill 0
                :line-width 1
                :line-color 0xffffff
                :x 100
                :y 125
                :rotation (* 0.05 t)
                })]))

(sketch 0 #'step #'draw)
```

![](https://i.imgur.com/OfVhDOH.png)


Plan
----
The trajectory of the project is towards a functional approach to creative coding that uses a "virtual scene graph" representation akin to [React's](https://facebook.github.io/react/). The current implementation is faster than any other similar technology for our purposes and can target the HTML DOM, ThreeJS scene graph, Pixi,js scene graph, or any other mutable tree-like data structure. The current prototype a minimal [JavaScript Electron](http://electron.atom.io/) application that loads ClojureScript and sets up a socket REPL and filewatcher.

Using
-----
[Electron](http://electron.atom.io/) needs to be installed.

    git clone https://github.com/nasser/zajal.git
    cd zajal
    git checkout atlantic
    npm install
    electron . zajal/draw/pixi.cljs

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