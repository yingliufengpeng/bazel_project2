#![feature(prelude_import)]
#[prelude_import]
use std::prelude::rust_2021::*;
#[macro_use]
extern crate std;
mod iac_usage {
    use iac_macro::iac;
    fn iac_usage() {}
}
