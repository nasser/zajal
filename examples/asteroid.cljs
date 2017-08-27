(ns examples.asteroid
  (:require [zajal.draw.pixi :refer
             [sketch
              v2 v2+
              circle polygon
              renderer container sprite graphics text thunk]]
            [zajal.input.keyboard :as keyboard]))

(defn vmap [f coll]
  (let [length (count coll)]
    (loop [coll* (transient [])
           i 0]
      (if (< i length)
        (recur (conj! coll* (f (nth coll i)))
               (inc i))
        (persistent! coll*)))))

(defn asteroid* [x y]
  {:position (v2 x y)
   :radius (+ 0.5 (rand))
   :speed (rand)
   :variation (inc (js/Math.floor (rand 3)))})

(def init
  {:player
   {:position (v2 0 100)
    :rotation 0
    :inertia 0}
   :asteroids
   (vec
     (for [x (range -5 5)
           y (range -5 5)]
       (asteroid* (+ 300 (* x 100))
                  (+ 300 (* y 100)))))})

(defn horizontal [player input]
  (cond (:arrow-right input)
        (update player :rotation + (* (:inertia player) 0.05))
        (:arrow-left input)
        (update player :rotation - (* (:inertia player) 0.05))
        :else player))

(defn vertical [player input]
  (let [forward (if (:arrow-up input) 1 0)
        rotation (:rotation player)
        inertia (:inertia player)
        movement (v2 (* (+ forward inertia) (js/Math.cos rotation))
                     (* (+ forward inertia) (js/Math.sin rotation)))]
    (update player :position v2+ movement)))

(defn inertia [player input]
  (if (and (:arrow-up input)
           (< (:inertia player)
              3))
    (update player :inertia + 0.1)
    (update player :inertia * 0.9)))

(defn controls [player input]
  (-> player
      (inertia input)
      (horizontal input)
      (vertical input)))

(defn inside? [point circle]
  (let [p1 (:position point)
        p2 (:position circle)
        r (* 80 (:radius circle))
        distance-squared (+ (* (- (.-x p2) (.-x p1))
                               (- (.-x p2) (.-x p1)))
                            (* (- (.-y p2) (.-y p1))
                               (- (.-y p2) (.-y p1))))
        r-sqared (* r r)]
    (< distance-squared r-sqared)))

(defn collision [{:keys [player asteroids] :as state}]
  (let [asteroids* (map #(if (inside? player %)
                           (assoc % :colliding? true)
                           (assoc % :colliding? false))
                        asteroids)]
    (-> state
        (assoc :asteroids asteroids*)
        (update :player assoc :colliding? (some :colliding? asteroids*)))))

(defn spin [objs]
  (map #(update % :rotation + (* 0.1 (:speed %))) objs))

(defn step [state input]
  (-> state
      (update :player controls input)
      collision
      (update :asteroids spin)
      (assoc :input input)))

(defn debug [state]
  (container {}
             [(text {:text (str "asteroids: " (:asteroids state))
                     :fill "white"
                     :y 1
                     :fontSize 8
                     :fontFamily "Menlo"})
              (text {:text (str "input:  " (:input state))
                     :fill "white"
                     :y 10
                     :fontSize 8
                     :fontFamily "Menlo"})]))

(defn draw-ship [position rotation colliding?]
  [:container
   {:position position
    :rotation rotation}
   [:sprite
    {:image "art/Cars/car_blue_5.png"
     ; :cacheAsBitmap true
     :tint (if colliding? 0x00ff00 0xffffff)
     :anchor (v2 0.5 0.5)
     :scale (v2 0.25 0.25)
     :rotation 1.57075}]])

(defn -draw-asteroid [{:keys [position colliding? radius shape rotation] :as asteroid}]
  (container {:position position
              :rotation rotation}
             [(graphics
                {:shape shape
                 :fill (if colliding? 0x00ff00 0xf0ff0f)
                 :alpha 1
                 :line-width 1
                 :line-color 0xffffff})
              (graphics
                {:shape (circle radius)
                 :alpha 0
                 :fill 0xffffff
                 :line-color 0x00ff00
                 :line-width 1})]))

(defn draw-asteroid [{:keys [position variation colliding? radius shape rotation] :as asteroid}]
  (sprite {:position position
           :rotation rotation
           :tint (if colliding? 0xff0000 0xffffff)
           :scale (v2 radius radius)
           :anchor (v2 0.5 0.5)
           :image (str "art/Objects/rock" variation ".png")}))

(defn readout [s]
  (text {:text s
         :fill "white"
         :alpha 1
         :x 10
         :y 10}))


(defn _draw [{:keys [player input] :as state}]
  (renderer
    {:width 800
     :height 800
     :resolution 1}
    [(container {:position (v2 100 100)}
                [(container {} (map draw-asteroid (:asteroids state)))
                 (draw-ship (:position player)
                            (:rotation player)
                            (:colliding? player))
                 (thunk readout (str input))])]))

(defn draw [{:keys [player input] :as state}]
  [:renderer {:width 800
              :height 800
              :resolution 1}
   [:container {:position (v2 100 100)}
    ; [:container {} (map draw-asteroid (:asteroids state))]
    [draw-ship
     (:position player)
     (:rotation player)
     (:colliding? player)]
    ; [readout (str input)]
    ]])

(defonce the-sketch (sketch init #'step #'draw #'keyboard/key-set))

