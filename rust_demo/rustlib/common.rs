
use my_macro::log_fn;
use my_macro::{Hello, UpperCaseName};

#[log_fn]
fn add(a: i32, b: i32) -> i32 {
    a + b
}

#[derive(Hello, UpperCaseName)]
struct Example;

#[derive(Hello)]
enum Pet {
    Cat
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {
        add(3, 4);
        let e = Example{};
        e.hello_world();
        e.uppercase();

        let p = Pet::Cat;
        p.hello_world();
    }
}