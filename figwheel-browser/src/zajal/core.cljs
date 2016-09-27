(ns zajal.core
  (:require [reagent.core :as reagent]))

(enable-console-print!)

(defn sketch [start update draw]
  (let [state (atom start)]
    (letfn [(render-loop [t]
                         (swap! state update)
                         (.begin js/stats) ;; TODO generalize this hack
                         (reagent/render-component
                          [draw @state]
                          (. js/document (getElementById "app")))
                         (.end js/stats) ;; TODO generalize this hack
                         (.requestAnimationFrame js/window render-loop))]
      (render-loop 0))))