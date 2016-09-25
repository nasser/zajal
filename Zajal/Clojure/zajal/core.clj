(ns zajal.core
  (:import [OpenTK Vector2]))

(defn parse-vector [v]
  (cond (map? v) (Vector2. ^double (v 'x) ^double (v 'y))
        (vector? v) (Vector2. ^double (first v) ^double (last v))))

(defn lerp [a b f]
  (Vector2/Lerp a b f))

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

(defmacro v+ [a b] `(Vector2/op_Addition ~a ~b))
(defmacro v- [a b] `(Vector2/op_Subtraction ~a ~b))
(defmacro v* [a b] `(Vector2/op_Multiply ~a ~b))
(defmacro sin [x] `(Math/Sin ~x))
(defmacro cos [x] `(Math/Cos ~x))
(defmacro pow [x p] `(Math/Pow ~x ~p))