(ns zajal.shape
  (:use zajal.core))

(defn line
  ([a b] (fn [t]
           (Vector2/op_Addition
             (Vector2/op_Multiply a (- 1 t))
             (Vector2/op_Multiply b t))))
  ([t a b] ((line a b) t)))

(def circle
  (memoize
    (fn [c ^double r]
      (fn [t] (let [t (* t 2 Math/PI)]
                (v+ c (v* r (Vector2. (Math/Cos t)
                                      (Math/Sin t)))))))))

(defn bezier
  ([a b c] (fn [t]
             (let [-t (- 1 t)]
               (v+ (v* a (pow -t 2))
                   (v+ (v* b (* t (* 2 -t)))
                       (v* c (pow t 2))))))))