use proc_macro::TokenStream;
use syn::{parse::{Parse, ParseStream}, parse_macro_input, spanned::Spanned, Ident, LitInt, Token};
use quote::quote;

mod iac;
mod iac_alt;
mod tokio_iac;
mod iac_with_kv;

#[proc_macro]
pub fn iac(item: TokenStream) -> TokenStream {
    iac::iac(item)
}

#[proc_macro]
pub fn iac_alt(item: TokenStream) -> TokenStream {
    iac_alt::iac(item)
}


#[proc_macro]
pub fn tokio_iac(item: TokenStream) -> TokenStream {
    tokio_iac::iac(item)
}

#[proc_macro]
pub fn iac_kv(item: TokenStream) -> TokenStream {
    iac_with_kv::iac(item)
}