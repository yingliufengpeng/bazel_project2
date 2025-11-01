use proc_macro::TokenStream;

use quote::quote;
use syn::{DataStruct, DeriveInput, FieldsNamed, Ident, LitStr, MetaList, parse_macro_input, Token};
use syn::Data::Struct;
use syn::Fields::Named;
use syn::parse::Parse;
use syn::parse::ParseStream;
use syn::meta::ParseNestedMeta;
use syn::token::Group;
use syn::PathArguments::Parenthesized;
use syn::punctuated::Punctuated;
use syn::PathSegment;
use syn::parse::Parser;

mod public_impl;
mod fields;


#[proc_macro_attribute]
pub fn public(attr: TokenStream, item: TokenStream) -> TokenStream {
    public_impl::public(attr, item)
}