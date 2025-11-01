use iac_macro::tokio_iac;


#[tokio_iac]
pub fn f1() {
    tokio_iac!(lambda);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {

    }
}
