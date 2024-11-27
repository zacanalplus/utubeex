use std::env;

const BITS_IN_BYTE : u64 = 8;

fn main() {
    println!("မင်္ဂလာပါ");
    let mut nbits = 5u64;
    let mut vbose = false;
    let vmodes = vec!["v", "V"];
    let args : Vec<String> = env::args().collect();

    for i in 1..args.len() {
        if !vbose {
            vbose = args[i].contains(vmodes[0]) || args[i].contains(vmodes[1]);
        }
        let nbitparam = args[i].parse::<u64>();
        if !nbitparam.is_err() {
            nbits = nbitparam.unwrap();
        }
    }
    let mut min : u64 = 0;
    for i in 1..(nbits + 1) {
        let res :Result<u64, String> = turnon_nbit(&mut min, i);
        if res.is_ok() {
            min = res.unwrap();
        }
    }
    let max : u64 = min << nbits;
    print!("Minimum start path is ");
    print_bits(min, nbits);
//  println!();
    print!("Maximum end path is   ");
    print_bits(max, nbits);
//  println!();
    
    let mut count : u64 = 0;
    if vbose {
        for i in min..(max + 1) {
            if print_bits(i, nbits) == 1{
                count += 1;
            }
        }
    }
    else{
        for i in min..(max + 1) {
            if count_bits(i) == nbits {
                count += 1;
            }
        }
    }
    println!("The total path for point {} square is {}", nbits + 1, count);
}

fn count_bits(mut n : u64) -> u64 {
    let mut count = 0;
    while n > 0 {
        n &= n -1;
        count += 1;
    }
    count
}

fn print_bits(n : u64, n_onbits : u64) -> u64 {
    let mut rop : u64 = 0x8000000000000000;
    if n_onbits < (BITS_IN_BYTE * std::mem::size_of_val(&n) as u64) && n_onbits > 0 {
        if count_bits(n) == n_onbits {
            rop = 1u64 << ((n_onbits * 2) - 1);
        }
        else{
            return 0; // not a valid path
        }
    }
    while rop > 0u64 {
        print!("{}", if (n & rop) > 0 {'1'} else {'0'});
        rop >>= 1;
    }
    println!();
    1 // found one path
}

/*
fn check_nthbit(n : u64, nth : u64) -> bool {
    if nth > (std::mem::size_of_val(&n) as u64 * BITS_IN_BYTE) {
        return false;
    }
    let rop : u64 = 1u64 << (nth - 1);
    (n & rop) != 0 
}
*/

fn turnon_nbit(n : &mut u64, nth : u64) -> Result<u64, String> {
    if nth > (std::mem::size_of_val(n) as u64 * BITS_IN_BYTE) {
        return Err(format!("Out of range bit"));
    }
    let rop : u64 = 1u64 << (nth - 1);
    *n |= rop;
    Ok(*n)
}