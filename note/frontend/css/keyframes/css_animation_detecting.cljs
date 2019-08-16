(ns css-animation-detecting
  (:require [clojure.string :as string]))

(defn detect []
  (let [std-name "animation"
        prefixs ["Webkit" "Moz" "O" "ms" "Khtml"]
        sample (js/document.createElement "div") 

        names-with-prefix (cons std-name (map prefixs #(str % "Animation")))
        js-prefixs (cons "" prefixs)
        css-prefixs (cons "" (map prefixs #(str "-" (string/lower-case %) "-")))
        prefix-triples (partition 3 (interleave names-with-prefix js-prefixs css-prefixs))]
    (loop [triple (first prefix-triples)
           rest-triples (rest prefix-triples)]
      (if (nil? (aget sample (first triple)))
        (if-not (zero? (count rest-triples))
          (recur (first rest-triples) (rest rest-triples))
          nil)
        triple))))

;; Usage
;; -----------------------------
(defn insert-style-rule-to-existed! [rule]
  (let [stylesheets (.-stylesheets js/document)
        stylesheet (when (and (some? stylesheets)
                              (pos? (.-length stylesheets)))
                     (aget 0 stylesheets))]
    (if (nil? stylesheet)
      false
      (do (.insertRule stylesheet rule 0)
          true))))

(defn insert-style-rule-from-scratch! [rule]
  (let [style-element (js/document.createElement "style")
        head (js/document.querySelector "head")]
    (set! (.-innerHTML style-element) rule)
    (.appendChild head style-element)))

(defn insert-style-rule! [rule]
  (when-not (insert-style-rule-to-existed! rule)
    (insert-style-rule-from-scratch! rule)))

(defn keyframes-rotate [prefix]
  (str "@" prefix "keyframes rotate {
    from {"
       prefix "transform: rotate(0deg);
    }
    to {"
       prefix "transform: rotate(360deg);
    }
  }"))

(when-let [triple (detect)]
  (-> triple
      last
      keyframes-rotate
      insert-style-rule!))
