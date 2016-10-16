(ns zajal.three
  (:require [reagent.core :as reagent]))

(def renderer (reagent/adapt-react-class js/ReactTHREE.Renderer))
(def camera (reagent/adapt-react-class js/ReactTHREE.PerspectiveCamera))
(def scene (reagent/adapt-react-class js/ReactTHREE.Scene))
(def obj3d (reagent/adapt-react-class js/ReactTHREE.Object3D))
(def mesh (reagent/adapt-react-class js/ReactTHREE.Mesh))
(def line (reagent/adapt-react-class js/ReactTHREE.Line))

(defn v3 [x y z] (js/THREE.Vector3. x y z))
(defn euler [x y z] (js/THREE.Euler. x y z))
(defn line-material [color]
  (js/THREE.LineBasicMaterial. #js {:color color}))

(defn basic-scene [{:keys [width height]} & children]
  [renderer {:width width :height height :antialias false}
   (into
     [scene {:camera "cam" :width width :height height}
      [camera {:name "cam"
               :position (v3 0 0 2)
               :lookat (v3 0 0 0)}]]
     children)])