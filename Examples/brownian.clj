(ns brownian)

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

(defn line
  "Draws a line between a and b"
  [^Vector2 a ^Vector2 b]
  (GL/Begin PrimitiveType/Lines)
  (GL/Vertex2 a)
  (GL/Vertex2 b)
  (GL/End))

(defn lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/LineStrip)
  (doseq [^Vector2 p ps] (GL/Vertex2 p))
  (GL/End))

(def tail
  "The points in the brownian line"
  (atom [(Vector2. 0 0)]))

(defn rand
  "Override clojure.core/rand to allow ranges"
  ([] (clojure.core/rand))
  ([n] (clojure.core/rand n))
  ([n m] (+ n (clojure.core/rand (- m n)))))

(defn randomize
  "Generate a random number near x"
  ([x] (randomize x 1))
  ([x n] (+ x (rand (- n) n))))

(defn next-point
  "Generate the next point given p. The next point is a random point near p."
  [p]
  (Vector2. (randomize (.X p))
            (randomize (.Y p))))

(defn grow
  "Extend a tail by adding a random point to the end"
  [t]
  (let [np (next-point (last t))]
    (conj t np)))

(defn constrain
  "Constrain a vector t to length l"
  [t l]
  (if (> (count t) l)
      (subvec t 1)
      t))

(defn brownian
  "Grow a tail t and constrain its length to l"
  [t l]
  (-> t
      grow
      (constrain l)))

(defn on-draw [w]
  (clear)                    ;; clear window
  (swap! tail brownian 1000) ;; update state
  (lines @tail))             ;; draw state

(Window. "brownian")         ;; spawn window for brownian namespace