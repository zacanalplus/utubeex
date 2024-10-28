use std::cmp::PartialOrd;

struct Collatz{
    start : u64,
    end : u64,
}

struct Table{
    v : Vec<u64>,    // Table entries
    l : usize,       // Table length
    w : usize,       // Table width
}

fn main() {
    println!("မင်္ဂလာပါ");
    let naturals = (0..).take(11).collect::<Vec<i32>>();
    
    let sliced_naturals = naturals.into_iter().skip(3).take(4).collect::<Vec<i32>>();
    println!("{:?}", sliced_naturals);
    let num = 23;
    let my_collatz_seq = Collatz::new(num);
    
    for i in my_collatz_seq{
        print!("{} ", i);
    }
    println!();
//  println!("Count in Collatz sequence start from {} is {}. ", num, my_collatz_seq.cnt);
    println!("The number {} is greater than {}. ", max(47, 233), min(233, 47));
    println!("The number {} is equal to {}. {}", 133, 233, equals(133, 233));
    
    for _i in 0..4 {
        Table::magic3x3().debug_print();
        println!("------");
    }
}

fn next_collatz(n:u64)->u64{
    if n & 1 == 1{
        return n * 3 + 1;
    }
    else{
        return n / 2;
    }
}


impl Collatz{
    fn new(start : u64) -> Collatz {
        Collatz{
            start : start * 2,
            end : 1,
        }
    }
}

impl Table{
    fn new(length : usize, width : usize) -> Table {
        Table{
            l : length,
            w : width,
            v : vec![0u64; length * width],
        }
    }
    fn init(&mut self){
        for _i in 0..9 {
            self.v.push(0);
        }
    }
    fn add(&mut self, x : usize, y : usize, val : u64)-> &Table {
        if x < self.l && y < self.w {
            self.v[x * self.l + y] = val;
        }
        self
    }
    fn reference(self, x : usize, y : usize) -> Option<u64> {
        if x < self.l && y < self.w {
            return Some(self.v[x * self.l + y]);
        }
        None
    }
    fn magic3x3() -> Table {
        static mut START :  usize = 0;
        let patterns = [[1, 6, 5, 8, 4, 0, 3, 2, 7], [3, 2, 7, 8, 4, 0, 1, 6, 5],
            [5, 6, 1, 0, 4, 8, 7, 2, 3], [7, 2, 3, 0, 4, 8, 5, 6, 1]];
        unsafe{
            let mut ms = Table::new(3, 3);
//          ms.init();
            for i in 1..10 {
                let x = patterns[START][i-1] / 3;
                let y = patterns[START][i-1] % 3;
//              println!("Indices are {}, {}.", x, y);
                ms.add(x, y, i as u64);
            }
            START += 1;
            ms
        }
    }
    fn debug_print(self) {
        for i in 0..3 {
            for j in 0..3 {
                print!("{} ", self.v[i * 3 + j]);
            }
            println!();
        }
    }
}

impl Iterator for Collatz{
    type Item = u64;
    
    fn next(&mut self) -> Option<u64>{
        if self.start == self.end {
            None
        }
        else
        {
            self.start = next_collatz(self.start);
            let result = Some(self.start);
            result
        }
    }
}

fn max<T : PartialOrd>(t1 : T, t2 : T) -> T {
    if t1 > t2 {
        return t1;
    }
    return t2;
}

fn min<T : PartialOrd>(t1 : T, t2 : T) -> T {
    if t1 < t2 {
        return t1;
    }
    return t2;
}

fn equals<T>(t1 : T, t2 : T) -> bool
where 
    T : PartialOrd
{
    t1 == t2
}