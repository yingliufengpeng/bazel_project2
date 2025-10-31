
use my_macro::{log_fn, public, get};
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

#[derive(Debug)]
#[public]
struct Student3 {
    i: i32,
    j: i32,
    k_age: i32
}


#[get(["/user/add", "/v2/user/add"])]
fn add_user() {
    println!("Adding user...");
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

        let s = Student3{i: 3, j: 4, k_age: 5};
        println!("s is {:?}", s);

        add_user();
    }
}