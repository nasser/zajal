(ns zajal.brownian
  (:require [zajal.three :as t :refer [renderer mesh euler scene camera v3]]
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

(def rainbow
  (let [position (g/attribute "position" :vec3)
        projectionMatrix (g/uniform "projectionMatrix" :mat4)
        viewMatrix (g/uniform "viewMatrix" :mat4)
        modelMatrix (g/uniform "modelMatrix" :mat4)
        varying (g/varying "v_position" :vec3 "highp")]
    (p/program
      {:vertex-shader
       {(g/gl-position)
        (reduce g/* [projectionMatrix viewMatrix modelMatrix (g/vec4 position 1)])
        varying position}
       :fragment-shader
       {(g/gl-frag-color) (g/* 16 (g/vec4 varying 1))}})))

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

(def step-size 0.01)

(def start
  {:trail [(v3 0 0 0)]})

(defn constrain [trail length]
  (->> trail
       (take-last length)
       vec))

(defn grow
  [trail p] (conj trail p))

(defn grow-random [trail]
  (grow trail (v3+ (last trail) (rand-point step-size))))

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
                          (grow-on-mouse input)
                          turn-trail
                          ))
      (assoc :angle (-> input :time :elapsed (/ 4000)))))

(defn draw [{:keys [trail angle]}]
  [t/basic-scene {:width 600 :height 600}
   [t/mesh {:geometry (geometry trail)
            :material gamma-material}]
   
   [t/obj3d {:rotation (euler 0 angle 0)}
    [shaded-line trail]
    ]])

(defonce sketch (zajal/sketch start #'step #'draw))

