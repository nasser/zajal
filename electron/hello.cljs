(ns hello
  (:require zajal
            there))

(defn p [& body]
  (if (map? (first body))
    (zajal/node "p" (first body) (rest body))
    (zajal/node "p" {} body)))

(defn em [& body]
  (if (map? (first body))
    (zajal/node "em" (first body) (rest body))
    (zajal/node "em" {} body)))

(defn text [& s]
  (zajal/text (apply str s)))

(def start {:click-count 0})

(defn step [state {:keys [mouse]}]
  (if (:pressed? mouse)
    (update state :click-count inc)
    state))

(defn draw [{:keys [click-count]}]
  (em (text "Clicks ")
      (text (there/prand click-count))))

(defonce test-sketch
  (zajal/sketch start #'step #'draw))