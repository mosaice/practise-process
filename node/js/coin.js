const denomination = [0, 1, 5, 10, 25, 50];

const find = (amount, kind) => {
    if (amount === 0) return 1;
    if (amount < 0 || kind === 0) return 0;
    return find(amount, kind - 1) + find(amount - denomination[kind], kind);

}
const result = find(1000, 5);
console.log(result);