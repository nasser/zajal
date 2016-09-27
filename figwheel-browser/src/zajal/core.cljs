(ns zajal.core
  (:require [reagent.core :as reagent]))

(enable-console-print!)

(defn sketch [start update draw]
  (let [state (reagent/atom start)]
    (letfn [(component [] [draw @state])
            (render-loop [t]
                         (.begin js/stats)
                         (swap! state update)
                         (.end js/stats)
                         (.requestAnimationFrame js/window render-loop))]
      (reagent/render-component
        [component]
        (. js/document (getElementById "app")))
      (render-loop 0))))