(ns zajal.brownian
  (:require [zajal.three :as t :refer [renderer euler scene camera v3]]
            [zajal.core :as zajal]
            [gamma.api :as g]
            [gamma.program :as p]))

(defn rrand [a b]
  (- (rand (- a b)) a))


(defn geometry [ps]
  (let [geo (js/THREE.Geometry.)]
    (aset geo "vertices" (-> ps into-array))
    (aset geo "verticesNeedUpdate" true)
    geo))

(defn v3+ [a b]
  (.. a clone (add b)))

(defn apply-angle-axis [v axis angle]
  (.. v clone (applyAxisAngle axis angle)))

(def vertex-position (g/attribute "position" :vec3))

(def vertex-varying (g/varying "pos" :vec3 "highp"))

(def vertex-shader
  {(g/gl-position) (g/vec4 vertex-position 1)
   vertex-varying vertex-position})

(def fragment-shader
  {(g/gl-frag-color) (g/vec4 vertex-varying 1)})

(def rainbow
  (p/program
    {:vertex-shader vertex-shader
     :fragment-shader fragment-shader}))

(def gamma-material
  (js/THREE.RawShaderMaterial.
    #js {:vertexShader (-> rainbow :vertex-shader :glsl)
         :fragmentShader (-> rainbow :fragment-shader :glsl)}))

(defn shaded-line [ps]
  [t/line {:geometry (geometry ps)
           :material gamma-material}])

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

(def step-size 0.1)

(def start
  {:trail [(v3 0 0 0)]})

(defn constrain [trail length]
  (->> trail
       (take-last length)
       vec))

(defn grow
  ([trail] (grow trail (last trail)))
  ([trail p] (conj trail p))
  ([trail p r] (conj trail (v3+ p r))))

(defn grow-random [trail]
  (grow trail (first trail) (rand-point step-size)))

(defn remap [v low1 high1 low2 high2]
  (+ low2
     (/ (* (- v low1)
           (- high2 low2))
        (- high1 low1))))

(defn grow-on-mouse [trail {:keys [mouse]}]
  (if (mouse :pressed?)
    (-> trail (grow (v3 
                      (remap (-> mouse :x) 0 600 -0.5 0.5)
                      (remap (-> mouse :y) 0 600 0.5 -0.5)
                      0)))
    trail))

(defn turn-trail [trail]
  (let [axis (v3 0 1 0)]
    (map #(apply-angle-axis % axis 0.01) trail)))

(defn step [state input]
  (-> state
      (update :trail #(-> %
                          grow-random
                          ; (grow-on-mouse input)
                          turn-trail
                          ))))

(defn draw [{:keys [trail]}]
  [:div 
   ; [:p {} (str (-> hello-triangle :fragment-shader :glsl))]
   [t/basic-scene {:width 600 :height 600}
    ; [line {:color 0xffffff} trail]
    [shaded-line trail]
    ]])

(defonce sketch (zajal/sketch start #'step #'draw))

