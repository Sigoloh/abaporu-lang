export function validateInstruction(instruction){
  if(!instruction.includes('#')){
    throw new Error('Remember: every instruction must be a HEX color, starting with #')
  }

  if(!(instruction.length === 7)){
    throw new Error('Remember: every instruction must be a HEX color with 7 characters. like #000000, #F0F0F0')
  }

  return true;
};
