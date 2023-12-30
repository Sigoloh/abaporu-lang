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

const blockNamesAndPositions = {};
let pointer = 0;

const tokenListLength = tokenized.length;
for(let i = 0; i < tokenListLength; i++){
  const token = tokenized[i];
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
      sausage[pointer] = 0;
      break;
    case 'prevCell':
      if(pointer - 1 < 0){
        throw new Error('Note: You are not able to write in this position')
      }
      pointer--;
      break;
    case 'put':
      process.stdout.write(`${String.fromCharCode(sausage[pointer])}`)
      break;
    case 'endBlock':
      let returnTo = -1;
      for(const blockName in blockNamesAndPositions){
        const block = blockNamesAndPositions[blockName]
        if(block.in){
          returnTo = block.entered;
          block.in = false;
        }
      }
      if(returnTo === -1){
        throw new Error('[FATAL] Could not find where to return the pointer after leave the block')
      }
      i = returnTo;
      break;
    case undefined: 
      const blockNameAndPosition = blockNamesAndPositions[token]
      if(blockNameAndPosition){
        blockNameAndPosition.in = true;

        blockNameAndPosition.entered = i;
        i = blockNameAndPosition.beginOfBlock + 1;

      } else {
        const beginOfBlock = i;

        const endOfBlock = tokenized.indexOf('#FFA500', i);

        if(endOfBlock === -1){
          throw new Error(`Note: you created a block assign the color: ${token} and did not closed it!`)
        }

        blockNamesAndPositions[token] = {
          beginOfBlock,
          endOfBlock,
          entered: -1,
          in: false,
        }

        i = endOfBlock;
      }

      break;
    default:
      throw new Error(`[FATAL] Invalid instruction or block: ${token}`);
  }
}
