use rand::Rng;
use serde::{Serialize, Deserialize};

#[derive(Serialize, Deserialize, Debug)]
pub struct Person {
    pub name: String,
    pub age: u32,
}

#[no_mangle]
pub extern "C" fn random_add(x: i32) -> i32 {
    let mut rng = rand::thread_rng();
    let r: i32 = rng.gen_range(0..10);
    x + r
}

#[no_mangle]
pub extern "C" fn make_person() {
    let p = Person {
        name: "Alice".to_string(),
        age: 30,
    };
    println!("Person = {:?}", p);
}
