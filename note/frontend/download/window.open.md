```
(defn open-continuously []
  (js/window.open "http://1st_url")
  (js/window.open "http://2nd_url"))

(comment 
  "Only click and dbclick events can trigger js/window.open.
   And the 2nd js/window.open would be intercepted in Chrome, IE6~10 and Opera.")
(doto (js/document.querySelector "button")
  (.addEventListener "click" open-continuously)
  (.addEventListener "dbclick" open-continuously))

(comment
  "js/window.open would be intercepted totally
  , because those are not triggered by user.")
(.then (js/fetch "url") open-continuously)
```
