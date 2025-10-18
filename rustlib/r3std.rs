// r3 standard library (embedded, minimal)
#![allow(dead_code)]
#![allow(unused_imports)]

pub mod process {
    pub struct Exit { pub code: i32 }
    impl Exit { pub fn success(&self) -> bool { self.code == 0 } }
    pub fn shell() -> (&'static str, &'static str) {
        if cfg!(windows) { ("cmd", "/C") } else { ("sh", "-c") }
    }
    pub fn run(cmd: &str) -> Exit {
        let (sh, flag) = shell();
        let code = std::process::Command::new(sh)
            .arg(flag).arg(cmd)
            .status()
            .map(|s| s.code().unwrap_or(-1))
            .unwrap_or(-1);
        Exit { code }
    }
    pub fn run_quiet(cmd: &str) -> i32 { run(cmd).code }

    pub struct Capture { pub code: i32, pub stdout: String, pub stderr: String }
    pub fn run_capture(cmd: &str) -> Capture {
        let (sh, flag) = shell();
        match std::process::Command::new(sh).arg(flag).arg(cmd).output() {
            Ok(out) => Capture {
                code: out.status.code().unwrap_or(-1),
                stdout: String::from_utf8_lossy(&out.stdout).into_owned(),
                stderr: String::from_utf8_lossy(&out.stderr).into_owned(),
            },
            Err(_) => Capture { code: -1, stdout: String::new(), stderr: String::new() }
        }
    }
    pub fn run_with_env(cmd: &str, env: &[(&str,&str)]) -> Exit {
        let (sh, flag) = shell();
        let mut c = std::process::Command::new(sh);
        c.arg(flag).arg(cmd);
        for (k,v) in env { c.env(k, v); }
        let code = c.status().map(|s| s.code().unwrap_or(-1)).unwrap_or(-1);
        Exit { code }
    }
    pub fn run_in_dir(dir: &str, cmd: &str) -> Exit {
        let (sh, flag) = shell();
        let code = std::process::Command::new(sh)
            .arg(flag).arg(cmd).current_dir(dir)
            .status().map(|s| s.code().unwrap_or(-1)).unwrap_or(-1);
        Exit { code }
    }
}

pub mod fs {
    pub fn read(p: &str) -> Result<String, String> {
        std::fs::read_to_string(p).map_err(|e| e.to_string())
    }
    pub fn write(p: &str, data: &str) -> Result<(), String> {
        std::fs::write(p, data).map_err(|e| e.to_string())
    }
    pub fn exists(p: &str) -> bool { std::path::Path::new(p).exists() }
    pub fn mkdir_p(p: &str) -> Result<(), String> {
        std::fs::create_dir_all(p).map_err(|e| e.to_string())
    }

    pub fn remove(p: &str) -> Result<(), String> { std::fs::remove_file(p).map_err(|e| e.to_string()) }
    pub fn remove_dir_all(p: &str) -> Result<(), String> { std::fs::remove_dir_all(p).map_err(|e| e.to_string()) }
    pub fn rename(src: &str, dst: &str) -> Result<(), String> { std::fs::rename(src, dst).map_err(|e| e.to_string()) }

    pub fn read_bytes(p: &str) -> Result<Vec<u8>, String> {
        std::fs::read(p).map_err(|e| e.to_string())
    }
    pub fn write_bytes(p: &str, data: &[u8]) -> Result<(), String> {
        std::fs::write(p, data).map_err(|e| e.to_string())
    }
    pub fn copy(src: &str, dst: &str) -> Result<u64, String> {
        std::fs::copy(src, dst).map_err(|e| e.to_string())
    }
    pub fn listdir(p: &str) -> Result<Vec<String>, String> {
        let mut out = Vec::new();
        for e in std::fs::read_dir(p).map_err(|e| e.to_string())? {
            let e = e.map_err(|e| e.to_string())?;
            out.push(e.path().to_string_lossy().into_owned());
        }
        Ok(out)
    }
}

pub mod path {
    pub fn join(a: &str, b: &str) -> String {
        let mut p = std::path::PathBuf::from(a);
        p.push(b); p.to_string_lossy().into_owned()
    }
    pub fn dirname(p: &str) -> String {
        std::path::Path::new(p).parent()
            .map(|x| x.to_string_lossy().into_owned()).unwrap_or_default()
    }
    pub fn basename(p: &str) -> String {
        std::path::Path::new(p).file_name()
            .map(|x| x.to_string_lossy().into_owned()).unwrap_or_default()
    }
    pub fn cwd() -> String {
        std::env::current_dir()
            .map(|p| p.to_string_lossy().into_owned()).unwrap_or_default()
    }
}

pub mod time {
    pub fn now_ms() -> u128 {
        use std::time::SystemTime;
        SystemTime::now().duration_since(SystemTime::UNIX_EPOCH)
            .map(|d| d.as_millis()).unwrap_or(0)
    }
    pub fn sleep_ms(ms: u64) { std::thread::sleep(std::time::Duration::from_millis(ms)); }

    pub struct Stopwatch { start: std::time::Instant }
    impl Stopwatch {
        pub fn start_new() -> Self { Self { start: std::time::Instant::now() } }
        pub fn elapsed_ms(&self) -> u128 { self.start.elapsed().as_millis() }
        pub fn reset(&mut self) { self.start = std::time::Instant::now(); }
    }
}

pub mod env {
    pub fn get(k: &str) -> Option<String> { std::env::var(k).ok() }
    pub fn set(k: &str, v: &str) -> bool { std::env::set_var(k, v); true }
}

pub mod args {
    pub fn args() -> Vec<String> { std::env::args().collect() }
}

pub mod log {
    pub fn info(m: &str) { println!("{}", m); }
    pub fn warn(m: &str) { eprintln!("[WARN] {}", m); }
    pub fn err(m: &str)  { eprintln!("[ERR] {}", m); }
}

// Standard I/O helpers suitable for r3 and plain Rust sources
pub mod io {
    use std::io::{self, Read, Write};

    // write to stdout without newline
    pub fn print(s: &str) -> Result<(), String> {
        let mut out = io::stdout();
        out.write_all(s.as_bytes()).map_err(|e| e.to_string())
    }
    // write to stdout with newline
    pub fn println(s: &str) -> Result<(), String> {
        let mut out = io::stdout();
        out.write_all(s.as_bytes()).map_err(|e| e.to_string())?;
        out.write_all(b"\n").map_err(|e| e.to_string())
    }
    // write to stderr (no newline)
    pub fn eprint(s: &str) -> Result<(), String> {
        let mut err = io::stderr();
        err.write_all(s.as_bytes()).map_err(|e| e.to_string())
    }
    // write to stderr with newline
    pub fn eprintln(s: &str) -> Result<(), String> {
        let mut err = io::stderr();
        err.write_all(s.as_bytes()).map_err(|e| e.to_string())?;
        err.write_all(b"\n").map_err(|e| e.to_string())
    }
    // read a single line (without trailing newline if present)
    pub fn read_line() -> Result<String, String> {
        let mut s = String::new();
        std::io::stdin().read_line(&mut s).map_err(|e| e.to_string())?;
        if s.ends_with('\n') { s.pop(); if s.ends_with('\r') { s.pop(); } }
        Ok(s)
    }
    // read entire stdin as UTF-8 string
    pub fn read_all() -> Result<String, String> {
        let mut s = String::new();
        std::io::stdin().read_to_string(&mut s).map_err(|e| e.to_string())?;
        Ok(s)
    }
    // read entire stdin as raw bytes
    pub fn read_all_bytes() -> Result<Vec<u8>, String> {
        let mut v = Vec::new();
        std::io::stdin().read_to_end(&mut v).map_err(|e| e.to_string())?;
        Ok(v)
    }
}

pub mod string {
    pub fn trim(s: &str) -> String { s.trim().to_string() }
    pub fn split(s: &str, pat: &str) -> Vec<String> {
        s.split(pat).map(|x| x.to_string()).collect()
    }
    pub fn contains(s: &str, pat: &str) -> bool { s.contains(pat) }
    pub fn replace(s: &str, from: &str, to: &str) -> String { s.replace(from, to) }
}

// Design-by-contract utilities (Ada-like contracts)
pub mod contract {
    #[inline(always)]
    pub fn require(cond: bool, msg: &str) {
        if !cond { panic!("[require] {}", msg); }
    }
    #[inline(always)]
    pub fn ensure(cond: bool, msg: &str) {
        if !cond { panic!("[ensure] {}", msg); }
    }
    #[inline(always)]
    pub fn invariant(cond: bool, msg: &str) {
        if !cond { panic!("[invariant] {}", msg); }
    }
    #[inline(always)]
    pub fn assume(cond: bool, _msg: &str) {
        // In release builds this could be hint-only; here we just assert as well for safety.
        if !cond { panic!("[assume] violated"); }
    }
}

// Minimal C-like helpers and direct assembly interop
pub mod c {
    pub fn strlen(s: &str) -> usize { s.as_bytes().len() }
    pub fn atoi(s: &str) -> i32 { s.trim().parse::<i32>().unwrap_or(0) }
    pub fn atoll(s: &str) -> i64 { s.trim().parse::<i64>().unwrap_or(0) }
    pub fn itoa(n: i32) -> String { n.to_string() }
    pub fn getenv(k: &str) -> Option<String> { std::env::var(k).ok() }
    pub fn system(cmd: &str) -> i32 { crate::r3std::process::run_quiet(cmd) }
}

pub mod arch {
    #[inline(always)]
    pub fn nop() {
        // SAFETY: single no-op instruction
        unsafe { core::arch::asm!("nop", options(nomem, nostack, preserves_flags)) }
    }

    #[cfg(target_arch = "x86_64")]
    pub fn rdtsc() -> u64 { unsafe { core::arch::x86_64::_rdtsc() } }
    #[cfg(target_arch = "x86")]
    pub fn rdtsc() -> u64 { unsafe { core::arch::x86::_rdtsc() } }

    #[cfg(target_arch = "x86_64")]
    pub fn cpuid(eax: u32, ecx: u32) -> (u32, u32, u32, u32) {
        unsafe {
            let r = core::arch::x86_64::__cpuid_count(eax, ecx);
            (r.eax, r.ebx, r.ecx, r.edx)
        }
    }
    #[cfg(target_arch = "x86")]
    pub fn cpuid(eax: u32, ecx: u32) -> (u32, u32, u32, u32) {
        unsafe {
            let r = core::arch::x86::__cpuid_count(eax, ecx);
            (r.eax, r.ebx, r.ecx, r.edx)
        }
    }

    #[cfg(any(target_arch = "x86", target_arch = "x86_64"))]
    pub fn pause() { std::hint::spin_loop() }

    #[cfg(any(target_arch = "aarch64"))]
    pub fn isb() { unsafe { core::arch::asm!("isb", options(nomem, nostack, preserves_flags)) } }

    #[cfg(any(target_arch = "aarch64"))]
    pub fn dsb() { unsafe { core::arch::asm!("dsb sy", options(nomem, nostack, preserves_flags)) } }
}

// Functional helpers (Rust-style, but handy for transpiled code)
pub mod fun {
    pub fn map<T, U, F>(v: Vec<T>, mut f: F) -> Vec<U>
    where F: FnMut(T) -> U {
        v.into_iter().map(|x| f(x)).collect()
    }
    pub fn filter<T, F>(v: Vec<T>, mut f: F) -> Vec<T>
    where F: FnMut(&T) -> bool {
        v.into_iter().filter(|x| f(x)).collect()
    }
    pub fn fold<T, U, F>(v: Vec<T>, init: U, mut f: F) -> U
    where F: FnMut(U, T) -> U {
        v.into_iter().fold(init, |acc, x| f(acc, x))
    }
}

// Borrowing helpers to encourage references over cloning
pub mod borrow {
    use std::borrow::Cow;
    pub fn as_str(s: &String) -> &str { s.as_str() }
    pub fn as_bytes(s: &String) -> &[u8] { s.as_bytes() }
    pub fn slice<T>(v: &Vec<T>, start: usize, end: usize) -> &[T] { &v[start..end] }
    pub fn to_cow<'a>(s: &'a str) -> Cow<'a, str> { Cow::Borrowed(s) }
}

// Operator overloading helpers and example types (Rust traits)
pub mod ops {
    use core::fmt;
    use core::ops::{Add, Sub};

    // Macro to forward Add/Sub for newtype wrappers
    #[macro_export]
    macro_rules! r3_newtype_add_sub {
        ($t:ty) => {
            impl Add for $t {
                type Output = Self;
                fn add(self, rhs: Self) -> Self::Output { Self(self.0 + rhs.0) }
            }
            impl Sub for $t {
                type Output = Self;
                fn sub(self, rhs: Self) -> Self::Output { Self(self.0 - rhs.0) }
            }
        };
    }

    // Example: 2D vector with Add/Sub and Display
    #[derive(Clone, Copy, PartialEq, Default)]
    pub struct Vec2 { pub x: f64, pub y: f64 }
    impl Add for Vec2 { type Output = Self; fn add(self, rhs: Self)->Self { Self { x: self.x+rhs.x, y: self.y+rhs.y } } }
    impl Sub for Vec2 { type Output = Self; fn sub(self, rhs: Self)->Self { Self { x: self.x-rhs.x, y: self.y-rhs.y } } }
    impl fmt::Display for Vec2 { fn fmt(&self, f: &mut fmt::Formatter<'_>)->fmt::Result { write!(f, "({}, {})", self.x, self.y) } }

    // Example: Monoid-like trait (functional style)
    pub trait Monoid { fn empty() -> Self; fn combine(self, other: Self) -> Self; }
    impl Monoid for Vec<u8> { fn empty()->Self { Vec::new() } fn combine(mut self, mut other: Self)->Self { self.append(&mut other); self } }
}

// Safe memory helpers: checked, slice-based operations and a small byte buffer
pub mod mem {
    use std::{ptr};

    pub fn memset(dst: &mut [u8], value: u8) {
        for b in dst.iter_mut() { *b = value; }
    }

    pub fn memcpy(dst: &mut [u8], src: &[u8]) -> Result<(), String> {
        if dst.len() != src.len() { return Err("length mismatch".into()); }
        dst.copy_from_slice(src);
        Ok(())
    }

    pub fn memmove(dst: &mut [u8], src: &[u8]) -> Result<(), String> {
        if dst.len() != src.len() { return Err("length mismatch".into()); }
        // SAFETY: lengths are equal and we copy within non-overlapping aliasing rules via raw ptr copy
        unsafe { ptr::copy(src.as_ptr(), dst.as_mut_ptr(), dst.len()); }
        Ok(())
    }

    pub fn read_le_u32(buf: &[u8], off: usize) -> Result<u32, String> {
        if off + 4 > buf.len() { return Err("out of bounds".into()); }
        Ok(u32::from_le_bytes([buf[off], buf[off+1], buf[off+2], buf[off+3]]))
    }
    pub fn write_le_u32(buf: &mut [u8], off: usize, v: u32) -> Result<(), String> {
        if off + 4 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_le_bytes();
        buf[off..off+4].copy_from_slice(&b);
        Ok(())
    }

    pub fn read_le_u16(buf: &[u8], off: usize) -> Result<u16, String> {
        if off + 2 > buf.len() { return Err("out of bounds".into()); }
        Ok(u16::from_le_bytes([buf[off], buf[off+1]]))
    }
    pub fn write_le_u16(buf: &mut [u8], off: usize, v: u16) -> Result<(), String> {
        if off + 2 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_le_bytes(); buf[off..off+2].copy_from_slice(&b); Ok(())
    }
    pub fn read_le_u64(buf: &[u8], off: usize) -> Result<u64, String> {
        if off + 8 > buf.len() { return Err("out of bounds".into()); }
        Ok(u64::from_le_bytes(buf[off..off+8].try_into().unwrap()))
    }
    pub fn write_le_u64(buf: &mut [u8], off: usize, v: u64) -> Result<(), String> {
        if off + 8 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_le_bytes(); buf[off..off+8].copy_from_slice(&b); Ok(())
    }
    pub fn read_be_u16(buf: &[u8], off: usize) -> Result<u16, String> {
        if off + 2 > buf.len() { return Err("out of bounds".into()); }
        Ok(u16::from_be_bytes([buf[off], buf[off+1]]))
    }
    pub fn write_be_u16(buf: &mut [u8], off: usize, v: u16) -> Result<(), String> {
        if off + 2 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_be_bytes(); buf[off..off+2].copy_from_slice(&b); Ok(())
    }
    pub fn read_be_u32(buf: &[u8], off: usize) -> Result<u32, String> {
        if off + 4 > buf.len() { return Err("out of bounds".into()); }
        Ok(u32::from_be_bytes([buf[off], buf[off+1], buf[off+2], buf[off+3]]))
    }
    pub fn write_be_u32(buf: &mut [u8], off: usize, v: u32) -> Result<(), String> {
        if off + 4 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_be_bytes(); buf[off..off+4].copy_from_slice(&b); Ok(())
    }
    pub fn read_be_u64(buf: &[u8], off: usize) -> Result<u64, String> {
        if off + 8 > buf.len() { return Err("out of bounds".into()); }
        Ok(u64::from_be_bytes(buf[off..off+8].try_into().unwrap()))
    }
    pub fn write_be_u64(buf: &mut [u8], off: usize, v: u64) -> Result<(), String> {
        if off + 8 > buf.len() { return Err("out of bounds".into()); }
        let b = v.to_be_bytes(); buf[off..off+8].copy_from_slice(&b); Ok(())
    }

    pub fn memchr(buf: &[u8], needle: u8) -> Option<usize> {
        buf.iter().position(|&b| b==needle)
    }
    pub fn memcmp(a: &[u8], b: &[u8]) -> i32 {
        use std::cmp::Ordering;
        match a.cmp(b) { Ordering::Less => -1, Ordering::Equal => 0, Ordering::Greater => 1 }
    }
    pub fn zeroize(dst: &mut [u8]) { for b in dst.iter_mut() { *b = 0; } }

    #[derive(Clone, Default)]
    pub struct ByteBuf { data: Vec<u8> }
    impl ByteBuf {
        pub fn new() -> Self { Self { data: Vec::new() } }
        pub fn with_capacity(n: usize) -> Self { Self { data: Vec::with_capacity(n) } }
        pub fn from_vec(v: Vec<u8>) -> Self { Self { data: v } }
        pub fn len(&self) -> usize { self.data.len() }
        pub fn is_empty(&self) -> bool { self.data.is_empty() }
        pub fn as_slice(&self) -> &[u8] { &self.data }
        pub fn as_mut_slice(&mut self) -> &mut [u8] { &mut self.data }
        pub fn push(&mut self, b: u8) { self.data.push(b) }
        pub fn extend_from_slice(&mut self, s: &[u8]) { self.data.extend_from_slice(s) }
        pub fn resize_zero(&mut self, new_len: usize) { self.data.resize(new_len, 0) }
        pub fn get(&self, i: usize) -> Option<u8> { self.data.get(i).cloned() }
        pub fn set(&mut self, i: usize, v: u8) -> Result<(), String> {
            if i >= self.data.len() { return Err("out of bounds".into()); }
            self.data[i] = v; Ok(())
        }
    }
}

// Simple codecs (hex/base64)
pub mod codec {
    pub fn hex_encode(data: &[u8]) -> String {
        const HEX: &[u8;16] = b"0123456789abcdef";
        let mut out = String::with_capacity(data.len()*2);
        for &b in data {
            out.push(HEX[(b>>4) as usize] as char);
            out.push(HEX[(b&0xF) as usize] as char);
        }
        out
    }
    pub fn hex_decode(s: &str) -> Result<Vec<u8>, String> {
        let bytes = s.as_bytes();
        if bytes.len()%2!=0 { return Err("invalid hex length".into()); }
        let mut out = Vec::with_capacity(bytes.len()/2);
        fn val(c:u8)->Option<u8>{match c{b'0'..=b'9'=>Some(c-b'0'),b'a'..=b'f'=>Some(10+c-b'a'),b'A'..=b'F'=>Some(10+c-b'A'),_=>None}}
        let mut i=0; while i<bytes.len(){
            let hi=val(bytes[i]).ok_or("invalid hex")?; let lo=val(bytes[i+1]).ok_or("invalid hex")?;
            out.push((hi<<4)|lo); i+=2;
        }
        Ok(out)
    }

    const B64: &[u8;64] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    pub fn base64_encode(data: &[u8]) -> String {
        let mut out = String::with_capacity((data.len()+2)/3*4);
        let mut i=0;
        while i+3 <= data.len() {
            let n = ((data[i] as u32)<<16)|((data[i+1] as u32)<<8)|(data[i+2] as u32);
            out.push(B64[((n>>18)&0x3F) as usize] as char);
            out.push(B64[((n>>12)&0x3F) as usize] as char);
            out.push(B64[((n>>6)&0x3F) as usize] as char);
            out.push(B64[(n&0x3F) as usize] as char);
            i+=3;
        }
        let rem = data.len()-i;
        if rem==1 {
            let n = (data[i] as u32)<<16;
            out.push(B64[((n>>18)&0x3F) as usize] as char);
            out.push(B64[((n>>12)&0x3F) as usize] as char);
            out.push('='); out.push('=');
        } else if rem==2 {
            let n = ((data[i] as u32)<<16)|((data[i+1] as u32)<<8);
            out.push(B64[((n>>18)&0x3F) as usize] as char);
            out.push(B64[((n>>12)&0x3F) as usize] as char);
            out.push(B64[((n>>6)&0x3F) as usize] as char);
            out.push('=');
        }
        out
    }
    pub fn base64_decode(s: &str) -> Result<Vec<u8>, String> {
        fn val(c:u8)->Option<u8>{match c{b'A'..=b'Z'=>Some(c-b'A'),b'a'..=b'z'=>Some(26+c-b'a'),b'0'..=b'9'=>Some(52+c-b'0'),b'+'=>Some(62),b'/'=>Some(63),_=>None}}
        let bytes=s.as_bytes();
        if bytes.len()%4!=0 { return Err("invalid b64 length".into()); }
        let mut out=Vec::with_capacity(bytes.len()/4*3);
        let mut i=0; while i<bytes.len(){
            let a=bytes[i]; let b=bytes[i+1]; let c=bytes[i+2]; let d=bytes[i+3];
            let va=val(a).ok_or("invalid b64")?; let vb=val(b).ok_or("invalid b64")?;
            let vc= if c==b'=' {None} else { val(c) }; let vd= if d==b'=' {None} else { val(d) };
            let n1=((va as u32)<<18)|((vb as u32)<<12)|(((vc.unwrap_or(0)) as u32)<<6)|((vd.unwrap_or(0)) as u32);
            out.push(((n1>>16)&0xFF) as u8);
            if c!=b'=' { out.push(((n1>>8)&0xFF) as u8); }
            if d!=b'=' { out.push((n1&0xFF) as u8); }
            i+=4;
        }
        Ok(out)
    }
}

// Contract conveniences
pub mod contract_extras {
    pub fn require_eq<T: core::cmp::PartialEq + core::fmt::Debug>(a: T, b: T, msg: &str) {
        if a != b { panic!("[require_eq] {}: left={:?} right={:?}", msg, a, b); }
    }
    pub fn ensure_eq<T: core::cmp::PartialEq + core::fmt::Debug>(a: T, b: T, msg: &str) {
        if a != b { panic!("[ensure_eq] {}: left={:?} right={:?}", msg, a, b); }
    }
}
