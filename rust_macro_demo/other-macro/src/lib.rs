use proc_macro::TokenStream;

mod other_impl;


#[proc_macro]
pub fn analyze(item: TokenStream) -> TokenStream {
    other_impl::analyze(item)
}