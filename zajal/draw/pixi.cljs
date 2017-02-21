(ns zajal.draw.pixi)

;; TODO organize
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
        (throw "Different types not supported"))
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
 
(defn input [] nil)

(defn sketch [start step draw]
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

(defn step [x] (inc x))

(defn draw [t]
  (renderer
    {:width 400
     :height 400}
    [(graphics
       {:shape (circle 20)
        :line-width 4 
        :line-color 0xffffff
        :x 100
        :y 100})
     (graphics
       {:shape (polygon [0 -15 -10 10 0 5 10 10 0 -15])
        :fill 0
        :line-width 1
        :line-color 0xffffff
        :x 100
        :y 75
        :rotation (* 0.05 t)
        })
     (text {:text "Hello?"
            :fill "white"
            :resolution 8})
     (graphics
       {:shape (polygon [0 -15 -10 10 0 5 10 10 0 -15])
        :fill 0
        :line-width 1
        :line-color 0xffffff
        :x 100
        :y 125
        :rotation (* 0.05 t)
        })
     ]))

(sketch 0 #'step #'draw)