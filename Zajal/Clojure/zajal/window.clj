(ns zajal.window)

(defn on-draw [w]
  (set! (.Title w) "zajal.window")
  (GL/Clear (enum-or ClearBufferMask/ColorBufferBit
                     ClearBufferMask/DepthBufferBit)))

(defn on-closed []
  (Console/WriteLine "closed"))

(defn on-mouse-wheel [e]
  (Console/WriteLine e))

(defn on-key-down [e]
  (Console/WriteLine (.Key e)))