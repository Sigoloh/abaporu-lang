import {processArgs} from './utils/processArgs.js'
import { openFile } from './utils/openFile.js';
import { tokenize } from './utils/tokenizer.js';
import { validateInstruction } from './utils/validateInstruction.js';
import { instructions } from './utils/instructions.js';
import { getBiggerBlockOrder } from './utils/getBiggerOrderBlock.js';
import { sortByBlockOrder } from './utils/sortBlockOrder.js';
import { generateImage } from './utils/generateImage.js';
import { findLoopByEndLoop } from './utils/findLoopByEndLoop.js';
const values = [];

const args =  process.argv.slice(2);
const organizedArgs =  processArgs(args);

const fileContent = openFile(organizedArgs.inputFile);

const tokenized = tokenize(fileContent);

const sausage = [0];

let blockNamesAndPositions = {};
let loopRegister = {}
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
        throw new Error('[FATAL] Could not find where to return the pointer after leave the block. Maybe you named two blocks with the same?')
      }
      i = returnTo;
      break;
    case 'endLoop':
      const [loopRunning, runningLoopKey] =  findLoopByEndLoop(loopRegister, i);
      
      if(!loopRunning || !runningLoopKey){
        throw new Error(`[FATAL]: Interpreted found a closing loop token but could not find the loop it belongs to in token ${i}. Maybe your trying to use a loop inside a loop?`)
      }

      if(loopRunning.counter - 1 > 0){
        loopRegister[runningLoopKey].counter--;
        i = loopRunning.startOfLoop;
      }else{
        delete loopRegister[runningLoopKey]
      } 
      break;
    case undefined: 
      if(token.startsWith('#11')){
        const counter = parseInt(token.replace('#11', ''), 16)
        const startOfLoop = tokenized.indexOf(token, i);
        const endOfLoop = tokenized.indexOf('#3FFFE8', i);
        if(endOfLoop === -1){
          throw new Error(`[FATAL]: You declared the loop ${token} in the position ${tokenized.indexOf(token)} without closing it.`)
        }
        const executingLoop = loopRegister[`${token}${startOfLoop}${endOfLoop}`];
        // Register loop as a token if it is not registered yet.
        if(!executingLoop){
          loopRegister[`${token}${startOfLoop}${endOfLoop}`] = {
            counter: counter,
            startOfLoop: startOfLoop,
            endOfLoop: endOfLoop
          }
          i--;
          break;
        }else{
          i = executingLoop.startOfLoop;
        }
        break;
      }
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
