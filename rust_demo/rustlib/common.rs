
use my_macro;
use my_macro::log_fn;

#[log_fn]
fn add(a: i32, b: i32) -> i32 {
    a + b
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {
        add(3, 4);
    }
}