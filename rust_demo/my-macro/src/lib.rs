extern crate proc_macro;
use proc_macro::TokenStream;
use syn::Ident as SynIdent;
use proc_macro_error::{emit_error, proc_macro_error};

use quote::quote;
use syn::{parse_macro_input, ItemFn};

mod hello;
mod log;
mod public;
mod router;
mod private;
mod compose;
mod multi_args;
mod builder;

#[path = "panic-to-result.rs"]
mod panic_to_result;
mod my_macro_rules;

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

#[proc_macro]
pub fn private(item: TokenStream) -> TokenStream {
    private::private_impl(item)
}

#[proc_macro]
pub fn local(_: TokenStream) -> TokenStream {
    quote!(
        let greeting = "Heya! It's me, Imoen!";
     ).into()
}


#[proc_macro]
pub fn compose(item: TokenStream) -> TokenStream {
    compose::compose_impl(item)
}

#[proc_macro]
pub fn gen_hello_world(item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as SynIdent);
    quote!(
        impl #input {
            pub fn hello_world(&self) -> String {
                "Hello, world!".to_string()
            }
        }
    )
        .into()
}

#[proc_macro]
pub fn multi_args(input: TokenStream) -> TokenStream {

    multi_args::multi_args_impl(input)
}

#[proc_macro_derive(Builder)]
pub fn builder(item: TokenStream) -> TokenStream {
    builder::create_builder(item.into()).into()
}

#[proc_macro_error]
#[proc_macro_attribute]
pub fn panic_to_result(_a: TokenStream, item: TokenStream) -> TokenStream {
    panic_to_result::panic_to_result_impl(_a, item)
}


