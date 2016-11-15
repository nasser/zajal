Zajal 0.6 - Atlantic
====================
Atlantic is the next major rewrite of the Zajal creative coding framework. It is built on [ClojureScript](http://clojurescript.org), [Reagent](https://reagent-project.github.io/), [React](https://facebook.github.io/react/), [ThreeJS](https://threejs.org/) and the ongoing progress of the [Arcadia project](https://github.com/arcadia-unity/arcadia). The goal, as always, is to create a highly expressive, completely live creative coding experience suitable for beginners and advanced programmers alike.

This fourth rewrite, continues the exploration of Clojure and Lisp in the service of creative coding, but builds on a web-based stack of functional reactive tools that have become practical in recent years. This incarnation of Zajal, like the previous one and the Arcadia project, experiments with the effects of functional programming on high performance interactive graphics programming. The hope is to provide a real semantic alternative to the imperative painters-algorithm style tools available today.

Status
------
Extremely early, nothing beyond the basic concept has been demonstrated to work. 

```clojure
;; start state of the sketch
(def start {:click-count 0})

;; function to update the state each frame
(defn step [state {:keys [mouse]}]
  (if (:pressed? mouse)
    (update state :click-count inc)
    state))

;; function to draw the state
(defn draw [{:keys [click-count]}]
  (em (text "Clicks ")
      (text (there/prand click-count))))

(defonce test-sketch
  (sketch start #'step #'draw))
```

![](http://i.imgur.com/4XRGXyh.png)


Plan
----
The current prototype (in the `electron` folder) is a [JavaScript Electron](http://electron.atom.io/) project with the [clojurescript-npm](https://github.com/nasser/clojurescript-npm) package built in.

The trajectory of the project is towards a functional approach that uses some kind of "virtual" representation of the HTML DOM and ThreeJS scene graph. [Existing](https://github.com/elm-lang/virtual-dom) [implementations](https://github.com/Matt-Esch/virtual-dom) were evaluated and rejected due to their performance and inflexibility. We're now using a [new virtual DOM implementation](https://github.com/nasser/zajal/blob/atlantic/electron/virtual-three.js) that is actively being researched and developed. Initial results are promising.

Using
-----
[Electron](http://electron.atom.io/) needs to be installed.

    git clone https://github.com/nasser/zajal.git
    cd zajal
    git checkout atlantic
    cd electron
    electron .


Using (Figwheel)
----------------
The old Figwheel prototype still works, but will be phased out of the repo at some point.

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