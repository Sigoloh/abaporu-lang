import fs from 'fs';
import {processArgs} from './utils/processArgs.js'
import { openFile } from './utils/openFile.js';
import { tokenize } from './utils/tokenizer.js';
import { validateInstruction } from './utils/validateInstruction.js';
import { instructions } from './utils/instructions.js';
const values = [];

const args =  process.argv.slice(2);
const organizedArgs =  processArgs(args);

const fileContent = openFile(organizedArgs.inputFile);

const tokenized = tokenize(fileContent);

const sausage = [0];

let pointer = 0;
for(const token of tokenized){
  if(validateInstruction(token)){
    const translatedInstruction = instructions[token];
    switch (translatedInstruction) {
      case 'addOne':
        if(sausage[pointer] !== undefined){
          sausage[pointer]++;
        }else{
          sausage[pointer] = 0
        }
        break;
      case 'subOne':
        if(sausage[pointer] !== undefined){
          sausage[pointer]--;
        }else{
          sausage[pointer] = 0
        }
        break;
      case 'nextCell':
        pointer++;
        break;
      case 'prevCell':
        if(pointer - 1 < 0){
          throw new Error('Note: You are not able to write in this position')
        }
        pointer--;
        break;
      case 'put':
        process.stdout.write(String.fromCharCode(sausage[pointer]))
        break;
      default:
        break;
    }
  }
}
