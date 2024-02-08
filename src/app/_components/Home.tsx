import { forwardRef, useRef, useEffect, useImperativeHandle, useState } from 'react';
import { animated, useSpring, useTrail } from '@react-spring/web';
import { random } from "lodash-es";

const letters = "ABCDEFGHIJKLMNOPQRSTUVWSYZ";

const Flipper = ({children, fps, stop}: {children: string, fps: number, stop: boolean}) => {
  const spanRef = useRef(null);
  const hdRef = useRef<any>();
  useEffect(() => {
    if (/^[,']$/.test(children)) return;

    const animate = () => {
      if (stop === true) {
        (spanRef.current! as HTMLSpanElement).textContent = children;
      }
      else {
        (spanRef.current! as HTMLSpanElement).textContent = letters[random(0, letters.length)];
        hdRef.current = setTimeout(animate, Math.floor(1000 / fps));
      }
    }
    hdRef.current = setTimeout(animate, Math.floor(1000 / fps))

    return () => {
      if (hdRef.current) {
        clearTimeout(hdRef.current);
      }
    }
  }, [children, fps, stop])

  return <span ref={spanRef}>{children}</span>;
}

const Headline = forwardRef(({children, className}: {children: string, className: string}, ref) => {
  const letters = children.split("");
  const [trails, api] = useTrail(
    letters.length, 
    () => ({
      from: {
        filter: "blur(10px)",
      }
    }), 
    [letters]
  );
  const [stopFlip, setStopFlip] = useState(false);
  
  useImperativeHandle(ref, () => ({
    async start() {
      setStopFlip(true);
      return new Promise((resolve) => {
        api.start({
          to: {
            filter: "blur(0)",
          },
          config: {
            duration: 80,
          },
          onRest(...rest) {
            resolve(rest);
          }
        })
      });
    }
  }), [api]);

  return (
    <h1 className={className}>
      {trails.map((trail, i) => {
        return (
          <animated.span key={i} style={trail}>
            <Flipper fps={10} stop={stopFlip}>{letters[i]}</Flipper>
          </animated.span>
        );
      })}
    </h1>
  )
});

export default function Home() {
  const [springs, api] = useSpring(() => ({from: { zoom: 0.9 }}));
  const headline1 = useRef<{start: () => Promise<void>}>(null);
  const headline2 = useRef<{start: () => Promise<void>}>(null);
  const headline3 = useRef<{start: () => Promise<void>}>(null);

  useEffect(() => {
    api.start({
      to: { zoom: 1},
      config: {
        duration: 800,
      },
      async onRest() {
        headline1.current && await headline1.current.start();
        headline2.current && await headline2.current.start();
        headline3.current && await headline3.current.start();
      }
    })
  }, []);

  return (
    <animated.div style={springs}>
      <Headline ref={headline1} className=" font-extrabold text-6xl sm:text-8xl lg:text-9xl">Hi,</Headline>
      <Headline ref={headline2} className=" font-extrabold text-6xl sm:text-8xl lg:text-9xl">I'm John</Headline>
      <Headline ref={headline3} className=" font-extrabold text-6xl sm:text-8xl lg:text-9xl">Huang</Headline>
      <p className="mt-3 break-keep whitespace-nowrap indent-1">A Passionate Full-Stack Developer.</p>
    </animated.div>
  );
}
