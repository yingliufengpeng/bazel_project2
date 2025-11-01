use iac_macro::iac_kv as iac;

fn iac_usage() {
    iac! {
        bucket uniquename
    }
    iac! {
        lambda (name = a_name)
    }
    iac! {
        lambda (name = my_name, mem = 1024, time = 15)
    }
    iac! {
        bucket uniquename => lambda (name = my_name, mem = 1024, time = 15)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {

    }
}
