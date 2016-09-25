(ns user)

(import Vector2)

(def range01
  (memoize ;; is this a bad idea?
    (fn
      ([] (range01 10))
      ([res]
       (let [step (/ 1.0 res)]
         (loop [i 0.0
                v (transient [])]
           (let [nxt (+ i step)] 
             (if (> nxt 1)
               (persistent! (conj! v 1))
               (recur nxt
                      (conj! v nxt))))))))))

(defn v+ [a b] (Vector2/op_Addition a b))
(defn v- [a b] (Vector2/op_Subtraction a b))
(defn v* [a b] (Vector2/op_Multiply a b))
(defn sin [x] (Math/Sin x))
(defn cos [x] (Math/Cos x))
(defn pow [x p] (Math/Pow x p))

(defn line
  ([a b] (fn [t]
           {:position
            (Vector2/op_Addition
              (Vector2/op_Multiply a (- 1 t))
              (Vector2/op_Multiply b t))}))
  ([t a b] ((line a b) t)))

(def circle
  (memoize
    (fn [c ^double r]
      (fn [t] (let [t (* t 2 Math/PI)]
                {:position
                 (v+ c (v* r (Vector2. (Math/Cos t)
                                       (Math/Sin t))))})))))

(defn bezier
  ([a b c] (fn [t]
             (let [-t (- 1 t)]
               {:position
                (v+ (v* a (pow -t 2))
                    (v+ (v* b (* t (* 2 -t)))
                        (v* c (pow t 2))))}))))

(defn clear
  "Clears the OpenGL buffer. Call this at the top of the draw function
  to clear the window."
  ([left right top bottom]
   (GL/Clear (enum-or ClearBufferMask/ColorBufferBit
                      ClearBufferMask/DepthBufferBit))
   (GL/MatrixMode MatrixMode/Projection)
   (GL/LoadIdentity)
   (GL/Enable EnableCap/Blend)
   (GL/Ortho left right top bottom 0 4))
  ([] (clear -50 50 -50 50)))

(defn points
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/Points)
  (doseq [{:keys [^Vector2 position
                  color]} ps]
    (let [^Color c (or color Color/White)]
      (GL/Color4 c))
    (GL/Vertex2 position))
  (GL/End)
  ps)

(defn lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/LineStrip)
  (doseq [{:keys [^Vector2 position
                  color]} ps]
    (let [^Color c (or color Color/White)]
      (GL/Color4 c))
    (GL/Vertex2 position))
  (GL/End)
  ps)

(defn disconnected-lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/Lines)
  (doseq [{:keys [^Vector2 position]} ps] (GL/Vertex2 position))
  (GL/End)
  ps)

(defn fan
  "Draws triangle fan"
  [ps]
  (GL/Begin PrimitiveType/TriangleFan)
  (GL/Vertex2 (v* (reduce #(v+ %1 %2) ps)
                  (float (/ 1 (count ps)))))
  (doseq [^Vector2 p ps] (GL/Vertex2 p))
  (GL/End)
  ps)

(def solid fan)

(def boid {:position Vector2/Zero
           :velocity Vector2/One
           :acceleration Vector2/Zero})

(defn boid* [pos]
  (-> boid
      (assoc :position pos)
      (assoc :velocity (let [angle (rand (* 2 Math/PI))]
                         (Vector2. (cos angle)
                                   (sin angle))))))

(defn draw-boid [boid]
  (GL/PointSize 5)
  (GL/LineWidth 2)
  (points [boid])
  (lines [boid
          (update boid :position v+ (v* 15 (boid :velocity)))])
  boid)

(defn apply-force [boid ^Vector2 force]
  (update boid :acceleration v+ force))

(defn flock-seek [boid ^Vector2 target]
  (let [desired (v- target (:position boid))]
    (filter #(re-find #"Norm" (.Name %)) (.GetMethods Vector2))
    )
  )

(defn fps []
  (/ 1000.0 (Program/FrameTime)))

(def boids (take 20 (repeat boid)))

(defn on-draw [^Window w]
  (let [width (.Width w)
        height (.Height w)
        half-width (/ width 2)
        half-height (/ height 2)]
    (clear (- half-width) half-width
           (- half-height) half-height)
    (set! (.Title w) (str "Zajal - " (int (fps))))
    (GL/PointSize 2)
    (GL/LineWidth 5)
    (GL/Enable EnableCap/Blend)
    (GL/BlendFunc BlendingFactorSrc/SrcAlpha, BlendingFactorDest/OneMinusSrcAlpha)
    (GL/Color4 1 1 1 1)
    
    (->> boids
         (map draw-boid))
    
    ))