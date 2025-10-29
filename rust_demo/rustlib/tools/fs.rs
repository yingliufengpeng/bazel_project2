use std::fs::File;
use std::io::{self, Result};

pub fn list_dir(f: &File) -> Result<u64> {
    let meta = f.metadata()?;
    let len = meta.len();
    println!("list_dir func: file size = {} bytes", len);
    Ok(len)
}
