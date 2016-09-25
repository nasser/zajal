Zajal 0.6 - Atlantic
====================
Atlantic is the next major rewrite of the Zajal creative coding framework. It is built on [ClojureScript](http://clojurescript.org), [Reagent](https://reagent-project.github.io/), [React](https://facebook.github.io/react/), [ThreeJS](https://threejs.org/) and the ongoing progress of the [Arcadia project](https://github.com/arcadia-unity/arcadia). The goal, as always, is to create a highly expressive, completely live creative coding experience suitable for beginners and advanced programmers alike.

This fourth rewrite, continues the exploration of Clojure and Lisp in the service of creative coding, but builds on a web-based stack of functional reactive tools that have become practical in recent years. This incarnation of Zajal, like the previous one and the Arcadia project, experiments with the effects of functional programming on high performance interactive graphics programming. The hope is to provide a real semantic alternative to the imperative painters-algorithm style tools available today.

Status
------
Extremely early, nothing beyond the basic concept has been demonstrated to work. 

```clojure
(def step-size 0.02)

;; start state of the sketch
(def start
  [(v3 0 0 0)])

;; function to update the state each frame
(defn update [trail]
  (let [last-point (last trail)]
    (conj trail (v3+ last-point (rand-point step-size)))))

;; function to draw the state
(defn draw [trail]
  [t/basic-scene {:width 800 :height 800}
   [line {:color 0xffffff} trail]])
```

![](https://pbs.twimg.com/media/CtJxSi2XgAAu8om.jpg:small)


Plan
----
The current prototype (in the `figwheel-browser` folder) is a traditional ClojureScript Figwheel project targeting the browser. Basic concepts and core libraries will be tested here.

The next prototype will be a [cljs-electron](https://github.com/Gonzih/cljs-electron) project, testing multiple windows and interaction with the operating system.

The final prototype will be a standard [JavaScript Electron](http://electron.atom.io/) project with the [clojurescript-npm](https://github.com/nasser/clojurescript-npm) package built in. This will test package management and distribution.

Using
-----
[Leiningen](http://leiningen.org/) needs to be installed.

    git clone https://github.com/nasser/zajal.git
    cd zajal
    git checkout atlantic
    cd figwheel-browser
    lein figwheel

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