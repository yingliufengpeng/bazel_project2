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

#[derive(Default)]
pub struct AlternativeExcludedFields {
    fields: Vec<String>,
}

impl AlternativeExcludedFields {
    pub fn matches_ident(&self, name: &Option<Ident>) -> bool {
        name.as_ref().map(|n| n.to_string())
            .map(|n| self.fields.iter().any(|f| *f == n))
            .unwrap_or_else(|| false)
    }
}

impl AlternativeExcludedFields {
    pub fn parse(&mut self, meta: ParseNestedMeta) -> Result<(), syn::Error> {
        if meta.path.is_ident(EXCLUDE_ATTRIBUTE_NAME) {
            meta.parse_nested_meta(|meta| {
                let ident = &meta.path.segments.first().unwrap().ident;
                self.fields.push(ident.to_string());
                Ok(())
            })
        } else {
            Err(meta.error("unsupported property"))
        }
    }
}

const EXCLUDE_ATTRIBUTE_NAME: &str = "exclude";

pub struct ExcludedFields {
    fields: Vec<String>,
}

impl ExcludedFields {
    pub fn matches_ident(&self, name: &Option<Ident>) -> bool {
        name.as_ref().map(|n| n.to_string())
            .map(|n| self.fields.iter().any(|f| *f == n))
            .unwrap_or_else(|| false)
    }
}

impl Parse for ExcludedFields {
    fn parse(input: ParseStream) -> Result<Self, syn::Error> {
        match input.parse::<MetaList>() {
            Ok(meta_list) => {
                if meta_list.path
                    .segments
                    .iter()
                    .find(|s| s.ident == EXCLUDE_ATTRIBUTE_NAME)
                    .is_some()
                {
                    let parser = Punctuated::<Ident, Token![,]>::parse_terminated;
                    let identifiers = parser.parse(meta_list.clone().tokens.into()).unwrap();
                    let fields = identifiers.iter()
                        .map(|v| v.to_string())
                        .collect();
                    Ok(ExcludedFields { fields })
                } else {
                    Ok(ExcludedFields { fields: vec![] })
                }
            }
            Err(_) => Ok(ExcludedFields { fields: vec![] })
        }
    }
}


