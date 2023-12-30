export function sortByBlockOrder(obj) {
  try {
    const sortedKeys = Object.keys(obj).sort((a, b) => {
      return obj[b].blockOrder - obj[a].blockOrder;
    });

    const sortedObj = {};
    sortedKeys.forEach(key => {
      sortedObj[key] = obj[key];
    });

    return sortedObj;
  } catch (error) {
    console.log(error); 
  }

}
