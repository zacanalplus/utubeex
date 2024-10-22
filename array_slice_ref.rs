

fn main() { 
    println!("မင်္ဂလာပါ");
    let x;
    x = 47;
    let natnums : [i32; 10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
    //let slc = ;
    get_slice(&natnums[3..6]);
    println!("{}", x);
}

fn get_slice(slice : &[i32]){
    for i in 0..slice.len(){
        println!("{}", slice[i]);
    }
}