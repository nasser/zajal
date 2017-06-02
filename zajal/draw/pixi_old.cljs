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

(defn replace-child [child with]
  (let [parent (.-parent child)
        index (.getChildIndex parent child)]
    (.removeChildAt parent index)
    (.addChildAt parent with index)))

(defn -reconcile [self other]
  (if (not (identical? (type self) (type other)))
    (replace-child _cache (.render other))
    (let [other-props (.-props other)]
      (when (not (identical? props other-props))
        (apply-properties (.-_cache self) other-props))
      ;; propagate the cache
      ; (set! (.-_cache other) (.-_cache self))
      )))

(defn -reconcile-children [self other]
  (let [children (.-children self)]
    (when (not (or (identical? children (.-children other))
                   (= children (.-children other))))
      (cond
        ;; seq-optimized
        (seq? children)
        (loop [self-children children
               other-children (.-children other)]
          (let [self-child (first self-children)
                other-child (first other-children)
                self-next (next self-children)
                other-next (next other-children)]
            (cond (or (identical? self-child other-child)
                      (= self-child other-child))
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
      (identical? self other)
      nil
      ; (and (= props (.-props other))
      ;      (= children (.-children other)))
      ; (set! (.-_cache other) _cache)
      :else
      (let [self-shape (:shape props)
            other-shape (:shape (.-props other))]
        (cond (not= self-shape other-shape)
              (do
                (.update-cached-shape self other-shape)
                (.draw-graphics self (.-props other)))
              (or (not (identical? (:fill props) (:fill (.-props other))))
                  (not (identical? (:alpha props) (:alpha (.-props other))))
                  (not (identical? (:line-color props) (:line-color (.-props other))))
                  (not (identical? (:line-width props) (:line-width (.-props other))))
                  (not (identical? (:alpha props) (:alpha (.-props other)))))
              (.draw-graphics self (.-props other)))
        ; (set! (.-_cache other) _cache)
        ; (-reconcile self other)
        ; (-reconcile-children self other)
        ))))

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


; (def *template-keys*
;   {::renderer ApplicationNode
;    ::container DisplayObjectNode
;    ::sprite SpriteNode
;    ::graphics GraphicsNode
;    ::text TextNode})

; (defn parse-template [tmp]
;   (let [head (first tmp)
;         args (subvec tmp 1)]
;     (cond (keyword? head)
;           (apply head )
;           (fn? head)
;           (ThunkNode. head args)
;           :else
;           tmp)))

(declare native-nodes)
(declare thunk)

(defn parse-template [t]
  (let [ret
        (if (vector? t)
          (let [f (first t)]
            (if-let [native (native-nodes f)]
              (let [maybe-props (second t)]
                (if (map? maybe-props)
                  (native maybe-props (mapv parse-template (subvec t 2)))
                  (native {} (mapv parse-template (subvec t 1)))))
              (thunk f (subvec t 1))))
          t)]
    ; (log "parse-template: " t (pr-str ret))
    ret))

(extend-type js/PIXI.Point
  IEquiv
  (-equiv
    [o other]
    (and (instance? js/PIXI.Point other)
         (identical? (.-x o) (.-x other))
         (identical? (.-y o) (.-y other)))))

;; TODO dont reconcile symbolic trees on mismatch
;; dont rerender everything
(deftype ThunkNode [func args ^:mutable _cache]
  Object
  (render 
    [self]
    (when-not _cache
      (set! _cache (-> (apply func args) parse-template .render))
      (js/console.log "cache is " (.-_cache self)))
    _cache)
  (reconcile 
    [self other]
    (when (or (not (identical? (type self) (type other)))
              (not (identical? func (.-func other)))
              (not= args (.-args other)))
      (log "rerendering!")
      (log "cache parent: " (pr-str (.-parent _cache)))
      (replace-child _cache (.render other)))
    ; (set! (.-_cache other) (.-_cache self))
    ))

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

(defn thunk [f args]
  (ThunkNode. f args))

(def native-nodes
  {:renderer renderer
   :container container
   :sprite sprite
   :graphics graphics
   :text text})


(defn circle [radius]
  {:ctor js/PIXI.Circle
   :args [0 0 radius]})

(defn polygon [ps]
  {:ctor js/PIXI.Polygon
   :args ps})

(defn v2 [x y] (js/PIXI.Point. x y))
(defn v2+ [a b] (js/PIXI.Point. (+ (.-x a) (.-x b))
                                (+ (.-y a) (.-y b))))
 
(defn sketch [start step draw input]
  (let [state (atom start)
        renderer (parse-template (draw start))
        current (atom renderer)
        sketch (js/document.querySelector "#sketch")]
    (js/console.log "OK")
    (js/console.log (pr-str renderer))
    (set! (.-innerHTML sketch) "")
    (.appendChild sketch (.. renderer render -view))
    (js/console.log "NICE")
    (letfn [(render-loop
              [t]
              (.requestAnimationFrame js/window render-loop)
              (swap! state step (input))
              (let [next (parse-template (draw @state))]
                ; (log (pr-str @current) (pr-str next))
                (.reconcile @current next)
                (reset! current next)))]
      (render-loop 0)
      (.render renderer))))