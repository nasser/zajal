(ns zajal.draw.pixi
  (:require [zajal.input.keyboard :as keyboard]))

;; TODO input
;; TODO removing props
;; TODO source maps, errors

(defn log [& s]
  (js/console.log (apply str s)))

(defn apply-properties [obj props]
  (reduce-kv 
    (fn [_ k v]
      (aset obj (.-fqn k) v))
    nil
    props))

(defn -reconcile [self other]
  (if (not (identical? (type self) (type other)))
    (let [_cache (.render self)
          parent (.-parent _cache)
          index (.getChildIndex parent _cache)]
      (.removeChildAt parent index)
      (.addChildAt parent (.render other) index))
    (let [other-props (.-props other)]
      (when (not (identical? props other-props))
        (apply-properties (.-_cache self) other-props))
      ;; propagate the cache
      (set! (.-_cache other) (.-_cache self)))))

(defn -reconcile-children [self other]
  (let [children (.-children self)]
    (when (not (identical? children (.-children other)))
      (cond
        ;; seq-optimized
        (seq? children)
        (loop [self-children children
               other-children (.-children other)]
          (let [self-child (first self-children)
                other-child (first other-children)
                self-next (next self-children)
                other-next (next other-children)]
            (cond (identical? self-child other-child)
                  nil
                  (nil? self-child)
                  (.. (.-_cache self) (addChild (.render other-child)))
                  (nil? other-child)
                  (.. (.-_cache self) (removeChild (.render self-child)))
                  :else
                  (.reconcile self-child other-child))
            (when (or (not (nil? self-next))
                      (not (nil? other-next)))
              (recur self-next other-next))))
        :else
        ;; nth-optimized
        (let [self-children children
              other-children (.-children other)
              self-children-count (count self-children)
              other-children-count (count other-children)
              min-length (js/Math.min self-children-count other-children-count)]
          ;; TODO what is the fastest way to iterate children?
          (loop [i 0]
            (let [self-child (nth self-children i)
                  other-child (nth other-children i)]
              (when (not (identical? self-child other-child))
                (.reconcile (nth self-children i)
                            (nth other-children i))))
            (when (< i (dec min-length))
              (recur (inc i))))
          (if (> other-children-count
                 self-children-count)
            ;; more elements
            (loop [i min-length]
              (.. (.-_cache self) (addChild (.render (nth other-children i))))
              (when (< i (dec other-children-count))
                (recur (inc i))))
            (if (> self-children-count
                   other-children-count)
              ;; fewer elements
              (loop [i min-length]
                (.. (.-_cache self) (removeChild (.-_cache (nth self-children i))))
                (when (< i (dec (count self-children)))
                  (recur (inc i)))))))))))

(deftype ApplicationNode [props children ^:mutable _cache]
  Object
  (render
    [self]
    (when-not _cache
      (set! _cache (new js/PIXI.Application
                        (or (:width props) 800)
                        (or (:height props) 600)
                        (clj->js (merge {}
                                        props))))
      ;; interface normalizing patch
      (aset _cache "removeChild" (fn [c] (.. _cache -stage (removeChild c))))
      (aset _cache "addChild" (fn [c] (.. _cache -stage (addChild c))))
      (doseq [child children]
        (.. _cache -stage (addChild (.render child)))))
    _cache)
  (reconcile
    [self other]
    (when-not (identical? self other)
      (when (not (identical? (type self) (type other)))
        (throw (str "Different types not supported " (type self) " vs " (type other))))
      (when (not (identical? self other))
        (-reconcile self other)
        (-reconcile-children self other)))))

(deftype DisplayObjectNode [ctor props children ^:mutable _cache]
  Object
  (render 
    [self]
    (when-not _cache
      (set! _cache (js/Object.create (.-prototype ctor)))
      (.call ctor _cache)
      (apply-properties _cache props)
      (when (not (nil? children))
        (doseq [child children]
          (.addChild _cache (.render child)))))
    _cache)
  (reconcile 
    [self other]
    (when (not (identical? self other))
      (-reconcile self other)
      (-reconcile-children self other))))

(deftype SpriteNode [props children ^:mutable _cache]
  Object
  (render 
    [self]
    (when-not _cache
      (set! _cache (js/PIXI.Sprite.fromImage (:image props)))
      (apply-properties _cache props)
      (when (not (nil? children))
        (doseq [child children]
          (.addChild _cache (.render child)))))
    _cache)
  (reconcile 
    [self other]
    (when (not (identical? self other))
      (-reconcile self other)
      (-reconcile-children self other))))

(deftype GraphicsNode [props children ^:mutable _cache]
  Object
  (update-cached-shape
    [self shape]
    (let [ctor (:ctor shape)
          args (:args shape)]
      (set! (.-cached-shape _cache) (js/Object.create (.-prototype ctor)))
      (.apply ctor (.-cached-shape _cache) (into-array args))))
  (draw-graphics
    [self props]
    (.clear _cache)
    (when (:fill props)
      (.beginFill _cache
                  (or (:fill props) 0xffffff)
                  (or (:alpha props) 1)))
    (.lineStyle _cache
                (or (:line-width props) 0)
                (or (:line-color props) 0)
                (or (:line-alpha props) 1))
    (.drawShape _cache (.-cached-shape _cache))
    (.endFill _cache))
  (render 
    [self]
    (when-not _cache
      (set! _cache (new js/PIXI.Graphics))
      (apply-properties _cache props)
      (when-let [shape (:shape props)]
        (.update-cached-shape self shape))
      (.draw-graphics self props)
      (.lineStyle _cache 5 0xffffff 1)
      (when (not (nil? children))
        (doseq [child children]
          (.addChild _cache (.render child)))))
    _cache)
  (reconcile 
    [self other]
    (cond
      (not (identical? (type self) (type other)))
      (let [_cache (.render self)
            parent (.-parent _cache)
            index (.getChildIndex parent _cache)]
        (.removeChildAt parent index)
        (.addChildAt parent (.render other) index))
      (not (identical? self other))
      (let [self-fill (:fill props)
            self-alpha (:alpha props)
            self-line-color (:line-color props)
            self-line-width (:line-width props)
            self-line-alpha (:line-alpha props)
            self-shape (:shape props)
            other-fill (:fill (.-props other))
            other-alpha (:alpha (.-props other))
            other-line-color (:line-color (.-props other))
            other-line-width (:line-width (.-props other))
            other-line-alpha (:line-alpha (.-props other))
            other-shape (:shape (.-props other))]
        (cond (not= self-shape other-shape)
              (do
                (.update-cached-shape self other-shape)
                (.draw-graphics self (.-props other)))
              (or (not (identical? self-fill other-fill))
                  (not (identical? self-alpha other-alpha))
                  (not (identical? self-line-color other-line-color))
                  (not (identical? self-line-width other-line-width))
                  (not (identical? self-alpha other-alpha)))
              (.draw-graphics self (.-props other)))
        (-reconcile self other)
        (-reconcile-children self other)))))

(deftype TextNode [props children ^:mutable _cache]
  Object
  (render 
    [self]
    (when-not _cache
      (set! _cache (js/PIXI.Text.))
      (apply-properties _cache props)
      (apply-properties (.-style _cache) props)
      (when (not (nil? children))
        (doseq [child children]
          (.addChild _cache (.render child)))))
    _cache)
  (reconcile 
    [self other]
    (when (not (identical? self other))
      (-reconcile self other)
      (apply-properties (.-style _cache) props)
      (-reconcile-children self other))))

;;; api

(defn renderer [props children]
  (ApplicationNode. props children nil))

(defn container [props children]
  (DisplayObjectNode. js/PIXI.Container props children nil))

(defn sprite [props children]
  (SpriteNode. props children nil))

(defn graphics [props children]
  (GraphicsNode. props children nil))

(defn text [props children]
  (TextNode. props children nil))




(defn circle [radius]
  {:ctor js/PIXI.Circle
   :args [0 0 radius]})

(defn polygon [ps]
  {:ctor js/PIXI.Polygon
   :args ps})

(defn v2 [x y] (js/PIXI.Point. x y))
(defn v2+ [a b] (js/PIXI.Point. (+ (.-x a) (.-x b))
                                (+ (.-y a) (.-y b))))
 
(defn input [] nil)

(defn sketch [start step draw input]
  (let [state (atom start)
        renderer (draw start)
        current (atom renderer)
        sketch (js/document.querySelector "#sketch")]
    (set! (.-innerHTML sketch) "")
    (.appendChild sketch (.. renderer render -view))
    (letfn [(render-loop
              [t]
              (.requestAnimationFrame js/window render-loop)
              (swap! state step (input))
              (let [next (draw @state)]
                (when (not (identical? @current next))
                  (.reconcile @current next)
                  (reset! current next))))]
      (render-loop 0)
      (.render renderer))))

(def init
  {:player
   {:position (v2 0 100)
    :rotation 0
    :inertia 0}
   :asteroids
   (mapv
     (fn [x]
       {:position (v2 (* x 100) 0)
        :radius (* (+ 1 (js/Math.abs (* 2 (js/Math.sin x)))) 20)})
     (range -2 2 0.1))})

(defn horizontal [player input]
  (cond (:arrow-right input)
        (update player :rotation + 0.05)
        (:arrow-left input)
        (update player :rotation - 0.05)
        :else player))

(defn vertical [player input]
  (let [forward (if (:arrow-up input) 1 0)
        rotation (-> player :rotation)
        inertia (:inertia player)
        movement (v2 (* (+ forward inertia) (js/Math.cos rotation))
                     (* (+ forward inertia) (js/Math.sin rotation)))]
    (update player :position v2+ movement)))

(defn inertia [player input]
  (if (and (or (:arrow-up input))
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
        r (:radius circle)
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

(defn grow [asteroids]
  (map #(if (:colliding? %)
          (update % :radius + 0.1)
          %)
       asteroids))

(defn step [state input]
  (-> state
      (update :player controls input)
      collision
      ; (update :asteroids grow)
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

(defn draw-ship [position rotation]
  (container
    {:position position
     :rotation rotation}
    [(graphics
       {:shape (polygon [0 -15 -10 10 0 5 10 10 0 -15])
        :rotation 1.5707963268
        :fill (if colliding? 0xff0000 0)
        :line-width 1
        :line-color 0xffffff})]))

; (def color (js/require "color"))

(defn draw-asteroid [{:keys [position colliding? radius rotation] :as asteroid}]
  (graphics
    {:shape (circle radius)
     :fill (if colliding? 0xff0000 0)
     :alpha 1
     :rotation (or rotation 0)
     :position position
     :line-width 1
     :line-color 0xffffff
     }))


(defn draw [{:keys [player input] :as state}]
  (renderer
    {:width 400
     :height 400
     :resolution 2}
    [(container
       {:x 200
        :y 200}
       [(container
          {}
          (map draw-asteroid (:asteroids state)))
        (draw-ship (:position player)
                   (:rotation player))
        ])
     (debug state)]))

(sketch init #'step #'draw #'keyboard/key-set)