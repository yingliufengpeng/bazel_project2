use other_macro::analyze;
analyze!(
            /// outer comment
            /** comment block */
            struct Example {
                //! inner comment
                /*! inner comment block */
                val: String
            }
        );
#[cfg(test)]
mod tests {

    use other_macro::analyze;

    #[test]
    fn it_works() {

        analyze!(
            /// outer comment
            /** comment block */
            struct Example {
                //! inner comment
                /*! inner comment block */
                val: String
            }
        );

    }

}