(ns zajal)

(defn renderer* [parent body]
  (js/window.VirtualDom.renderer parent nil body))

(defn text [s]
  (js/window.VirtualDom.text s))

(defn node [tag attrs children]
  (js/window.VirtualDom.node tag (clj->js attrs) (clj->js children)))

;; input

(defonce start-time (js/Date.now))
(defonce mouse-state (atom {:x 0 :y 0 :pressed false}))

(js/window.document.addEventListener
  "mousemove"
  #(swap! mouse-state
          assoc
          :x (.-pageX %)
          :y (.-pageY %)))

(js/window.document.addEventListener
  "mousedown"
  #(swap! mouse-state
          assoc :pressed? true))

(js/window.document.addEventListener
  "mouseup"
  #(swap! mouse-state
          assoc :pressed? false))

(defn input []
  (let [t (js/Date.now)]
    {:time {:elapsed (- t start-time)}
     :mouse @mouse-state }))

(defn sketch [start step draw]
  (js/console.log "sketch")
  (let [state (atom start)
        renderer (renderer* (js/document.querySelector "#app")
                            (draw start))]
    (letfn [(render-loop [t]
                         (.requestAnimationFrame js/window render-loop)
                         (swap! state step (input))
                         (.update renderer (draw @state)))]
      (render-loop 0)))
  :ok)