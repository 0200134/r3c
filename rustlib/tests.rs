// r3c tests (standalone). Build with:
//   rustc +1.65.0 --edition=2021 rustlib/tests.rs --test -o build/tests.exe

#![allow(unused_imports)]

mod r3std;
mod vendor; // optional, may be empty

use r3std::*;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn string_trim() {
        assert_eq!(string::trim("  hi  "), "hi");
    }

    #[test]
    fn functional_helpers() {
        let v = vec![1,2,3,4];
        let even = fun::filter(v.clone(), |x| x % 2 == 0);
        assert_eq!(even, vec![2,4]);
        let doubled = fun::map(v.clone(), |x| x*2);
        assert_eq!(doubled, vec![2,4,6,8]);
        let sum = fun::fold(v, 0, |acc, x| acc + x);
        assert_eq!(sum, 10);
    }

    #[test]
    fn borrow_helpers() {
        let s = String::from("abc");
        let r: &str = borrow::as_str(&s);
        assert_eq!(r, "abc");
        let bytes = borrow::as_bytes(&s);
        assert_eq!(bytes, b"abc");
        let vv = vec![10,20,30,40];
        let sl = borrow::slice(&vv, 1, 3);
        assert_eq!(sl, &[20,30]);
    }

    #[test]
    fn fs_roundtrip() {
        let dir = "build/test_tmp";
        let file = "build/test_tmp/hello.txt";
        let _ = fs::mkdir_p(dir);
        fs::write(file, "hello").expect("write");
        assert!(fs::exists(file));
        let s = fs::read(file).expect("read");
        assert_eq!(s, "hello");
    }

    #[test]
    fn contracts_ok() {
        contract::require(1+1==2, "math");
        contract::ensure(true, "ok");
        contract::invariant(!false, "ok");
    }

    #[test]
    #[should_panic]
    fn contracts_fail() {
        contract::require(false, "must fail");
    }

    #[test]
    fn c_like_helpers() {
        assert_eq!(c::atoi("123"), 123);
        assert_eq!(c::atoll("-42"), -42);
        assert_eq!(c::itoa(7), "7");
        assert_eq!(c::strlen("abc"), 3);
    }

    #[test]
    fn arch_nop_smoke() {
        // Just ensure the call/link works; nothing to assert.
        arch::nop();
    }

    #[test]
    fn mem_helpers() {
        let mut a = [0u8; 8];
        r3std::mem::memset(&mut a, 0xAA);
        assert!(a.iter().all(|&b| b==0xAA));
        let mut b = [0u8; 8];
        r3std::mem::memcpy(&mut b, &a).unwrap();
        assert_eq!(a, b);
        r3std::mem::write_le_u32(&mut b, 0, 0x11223344).unwrap();
        let v = r3std::mem::read_le_u32(&b, 0).unwrap();
        assert_eq!(v, 0x11223344);
        let mut bb = r3std::mem::ByteBuf::with_capacity(4);
        bb.resize_zero(4);
        bb.set(2, 7).unwrap();
        assert_eq!(bb.get(2), Some(7));
    }

    #[test]
    fn mem_more() {
        let mut b = [0u8; 16];
        r3std::mem::write_be_u16(&mut b, 0, 0xABCD).unwrap();
        assert_eq!(r3std::mem::read_be_u16(&b, 0).unwrap(), 0xABCD);
        r3std::mem::write_le_u64(&mut b, 8, 0x1122334455667788).unwrap();
        assert_eq!(r3std::mem::read_le_u64(&b, 8).unwrap(), 0x1122334455667788);
        assert_eq!(r3std::mem::memchr(&b, 0xCD), Some(1));
        assert_eq!(r3std::mem::memcmp(&b, &b), 0);
        r3std::mem::zeroize(&mut b);
        assert!(b.iter().all(|&x| x==0));
    }

    #[test]
    fn codec_hex_b64() {
        let data = b"hello";
        let h = r3std::codec::hex_encode(data);
        assert_eq!(h, "68656c6c6f");
        let back = r3std::codec::hex_decode(&h).unwrap();
        assert_eq!(&back, data);
        let b64 = r3std::codec::base64_encode(data);
        assert_eq!(b64, "aGVsbG8=");
        let back2 = r3std::codec::base64_decode(&b64).unwrap();
        assert_eq!(&back2, data);
    }

    #[test]
    fn process_capture() {
        let cap = r3std::process::run_capture("echo test-capture");
        assert_eq!(cap.code, 0);
        assert!(cap.stdout.to_lowercase().contains("test-capture"));
    }

    #[test]
    fn stdio_helpers_smoke() {
        // Ensure functions are callable and return Ok
        r3std::io::print("hello").unwrap();
        r3std::io::println("world").unwrap();
        r3std::io::eprint("err").unwrap();
        r3std::io::eprintln("line").unwrap();
        // read_line/read_all cannot be reliably tested non-interactively; just type-check via calls would block.
    }

    #[test]
    fn ops_overloading_and_traits() {
        use r3std::ops::{Vec2, Monoid};
        let a = Vec2 { x: 1.0, y: 2.0 };
        let b = Vec2 { x: -3.0, y: 4.5 };
        let c = a + b;
        assert_eq!(format!("{}", c), "(-2, 6.5)");
        let d = c - a;
        assert_eq!(format!("{}", d), "(-3, 4.5)");
        let v = Vec::<u8>::empty().combine(vec![1,2]).combine(vec![3]);
        assert_eq!(v, vec![1,2,3]);
    }

    #[test]
    fn stopwatch_basic() {
        let mut sw = r3std::time::Stopwatch::start_new();
        r3std::time::sleep_ms(5);
        let e = sw.elapsed_ms();
        assert!(e >= 1);
        sw.reset();
        let e2 = sw.elapsed_ms();
        assert!(e2 < e);
    }

    #[test]
    fn contracts_eq() {
        r3std::contract_extras::require_eq(1+1, 2, "math");
        r3std::contract_extras::ensure_eq("a", "a", "str eq");
    }
}
