(ns examples.hummus
  (:refer-clojure :exclude [compile])
  (:require [clojure.string :as string]
            [gamma.api :as g]
            [gamma.program :as p])
  (:import [OpenTK Vector2 Vector3 Vector4]
           Math))

(defn v3 [a b c] (Vector3. a b c))

(defn compile [type source]
  (let [type (or (type
                   {:vertex ShaderType/VertexShader
                    :fragment ShaderType/FragmentShader})
                 type)
        id (GL/CreateShader type)]
    (GL/ShaderSource id (str "#version 120\n" source))
    (GL/CompileShader id)
    (Console/WriteLine (GL/GetShaderInfoLog id))
    id))

(defn shader [{:keys [vertex-shader fragment-shader]}]
  (let [id (GL/CreateProgram)]
    (GL/AttachShader id (compile :vertex (:glsl vertex-shader)))
    (GL/AttachShader id (compile :fragment (:glsl fragment-shader)))
    (GL/LinkProgram id)
    (Console/WriteLine (GL/GetProgramInfoLog id))
    id))

(defonce window (Zajal.Window. (str *ns*) 400 400 2 1))

(def matrix-array
  (memoize (fn matrix-array [^Matrix4 m]
             (let [^floats a (make-array Single 16)]
               (aset a 0 (.M11 m))
               (aset a 1 (.M12 m))
               (aset a 2 (.M13 m))
               (aset a 3 (.M14 m))
               (aset a 4 (.M21 m))
               (aset a 5 (.M22 m))
               (aset a 6 (.M23 m))
               (aset a 7 (.M24 m))
               (aset a 8 (.M31 m))
               (aset a 9 (.M32 m))
               (aset a 10 (.M33 m))
               (aset a 11 (.M34 m))
               (aset a 12 (.M41 m))
               (aset a 13 (.M42 m))
               (aset a 14 (.M43 m))
               (aset a 15 (.M44 m))
               a))))

(defn on-load [w]
  ; (.. w MakeCurrent)
  (GL/BindVertexArray (GL/GenVertexArray))
  
  (def program
    (shader
      (let [horiz (g/varying "horizontal" :float)
            vert  (g/varying "vertical" :float)
            pos   (g/attribute "position" :vec4)]
        (p/program
          {:vertex-shader
           {horiz (g/swizzle pos :x)
            vert  (g/swizzle pos :y)
            (g/gl-position)
            (reduce g/* [(g/uniform "projectionMatrix" :mat4)
                         (g/uniform "viewMatrix" :mat4)
                         (g/uniform "modelMatrix" :mat4) 
                         (g/attribute "position" :vec4)])}
           :fragment-shader
           {(g/gl-frag-color)
            (g/vec4 (g/* horiz horiz) (g/- 0 vert) 1 1)
            }}))))
    
  (def model-matrix (GL/GetUniformLocation ^int program "modelMatrix"))
  (def projection-matrix (GL/GetUniformLocation ^int program "projectionMatrix"))
  (def view-matrix (GL/GetUniformLocation ^int program "viewMatrix"))
  
  (def position-attr (GL/GetAttribLocation ^int program "position"))
  (def position-buff (GL/GenBuffer))
  )

;; (on-load nil)

(def half-pi (/ 2 Math/PI))

(defn camels-to-hyphens [s]
  (string/replace s #"([a-z])([A-Z])" "$1-$2"))

(defonce points (atom (make-array Vector3 0)))

(defn v2 [a b] (Vector2. a b))

(defn ortho [left right bottom top near far]
  (let [m (make-array Single 16)]
    (aset m 0 (/ 2.0 (- right left)))
    (aset m 5 (/ 2.0 (- top bottom)))
    (aset m 10 (/ -2.0 (- far near)))
    
    (aset m 12 (- (/ (+ right left) (- right left))))
    (aset m 13 (- (/ (+ top bottom) (- top bottom))))
    (aset m 14 (- (/ (+ far near) (- far near))))
    (aset m 15 1)
    m))

;; (reset! points
;;         (into-array [(v3 -0.5 -0.5 0.5)
;;                      (v3 0.5 -0.5 0.5)
;;                      (v3 0.5 0.5 0.5)
;;                      (v3 -0.5 0.5 0.5)
;;                      (v3 -0.5 -0.5 0.5)
;;                      (v3 -0.5 -0.5 -0.5)
;;                      (v3 0.5 -0.5 -0.5)
;;                      (v3 0.5 0.5 -0.5)
;;                      (v3 -0.5 0.5 -0.5)
;;                      (v3 -0.5 -0.5 -0.5)]))

(def t (atom 0.0))

(reset! points (->> [(v3 0 0 0)
                     (v3 0 1 0)
                     (v3 1 1 0)
                     (v3 0 0 0)
                     ]
                    into-array))

(defn update-points-loop []
  (let [^|OpenTK.Vector3[]| ps @points
        c (dec (count ps))
        t @t]
    (loop [i 0]
      (aset ps i
            (v3 (+ -1 (* 0.25 (+ (/ i 500.0)
                                 (Math/Cos (+ i t)))))
                (+ (* 0.5 (Math/Sin (+ (* 0.02 t) (* 0.5 i))))
                   (* 0.25 (Math/Cos (* 0.005 i t))))
                0))
      (if (< i c)
        (recur (inc i))
        ps))))

(defn update-points []
  (let [t @t]
    (reset! points
            (->> (range 2000)
                 (map (fn [i]
                        (v3 (+ -2 (* 0.01 (+ (/ i 50.0)
                                              (Math/Cos (+ i t)))))
                            (* (+ (* 0.75 (Math/Sin (+ (* 0.002 t) (* 0.005 t i))))
                                  (* 0.25 (Math/Cos (* 0.005 i t))))
                               (* 3 (Math/Sin (* 2 i t 0.001))))
                            0)))
                 into-array))))

(defn update-time []
  (reset! t (+ @t 0.01)))

(def id-matrix (matrix-array Matrix4/Identity))

(defn gl-stuff [^|OpenTK.Vector3[]| vs]
  (GL/Enable EnableCap/Blend)
  (GL/ClearColor 0 0 0 0)
  (GL/Clear ClearBufferMask/ColorBufferBit)
  (GL/UseProgram ^int program)
  (GL/UniformMatrix4 ^int projection-matrix 1 false ^floats (ortho -3 3 -3 3 -3 3))
  ; (GL/UniformMatrix4 ^int projection-matrix 1 false id-matrix)
  (GL/UniformMatrix4 ^int view-matrix 1 false ^floats id-matrix)
  (GL/UniformMatrix4 ^int model-matrix 1 false ^floats id-matrix)
  ; 
  (GL/BindBuffer BufferTarget/ArrayBuffer ^int position-buff)
  (GL/BufferData BufferTarget/ArrayBuffer
                 (* (count vs) Vector3/SizeInBytes)
                 vs BufferUsageHint/StaticDraw)
  (GL/VertexAttribPointer ^int position-attr (int 3)
                          VertexAttribType/Float false 0 0)
  ; 
  (GL/EnableVertexAttribArray ^int position-attr)
  (GL/DrawArrays PrimitiveType/Points 0 (count vs))
  (GL/DisableVertexAttribArray ^int position-attr))

(defn on-draw [^Zajal.Window w]
  ; (Console/WriteLine (.Width w))
  (GL/Viewport 0 0 (.Width w) (.Height w))
  (GL/PointSize 1)
  (GL/LineWidth 4)
  (let [^|OpenTK.Vector3[]| vs @points]
    (update-time)
    (update-points)
    (gl-stuff vs)
    ))