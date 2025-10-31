
use my_macro::{log_fn, public, get, private, local, compose, gen_hello_world, multi_args};
use my_macro::{Hello, UpperCaseName, Builder};

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


private!{
 #[derive(Debug)]
 struct User {
     name: String,
     age: i32,
 }
}


fn add_one(n: i32) -> i32 {
    n + 1
}

fn stringify(n: i32) -> String {
    n.to_string()
}

struct Greeter;

gen_hello_world!(Greeter);

#[derive(Builder)]
struct Gleipnir {
    roots_of: String,
    breath_of_a_fish: u8
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

        let user = User {name: "wang".into(), age:44};
        println!("user is {:?}", user);
        println!("user'name is {:?}", user.get_name());

        local!();
        println!("local greeting is {:?}", greeting);

        fn compose_two<FIRST, SECOND, THIRD, F, G>(first: F, second: G)
                                                   -> impl Fn(FIRST) -> THIRD
        where
            F: Fn(FIRST) -> SECOND,
            G: Fn(SECOND) -> THIRD,
        {
            move |x| second(first(x))
        }

        let f = compose_two(compose_two(compose_two(add_one, add_one), add_one), stringify);
        let r = f(4);
        println!("fffff (4) is {:?}", r);
    }

    #[test]
    fn test_compose() {

        let composed = compose!(
            add_one >> add_one >> stringify
        );
        println!("{:?}", composed(5));

        println!("{:?}", (Greeter).hello_world());


        multi_args!("hello, world", M, N, Q);
        hello();

        let gleipnir = Gleipnir::builder()
            .roots_of("mountains".to_string())
            .breath_of_a_fish(1)
            .build();

    }
}