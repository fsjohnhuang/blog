import type { MDXComponents } from 'mdx/types'
 
export function useMDXComponents(components: MDXComponents): MDXComponents {
  return {
    h1: ({children}) => <h1 className='text-2xl text-bold'>{children}</h1>,
    h2: ({children}) => <h2 className="text-xl font-bold">{children}</h2>,
    p: ({children}) => <p className="text-gray-700 my-4 text-base">{children}</p>,
    ...components,
  }
}