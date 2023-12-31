export function findLoopByEndLoop(loops, endingOfLoop){
  try {
    const allLoopsNames = Object.keys(loops);
    let loopToReturn = undefined;
    let loopKey = undefined;
    for(const key of allLoopsNames){
      if(loops[key].endOfLoop == endingOfLoop){
        loopToReturn = loops[key];
        loopKey = key;
      }
    }
    return [loopToReturn, loopKey];
  } catch (error) {
    console.log(error)  
  }
}
