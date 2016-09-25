(ns user
  (:use zajal.core)
  (:require [zajal.draw :as draw]
            [zajal.shape :as shape]))

(defn jitter [p]
  (v+ p (Vector2. (rand 10)
                  (rand 10))))

(defn wave [p]
  (let [^Vector2 position p
        t (* 0.0000001 (.Ticks DateTime/UtcNow))]
    (v+ position
        (Vector2. (* 50.0 (sin (+ t (* 0.01 (.Y position)))) (cos (* 0.01 (.X position))))
                  (* 50.0 (sin (+ t (* 0.01 (.Y position)))) (sin (* 0.01 (.X position))))))))

(defonce window
  (Zajal.Window. "user"))

(defn lerp [a b f]
  (Vector2/Lerp a b f))

(defn on-draw [^Window w]
  (let [width (.Width w)
        height (.Height w)
        center (Vector2. (/ width 2) (/ height 2))]
    (draw/clear 0 width 0 height)
    (GL/PointSize 5)
    (GL/LineWidth 0.5)
    (GL/Enable EnableCap/Blend)
    (GL/BlendFunc BlendingFactorSrc/SrcAlpha, BlendingFactorDest/OneMinusSrcAlpha)
    
    (GL/Color4 1 1 1 1)
            
    (->> (range01 50)
         (map (shape/circle center 200))
         draw/points
         (map wave)
         draw/lines
         (map #(map (shape/line % (lerp % center 0.5)) (range01 10)))
         flatten
         draw/lines
         (interleave (repeat center))
         (map wave)
         draw/points
         draw/lines
         )
    ))