var topKFrequent = function(nums, k) {
    let freqMap = new Map();
    for (let num of nums) {
        freqMap.set(num, (freqMap.get(num) || 0) + 1);
    }

    let freqArray = Array.from(freqMap.entries());
    
    freqArray.sort((a, b) => b[1] - a[1]); 

    return freqArray.slice(0, k).map(entry => entry[0]); 
};


