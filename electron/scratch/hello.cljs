(ns hello
  (:require zajal
            there))

;; dom functions
(defn vdom-node [name]
  (fn [& body]
    (if (map? (first body))
      (zajal/node name (clj->js (first body)) (rest body))
      (zajal/node name nil  body))))

(def p (vdom-node "p"))
(def em (vdom-node "em"))
(def div (vdom-node "div"))
(defn text [& s]
  (zajal/text (apply str s)))

(defn custom-node [name impl]
  (fn [& body]
    (if (map? (first body))
      (zajal/custom name (clj->js (first body)) (rest body))
      (zajal/custom name nil body)))
  )

(def scene (vdom-node "scene"))
(def line (vdom-node "line"))
(def object3d (vdom-node "object3d"))
(def mesh (vdom-node "mesh"))
(def three (vdom-node "three"))

;; sketch
(def start {:click-count 0})

(defn step [state {:keys [mouse]}]
  (if (:pressed? mouse)
    (update state :click-count inc)
    state))

(defn draw [{:keys [click-count]}]
  (div
    (p (text "Here We Go"))
    (zajal/custom
      {}
      (three {:background 0x2C3E50})
      {:diff (fn [a b]
               (when-not (identical? (.-tag a) (.-tag b))
                 {}
                 ))
       :render (fn [vdom]
                 (case (.-tag vdom)
                   "three" (let [gl (js/THREE.WebGLRenderer.)]
                             (.setSize gl js/window.-innerWidth js/window.-innerHeight)
                             ; (.. gl -domElement)
                             )
                   "scene" (js/THREE.Scene.)
                   "line" (js/THREE.Line.)
                   "mesh" (js/THREE.Mesh.)
                   "object3d" (js/THREE.Object3D.)
                   (throw (str "Unknown node type " (.-tag vdom)))
                   ))}
      )))

(defonce test-sketch
  (zajal/sketch start #'step #'draw))
