(ns zajal.input.keyboard
  (:require [clojure.string :as string]))

(defn- camels-to-hyphens [s]
  (-> s
      (string/replace #"([A-Za-z])([A-Z][a-z])" "$1-$2")
      (string/replace #"([A-Za-z]{2,})([A-Z0-9])$" "$1-$2")
      string/lower-case))

(defn- kw [s]
  (-> s camels-to-hyphens keyword))

(def pressed-keys (atom {}))

(defn add-listeners! []
  (js/window.document.addEventListener
    "keydown"
    #(swap! pressed-keys assoc (.-code %) %))
  (js/window.document.addEventListener
    "keyup"
    #(swap! pressed-keys dissoc (.-code %))))

(add-listeners!)

(defn key-set []
  (->> @pressed-keys
       keys
       (map kw)
       set))