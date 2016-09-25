(ns zajal.core
  (:require-macros [reagent.ratom :refer [reaction]])
  (:require [reagent.core :as reagent :refer [cursor track track!]]
            [zajal.brownian :as brownian]
            [reagent.ratom :refer [make-reaction]]))

(enable-console-print!)

(defonce app-state
  (atom brownian/start))

(defn render-loop [t]
  (.begin js/stats)
  (swap! app-state brownian/update)
  (reagent/render-component
    [brownian/draw @app-state]
    (. js/document (getElementById "app")))
  (.end js/stats)
  (.requestAnimationFrame js/window render-loop))

(defonce animation-frame
  (render-loop 0))