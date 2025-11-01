

use public_macro::public;

#[public(exclude(fourth, third))]
struct Example {
    first: String,
    pub second: u32,
    third: bool,
    fourth: String,
}

#[public]
struct AlsoWorksExample {
    first: String,
    pub second: u32,
}

impl Example {
    pub fn new() -> Self {
        Example {
            first: "first".to_string(),
            second: 5,
            third: false,
            fourth: "fourth".to_string(),
        }
    }
}


#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn it_works() {
        let _ = AlsoWorksExample {
            first: "".to_string(),
            second: 0,
        };
        let e = Example::new();
        println!("{}", e.first);
        println!("{}", e.second);

    }

}