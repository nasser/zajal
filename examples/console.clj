(ns examples.console
  (:require [clojure.string :as string])
  (:import [OpenTK Vector2 Vector3 Vector4]
           Math))

(defn camels-to-hyphens [s]
  (string/replace s #"([a-z])([A-Z])" "$1-$2"))

(def enum-map
  (memoize (fn [e]
             (let [ks (->> e
                           Enum/GetNames
                           (map camels-to-hyphens)
                           (map string/lower-case)
                           (map keyword))
                   vs (->> e
                           Enum/GetNames
                           (map #(Enum/Parse e %)))]
               (apply hash-map (interleave ks vs))))))

(use 'clojure.repl)

(render [{:left 20 :right 10 :color :white :background :black} "hello"])
(render [{:left 20 :color :dark-red}
          "abs"
          [{:color :green} "what"]])
(render [{:top 20 :left 1}
         [{:color :red} "nixce"]
         [{:color :blue} "man"]
         
         ]
        )

(render [{:color :blue :left 50}
         [{:top 20} "│"]
         [{:top 21} "│"]
         [{:top 22} "│"]
         [{:top 23} "¹/₂"]
         [{:top 24} "⇶"]
         [{:top 25} "■▶"]
         ])

(Console/Clear)
(Console/ResetColor)

(defn render
  ([spec] (render {:left 0 :top 0 :color :gray :background :black}
                  spec))
  ([env [props & body]]
   (let [colors (enum-map ConsoleColor)
         props (merge env props)]
     (if-let [v (:color props)] (set! Console/ForegroundColor (colors v)))
     (if-let [v (:background props)] (set! Console/BackgroundColor (colors v)))
     (if-let [v (:left props)] (set! Console/CursorLeft v))
     (if-let [v (:top props)] (set! Console/CursorTop v))
     (reduce (fn [props b]
               (if (string? b)
                 (do
                   (Console/Write b)
                   props)
                 (render props b)))
             props
             body))))





(use 'arcadia.core)

(set! Selection/a)

(doall (map destroy (objects-named "Ivan")))