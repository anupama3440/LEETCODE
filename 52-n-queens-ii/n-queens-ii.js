/**
 * @param {number} n
 * @return {number}
 */
var totalNQueens = function(n) {
    let count = 0;

    function backtrack(row, cols, diag1, diag2) {
        if (row === n) {
            count++; // Found a valid solution
            return;
        }

        for (let col = 0; col < n; col++) {
            if (cols.has(col) || diag1.has(row + col) || diag2.has(row - col)) continue;
            cols.add(col);
            diag1.add(row + col);
            diag2.add(row - col);
            backtrack(row + 1, cols, diag1, diag2);
            cols.delete(col);
            diag1.delete(row + col);
            diag2.delete(row - col);
        }
    }

    backtrack(0, new Set(), new Set(), new Set());

    return count;
};
