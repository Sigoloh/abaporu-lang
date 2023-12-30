import path from 'path'
import fs from 'fs'
export function openFile(inputPath){
  try {
    if(!inputPath){
      throw new Error('Remember: you have to provide a path to openFile.ts')
    }
    const parsedPath = path.parse(inputPath)

    if(parsedPath.ext !== '.abapl'){
      throw new Error('Remember: the first and only extension suported is .abapl')
    }

    const fileContent = fs.readFileSync(path.resolve(inputPath), {encoding: 'utf-8'}).toString()

    return fileContent;
  } catch (error) {
    throw error;   
  }
}
