(ns examples.other
  (:require [zajal.draw.pixi :refer
             [sketch v2 v2+]]
            [zajal.alt.draw.pixi :as p]
            [zajal.input.keyboard :as keyboard]))

(def init {:count 0})

(defn step [state input]
  (if (empty? input)
    (update state :count inc)
    (update state :count + 3)))

(defn draw [state]
  (p/renderer
    #js {:width 400
         :alpha true
         :height 400}
    #js [(p/container
           nil
           (loop [texts #js []
                  i 400
                  j 10]
             (.push texts (p/text #js {:text "Hello"
                                       :fill "white"
                                       :fontSize 18
                                       :rotation (* 0.01 (:count state))
                                       :x i
                                       :y j}))
             (cond
               (zero? i) (recur texts 400 (dec j))
               (zero? j) texts
               :else (recur texts (dec i) j))))]))

(defonce the-sketch (sketch init #'step #'draw #'keyboard/key-set))