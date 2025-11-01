use proc_macro::TokenStream;
use builder_code::create_builder;
use builder_code::builder_better;

#[proc_macro_derive(Builder, attributes(builder_defaults,rename,uppercase))]
pub fn builder(item: TokenStream) -> TokenStream {
    create_builder(item.into()).into()
}



#[proc_macro_derive(BuilderBetter)]
pub fn builder_better(item: TokenStream) -> TokenStream {
    builder_better::create_builder(item.into()).into()
}