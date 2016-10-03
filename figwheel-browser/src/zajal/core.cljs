(ns zajal.core
  (:require [reagent.core :as reagent]))

(enable-console-print!)

(defonce start-time (js/Date.now))

(defonce mouse-state (atom {:x 0 :y 0 :pressed false}))

(set! js/document.onmousemove
      #(swap! mouse-state
             assoc
             :x (.-pageX %)
             :y (.-pageY %)))

(set! js/document.onmousedown
      #(swap! mouse-state
              assoc :pressed? true))

(set! js/document.onmouseup
      #(swap! mouse-state
              assoc :pressed? false))

(defn input []
  (let [t (js/Date.now)]
    {:time {:elapsed (- t start-time)}
     :mouse @mouse-state }))

(defn sketch [start step draw]
  (step {} (input))
  (let [state (reagent/atom start)]
    (letfn [(component [] [draw @state])
            (render-loop [t]
                         (.begin js/stats)
                         (swap! state step (input))
                         (.end js/stats)
                         (.requestAnimationFrame js/window render-loop))]
      (reagent/render-component
        [component]
        (. js/document (getElementById "app")))
      (render-loop 0))))