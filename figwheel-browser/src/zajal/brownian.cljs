(ns zajal.brownian
  (:refer-clojure :exclude [update])
  (:require [zajal.three :as t :refer [renderer scene camera v3]]
            [zajal.core :as zajal]))

(defn rrand [a b]
  (- (rand (- a b)) a))


(defn geometry [ps]
  (let [geo (js/THREE.Geometry.)]
    (aset geo "vertices" (-> ps into-array))
    (aset geo "verticesNeedUpdate" true)
    geo))

(defn v3+ [a b]
  (.. a clone (add b)))

(defn line [{:keys [color]
             :or {color 0xffffff}}
            ps]
  [t/line {:geometry (geometry ps)
           :material (t/line-material color)}])


(defn rand-point [v]
  (.. (v3 (rrand -0.5 0.5)
          (rrand -0.5 0.5)
          (rrand -0.5 0.5))
      (multiplyScalar v)))

;; not bad!

(def step-size 0.02)

(def start
  [(v3 0 0 0)])

(defn update [trail]
  (let [last-point (last trail)]
    (conj trail (v3+ last-point (rand-point step-size)))))

(defn draw [trail]
  [t/basic-scene {:width 600 :height 600}
   [line {:color 0xffffff} trail]])

(defonce sketch (zajal/sketch start update draw))