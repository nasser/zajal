(ns zajal.draw
  (:use zajal.core))

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
  (doseq [^Vector2 position ps] (GL/Vertex2 position))
  (GL/End)
  ps)

(defn lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/LineStrip)
  (let [ps (conj ps (last ps))]
    (doseq [^Vector2 position ps] (GL/Vertex2 position)))
  (GL/End)
  ps)

(defn open-lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/LineStrip)
  (doseq [^Vector2 position ps] (GL/Vertex2 position))
  (GL/End)
  ps)

(defn disconnected-lines
  "Draws a line strip connecting all points in ps"
  [ps]
  (GL/Begin PrimitiveType/Lines)
  (doseq [^Vector2 position ps] (GL/Vertex2 position))
  (GL/End)
  ps)

(defn fan
  "Draws triangle fan"
  [ps]
  (GL/Begin PrimitiveType/TriangleFan)
  (doseq [^Vector2 position ps] (GL/Vertex2 position))
  (GL/End)
  ps)

(def solid fan)