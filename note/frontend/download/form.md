```
<form action="./test1"></form>
<form action="./test2"></form>
..............................
<form action="./test1000"></form>

(defn exec [action]
  (let [forms (js/document.querySelectorAll "form")
        len (.-length forms)]
    (loop [i 0]
      (action (aget forms i))
      (when (< i len)
        (recur (inc i))))))

(defn download-immediately [form]
  (.submit form))

(defn download-in-future [form]
  (js/setTimeout #(.submit form) (* (js/Math.random) (js/random) 1000)))

(comment
  "1. In download-immediately, just the last request would be fired.
   2. In download-in-future, just a few requests would be fired, most of requests would be canceled.")
(exec download-immediately)
(exec download-in-future)
```

