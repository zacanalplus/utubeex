struct NumMatrix{ // two dimentional vector with
    v : Vec<i128>,
    l : usize, // length of two dimensional array
    w : usize, // width of two dimensional array
}

fn main() {
    println!("မင်္ဂလာပါ");
    let x = NumMatrix::new(3, 3);
    println!("The size of number matrix is {}. ", x.len());
    let mut x = NumMatrix::new(0, 3);
    let mut v : i128 = 1;
    for i in 0..3 {
        x.add(0, i, v);
        v += 1;
    }
    println!("The size of number matrix is {}. ", x.len());
    x.print();
    let mut x = NumMatrix::new(3, 0);
    for i in 0..3 {
        x.add(i, 0, v);
        v += 1;
    }
    println!("The size of number matrix is {}. ", x.len());
    x.print();
    let ms = NumMatrix::matrixnxn(0);
    println!("The size of number matrix is {}. ", ms.len());
    ms.print();
    let ms = NumMatrix::matrixnxn(1);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(2);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(3);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(4);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(5);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(6);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(7);
    println!("-----");
    ms.print();
    let ms = NumMatrix::matrixnxn(8);
    println!("-----");
    ms.print();
    let x = NumMatrix::new(0, 0);
    x.print();
//  x = 47;
//  println!("{}", x);
}

impl NumMatrix {
    fn new(length : usize, width : usize) -> Self {
        let mut arr_size : usize = 0;
        if length != 0 {
            arr_size = length;
            if width != 0 {
                arr_size *= width;
            }
        }
        else {
            if width != 0 {
                arr_size = width;
            }
        }
        Self{
            l : length,
            w : width,
            v : vec![0i128; arr_size],
        }
    }
    
    fn matrixnxn(n : usize) -> NumMatrix {
        static MSIZE : usize = 3;
        static PATTERNS: &'static [[usize ; 9]; 8] =  &[[1, 6, 5, 8, 4, 0, 3, 2, 7], [3, 2, 7, 8, 4, 0, 1, 6, 5], [5, 6, 1, 0, 4, 8, 7, 2, 3], [7, 2, 3, 0, 4, 8, 5, 6, 1], [1, 8, 3, 6, 4, 2, 5, 0, 7], [3, 8, 1, 2, 4, 6, 7, 0, 5], [5, 0, 7, 6, 4, 2, 1, 8, 3], [7, 0, 5, 2, 4, 6, 3, 8, 1]];
        
        let mut ms = NumMatrix::new(MSIZE, MSIZE);
        let midx = n % PATTERNS.len();
        
        for i in 1..10 {
            let x = PATTERNS[midx][i - 1] / MSIZE;
            let y = PATTERNS[midx][i - 1] % MSIZE;
            ms.add(x, y, i as i128);
        }
        
        ms
    }
    
    fn empty(&self) -> bool {
        self.l == 0 && self.w == 0
    }
    
    fn len(&self) -> usize {
        if self.empty() {
            return 0usize;
        }
        else{
            if self.l == 0 {
                return self.w;
            }
            if self.w == 0 {
                return self.l;
            }
            self.l * self.w
        }
    }
    
    fn add(&mut self, x : usize, y : usize, val : i128) -> &mut Self {
        if self.l == 0 {
            if self.w > y {
                self.v[y] = val;
            }
            return self;
        }
        if self.w == 0 {
            if self.l > x {
                self.v[x] = val;
            }
            return self;
        }
        if self.inrange(x, y) {
            self.v[x * self.l + y] = val;
        }
        self
    }
    
    fn inrange(&self, x : usize, y : usize) -> bool {
        self.l > x && self.w > y
    }
    
    fn deref(&self, x : usize, y : usize) -> Option<i128> {
        if self.l == 0 {
            if self.w > y {
                return Some(self.v[y]);
            }
        }
        if self.w == 0 {
            if self.l > x {
                return Some(self.v[x]);
            }
        }
        if self.inrange(x, y) {
            return Some(self.v[x * self.l + y]);
        }
        None
    }
    
    fn print(&self) {
        let empty_value = -1;
        if self.empty() { return(); }
        if self.l == 0 {
            for j in 0..self.w {
                print!("{} ", if self.deref(0, j).is_some() { self.deref(0, j).unwrap() } else { empty_value });
            }
            println!();
            return;
        }
        if self.w == 0 {
            for i in 0..self.l {
                println!("{}", if self.deref(i, 0).is_some() { self.deref(i, 0).unwrap() } else { empty_value });
            }
            return;
        }
        for i in 0..self.l {
            for j in 0..self.w {
                print!("{} ", if self.deref(i, j).is_some() { self.deref(i, j).unwrap() } else { empty_value });
            }
            println!();
        }
    }
}