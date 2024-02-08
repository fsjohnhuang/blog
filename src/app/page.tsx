"use client"

import { useRef, useEffect, useMemo, useState } from "react";
import { animated, useSpring } from "@react-spring/web";
import Home from "./_components/Home";

export default function Page() {
  const [springs, api] = useSpring(() => ({
    from: {
      backgroundColor: "#fff",
      color: "#000",
    }
  }));

  const [current, setCurrent] = useState("home");
  const content = useMemo(() => {
    if (current === "home") {
      return <Home/>;
    }
    else {
      return null;
    }
  }, [current]);

  const toRef = useRef({backgroundColor: "#000", color: "#fff"});
  useEffect(() => {
    const {backgroundColor: color, color: backgroundColor} = toRef.current;
    api.start({
      to: toRef.current,
      onRest() {
        toRef.current = {backgroundColor, color};
      }
    });
  }, [current])

  return (
    <animated.main className="w-screen h-screen overflow-hidden p-5 relative flex flex-col justify-between" style={springs}>
      <nav className="flex flex-row justify-between uppercase">
        <div 
        className={`cursor-pointer ${ current === "home" ? "text-white" : "text-gray-300 hover:text-white" }`}>
          home</div>
        <div 
          className={`cursor-pointer ${ current === "about" ? "text-white" : "text-gray-300 hover:text-white" }`}
          onMouseEnter={() => {setCurrent("about")}} onMouseLeave={() => { setCurrent("home") }}>about</div>
      </nav>
      <nav className="flex flex-row justify-between uppercase">
        <div 
          className={`cursor-pointer ${ current === "post" ? "text-white" : "text-gray-300 hover:text-white" }`}
          onMouseEnter={() => {setCurrent("post")}} onMouseLeave={() => { setCurrent("home") }}>post</div>
        <div 
          className={`cursor-pointer ${ current === "work" ? "text-white" : "text-gray-300 hover:text-white" }`}
          onMouseEnter={() => {setCurrent("work")}} onMouseLeave={() => { setCurrent("home") }}>work</div>
      </nav>

      <section 
        className="absolute left-1/2 top-1/2 transform -translate-x-1/2 -translate-y-1/2 w-4/5"
      >
        {content}    
      </section>
    </animated.main>
  )
}
