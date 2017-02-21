(require '[zajal.three :as t])
(require '[zajal.core :as z])

(defn step [x]
  (update x :angle #(+ 0.01 %)))

(def box-geo (js/THREE.BoxGeometry. 0.1 0.1 0.1))
(def mesh-mat (js/THREE.MeshBasicMaterial.
                #js {:wireframe true
                     :color "white"}))

(defn box [x y z r]
  (t/mesh
         #js {:position (js/THREE.Vector3. x y z)
              :rotation (js/THREE.Euler. 0 r 0)
              :geometry box-geo
              :material mesh-mat}))


(defn draw [{:keys [angle]}]
  (t/rednerer
    {}
    (t/perspectiveCamera
      #js {:position (js/THREE.Vector3. 0 0 3)})
    (t/scene
      {}
      (into-array
        (for [x (range -8 8)
              y (range -8 8)]
          (box (/ x 8) (/ y 8) 0 (* x angle)))))))

(z/sketch {} #'step #'draw)