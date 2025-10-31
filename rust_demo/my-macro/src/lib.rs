extern crate proc_macro;
use proc_macro::TokenStream;

use quote::quote;
use syn::{parse_macro_input, ItemFn};

mod hello;
mod log;
mod public;
mod router;

/// 一个简单属性宏，打印函数开始和结束
#[proc_macro_attribute]
pub fn log_fn(_attr: TokenStream, item: TokenStream) -> TokenStream {
    log::log_fn_impl(_attr, item)
}


#[proc_macro_derive(Hello)]
pub fn hello_world(_item: TokenStream) -> TokenStream {
    hello::hello_impl(_item)
}


#[proc_macro_derive(UpperCaseName)]
pub fn uppercase(item: TokenStream) -> TokenStream {
    hello::uppercase_impl(item)
}

#[proc_macro_attribute]
pub fn public(_attr: TokenStream, item: TokenStream) -> TokenStream {
    public::public_impl(_attr, item)
}


#[proc_macro_attribute]
pub fn get(attr: TokenStream, item: TokenStream) -> TokenStream {
    router::get_impl(attr, item)
}