struct CamelName(String, i32, f32);

fn main() {
    println!("မင်္ဂလာပါ");
    let mut x;
    x = 47;
    println!("{}", x);
    let cname = CamelName("Identity".into(), 133, 3.1415);
    println!("{} - {} / {}", cname.0, cname.1, cname.2);
    for i in 1..1000000{
        let (n, cnt) = collatz(i);
        println!("{} - {}", n, cnt);
    }
}

fn collatz(n : i32) -> (i32, i32) {
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