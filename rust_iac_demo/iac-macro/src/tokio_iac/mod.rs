mod input;
mod s3;
mod lambda;
mod errors;

use proc_macro::TokenStream;
use quote::{quote};
use syn::parse_macro_input;

use input::IacInput;
use errors::IacError;
use lambda::LambdaClient;
use s3::{S3Client};
use aws_sdk_s3::error::SdkError;

async fn create_infra(iac_input: IacInput) -> Result<(), IacError> {
    let s3_client = S3Client::new().await;
    let lambda_client = LambdaClient::new().await;
    let mut output = None;

    if let Some(lambda) = &iac_input.lambda {
        eprintln!("creating lambda...");
        output = match lambda_client.create_lambda(&lambda).await {
            Ok(resp) => {
                println!("Lambda created: {:?}", resp);
                Some(resp)
            }
            Err(e) => {
                if let SdkError::ServiceError(ref service_err) = &e {
                    eprintln!("AWS Lambda create failed: {:?}", service_err.err());
                } else {
                    eprintln!("Other error: {:?}", e);
                }

                None
            }
        };
        // output = Some(lambda_client.create_lambda(lambda).await?);
    }

    if let Some(bucket) = &iac_input.bucket {
        eprintln!("creating bucket...");
        s3_client.create_bucket(bucket).await?;

        if bucket.has_event {
            eprintln!("linking bucket and lambda by an event...");
            let lambda_arn_output = output
                .expect("when we have an event, we should have a lambda");
            let lambda = iac_input.lambda
                .expect("when we have an event, we should have a lambda");

            let lambda_arn = lambda_arn_output.function_arn()
                .expect("creating a lambda should return its ARN");
            lambda_client.add_bucket_permission(&lambda, &bucket.name).await?;
            s3_client.link_bucket_with_lambda(bucket, lambda_arn).await?;
        }
    }
    Ok(())
}


pub fn iac(item: TokenStream) -> TokenStream {
    let ii: IacInput = parse_macro_input!(item);
    eprintln!("{:?} {:?}", ii, file!());

    if ii.has_resources() {
        let rt = tokio::runtime::Runtime::new().unwrap();

        match rt.block_on(create_infra(ii)) {
            Ok(_) => quote!().into(), // this could also produce something useful. to interact with the bucket for example
            Err(e) => e.into_compile_error()
        }
    } else {
        quote!().into()
    }
}