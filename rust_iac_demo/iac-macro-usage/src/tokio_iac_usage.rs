use iac_macro::tokio_iac;


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {
        tokio_iac!(bucket nameshouldbeunique => lambda anothername mem 1024 time 15);

    }
}
