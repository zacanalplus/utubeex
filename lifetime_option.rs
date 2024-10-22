use std::process;

#[derive(Debug)]
struct CamelName{
    
}

fn longer<'a>(x : &'a str, y : &'a str) -> &'a str {
    if x.len() > y.len(){
        x
    }
    else{
        y
    }
}

fn divide(num : f64, den : f64) -> Option<f64> {
    if den == 0.0 {
        return None;
    }
    Some(num / den)
}

fn add_one(n : &mut i32 ) {
    *n += 1;
}

fn mul_two(n : &mut i32) {
    *n *= 2;
}

fn main() {
    let cObj = CamelName {};
    let greet1 = "မင်္ဂလာပါ";
    let greet2 = "Hello, ";
    println!("{}", greet1);
    let mut x : i32 = 47;
    println!("{}", x);
    println!("{} {:?}", longer(&greet1, &greet2), cObj);
    let numerator = 1.0;
    let denominator = 0.0;
    let rtval = divide(numerator, denominator);
    println!("{:?}", rtval);
//  if rtval == None {
//      eprintln!("Zero division executed. Process going to abort..");
//      process::exit(-1);
//  }
    add_one(&mut x);
    mul_two(&mut x);
    println!("{}", x);
}