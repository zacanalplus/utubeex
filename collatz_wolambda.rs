

fn main() {
    let mut x;
    let mut pair = (1, 1);
    x = 47;
    for i in 1..1000000{
        let (n, cnt) = collatz(i);
        if(x < cnt){
            pair = (n, cnt);
            x = cnt;
        }
    }
    println!("{} - {}", pair.0, pair.1);
}

fn collatz(n : i64) -> (i64, i64) {
    let mut cnt = 0;
    let mut num = n;
    if n == 1 { return (1, 1); }
    while(num > 1){
        if(num & 1) == 1{
            num = 3 * num + 1;
        }
        else{
            num /= 2;
        }
        cnt += 1;
    }
    return (n, cnt);
}