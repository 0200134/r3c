fn add(a: i64, b: i64) -> i64 { a + b }
fn pow(a: i64, b: i64) -> i64 {
    let mut res = 1;
    let mut i = 0;
    while i < b {
        res = res * a;
        i = i + 1;
    }
    return res;
}
