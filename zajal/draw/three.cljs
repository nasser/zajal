(ns virtual-three)

(deftype RendererNode [props camera scene ^:mutable _cache]
  Object
  (apply-property
    [self property value]
    (.render self)
    (case property
      :viewport
      (.. _cache
          (setViewport (:x value)
                       (:y value)
                       (:width value)
                       (:height value)))
      :size
      (.. _cache
          (setSize (:width value)
                   (:height value)))
      ;; TODO the rest
      nil))
  (render
    [self]
    (when-not _cache
      (set! _cache (new js/THREE.WebGLRenderer
                        (clj->js props)))
      (doseq [prop (keys props)]
        (.apply-property self prop (props prop)))
      (.render camera)
      (.render scene))
    _cache)
  (reconcile
    [self other]
    (when-not (identical? self other)
      (when (not (identical? (type self) (type other)))
        (throw "Different types not supported"))
      (let [other-props (.-props other)]
        (doseq [prop (keys other-props)]
          (.apply-property self prop (other-props prop))))
      ;; TODO removing props
      (.reconcile camera (.-camera other))
      (.reconcile scene (.-scene other))
      ;; propagate the cache
      (set! (.-_cache other) _cache))))

(deftype Object3DNode [ctor props children ^:mutable _cache]
  Object
  (apply-property
    [self property value]
    (.render self)
    (case property
      :rotation
      (.. _cache -rotation (copy value))
      :position
      (.. _cache -position (copy value))
      :scale
      (.. _cache -scale (copy value))
      ;; TODO the rest  
      (aset _cache (.-fqn property) value)))
  (render 
    [self]
    (when-not _cache
      (set! _cache (js/Object.create (.-prototype ctor)))
      (.call ctor _cache)
      (doseq [prop (keys props)]
        (.apply-property self prop (props prop)))
      (when children
        (doseq [child children]
          (.add _cache
                (if (.-uuid child)
                  child
                  (.render child))))))
    _cache)
  (reconcile 
    [self other]
    (when-not (identical? self other)
      (when (not (identical? (type self) (type other)))
        (throw "Different types not supported"))
      ;; TODO removing props
      (when (not (identical? props (.-props other)))
        (let [other-props (.-props other)]
          (doseq [prop (keys other-props)]
            (.apply-property self prop (other-props prop)))))
      ;; children
      (when (and (not (nil? children))
                 (not (nil? (.-children other))))
        (cond
          (seq? children)
          (loop [self-children children
                 other-children (.-children other)]
            (let [self-child (first self-children)
                  other-child (first other-children)
                  self-next (next self-children)
                  other-next (next other-children)]
              (cond (nil? self-child)
                    (.. _cache (add (.render other-child)))
                    (nil? other-child)
                    (.. _cache (remove (.render self-child)))
                    :else
                    (.reconcile self-child other-child))
              (when (or (not (nil? self-next))
                        (not (nil? other-next)))
                (recur self-next other-next))))
          :else
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
                (.. _cache (add (.render (nth other-children i))))
                (when (< i (dec other-children-count))
                  (recur (inc i))))
              (if (> self-children-count
                     other-children-count)
                ;; fewer elements
                (loop [i min-length]
                  (.. _cache (remove (.-_cache (nth self-children i))))
                  (when (< i (dec (count self-children)))
                    (recur (inc i)))))))))
      ;; propagate the cache
      (set! (.-_cache other) _cache))))

(defn renderer [props camera scene]
  (RendererNode. props camera scene nil))

(defn camera [props children]
  (Object3DNode. js/THREE.PerspectiveCamera props children nil))

(defn scene [props children]
  (Object3DNode. js/THREE.Scene props children nil))

(defn mesh [props children]
  (Object3DNode. js/THREE.Mesh props children nil))

(defn line [props children]
  (Object3DNode. js/THREE.Line props children nil))

(defn group [props children]
  (Object3DNode. js/THREE.Group props children nil))

(def box-geo (js/THREE.BoxGeometry. 1 1 1))
(def mesh-mat (js/THREE.MeshBasicMaterial.
                #js {:wireframe true
                     :color "white"}))

(defn v3 [x y z] (js/THREE.Vector3. x y z))
(defn euler [x y z] (js/THREE.Euler. x y z))
 
(defn input [] nil)

(defn sketch [start step draw]
  (let [state (atom start)
        renderer (draw start)
        current (atom renderer)]
    (js/document.body.appendChild (.. renderer render -domElement))
    (letfn [(render-loop
              [t]
              (.requestAnimationFrame js/window render-loop)
              (swap! state step (input))
              (let [next (draw @state)]
                (when (not (identical? @current next))
                  (.reconcile @current next)
                  (reset! current next)
                  (.. @current render (render (.. @current -scene render)
                                              (.. @current -camera render) )))))]
      (render-loop 0)
      (.render renderer)))
  :ok)

(def resources (atom {}))

(.. (new js/THREE.OBJLoader)
    (load "models/watercraftPack_003.obj"
          (fn [obj]
            (doseq [child (.-children obj)]
              (js/console.log child)
              (aset child "material" mesh-mat))
            (swap! resources assoc :boat obj))))

(defn step [x] (inc x))

(defn draw [t]
  (renderer
    {:size {:width 500
            :height 500}}
    (camera {:position (v3 0 5 5)
             :rotation (euler -1 0 0)})
    (scene
      {}
      [(group {:position (v3 (* 0.1 1) (* 0.1 3) (* 0.5 4))
               :rotation (euler (* 0.1 t) 0 (* 0.05 t))
               :scale (v3 1 1 1)}
              #_
              [(mesh {:geometry box-geo
                      :material mesh-mat})]
              (when (@resources :boat)
                [(@resources :boat)]))])))

(sketch 0 #'step #'draw)