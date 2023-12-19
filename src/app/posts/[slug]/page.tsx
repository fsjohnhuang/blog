import fs from "node:fs/promises"
import path from "node:path"
import { MDXRemote } from 'next-mdx-remote/rsc';

export async function generateStaticParams() {
  const files = await fs.readdir('database');
  return files.map((file) => ({
    slug: file.replace(path.extname(file), ""),
  }))
}


async function getSource(slug: string) {
  const source = await fs.readFile(
    path.join('database', slug + ".mdx"),
    'utf8'
  );
  return source
}


async function ArticlePage({params}: {params: {slug: string}}) {
  const source = await getSource(params.slug)

  return (
    <MDXRemote source={source}/>
  );
}


export default ArticlePage;

