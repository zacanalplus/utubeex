const DEF_PIX_LEN : usize = 80;
const DEF_PIX_VAL : u32 = 0;

use rand::Rng;

fn main() {
    let mut rng = rand::thread_rng();
    let mut bp : Bitpic = Bitpic::new(DEF_PIX_LEN, DEF_PIX_LEN);
    bp.alloc();
    let mut sbag : Setbag = Setbag::new();
    for i in 0..DEF_PIX_LEN {
        for j in 0..DEF_PIX_LEN {
            let pval : u32 = rng.gen::<u32>() % 10;
            bp.setpixel(i, j, pval);
            sbag.add(&PixCounter::new(pval));
        }
    }
    sbag.print_maxmin();
    sbag.print_all();
    bp.print();
}

struct Bitpic{
    base : Vec::<u32>,
    xlen : usize,
    ylen : usize,
}

struct PixCounter{
    p : u32,
    cnt : usize,
}

struct Setbag{
    pset : Vec::<PixCounter>,
    minidx : usize,
    maxidx : usize,
}

impl Bitpic {
    //  initialize new bitpic
    fn new(x : usize, y : usize) -> Self {
        Self {
            base : Vec::<u32>::with_capacity(x * y),
            xlen : x,
            ylen : y,
        }
    }
    fn setpixel(&mut self, x : usize, y : usize, pval : u32) -> &mut Bitpic {
        if x < self.xlen && y < self.ylen {
            self.base[x * self.xlen + y] = pval;
        }
        self
    }
    
    fn alloc(&mut self) -> &mut Bitpic {
        for _i in 0..self.xlen * self.ylen {
            self.base.push(DEF_PIX_VAL);
        }
        self
    }
    
    fn getpixel(&self, x : usize, y : usize) -> u32 {
        if x < self.xlen && y < self.ylen {
            return self.base[x * self.xlen + y]; // base[x][y]
        }
        0
    }
    fn print(&self){
        for i in 0..self.xlen {
            for j in 0..self.ylen {
                print!("{} ", self.getpixel(i, j));
            }
            println!();
        }
    }
}

impl PixCounter {
    // Initialize new Pixel Counter object
    fn new (pval : u32) -> Self {
        Self{
            p : pval,
            cnt : 1,
        }
    }
    
    fn value(&self) -> u32 {
        self.p
    }
    
    fn count(&self) -> usize {
        self.cnt
    }
    
    fn print(&self) {
        println!("Pixel value {} has count {}. ", self.p, self.cnt);
    }
    
    fn add_count(&mut self) -> &mut PixCounter {
        self.cnt += 1;
        self
    }
}

impl Setbag{
    fn new() -> Self {
        Self{
            pset : Vec::<PixCounter>::new(),
            minidx : 0,
            maxidx : 0,
        }
    }
    fn add(&mut self, pc : &PixCounter) -> &mut Setbag {
        if ! self.add_count(pc) {
            self.pset.push(PixCounter::new(pc.value()));
        }
        self
    }
    fn add_count(&mut self, pc : &PixCounter) -> bool {
        for i in 0..self.pset.len() {
            if self.pset[i].value() == pc.value() {
                self.pset[i].add_count();
                if self.pset[self.maxidx].count() < self.pset[i].count() {
                    (*self).maxidx = i; 
                }
                return true;
            }
            if self.pset[self.minidx].count() > self.pset[i].count() {
                (*self).minidx = i;
            }
        }
        false
    }
    fn print_maxmin(&self) {
        println!("Pixel value {} has maximum count {}. ", self.pset[self.maxidx].value(), self.pset[self.maxidx].count());
        println!("Pixel value {} has minimum count {}. ", self.pset[self.minidx].value(), self.pset[self.minidx].count());
    }
    
    fn print_all(&self) {
        for i in 0..self.pset.len() {
            self.pset[i].print();
        }
    }
}
