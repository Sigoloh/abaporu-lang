export function getBiggerBlockOrder(obj) {
  let maxBlockOrder = -Infinity;

  for (const key in obj) {
    if (obj.hasOwnProperty(key)) {
      const blockOrderValue = obj[key].blockOrder;
      if (blockOrderValue > maxBlockOrder) {
        maxBlockOrder = blockOrderValue;
      }
    }else {
      maxBlockOrder = 0;
    }
  }

  return maxBlockOrder;
}
