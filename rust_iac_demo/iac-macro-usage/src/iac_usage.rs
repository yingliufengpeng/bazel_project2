use iac_macro::iac;

fn iac_usage() {
    iac! {
        bucket uniquename
    }
    iac! {
        lambda a_name
    }
    iac! {
        lambda my_name mem 1024 time 15
    }
    iac! {
        lambda name bucket uniquename
    }
    iac! {
        bucket uniquename => lambda anothername
    }

    iac! {
        bucket b => lambda l mem 1024 time 15
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {

    }
}
