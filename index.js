import {processArgs} from './utils/processArgs.js'
import { openFile } from './utils/openFile.js';
import { tokenize } from './utils/tokenizer.js';
import { validateInstruction } from './utils/validateInstruction.js';
import { instructions } from './utils/instructions.js';
import { getBiggerBlockOrder } from './utils/getBiggerOrderBlock.js';
import { sortByBlockOrder } from './utils/sortBlockOrder.js';
import { generateImage } from './utils/generateImage.js';
const values = [];

const args =  process.argv.slice(2);
const organizedArgs =  processArgs(args);

const fileContent = openFile(organizedArgs.inputFile);

const tokenized = tokenize(fileContent);

const sausage = [0];

let blockNamesAndPositions = {};
let pointer = 0;

console.log('+===================================+')
console.log('+                                   +')
console.log('+            Code result            +')
console.log('+                                   +')
console.log('+===================================+')


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
    case 'putVal':
      process.stdout.write(`${(sausage[pointer])}`)
      break;
    case 'endBlock':
      let returnTo = -1;
      blockNamesAndPositions = sortByBlockOrder(blockNamesAndPositions);
      const firstBlockName = Object.keys(blockNamesAndPositions)[0];
      if(blockNamesAndPositions[firstBlockName].in){
        returnTo = blockNamesAndPositions[firstBlockName].entered;
        blockNamesAndPositions[firstBlockName].in = false;
        blockNamesAndPositions[firstBlockName].blockOrder = -1;
      }
      if(returnTo === -1){
        throw new Error('[FATAL] Could not find where to return the pointer after leave the block')
      }
      i = returnTo;
      break;
    case undefined: 
      const blockNameAndPosition = blockNamesAndPositions[token]
      if(blockNameAndPosition){
        const biggerOrderBlock = Object.keys(blockNamesAndPositions).length > 0 ?
          getBiggerBlockOrder(blockNamesAndPositions) : 
          0;

        blockNameAndPosition.blockOrder = biggerOrderBlock + 1;

        blockNameAndPosition.in = true;

        blockNameAndPosition.entered = i;

        i = blockNameAndPosition.beginOfBlock;

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
          blockOrder: -1
        }

        i = endOfBlock;
      }

      break;
    default:
      throw new Error(`[FATAL] Invalid instruction or block: ${token}`);
  }
}
process.stdout.write(String.fromCharCode(10));
console.log('+===================================+')
console.log('+                                   +')
console.log('+           Art Creation            +')
console.log('+                                   +')
console.log('+===================================+')

try {
  generateImage(tokenized, organizedArgs.outputPath);
} catch (error) {
  console.log(error); 
}
