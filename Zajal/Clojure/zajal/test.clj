(ns zajal.test
  (:use zajal.core))

(defn on-closed []
  (Console/WriteLine "test closed"))

(defn on-mouse-wheel [e]
  (Console/WriteLine "test")
  (Console/WriteLine e))

(defn on-key-down [e]
  (Console/WriteLine "test")
  (Console/WriteLine (.Key e)))
