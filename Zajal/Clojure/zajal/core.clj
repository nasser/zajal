(ns zajal.core
  (:import [OpenTK Vector2]))

(defn parse-vector [v]
  (cond (map? v) (Vector2. ^double (v 'x) ^double (v 'y))
        (vector? v) (Vector2. ^double (first v) ^double (last v))))